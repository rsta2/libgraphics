//
// objectviewer3d.cpp
//
// This has been derived from the hello_triangle demo, which is:
//	Copyright (c) 2012, Broadcom Europe Ltd
//	All rights reserved.
//	Licensed under the 3-Clause BSD License
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
#include "objectviewer3d.h"
#include <math.h>
#include <assert.h>

#define PI	3.141592654f

CObjectViewer3D::CObjectViewer3D (CObjectModel3D *pModel, CEglRenderingContext *pRenderingContext,
				  GLfloat fProjectionNear, GLfloat fProjectionFar,
				  GLfloat fDistance)
:	m_pModel (pModel),
	m_pRenderingContext (pRenderingContext),
	m_fProjectionNear (fProjectionNear),
	m_fProjectionFar (fProjectionFar),
	m_fDistance (fDistance),
	m_bInitialized (FALSE),
	m_fAngleX (45.0f),
	m_fAngleY (30.0f),
	m_fAngleZ (0.0f)
{
}

CObjectViewer3D::~CObjectViewer3D (void)
{
	Close ();
}

boolean CObjectViewer3D::Initialize (void)
{
	assert (!m_bInitialized);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	assert (m_pRenderingContext != 0);
	glViewport (0, 0, (GLsizei) m_pRenderingContext->GetWidth (),
		    (GLsizei) m_pRenderingContext->GetHeight ());

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	float fHeight = m_fProjectionNear * tanf (45.0f / 2.0f / 180.0f * PI);
	float fWidth  = fHeight * (float) m_pRenderingContext->GetWidth () /
			(float) m_pRenderingContext->GetHeight ();

	glFrustumf (-fWidth, fWidth, -fHeight, fHeight, m_fProjectionNear, m_fProjectionFar);

	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_COLOR_ARRAY);

	m_bInitialized = TRUE;

	return TRUE;
}

void CObjectViewer3D::Close (void)
{
	if (m_bInitialized)
	{
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		assert (m_pRenderingContext != 0);
		m_pRenderingContext->SwapBuffers ();

		m_bInitialized = FALSE;
	}
}

void CObjectViewer3D::RotateTo (GLfloat fAngleX, GLfloat fAngleY, GLfloat fAngleZ)
{
	m_fAngleX = NormalizeAngle (fAngleX);
	m_fAngleY = NormalizeAngle (fAngleY);
	m_fAngleZ = NormalizeAngle (fAngleZ);
}

void CObjectViewer3D::RotateBy (GLfloat fAngleX, GLfloat fAngleY, GLfloat fAngleZ)
{
	m_fAngleX = NormalizeAngle (m_fAngleX + fAngleX);
	m_fAngleY = NormalizeAngle (m_fAngleY + fAngleY);
	m_fAngleZ = NormalizeAngle (m_fAngleZ + fAngleZ);
}

void CObjectViewer3D::UpdateView (void)
{
	assert (m_bInitialized);

	glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode (GL_MODELVIEW);

	glLoadIdentity ();
	glTranslatef (0.0f, 0.0f, -m_fDistance);
	glRotatef (m_fAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef (m_fAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef (m_fAngleZ, 0.0f, 0.0f, 1.0f);

	assert (m_pModel != 0);
	m_pModel->Draw ();

	assert (m_pRenderingContext != 0);
	m_pRenderingContext->SwapBuffers ();
}

GLfloat CObjectViewer3D::NormalizeAngle (GLfloat fAngle)
{
	while (fAngle >= 360.0f)
	{
		fAngle -= 360.0f;
	}

	while (fAngle < 0.0f)
	{
		fAngle += 360.f;
	}

	return fAngle;
}
