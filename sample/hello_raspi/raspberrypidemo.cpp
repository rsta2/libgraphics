//
// raspberrypidemo.cpp
//
// libgraphics - Accelerated graphics support library for Circle
// Copyright (C) 2019  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "raspberrypidemo.h"
#include <circle/sched/scheduler.h>
#include <circle/timer.h>
#include <circle/logger.h>

#define FPS_COUNT	500

CRaspberryPiDemo::CRaspberryPiDemo (CBcmDisplay *pBcmDisplay,
				    int nPosX, int nPosY, int nWidth, int nHeight)
:	m_nPosX (nPosX),
	m_nPosY (nPosY),
	m_nWidth (nWidth),
	m_nHeight (nHeight),
	m_BcmDisplayElement (pBcmDisplay),
	m_RenderingContext (&m_BcmDisplayElement, EGL_OPENGL_ES_API),
	m_Viewer (&m_Model3D, &m_RenderingContext, 10.0f, 5000.0f, 200.0f)
{
}

CRaspberryPiDemo::~CRaspberryPiDemo (void)
{
}

void *CRaspberryPiDemo::Run (void)
{
	if (!m_BcmDisplayElement.CreateWindow (m_nPosX, m_nPosY, m_nWidth, m_nHeight))
	{
		return 0;
	}

	if (!m_RenderingContext.Initialize ())
	{
		return 0;
	}

	if (!m_Viewer.Initialize ())
	{
		return 0;
	}

	m_Viewer.RotateTo (45.0f, 30.0f, 0.0f);

	while (Continue ())
	{
		unsigned nStartTicks = CTimer::Get ()->GetClockTicks ();

		for (unsigned i = 0; i < FPS_COUNT; i++)
		{
			if (!Continue ())
			{
				break;
			}

			m_Viewer.RotateBy (0.5f, 0.5f, 0.0f);

			m_Viewer.UpdateView ();

			CScheduler::Get ()->Yield ();
		}

		if (Continue ())
		{
			unsigned nEndTicks = CTimer::Get ()->GetClockTicks ();
			double fFPS = 1000000.0f * FPS_COUNT / (nEndTicks - nStartTicks);

			CLogger::Get ()->Write ("rpidemo", LogDebug, "%.1f Fps", fFPS);
		}
	}

	m_Viewer.Close ();

	return 0;
}
