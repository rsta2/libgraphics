//
// vgsimpledrawing.cpp
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
#include <graphics/vgsimpledrawing.h>

CVgSimpleDrawing::CVgSimpleDrawing (EGLint nSwapBehavior, unsigned char uchAlpha, unsigned nDeviceID)
:	CVgDrawingContext (&m_BcmDisplayElement),
	m_BcmDisplay (nDeviceID),
	m_BcmDisplayElement (&m_BcmDisplay)
{
	m_BcmDisplayElement.SetAlpha (uchAlpha);

	SetSwapBehavior (nSwapBehavior);
}

CVgSimpleDrawing::~CVgSimpleDrawing (void)
{
}

boolean CVgSimpleDrawing::Initialize (void)
{
	if (!m_BcmDisplay.Initialize ())
	{
		return FALSE;
	}

	if (!m_BcmDisplayElement.CreateFullScreen ())
	{
		return FALSE;
	}

	return CVgDrawingContext::Initialize ();
}
