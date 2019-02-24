//
// vgsimpledrawing.h
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
#ifndef _graphics_vgsimpledrawing_h
#define _graphics_vgsimpledrawing_h

#include <graphics/vgdrawingcontext.h>
#include <graphics/bcmdisplay.h>
#include <graphics/bcmdisplayelement.h>
#include <circle/types.h>

class CVgSimpleDrawing : public CVgDrawingContext
{
public:
	CVgSimpleDrawing (EGLint nSwapBehavior = EGL_BUFFER_DESTROYED,
			  unsigned char uchAlpha = 255,
			  unsigned nDeviceID = DISPMANX_ID_MAIN_LCD);
	~CVgSimpleDrawing (void);

	boolean Initialize (void);

private:
	CBcmDisplay m_BcmDisplay;
	CBcmDisplayElement m_BcmDisplayElement;
};

#endif
