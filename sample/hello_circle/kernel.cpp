//
// kernel.h
//
// libgraphics - Accelerated graphics support library for Circle
// Copyright (C) 2014-2019  R. Stange <rsta2@o2online.de>
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
#include "kernel.h"
#include <circle/util.h>
#include <graphics/vgpath.h>
#include <graphics/vgpaint.h>
#include <graphics/vgfont.h>
#include <fonts/vg/DejaVuSans.h>

#define ALPHA	180		// set to 255 to suppress logger output

static const char FromKernel[] = "kernel";

CKernel::CKernel (void)
:	m_Screen (m_Options.GetWidth (), m_Options.GetHeight ()),
	m_Timer (&m_Interrupt),
	m_Logger (m_Options.GetLogLevel (), &m_Timer),
	m_VCHIQ (&m_Memory, &m_Interrupt),
	m_Drawing (EGL_BUFFER_DESTROYED, ALPHA)
{
	m_ActLED.Blink (5);	// show we are alive
}

CKernel::~CKernel (void)
{
}

boolean CKernel::Initialize (void)
{
	boolean bOK = TRUE;

	if (bOK)
	{
		bOK = m_Screen.Initialize ();
	}

	if (bOK)
	{
		bOK = m_Serial.Initialize (115200);
	}

	if (bOK)
	{
		CDevice *pTarget = m_DeviceNameService.GetDevice (m_Options.GetLogDevice (), FALSE);
		if (pTarget == 0)
		{
			pTarget = &m_Screen;
		}

		bOK = m_Logger.Initialize (pTarget);
	}

	if (bOK)
	{
		bOK = m_Interrupt.Initialize ();
	}

	if (bOK)
	{
		bOK = m_Timer.Initialize ();
	}

	if (bOK)
	{
		bOK = m_VCHIQ.Initialize ();
	}

	if (bOK)
	{
		bOK = m_Drawing.Initialize ();
	}

	return bOK;
}

TShutdownMode CKernel::Run (void)
{
	m_Logger.Write (FromKernel, LogNotice, "Compile time: " __DATE__ " " __TIME__);

	CVgFont Font (MAKE_FONT (DejaVuSans, 24.0f));

	while (1)
	{
		for (VGfloat fAngle = 357.0f; fAngle >= 0.0f; fAngle -= 3.0f)
		{
			// clear whole screen buffer
			m_Drawing.ClearAll ();

			CVgPaint Paint;

			// draw filled arc with color
			static const VGfloat DarkSlateBlueColor[] = {0.28f, 0.24f, 0.54f, 1.0f};
			Paint.SetColor (DarkSlateBlueColor);

			CVgPath Path;
			Path.AppendArc (m_Drawing.GetWidth () / 2.0f, m_Drawing.GetHeight () / 2.0f,
					m_Drawing.GetHeight () / 3.0f, m_Drawing.GetHeight () / 3.0f,
					fAngle, 270.0f, VGU_ARC_PIE);
			Path.Draw ();

			// write white centered text
			Paint.SetColor (m_Drawing.WhiteColor);
			Font.TextCenter (m_Drawing.GetWidth () / 2.0f,
					 m_Drawing.GetHeight () / 4.0f,
					 "Hello Circle!");

			// now write screen buffer to screen
			m_Drawing.SwapBuffers ();

			// let other tasks run
			m_Scheduler.Yield ();
		}
	}

	return ShutdownHalt;
}
