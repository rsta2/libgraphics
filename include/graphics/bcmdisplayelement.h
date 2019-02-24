//
// bcmdisplayelement.h
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
#ifndef _graphics_bcmdisplayelement_h
#define _graphics_bcmdisplayelement_h

#include <graphics/bcmdisplay.h>
#include <interface/vmcs_host/vc_dispmanx.h>
#include <circle/types.h>

class CBcmDisplayElement	/// An element on a VC4 display
{
public:
	CBcmDisplayElement (CBcmDisplay *pDisplay);
	~CBcmDisplayElement (void);

	void SetLayer (unsigned nLayer);
	void SetAlpha (unsigned char uchAlpha);

	boolean CreateFullScreen (void);
	boolean CreateWindow (int nPosX, int nPosY, int nWidth, int nHeight);

	DISPMANX_ELEMENT_HANDLE_T GetHandle (void) const;

	int GetWidth (void) const;
	int GetHeight (void) const;

private:
	CBcmDisplay *m_pDisplay;

	unsigned m_nLayer;
	unsigned char m_uchAlpha;

	DISPMANX_ELEMENT_HANDLE_T m_Handle;
	int m_nWidth;
	int m_nHeight;
};

#endif
