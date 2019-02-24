//
// bcmdisplay.h
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
#ifndef _graphics_bcmdisplay_h
#define _graphics_bcmdisplay_h

#include <interface/vmcs_host/vc_dispmanx.h>
#include <circle/types.h>

class CBcmDisplay	/// A native VC4 display
{
public:
	CBcmDisplay (unsigned nDeviceID = DISPMANX_ID_MAIN_LCD);
	~CBcmDisplay (void);

	boolean Initialize (void);

	DISPMANX_DISPLAY_HANDLE_T GetHandle (void) const;

	int GetWidth (void) const;
	int GetHeight (void) const;

private:
	unsigned m_nDeviceID;
	DISPMANX_DISPLAY_HANDLE_T m_Handle;
	DISPMANX_MODEINFO_T m_ModeInfo;
};

#endif
