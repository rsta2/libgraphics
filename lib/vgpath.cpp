//
// vgpath.cpp
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
#include <graphics/vgpath.h>
#include <assert.h>

CVgPath::CVgPath (void)
{
	m_Path = vgCreatePath (VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
			       1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
	assert (m_Path != VG_INVALID_HANDLE);
}

CVgPath::~CVgPath (void)
{
	assert (m_Path != VG_INVALID_HANDLE);
	vgDestroyPath (m_Path);
}

void CVgPath::AppendLine (VGfloat X0, VGfloat Y0, VGfloat X1, VGfloat Y1)
{
	assert (m_Path != VG_INVALID_HANDLE);
#ifndef NDEBUG
	VGUErrorCode ErrorCode =
#endif
		vguLine (m_Path, X0, Y0, X1, Y1);
	assert (ErrorCode == VGU_NO_ERROR);
}

void CVgPath::AppendRect (VGfloat X, VGfloat Y, VGfloat Width, VGfloat Height)
{
	assert (m_Path != VG_INVALID_HANDLE);
#ifndef NDEBUG
	VGUErrorCode ErrorCode =
#endif
		vguRect (m_Path, X, Y, Width, Height);
	assert (ErrorCode == VGU_NO_ERROR);
}

void CVgPath::AppendArc (VGfloat X, VGfloat Y, VGfloat Width, VGfloat Height,
			 VGfloat StartAngle, VGfloat AngleExt, VGUArcType Type)
{
	assert (m_Path != VG_INVALID_HANDLE);
#ifndef NDEBUG
	VGUErrorCode ErrorCode =
#endif
		vguArc (m_Path, X, Y, Width, Height, StartAngle, AngleExt, Type);
	assert (ErrorCode == VGU_NO_ERROR);
}

void CVgPath::Draw (VGbitfield PaintMode)
{
	assert (m_Path != VG_INVALID_HANDLE);
	vgDrawPath (m_Path, PaintMode);

	assert (vgGetError () == VG_NO_ERROR);
}
