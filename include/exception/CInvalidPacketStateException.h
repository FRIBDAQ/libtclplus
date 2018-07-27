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


//////////////////////////CInvalidPacketStateException.h file//////////////////////////////////

#ifndef CINVALIDPACKETSTATEEXCEPTION_H  
#define CINVALIDPACKETSTATEEXCEPTION_H


                               
#ifndef READOUTEXCEPTION_H
#include "CReadoutException.h"
#endif

#include <string>
                               
/*!
   Encapsulates exceptions which are thrown as a result of 
   mis-manipulating packets.
   The ReasonCode function returns nonzero if the packet was open.
 */		
class CInvalidPacketStateException  : public CReadoutException        
{ 
private:
  bool   m_nWasOpen;		//!< nonzero if packet was open.
  std::string m_sReasonText;		//!< Reason for exception is built here.
 
public:

  CInvalidPacketStateException (bool WasOpen, const char* pszAction);
  CInvalidPacketStateException(const CInvalidPacketStateException& rhs);
  ~ CInvalidPacketStateException ( ) { }
  
  CInvalidPacketStateException& operator= (const CInvalidPacketStateException& rhs);
  int         operator==(const CInvalidPacketStateException& rhs);
  int         operator!=(const CInvalidPacketStateException& rhs) {
    return !(operator==(rhs));
  }
  
  // Selectors for class attributes:
public:
  
  int getWasOpen() const {
    return m_nWasOpen;
  }
  
  // Mutators:
protected:  
  
  // Class operations:
public:
  
  Int_t ReasonCode () const  ;
  virtual   const char* ReasonText () const  ;

protected:
   void BuildReasonText();
  
};

#endif
