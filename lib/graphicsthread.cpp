//
// graphicsthread.cpp
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
#include <graphics/graphicsthread.h>
#include <assert.h>

CGraphicsThread::CGraphicsThread (void)
:	m_pThread (0),
	m_bContinue (TRUE)
{
	pthread_attr_t Attributes;
	pthread_attr_init (&Attributes);

#ifndef NDEBUG
	int nResult =
#endif
		pthread_create (&m_pThread, &Attributes, ThreadStub, this);
	assert (nResult == 0);

	pthread_attr_destroy (&Attributes);
}

CGraphicsThread::~CGraphicsThread (void)
{
	// TODO
}

void CGraphicsThread::Exit (void *pResult)
{
	pthread_exit (pResult);
}

void *CGraphicsThread::Wait (void)
{
	void *pResult;

#ifndef NDEBUG
	int nResult =
#endif
		pthread_join (m_pThread, &pResult);
	assert (nResult == 0);

	return pResult;
}

void *CGraphicsThread::ThreadStub (void *pParam)
{
	CGraphicsThread *pThis = reinterpret_cast<CGraphicsThread *> (pParam);
	assert (pThis != 0);

	return pThis->Run ();
}
