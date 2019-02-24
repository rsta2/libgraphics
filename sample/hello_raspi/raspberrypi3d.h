//
// raspberrypi3d.h
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
#ifndef _raspberrypi3d_h
#define _raspberrypi3d_h

#include "objectmodel3d.h"

class CRaspberryPi3D : public CObjectModel3D
{
public:
	CRaspberryPi3D (void);

	void AddPins (unsigned nColumns, unsigned nRows,
		      float fPosX, float fPosY, float fPosZ);

private:
	static const TObjectInfo3D s_ObjectList[];
};

#endif
