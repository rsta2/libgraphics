//
// objectmodel3d.h
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
#ifndef _objectmodel3d_h
#define _objectmodel3d_h

#include "colorbox3d.h"
#include <stdint.h>

// all measurements in millimeters
// origin is left/front/bottom corner
// z-value is growing from front towards back
struct TObjectInfo3D
{
	float Width, Height, Depth;
	float PosX, PosY, PosZ;
	uint32_t Color;
};

class CObjectModel3D
{
private:
	static const unsigned MaxObjects = 500;

public:
	CObjectModel3D (float fOriginOffsetX = 0.0f,
			float fOriginOffsetY = 0.0f,
			float fOriginOffsetZ = 0.0f);
	~CObjectModel3D (void);

	void AddObjects (const TObjectInfo3D *pObjectInfo, unsigned nObjectCount);

	void Draw (void);

private:
	float m_fOriginOffsetX;
	float m_fOriginOffsetY;
	float m_fOriginOffsetZ;

	CColorBox3D *m_pObjectArray[MaxObjects];
	unsigned m_nObjectCount;
};

#endif
