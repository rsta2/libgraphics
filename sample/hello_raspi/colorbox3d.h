//
// colorbox3d.h
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
#ifndef _colorbox3d_h
#define _colorbox3d_h

#include <GLES/gl.h>
#include <stdint.h>

class CColorBox3D
{
public:		// RGBA colors
	static const uint32_t BlackColor      = 0xFF000000;
	static const uint32_t RedColor        = 0xFF0000DF;
	static const uint32_t GreenColor      = 0xFF00DF00;
	static const uint32_t DarkGreenColor  = 0xFF006400;
	static const uint32_t SilverColor     = 0xFFC0C0C0;
	static const uint32_t GoldColor       = 0xFF00BBDE;

private:
	static const unsigned BoxFaces = 6;
	static const unsigned FacePoints = 4;
	static const unsigned PointCoords = 3;
	static const unsigned PointsTotal = BoxFaces*FacePoints;
	static const unsigned VerticesTotal = PointsTotal*PointCoords;

public:
	CColorBox3D (GLfloat fWidth, GLfloat fHeight, GLfloat fDepth,	// size of the box
		     GLfloat fPosX, GLfloat fPosY, GLfloat fPosZ,	// position in the model
		     uint32_t nColor);
	~CColorBox3D (void);

	void Draw (void);

private:
	uint32_t ModifyColor (uint32_t Color);

private:
	GLfloat m_fPosX;
	GLfloat m_fPosY;
	GLfloat m_fPosZ;

	GLfloat *m_pVertexArray;
	uint32_t *m_pColorArray;

	static const GLfloat s_VertexTemplate[VerticesTotal];
};

#endif
