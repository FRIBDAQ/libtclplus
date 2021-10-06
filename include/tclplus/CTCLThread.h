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

/** @file:  CTCLThread.h
 *  @brief: Class to encapsulate threading via TclAPI.
 */
#ifndef CTCLTHREAD_H
#define CTCLTHREAD_H
#include <tcl.h>
/**
 * @class CTCLThread
 *     Concrete derivations of this class are instances of threads that
 *     are started using the TCL API (Tcl_CreateThread).
 */
class CTCLThread
{
private:
    Tcl_ThreadId  m_threadId;
    int           m_flags;
    int           m_stacksize;
    bool          m_exitRequested;
    
    // A pointer to this is passed as client data to the static thread starter.
    
    struct MyClientData  {
        CTCLThread*  m_pThis;
        ClientData   m_pArg;
    } m_trampolineArgs;
    static Tcl_ThreadDataKey m_tsdkey;
public:
    CTCLThread(int flags = TCL_THREAD_JOINABLE, int stacksize = TCL_THREAD_STACK_DEFAULT);
    virtual ~CTCLThread();
    
    void start(ClientData pData = nullptr);
    void requestExit();
    
    virtual int operator()(ClientData arg) = 0;
    virtual void exitHandler();
    
    int join();
    
    static Tcl_ThreadId currentThread();
protected:
    bool exitRequested() const;
private:
    static Tcl_ThreadCreateType runTrampoline(ClientData pData);
    static void exitTrampoline(ClientData obj);
};


#endif