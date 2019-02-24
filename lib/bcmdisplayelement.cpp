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
#include <graphics/bcmdisplayelement.h>
#include <assert.h>

CBcmDisplayElement::CBcmDisplayElement (CBcmDisplay *pDisplay)
:	m_pDisplay (pDisplay),
	m_nLayer (0),
	m_uchAlpha (255),
	m_Handle (DISPMANX_NO_HANDLE)
{
	assert (m_pDisplay != 0);
}

CBcmDisplayElement::~CBcmDisplayElement (void)
{
	if (m_Handle != DISPMANX_NO_HANDLE)
	{
		DISPMANX_UPDATE_HANDLE_T hUpdate = vc_dispmanx_update_start (0);
		if (   hUpdate != DISPMANX_NO_HANDLE
		    && vc_dispmanx_element_remove (hUpdate, m_Handle) == DISPMANX_SUCCESS)
		{
			vc_dispmanx_update_submit_sync (hUpdate);
		}

		m_Handle = DISPMANX_NO_HANDLE;
	}

	m_pDisplay = 0;
}

void CBcmDisplayElement::SetLayer (unsigned nLayer)
{
	assert (m_Handle == DISPMANX_NO_HANDLE);
	m_nLayer = nLayer;
}

void CBcmDisplayElement::SetAlpha (unsigned char uchAlpha)
{
	assert (m_Handle == DISPMANX_NO_HANDLE);
	m_uchAlpha = uchAlpha;
}

boolean CBcmDisplayElement::CreateFullScreen (void)
{
	return CreateWindow (0, 0, -1, -1);
}

boolean CBcmDisplayElement::CreateWindow (int nPosX, int nPosY, int nWidth, int nHeight)
{
	assert (m_Handle == DISPMANX_NO_HANDLE);

	assert (m_pDisplay != 0);
	m_nWidth = nWidth > 0 ? nWidth : m_pDisplay->GetWidth ();
	m_nHeight = nHeight > 0 ? nHeight : m_pDisplay->GetHeight ();

	DISPMANX_UPDATE_HANDLE_T hUpdate = vc_dispmanx_update_start (0);
	if (hUpdate == DISPMANX_NO_HANDLE)
	{
		return FALSE;
	}

	VC_RECT_T SrcRect;
	vc_dispmanx_rect_set (&SrcRect, nPosX << 16, nPosY << 16, m_nWidth << 16, m_nHeight << 16);

	VC_RECT_T DestRect;
	vc_dispmanx_rect_set (&DestRect, nPosX, nPosY, m_nWidth, m_nHeight);

	VC_DISPMANX_ALPHA_T Alpha = {DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS, m_uchAlpha, 0};

	m_Handle = vc_dispmanx_element_add (hUpdate, m_pDisplay->GetHandle (), m_nLayer,
					    &DestRect, 0, &SrcRect, DISPMANX_PROTECTION_NONE,
					    &Alpha, 0, DISPMANX_NO_ROTATE);
	if (m_Handle == DISPMANX_NO_HANDLE)
	{
		return FALSE;
	}

	if (vc_dispmanx_update_submit_sync (hUpdate) != DISPMANX_SUCCESS)
	{
		m_Handle = DISPMANX_NO_HANDLE;

		return FALSE;
	}

	return TRUE;
}

DISPMANX_ELEMENT_HANDLE_T CBcmDisplayElement::GetHandle (void) const
{
	assert (m_Handle != DISPMANX_NO_HANDLE);
	return m_Handle;
}

int CBcmDisplayElement::GetWidth (void) const
{
	assert (m_Handle != DISPMANX_NO_HANDLE);
	return m_nWidth;
}

int CBcmDisplayElement::GetHeight (void) const
{
	assert (m_Handle != DISPMANX_NO_HANDLE);
	return m_nHeight;
}
