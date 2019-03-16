//
// eglrenderingcontext.cpp
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
#include <graphics/eglrenderingcontext.h>
#include <assert.h>

CEglRenderingContext::CEglRenderingContext (CBcmDisplayElement *pBcmDisplayElement, EGLenum API)
:	m_pBcmDisplayElement (pBcmDisplayElement),
	m_API (API),
	m_nSwapBehavior (EGL_BUFFER_DESTROYED),
	m_EglDisplay (EGL_NO_DISPLAY),
	m_EglSurface (EGL_NO_SURFACE),
	m_EglContext (EGL_NO_CONTEXT)
{
	assert (m_pBcmDisplayElement != 0);
}

CEglRenderingContext::~CEglRenderingContext (void)
{
	Close ();

	m_pBcmDisplayElement = 0;
}

void CEglRenderingContext::SetSwapBehavior (EGLint nBehavior)
{
	m_nSwapBehavior = nBehavior;
}

boolean CEglRenderingContext::Initialize (void)
{
	assert (m_EglDisplay == EGL_NO_DISPLAY);
	m_EglDisplay = eglGetDisplay (EGL_DEFAULT_DISPLAY);
	if (m_EglDisplay == EGL_NO_DISPLAY)
	{
		return FALSE;
	}

	if (!eglInitialize (m_EglDisplay, 0, 0))
	{
		return FALSE;
	}

	assert (m_API == EGL_OPENGL_ES_API || m_API == EGL_OPENVG_API);
	if (!eglBindAPI (m_API))
	{
		return FALSE;
	}

	static const EGLint AttributeList[] =
	{
		EGL_RED_SIZE,		8,
		EGL_GREEN_SIZE, 	8,
		EGL_BLUE_SIZE,		8,
		EGL_ALPHA_SIZE, 	8,
		EGL_DEPTH_SIZE,		8,	// required for depth test
		EGL_SURFACE_TYPE,	EGL_WINDOW_BIT,
		EGL_NONE
	};

	EGLint nConfigs;
	if (!eglChooseConfig (m_EglDisplay, AttributeList, m_EglConfig, 1, &nConfigs))
	{
		return FALSE;
	}
	assert (nConfigs == 1);

	assert (m_pBcmDisplayElement != 0);
	m_NativeWindow.element = m_pBcmDisplayElement->GetHandle ();
	m_NativeWindow.width = m_pBcmDisplayElement->GetWidth ();
	m_NativeWindow.height = m_pBcmDisplayElement->GetHeight ();

	assert (m_EglSurface == EGL_NO_SURFACE);
	m_EglSurface = eglCreateWindowSurface (m_EglDisplay, m_EglConfig[0], &m_NativeWindow, 0);
	if (m_EglSurface == EGL_NO_SURFACE)
	{
		return FALSE;
	}

	if (!eglSurfaceAttrib (m_EglDisplay, m_EglSurface, EGL_SWAP_BEHAVIOR, m_nSwapBehavior))
	{
		return FALSE;
	}

	assert (m_EglContext == EGL_NO_CONTEXT);
	m_EglContext = eglCreateContext (m_EglDisplay, m_EglConfig[0], EGL_NO_CONTEXT, 0);
	if (m_EglContext == EGL_NO_CONTEXT)
	{
		return FALSE;
	}

	if (!eglMakeCurrent (m_EglDisplay, m_EglSurface, m_EglSurface, m_EglContext))
	{
		return FALSE;
	}

	return TRUE;
}

void CEglRenderingContext::Close (void)
{
	if (m_EglContext != EGL_NO_CONTEXT)
	{
		eglDestroyContext (m_EglDisplay, m_EglContext);

		m_EglContext = EGL_NO_CONTEXT;
	}

	if (m_EglSurface != EGL_NO_SURFACE)
	{
		eglDestroySurface (m_EglDisplay, m_EglSurface);

		m_EglSurface = EGL_NO_SURFACE;
	}

	if (m_EglDisplay != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(m_EglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglTerminate (m_EglDisplay);
		eglReleaseThread ();

		m_EglDisplay = EGL_NO_DISPLAY;
	}
}

void CEglRenderingContext::SwapBuffers (void)
{
	assert (m_EglDisplay != EGL_NO_DISPLAY);
	assert (m_EglSurface != EGL_NO_SURFACE);
#ifndef NDEBUG
	EGLBoolean bOK =
#endif
		eglSwapBuffers (m_EglDisplay, m_EglSurface);
	assert (bOK);
}

int CEglRenderingContext::GetWidth (void) const
{
	assert (m_pBcmDisplayElement != 0);
	return m_pBcmDisplayElement->GetWidth ();
}

int CEglRenderingContext::GetHeight (void) const
{
	assert (m_pBcmDisplayElement != 0);
	return m_pBcmDisplayElement->GetHeight ();
}
