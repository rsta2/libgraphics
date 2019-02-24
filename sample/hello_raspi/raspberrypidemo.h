//
// raspberrypidemo.h
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
#ifndef _raspberrypidemo_h
#define _raspberrypidemo_h

#include <graphics/graphicsthread.h>
#include <graphics/bcmdisplay.h>
#include <graphics/bcmdisplayelement.h>
#include <graphics/eglrenderingcontext.h>
#include "raspberrypi3d.h"
#include "objectviewer3d.h"

class CRaspberryPiDemo : public CGraphicsThread
{
public:
	CRaspberryPiDemo (CBcmDisplay *pBcmDisplay,
			  int nPosX, int nPosY, int nWidth, int nHeight);
	~CRaspberryPiDemo (void);

	void *Run (void);

private:
	int m_nPosX;
	int m_nPosY;
	int m_nWidth;
	int m_nHeight;

	CBcmDisplayElement m_BcmDisplayElement;
	CEglRenderingContext m_RenderingContext;
	CRaspberryPi3D m_Model3D;
	CObjectViewer3D m_Viewer;
};

#endif
