#ifndef CTCLCONDITIONVARIABLE_H
#define CTCLCONDITIONVARIABLE_H
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

// Since it seems that I can't get Tcl_Mutex's to work properly (they must
// somehow but I can't figure out what I did wrong), and that implies that
// condition variables won't work either, I'm grabbing the ConditionVariable
// code from NSCLDAQ/main/base/thread and aliasing class names to make it look
// like these are actually in Tcl libraries.


#include <pthread.h>
#include <time.h>


class CMutex;

/*!
  Direct encapsulation of a pthread condition variable attributes block.  We are only going
  to define interfaces to the base level pthread attributes.
*/
struct CConditionAttributes
{
  pthread_condattr_t     m_attributes;

  CConditionAttributes();
  ~CConditionAttributes();

  void setShared();
  void setUnshared();
  bool isShared();

  static void throwifbad(int status, const char* msg);
};

/*!
  Direct encapsulation of a pthread condition variable.
  
*/
class CConditionVariable
{
public:
  pthread_cond_t    m_condition;

public:
  CConditionVariable();
  CConditionVariable(pthread_condattr_t& attr);
  CConditionVariable(CConditionAttributes& attr);
  virtual ~CConditionVariable();
private:
  CConditionVariable(const CConditionVariable& rhs);
  CConditionVariable& operator=(const CConditionVariable& rhs);
  int operator==(const CConditionVariable& rhs) const;
  int operator!=(const CConditionVariable& rhs) const;

  // Synchronization operations:

public:
  void signal();
  void broadcast();

  bool timedwait(CMutex& mutex,
		 const struct timespec* abstime);
  bool timedwait(pthread_mutex_t* mutex,
		 const struct timespec* abstime);

  bool timedwait(CMutex& mutex,
		 int     milliseconds);
  bool timedwait(pthread_mutex_t* mutex,
		  int    milliseconds);

  void wait(CMutex& mutex);
  void wait(pthread_mutex_t* mutex);


private:
  void create(pthread_condattr_t* pAttributes);
  struct timespec timeout(int milliseconds);
  

};
// Alias trick:

using CTCLConditionVariable = CConditionVariable;
using CTCLConditionVariableAttributes = CConditionAttributes;
#endif
