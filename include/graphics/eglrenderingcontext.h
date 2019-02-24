//
// eglrenderingcontext.h
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
#ifndef _graphics_eglrenderingcontext_h
#define _graphics_eglrenderingcontext_h

#include <graphics/bcmdisplayelement.h>
#include <EGL/egl.h>
#include <circle/types.h>

class CEglRenderingContext	/// EGL rendering context
{
public:
	CEglRenderingContext (CBcmDisplayElement *pBcmDisplayElement, EGLenum API);
	~CEglRenderingContext (void);

	void SetSwapBehavior (EGLint nBehavior);

	boolean Initialize (void);

	void Close (void);

	void SwapBuffers (void);

	int GetWidth (void) const;
	int GetHeight (void) const;

private:
	CBcmDisplayElement *m_pBcmDisplayElement;
	EGLenum m_API;
	EGLint m_nSwapBehavior;

	EGLDisplay m_EglDisplay;
	EGLConfig m_EglConfig[1];
	EGLSurface m_EglSurface;
	EGLContext m_EglContext;

	EGL_DISPMANX_WINDOW_T m_NativeWindow;
};

#endif
