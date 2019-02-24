//
// colorbox3d.cpp
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
#include "colorbox3d.h"
#include <assert.h>

const GLfloat CColorBox3D::s_VertexTemplate[BoxFaces*FacePoints*PointCoords] =
{
	-1.f, -1.f,  1.f,	// front
	1.f, -1.f,  1.f,
	-1.f,  1.f,  1.f,
	1.f,  1.f,  1.f,

	-1.f, -1.f, -1.f,	// back
	-1.f,  1.f, -1.f,
	1.f, -1.f, -1.f,
	1.f,  1.f, -1.f,

	-1.f, -1.f,  1.f,	// left
	-1.f,  1.f,  1.f,
	-1.f, -1.f, -1.f,
	-1.f,  1.f, -1.f,

	1.f, -1.f, -1.f,	// right
	1.f,  1.f, -1.f,
	1.f, -1.f,  1.f,
	1.f,  1.f,  1.f,

	-1.f,  1.f,  1.f,	// top
	1.f,  1.f,  1.f,
	-1.f,  1.f, -1.f,
	1.f,  1.f, -1.f,

	-1.f, -1.f,  1.f,	// bottom
	-1.f, -1.f, -1.f,
	1.f, -1.f,  1.f,
	1.f, -1.f, -1.f
};

CColorBox3D::CColorBox3D (GLfloat fWidth, GLfloat fHeight, GLfloat fDepth,
			  GLfloat fPosX, GLfloat fPosY, GLfloat fPosZ,
			  uint32_t nColor)
:	m_fPosX (fPosX),
	m_fPosY (fPosY),
	m_fPosZ (fPosZ),
	m_pVertexArray (0),
	m_pColorArray (0)
{
	m_pVertexArray = new GLfloat[VerticesTotal];
	assert (m_pVertexArray != 0);

	for (unsigned i = 0; i < VerticesTotal;)
	{
		m_pVertexArray[i] = s_VertexTemplate[i] * fWidth  / 2.0f; 	i++;
		m_pVertexArray[i] = s_VertexTemplate[i] * fHeight / 2.0f;	i++;
		m_pVertexArray[i] = s_VertexTemplate[i] * fDepth  / 2.0f; 	i++;
	}

	m_pColorArray = new uint32_t[BoxFaces*FacePoints];
	assert (m_pColorArray != 0);

	unsigned i = 0;
	for (; i < 2*FacePoints; i++)	m_pColorArray[i] = ModifyColor (nColor); // front / back
	for (; i < 4*FacePoints; i++)	m_pColorArray[i] = ModifyColor (nColor); // left / right
	for (; i < 6*FacePoints; i++)	m_pColorArray[i] = nColor;		 // top / bottom
}

CColorBox3D::~CColorBox3D (void)
{
	delete [] m_pColorArray;
	m_pColorArray = 0;

	delete [] m_pVertexArray;
	m_pVertexArray = 0;
}

void CColorBox3D::Draw (void)
{
	glPushMatrix ();

	glTranslatef (m_fPosX, m_fPosY, m_fPosZ);

	assert (m_pVertexArray != 0);
	glVertexPointer (PointCoords, GL_FLOAT, 0, m_pVertexArray);
	assert (m_pColorArray != 0);
	glColorPointer (4, GL_UNSIGNED_BYTE, 0, m_pColorArray);

	glDrawArrays (GL_TRIANGLE_STRIP, 0, PointsTotal);

	glPopMatrix ();
}

uint32_t CColorBox3D::ModifyColor (uint32_t Color)
{
	assert ((Color       & 0xFF) < 0xE0);
	assert ((Color << 8  & 0xFF) < 0xE0);
	assert ((Color << 16 & 0xFF) < 0xE0);

	return Color + 0x202020;
}
