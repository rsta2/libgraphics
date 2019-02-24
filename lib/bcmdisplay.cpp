//
// bcmdisplay.cpp
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
#include <graphics/bcmdisplay.h>
#include <bcm_host.h>
#include <assert.h>

CBcmDisplay::CBcmDisplay (unsigned nDeviceID)
:	m_nDeviceID (nDeviceID),
	m_Handle (DISPMANX_NO_HANDLE)
{
}

CBcmDisplay::~CBcmDisplay (void)
{
	if (m_Handle != DISPMANX_NO_HANDLE)
	{
		vc_dispmanx_display_close (m_Handle);

		m_Handle = DISPMANX_NO_HANDLE;
	}
}

boolean CBcmDisplay::Initialize (void)
{
	assert (m_Handle == DISPMANX_NO_HANDLE);

	bcm_host_init();

	m_Handle = vc_dispmanx_display_open (m_nDeviceID);
	if (m_Handle == DISPMANX_NO_HANDLE)
	{
		return FALSE;
	}

	if (vc_dispmanx_display_get_info (m_Handle, &m_ModeInfo) != DISPMANX_SUCCESS)
	{
		return FALSE;
	}

	return TRUE;
}

DISPMANX_DISPLAY_HANDLE_T CBcmDisplay::GetHandle (void) const
{
	assert (m_Handle != DISPMANX_NO_HANDLE);
	return m_Handle;
}

int CBcmDisplay::GetWidth (void) const
{
	assert (m_Handle != DISPMANX_NO_HANDLE);
	return m_ModeInfo.width;
}

int CBcmDisplay::GetHeight (void) const
{
	assert (m_Handle != DISPMANX_NO_HANDLE);
	return m_ModeInfo.height;
}
