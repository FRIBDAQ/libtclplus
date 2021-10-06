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

/** @file:  CTCLMutex.h
 *  @brief: Class that encpsulates a Mutex via the Tcl API.
 */
#ifndef CTCLMUTEX_H
#define CTCLMUTEX_H
#include <tcl.h>

/**
 *  @class CTCLMutex
 *     Class to encapsulate a mutex using the Tcl api.
 *     - Construction creates the mutex,
 *     - Destruction finalizes the mutex,
 *     - Lock and Unlock do that as well.
 *
 * @note - we don't create the mutex with TCL_DECLARE_MUTEX because
 *         *   They make it a static and that's bad for us.
 *         *   We know we need threading turned on so the other reason --
 *             making it a nullity is not relevant for us.
 */
class CTCLMutex {
private:
    Tcl_Mutex m_mutex;
public:
    CTCLMutex();
    virtual ~CTCLMutex();
    
    void lock();
    void unlock();
};

/**
 * @class CTCLCriticalSection
 *    This class implements a critical section of code.  Critical sections
 *    of code are sections of code that can only be executed by one thread at a time.
 *    CTCLCritical section constructs on a mutex and locks that mutex at construction
 *    on destruction the mutex is unlocked.  A typical example is:
 * \verbatim
 *      CTCLMutex guard;      // Used to guard the critical sections:
 *      ...
 *      {
 *         CTCLCriticalSection(guard);        // guard is locked
 *              ... Thread critical code
 *      }                                     // guard is unlocked.
 */
class CTCLCriticalSection
{
private:
    CTCLMutex& m_mutex;
public:
    CTCLCriticalSection (CTCLMutex& mutex) : m_mutex(mutex) {
        m_mutex.lock();
    }
    ~CTCLCriticalSection() {m_mutex.unlock(); }
};

#endif