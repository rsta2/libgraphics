//
// vgpaint.cpp
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
#include <graphics/vgpaint.h>
#include <assert.h>

CVgPaint::CVgPaint (void)
:	m_Paint (vgCreatePaint ())
{
	assert (m_Paint != VG_INVALID_HANDLE);

}

CVgPaint::~CVgPaint (void)
{
	assert (m_Paint != VG_INVALID_HANDLE);
	vgDestroyPaint (m_Paint);
}

void CVgPaint::SetColor (const VGfloat Color[4], VGbitfield PaintMode)
{
	assert (m_Paint != VG_INVALID_HANDLE);

	vgSetParameteri (m_Paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetParameterfv (m_Paint, VG_PAINT_COLOR, 4, Color);

	vgSetPaint (m_Paint, PaintMode);

	assert (vgGetError () == VG_NO_ERROR);
}
