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

/** @file:  
 *  @brief: 
 */
//  CTCLException.h:
//
//    This file defines the CTCLException class.
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

#ifndef CTCLEXCEPTION_H  //Required for current class
#define CTCLEXCEPTION_H
        

#include <tcl.h>

#ifndef TCLINTERPRETEROBJECT_H
#include "TCLInterpreterObject.h"
#endif

#ifndef TCLINTERPRETER_H
#include "TCLInterpreter.h"
#endif

#ifndef TCLRESULT_H
#include "TCLResult.h"
#endif

                               //Required for base classes
#ifndef EXCEPTION_H
#include "Exception.h"
#endif  
                           
#include <string>
#ifndef DAQTYPES_H
#include <libtclplusdatatypes.h>
#endif

                               
class CTCLException  : public CTCLInterpreterObject ,public CException
{
   Int_t m_nReason;  // Reason the exception was thrown
				// TCL_ERROR    - Error in script.
				// TCL_BREAK    - Break from loop.
				// TCL_CONTINUE - continue loop.
				// TCL_RETURN   - fuction return.
				// NOTE: Really no business throwing anything
				//       but TCL_ERRORs.
   std::string m_ResultText;		// Cached result text at construction time.
public:
			//Default constructor

  CTCLException (CTCLInterpreter& am_rInterpreter,  
		 Int_t am_nReason,
		 const char* pString) :
    CTCLInterpreterObject(&am_rInterpreter), 
    CException(pString),
    m_nReason(am_nReason)
  {
    m_ResultText = std::string(Tcl_GetStringResult(am_rInterpreter.getInterpreter()));
  }
  CTCLException(CTCLInterpreter& am_rInterpreter,
		Int_t am_nReason,
		const std::string& rString) : 
    CTCLInterpreterObject(&am_rInterpreter),
    CException(rString),
    m_nReason(am_nReason)
  {
    m_ResultText = std::string(Tcl_GetStringResult(am_rInterpreter.getInterpreter()));
  }
  virtual ~CTCLException ( ) { }       //Destructor
	
			//Copy constructor

  CTCLException (const CTCLException& aCTCLException )   : 
    CTCLInterpreterObject (aCTCLException),   
    CException (aCTCLException) 
  {   
    m_nReason = aCTCLException.m_nReason;            
    m_ResultText = aCTCLException.m_ResultText;
  }                                     

			//Operator= Assignment Operator

  CTCLException operator= (const CTCLException& aCTCLException)
  { 
    if (this == &aCTCLException) return *this;          
    CTCLInterpreterObject::operator= (aCTCLException);
    CException::operator= (aCTCLException);

    if(this != &aCTCLException) {
      m_nReason = aCTCLException.m_nReason;
      m_ResultText = aCTCLException.m_ResultText;
    }
    return *this;
  }                                     

			//Operator== Equality Operator

  int operator== (const CTCLException& aCTCLException)
  { return (
	    (CTCLInterpreterObject::operator== (aCTCLException)) &&
	    (CException::operator== (aCTCLException)) &&
	    (m_nReason == aCTCLException.m_nReason) 
	    );
  }                  
  // Selectors:  - Stick to generic CException and CTCLInterpreterObject
  //               interfaces unless you really know what you're doing.
  //
public:

  Int_t getReason() const
  {
    return m_nReason;
  }
  std::string getTraceback();
  static std::string getTraceback(CTCLInterpreter& interp);
  //
  //  Mutators:   Available to derivce classes only:
  //
protected:
                       
          
  void setInterpreter (CTCLInterpreter& am_rInterpreter)
  { 
    Bind(am_rInterpreter);
  }
  void setReason (Int_t am_nReason)
  { 
    m_nReason = am_nReason;
  }
  // TCL Specific interface:
  //
public:
  void AddErrorInfo (const char* pMessage)  ;
  void AddErrorInfo(const std::string& rMessage) {
    AddErrorInfo(rMessage.c_str());
  }
  void AddErrorInfo(const CTCLString& rMessage) {
    AddErrorInfo((const char*)(rMessage));
  }

  void SetErrorCode (const char* pMessage, 
		     const char* pMnemonic="???", 
		     const char* pFacility="TCL", 
		     const char* pSeverity="FATAL")  ;
  void SetErrorCode(const std::string rMessage,
		    const std::string &rMnemonic=std::string("???"),
		    const std::string &rFacility=std::string("TCL"),
		    const std::string &rSeverity=std::string("FATAL")) {
    SetErrorCode(rMessage.c_str(), rMnemonic.c_str(),
		 rFacility.c_str(), rSeverity.c_str());
  }

  //
  // CException generic interface:
  //
  virtual   const char* ReasonText () const;
  virtual   Int_t ReasonCode () const  ;
private:
  CTCLResult GetResult ();
  
};

#endif
