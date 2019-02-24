//
// graphicsthread.h
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
#ifndef _graphics_graphicsthread_h
#define _graphics_graphicsthread_h

#include <linux/pthread.h>
#include <circle/types.h>

class CGraphicsThread		/// A thread in an accelerated graphics application
{
public:
	CGraphicsThread (void);
	virtual ~CGraphicsThread (void);

	/// \brief The thread routine
	virtual void *Run (void) = 0;

	/// \brief Request the thread, that it should stop
	void Stop (void)		{ m_bContinue = FALSE; }

	/// \brief Terminate the thread
	/// \param pResult Resulting thread status to be returned from Wait()
	/// \note Callable from the thread itself only
	void Exit (void *pResult);

	/// \brief Wait for termination of the thread
	/// \note Callable from an other thread only
	void *Wait (void);

protected:
	/// \brief Call this in the thread to know, if it should stop
	boolean Continue (void) const	{ return m_bContinue; }

private:
	static void *ThreadStub (void *pParam);

private:
	pthread_t m_pThread;

	boolean m_bContinue;
};

#endif
