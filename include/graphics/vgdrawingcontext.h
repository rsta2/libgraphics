//
// vgdrawingcontext.h
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
#ifndef _graphics_vgdrawingcontext_h
#define _graphics_vgdrawingcontext_h

#include <graphics/eglrenderingcontext.h>
#include <graphics/bcmdisplayelement.h>
#include <VG/openvg.h>
#include <VG/vgu.h>

class CVgDrawingContext : public CEglRenderingContext	/// OpenVG rendering context
{
public:
	static const VGfloat BlackColor[], RedColor[], GreenColor[], BlueColor[],
			     YellowColor[], MagentaColor[], CyanColor[], WhiteColor[];

public:
	CVgDrawingContext (CBcmDisplayElement *pBcmDisplayElement);
	~CVgDrawingContext (void);

	/// \brief Clear the whole screen with color
	void ClearAll (const VGfloat Color[4] = BlackColor);

	/// \brief Copy image from memory to display
	/// \param pData	Pointer to image buffer
	/// \param nDataStride	Value to add to pData to get to the next pixel line in memory
	/// \param Format	Image format specifier (see OpenVG spec.)
	void WritePixels (const void *pData, VGint nDataStride,
			  VGfloat fX, VGfloat fY, VGfloat fWidth, VGfloat fHeight,
			  VGImageFormat Format);

private:
	void CheckError (void);
};

#endif
