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

//  CTCLTimer.h:
//
//    This file defines the CTCLTimer class.
//
// Author:
//    Ron Fox
//    NSCL
//    Michigan State University
//    East Lansing, MI 48824-1321
//    mailto:fox@nscl.msu.edu
//
//  Copyright 1999 NSCL, All Rights Reserved.
//
/////////////////////////////////////////////////////////////

#ifndef TCLTIMER_H  //Required for current class
#define TCLTIMER_H
                               //Required for base classes
#ifndef TCLINTERPRETEROBJECT_H
#include "TCLInterpreterObject.h"
#endif    

#ifndef TCLPLUSTYPES_H
#include <libtclplusdatatypes.h>
#endif


#include <tcl.h>

                  
                               
class CTCLTimer  : public CTCLInterpreterObject        
{
  Tcl_TimerToken m_tToken;  // Timer token returned from Tcl_CreateTimerHandler.
  TCLPLUS::UInt_t m_nMsec;		// No. Milleseconds delay on timer.
  TCLPLUS::Bool_t m_fSet;		// kfTRUE if timer is  pending (m_tToken valid).
  
public:
			//Default constructor

  CTCLTimer () :  
    CTCLInterpreterObject(),
    m_tToken(0),  
    m_nMsec(0),  
    m_fSet(0)   
  { } 
  CTCLTimer(CTCLInterpreter* pInterp, TCLPLUS::UInt_t nMsec = 0) :
    CTCLInterpreterObject(pInterp),
    m_tToken(0),
    m_nMsec(nMsec),
    m_fSet(0)
  {}
  virtual ~CTCLTimer ( ) { 
    Clear();
  }       
  //Destructor

			//Copy constructor [ not allowed ]
private:
  CTCLTimer (const CTCLTimer& aCTCLTimer );

			//Operator= Assignment Operator [ not allowed ]

  CTCLTimer& operator= (const CTCLTimer& aCTCLTimer);

			//Operator== Equality Operator [ makes no sense ]
  int operator== (const CTCLTimer& aCTCLTimer);

  // Selectors:

public:

  Tcl_TimerToken getToken() const
  {
    return m_tToken;
  }
  TCLPLUS::UInt_t getMsec() const
  {
    return m_nMsec;
  }
  TCLPLUS::Bool_t IsSet() const
  {
    return m_fSet;
  }
  // Mutators:

protected:                   

  void setToken (Tcl_TimerToken am_tToken)
  { 
    m_tToken = am_tToken;
  }
  void setMsec (TCLPLUS::UInt_t am_nMsec)
  { 
    m_nMsec = am_nMsec;
  }
  void setSet (TCLPLUS::Bool_t am_fSet)
  { 
    m_fSet = am_fSet;
  }
  // Operations and overridables:

public:
  virtual   void operator() ()   = 0;
  static  void CallbackRelay (ClientData pObject)  ;
  void Set ()  ;
  void Set(TCLPLUS::UInt_t nms) {
    m_nMsec = nms;
    Set();
  }
  void Clear ()  ;
};

#endif




