//
// vgpath.h
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
#ifndef _graphics_vgpath_h
#define _graphics_vgpath_h

#include <VG/openvg.h>
#include <VG/vgu.h>

class CVgPath		/// OpenVG path
{
public:
	CVgPath (void);
	~CVgPath (void);

	VGPath GetHandle (void)		{ return m_Path; }

	void AppendLine (VGfloat X0, VGfloat Y0, VGfloat X1, VGfloat Y1);

	void AppendRect (VGfloat X, VGfloat Y, VGfloat Width, VGfloat Height);

	void AppendArc (VGfloat X, VGfloat Y, VGfloat Width, VGfloat Height,
			VGfloat StartAngle, VGfloat AngleExt, VGUArcType Type);

	void Draw (VGbitfield PaintMode = VG_FILL_PATH | VG_STROKE_PATH);

private:
	VGPath m_Path;
};

#endif
