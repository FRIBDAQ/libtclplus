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

#ifndef STATEEXCEPTION_H
#define STATEEXCEPTION_H

#ifndef EXCEPTION_H
#include <Exception.h>
#endif

#include <string>

/*!
   This class provides an exception that can be thrown if
   a program detects a 'state mismatch'. A state mismatch
   is said to occur when something is requested of an object,
   but its internal state forbids that service from being rendered to
   the client.  In particular, this was developed to deal with
   services being requested in the TCL class library of objects
   that require an interpreter to satisfy, when objects were not
   (yet) bound to an interpreter.
*/
class CStateException : public CException
{
private:
  std::string m_Reason;
public:
  // Constructors and other canonicals:

  CStateException(const char* state, const char* allowedStates,
		  const char* pAction);
  virtual ~CStateException();
  CStateException(const CStateException& rhs);
  CStateException& operator=(const CStateException& rhs);
  int operator==(const CStateException& rhs) const;
  int operator!=(const CStateException& rhs) const;


  // Overrides so this can function correctly as a CException:

  virtual const char* ReasonText() const;
  virtual  int ReasonCode() const;

};

#endif
