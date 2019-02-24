//
// objectmodel3d.cpp
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
#include "objectmodel3d.h"
#include <assert.h>

CObjectModel3D::CObjectModel3D (float fOriginOffsetX, float fOriginOffsetY, float fOriginOffsetZ)
:	m_fOriginOffsetX (fOriginOffsetX),
	m_fOriginOffsetY (fOriginOffsetY),
	m_fOriginOffsetZ (fOriginOffsetZ),
	m_nObjectCount (0)
{
}

CObjectModel3D::~CObjectModel3D (void)
{
	for (unsigned i = 0; i < m_nObjectCount; i++)
	{
		delete m_pObjectArray[i];
	}
}

void CObjectModel3D::AddObjects (const TObjectInfo3D *pObjectInfo, unsigned nObjectCount)
{
	assert (pObjectInfo != 0);

	for (unsigned i = 0; i < nObjectCount; i++)
	{
		float fPosX = pObjectInfo[i].PosX + pObjectInfo[i].Width  / 2.0f + m_fOriginOffsetX;
		float fPosY = pObjectInfo[i].PosY + pObjectInfo[i].Height / 2.0f + m_fOriginOffsetY;
		float fPosZ = pObjectInfo[i].PosZ + pObjectInfo[i].Depth  / 2.0f + m_fOriginOffsetZ;
		fPosZ = -fPosZ;

		assert (m_nObjectCount < MaxObjects);
		m_pObjectArray[m_nObjectCount] = new CColorBox3D (pObjectInfo[i].Width,
								  pObjectInfo[i].Height,
								  pObjectInfo[i].Depth,
								  fPosX, fPosY, fPosZ,
								  pObjectInfo[i].Color);
		assert (m_pObjectArray[m_nObjectCount] != 0);

		m_nObjectCount++;
	}
}

void CObjectModel3D::Draw (void)
{
	for (unsigned i = 0; i < m_nObjectCount; i++)
	{
		assert (m_pObjectArray[i] != 0);
		m_pObjectArray[i]->Draw ();
	}
}
