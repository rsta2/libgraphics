//
// vgdrawingcontext.cpp
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
#include <graphics/vgdrawingcontext.h>
#include <circle/logger.h>
#include <assert.h>

const VGfloat CVgDrawingContext::BlackColor[]	= {0.0f, 0.0f, 0.0f, 1.0f};
const VGfloat CVgDrawingContext::RedColor[]	= {1.0f, 0.0f, 0.0f, 1.0f};
const VGfloat CVgDrawingContext::GreenColor[]	= {0.0f, 1.0f, 0.0f, 1.0f};
const VGfloat CVgDrawingContext::BlueColor[]	= {0.0f, 0.0f, 1.0f, 1.0f};
const VGfloat CVgDrawingContext::YellowColor[]	= {1.0f, 1.0f, 0.0f, 1.0f};
const VGfloat CVgDrawingContext::MagentaColor[]	= {1.0f, 0.0f, 1.0f, 1.0f};
const VGfloat CVgDrawingContext::CyanColor[]	= {0.0f, 1.0f, 1.0f, 1.0f};
const VGfloat CVgDrawingContext::WhiteColor[]	= {1.0f, 1.0f, 1.0f, 1.0f};

CVgDrawingContext::CVgDrawingContext (CBcmDisplayElement *pBcmDisplayElement)
:	CEglRenderingContext (pBcmDisplayElement, EGL_OPENVG_API)
{
}

CVgDrawingContext::~CVgDrawingContext (void)
{
}

void CVgDrawingContext::ClearAll (const VGfloat Color[4])
{
	vgSetfv (VG_CLEAR_COLOR, 4, Color);

	vgClear (0, 0, GetWidth (), GetHeight ());
	CheckError ();
}

void CVgDrawingContext::WritePixels (const void *pData, VGint DataStride,
				     VGfloat X, VGfloat Y, VGfloat Width, VGfloat Height,
				     VGImageFormat Format)
{
	vgWritePixels (pData, DataStride, Format, X, Y, Width, Height);
	CheckError ();
}

void CVgDrawingContext::CheckError (void)
{
	VGErrorCode ErrorCode = vgGetError ();
	if (ErrorCode != VG_NO_ERROR)
	{
		CLogger::Get ()->Write ("vgctx", LogError,
					"OpenVG error 0x%X", (unsigned) ErrorCode);

		assert (ErrorCode == VG_NO_ERROR);
	}
}
