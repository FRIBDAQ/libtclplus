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

#ifndef __NOSUCHOBJECTEXCEPTION_H
#define __NOSUCHOBJECTEXCEPTION_H

#ifndef __EXCEPTION_H
#include "Exception.h"
#endif


#ifndef __STL_STRING
#include <string>
#ifndef __STL_STRING
#define __STL_STRING
#endif
#endif

class CNoSuchObjectException : public CException
{
  std::string m_sName;
  std::string m_sReasonText;
 public:

  CNoSuchObjectException(const char* pDoing, const char* pName) :
    CException(pDoing),
    m_sName(pName)
    { UpdateReasonText(); }

  CNoSuchObjectException(const char* pDoing, const std::string& rName) :
    CException(pDoing),
    m_sName(rName)
    { UpdateReasonText(); }

  CNoSuchObjectException(const std::string& rDoing, const char* pName) :
    CException(rDoing),
    m_sName(pName)
    { UpdateReasonText(); }

  CNoSuchObjectException(const std::string& rDoing, const std::string& rName) :
    CException(rDoing),
    m_sName(rName)
    { UpdateReasonText(); }

  virtual ~CNoSuchObjectException() { } // Destructor

  // Copy constructor
  CNoSuchObjectException 
    (const CNoSuchObjectException& aCNoSuchObjectException ) : 
    CException (aCNoSuchObjectException) 
    {   
      m_sName = aCNoSuchObjectException.m_sName;
      UpdateReasonText();
    }

			//Operator= Assignment Operator

  CNoSuchObjectException operator= 
         (const CNoSuchObjectException& aCNoSuchObjectException)
  { 
    if (this != &aCNoSuchObjectException) {
      CException::operator= (aCNoSuchObjectException);
      m_sName = aCNoSuchObjectException.m_sName;
      UpdateReasonText();
    }
  }

			//Operator== Equality Operator

  int operator== (const CNoSuchObjectException& aCNoSuchObjectException)
    { 
      return (
	      (CException::operator== (aCNoSuchObjectException)) &&
	      (m_sName == aCNoSuchObjectException.m_sName)
	      );
    }

 public:
  std::string getName() const
    {
      return m_sName;
    }

 public:
  void setName (std::string am_sName)
    {
      m_sName = am_sName;
    }

 public:
  
  virtual const char* ReasonText() const;

 protected:
  void UpdateReasonText();
};

#endif
