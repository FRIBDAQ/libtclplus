/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2017.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Authors:
             Ron Fox
             Giordano Cerriza
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/

/** @file:  CTCLThread.cpp
 *  @brief: Implement the CTCLThread class.
 */
#include <CTCLThread.h>
#include <stdexcept>
/**
 * constructor
 *    We save the stack and flags for when start is called at which point
 *    they'll be needed.
 * @param flags - start flags.
 * @param stacksize - bytes in stack.
 */
CTCLThread::CTCLThread(int flags, int stacksize) :
    m_threadId(0),
    m_flags(flags),
    m_stacksize(stacksize),
    m_exitRequested(false)
{
        m_trampolineArgs.m_pThis = this;
        m_trampolineArgs.m_pArg  = nullptr;
}
/**
 * destructor
 *   This must be used with caution.  Ideally the sequence is
 *   -  Construct a thread.
 *   -  Start the thread.
 *   -  Ask the thread to exit (if it supports that).
 *   -  join the thread (if it supports that).
 *   -  Now that the thread is no longer schedulable destroy .
 */
CTCLThread::~CTCLThread()
{
    
}

/**
 * start
 *    Starts the thread:
 *    - Any client data is putin the m_trampolineArgs struct as m_pArg.
 *    - Tcl_CreateThread is called with runTrampoline as the thread run
 *      function with a pointer to m_trampolnieArgs as the client data.
 * @param pData - argument to pass to operator() - defaults to a nullptr.
 */
void
CTCLThread::start(ClientData pData)
{
    m_trampolineArgs.m_pArg = pData;
    Tcl_CreateThread(
        &m_threadId, runTrampoline, &m_trampolineArgs, m_stacksize, m_flags
    );
    
}
/**
 * requestExit
 *    There's no way to actually force the exit of a thread.  What we can
 *    do is set a flag (m_exitRequested) and hope the thread looks at it
 *    from time to time (via exitRequested) and, when its true cleans up and
 *    exits.
 *    There is no penalty to ask for an exit more than once.
 */
void
CTCLThread::requestExit()
{
    m_exitRequested = true;
}
/**
 * exitHandler
 *     The runTrampoline, running in the context of the thread,
 *     always sets up an exit handler which, eventually invokes us.
 *     Since exit handlers are optional, we provide a default do-nothing handler.
 *     Tcl provides for a chain of handlers.  This is less appropriate for
 *     an object oriented thread.   We do recommend, however that
 *     at an appropriate time, overrides of this invoke the base class
 *     exit handler so we get object oriented exit handler chaning.
 */
void
CTCLThread::exitHandler()
{
}
/**
 * join
 *  If the thread is joinable and running it can be joined here.
 *  If this is not the case, an exception will be thrown
 * @return int - exit code of the thread.
 * @throws std::logic_error if join could not be done.
 *
 */
int
CTCLThread::join()
{
    int result;
    if (Tcl_JoinThread(m_threadId, &result) != TCL_OK) {
        throw std::logic_error("Join call failed.");
    }
    return result;
}
/**
 * currentThread [static]
 *    Returns the current thread id
 *  @return Tcl_ThreadId
*/
Tcl_ThreadId
CTCLThread::currentThread()
{
    return Tcl_GetCurrentThread();
}
///////////////////////////////////////////////////////////////////////////////
// Protected methods:

/**
 * exitRequested
 *
 * @return bool - returns true if exit was requested.
 */
bool
CTCLThread::exitRequested() const
{
    return m_exitRequested;
}
///////////////////////////////////////////////////////////////////////////////
// private - note a trampoline in this context is a method that is static
//          which puts us into object context.
//

/**
 * runTrampoline [static]
 *    Thread entry point:
 *    - Establish an exit handler.
 *    - Pass control over to operator() for the thread object that got started.
 *    - On return, clean up the thread with (Tcl_ExitThread).
 * @param pRawData - pointer to the m_trampolineArgs for this thread.
 */
Tcl_ThreadCreateType
CTCLThread::runTrampoline(ClientData pRawData)
{
    MyClientData* pData = reinterpret_cast<MyClientData*>(pRawData);
    Tcl_CreateThreadExitHandler(exitTrampoline,  pData->m_pThis);
    int result = (*pData->m_pThis)(pData->m_pArg);
    Tcl_ExitThread(result);
}
/**
 * exitTrampoline [static]
 *    Trampline to establish object context and invoke the object's
 *    exithandler.
 */
void
CTCLThread::exitTrampoline(ClientData obj)
{
    CTCLThread* pThis = reinterpret_cast<CTCLThread*>(obj);
    pThis->exitHandler();
}
