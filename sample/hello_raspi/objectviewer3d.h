//
// objectviewer3d.h
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
#ifndef _objectviewer3d_h
#define _objectviewer3d_h

#include "objectmodel3d.h"
#include <graphics/eglrenderingcontext.h>
#include <circle/types.h>
#include <GLES/gl.h>

class CObjectViewer3D
{
public:
	CObjectViewer3D (CObjectModel3D *pModel, CEglRenderingContext *pRenderingContext,
			 GLfloat fProjectionNear, GLfloat fProjectionFar, GLfloat fDistance);
	~CObjectViewer3D (void);

	boolean Initialize (void);

	void Close (void);

	void RotateTo (GLfloat fAngleX, GLfloat fAngleY, GLfloat fAngleZ);
	void RotateBy (GLfloat fAngleX, GLfloat fAngleY, GLfloat fAngleZ);

	void UpdateView (void);

private:
	GLfloat NormalizeAngle (GLfloat fAngle);

private:
	CObjectModel3D *m_pModel;
	CEglRenderingContext *m_pRenderingContext;
	GLfloat m_fProjectionNear;
	GLfloat m_fProjectionFar;
	GLfloat m_fDistance;

	boolean m_bInitialized;

	GLfloat m_fAngleX;
	GLfloat m_fAngleY;
	GLfloat m_fAngleZ;
};

#endif
