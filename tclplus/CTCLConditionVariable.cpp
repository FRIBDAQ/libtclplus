/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2005.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
             Ron Fox
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/

#include <config.h>
#include <CTCLConditionVariable.h>
#include <CTCLMutex.h>
#include <ErrnoException.h>
#include <time.h>
#include <errno.h>

// Imported from NSCLDAQ so no tests are needed as it was tested 

//////////////////////////////////////////////////////////////////////////////////
////////////////// Implement the interface to condition variable attributes //////
//////////////////////////////////////////////////////////////////////////////////

CConditionAttributes::CConditionAttributes()
{
  int stat = pthread_condattr_init(&m_attributes);
  throwifbad(stat, "CConditionAttributes::constructor");
}
CConditionAttributes::~CConditionAttributes()
{
  int stat = pthread_condattr_destroy(&m_attributes);
  throwifbad(stat, "CConditionAttributes::destructor");
}

/*!
   Set the condition variable to be sharable across processes (if located in
   shared memory).
*/
void
CConditionAttributes::setShared()
{
  int stat = pthread_condattr_setpshared(&m_attributes, PTHREAD_PROCESS_SHARED);
  throwifbad(stat, "CConditionAttributes::setShared");
}
/*!
  Set the condition variable to be only usable to synchronize threads within this
  process.
*/
void
CConditionAttributes::setUnshared()
{
  int stat = pthread_condattr_setpshared(&m_attributes, PTHREAD_PROCESS_PRIVATE);
  throwifbad(stat, "CConditionAttributes::setShared");
}
/*!
    \return bool
    \retval true - the attributes have PTHREAD_PROCESS_SHARED set.
    \retval false 

*/
bool
CConditionAttributes::isShared()
{
  int value;
  int stat = pthread_condattr_getpshared(&m_attributes, &value);
  throwifbad(stat, "CConditionAttributes::isShared");

  return (value == PTHREAD_PROCESS_SHARED);
}
/*
**  throw a CErrnoException hissy fit if stat is not zero.. in that case,
**  stat is treated as the errno.
*/
void
CConditionAttributes::throwifbad(int status, const char* message)
{
  if (status != 0) {
    errno = status;
    throw CErrnoException(message);
  }
}
//////////////////////////////////////////////////////////////////////////////////
/////// Implementation of the CConditionVariable class ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////

/*!
   Construct a condition variable with default attributes:
*/

CConditionVariable::CConditionVariable()
{
  create(reinterpret_cast<pthread_condattr_t*>(NULL));
}
/*!
  Construct a condition variable givena a reference to a raw attributes block
  \param attr - reference to a pthread_condattr_t.
*/
CConditionVariable::CConditionVariable(pthread_condattr_t& attr)
{
  create(&attr);
}
/*!
  Construct a condition variable given a reference to an encapsulated
  condition variable attribute block.
  \param attr - A CConditionAttributes reference.
*/
CConditionVariable::CConditionVariable(CConditionAttributes& attr)
{
  create(&(attr.m_attributes));
}

/*!
  Destructor destroys the condition variable. We will ignore the return status.

*/
CConditionVariable::~CConditionVariable()
{
  pthread_cond_destroy(&m_condition);
}

/*!
   Signal a condition variable unblocking one thread...the unblocked thread
   will come out of the block holding the mutex it associated with its wait.
*/
void
CConditionVariable::signal()
{
  int stat = pthread_cond_signal(&m_condition);
  CConditionAttributes::throwifbad(stat, "CConditionVariable::signal");
}
/*!
  Broadcast a condition variable.  This unblocks all thread blocked on the condition
  variable.  If the threads are using the same mutex, the scheduler will determine the
  order in which the threads gain access to the mutex.
  When the thread application code regains control, it will hold the mutex associated
  with the block.
*/
void
CConditionVariable::broadcast()
{
  int stat = pthread_cond_broadcast(&m_condition);
}
/*!
  Waits for a condition variable to be signalled.
  - Atomically releases the mutex passed in and
  - wait to be wakened by either a signal or broadcast operation for at most
    a timeout.
  - If action on the condition variable woke the blocked thread, the
    thread will own the mutex as well.
  - If the wait timedout, the thread will not own the mutex.

  \param mutex  - The encapsulated mutex that will be atomically released when blocking.
                  Note that all threads that cooperate on this condition variable should use
                  the same mutex, but this is not enforeced.
  \param abstime - Absolute time at which the condition variable should timeout.

  \return bool
  \retval true - The thread woke up due to a signal/broadcast on the condition variable.
  \retval false- The thread timed out on the wait.
  
  \throw CErrnoException - if there was another error.
*/
bool
CConditionVariable::timedwait(CMutex& mutex,
			      const struct timespec* abstime)
{
  return timedwait(&(mutex.m_mutex), abstime);
}
/*!
   Same as above but the mutex is a bare pthread mutex.
   This function actually is the one that does all the work.
   The overloads just map parameters and call us.
*/
bool
CConditionVariable::timedwait(pthread_mutex_t* mutex,
			      const struct timespec* abstime)
{
  int status = pthread_cond_timedwait(&m_condition, mutex, abstime);
  if (status == 0) return true;
  if (status == ETIMEDOUT) return false;

  CConditionAttributes::throwifbad(status, "CConditionVariable::timedwait");
  return true;
}
/*!
  Same as above, however the timeout is expressed as milliseconds
*/
bool
CConditionVariable::timedwait(CMutex& mutex, 
			      int milliseconds)
{

  struct timespec abstime = timeout(milliseconds);
  return timedwait(mutex, &abstime);
}


/*!
   Same as above, but the mutex is a pthread mutex
*/
bool
CConditionVariable::timedwait(pthread_mutex_t* mutex,
			      int milliseconds)
{
  struct timespec abstime = timeout(milliseconds);
  return timedwait(mutex, &abstime);
}

/*!
   Wait until the condition variable is signalled, or we are interrupted.


   \param mutex  - The wrapped mutex we are holding that is associated with the 
                   condition variable.  This should be the same for all callers of
		   wait and timedwait.
   
*/
void
CConditionVariable::wait(CMutex& mutex)
{
  return wait(&(mutex.m_mutex));
}
/*!
  Same as above, but with a bare Pthread mutex.
*/
void
CConditionVariable::wait(pthread_mutex_t* mutex)
{
  CConditionAttributes::throwifbad(pthread_cond_wait(&m_condition, mutex),
				   "CConditionVariable::wait");
}



///////////////////////////////////////////////////////////////////////////////////
//
// Utilities:

// common condition variable creating code:

void
CConditionVariable::create(pthread_condattr_t* pAttributes)
{
  CConditionAttributes::throwifbad(pthread_cond_init(&m_condition, pAttributes),
				   "CConditionVariable::Constructing");
}

// convert a millisecond timeout into an absolute expiration time

struct timespec
CConditionVariable::timeout(int milliseconds)
{
  int seconds     = milliseconds / 1000;
  int nanoseconds = (milliseconds % 1000)*1000000; // mult  by nanoseconds/millisecond.

  struct timespec abstime;
  clock_gettime(CLOCK_REALTIME, &abstime);
  abstime.tv_sec  += seconds;
  abstime.tv_nsec += nanoseconds;

  // Carry the one?

  if (abstime.tv_nsec > 1000000000)  {          // 1 second in nanos.
    abstime.tv_sec++;
    abstime.tv_nsec = abstime.tv_nsec % 1000000000;
  }

  return abstime;
}
