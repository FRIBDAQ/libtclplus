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


//  CTCLVariable.h:
//
//    This file defines the CTCLVariable class.
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

#ifndef TCLVARIABLE_H  //Required for current class
#define TCLVARIABLE_H

#ifndef TCLVERSIONHACKS_H
#include "TCLVersionHacks.h"
#endif 
                              //Required for base classes
#ifndef TCLINTERPRETEROBJECT_H
#include "TCLInterpreterObject.h"
#endif                               

#ifndef TCLPLUSTYPES_H
#include <libtclplusdatatypes.h>
#endif

#include <string>
                               
class CTCLVariable  : public CTCLInterpreterObject        
{
  std::string m_sVariable;	// Name of the variable represented.
  TCLPLUS::Bool_t m_fTracing;		// kfTRUE if tracing is enabled.
  TCLPLUS::Int_t  m_nTraceFlags;		// Set of trace flags for variable.
  std::string m_sTraceIndex;
public:
  // Default construtor needed to allow use in STL container.

  CTCLVariable() :
    m_fTracing(false),
    m_nTraceFlags(0)
    {}


			//Constructor with arguments


  CTCLVariable (std::string am_sVariable,  TCLPLUS::Bool_t am_fTracing  )  :   
    CTCLInterpreterObject(),
    m_sVariable (am_sVariable),  
    m_fTracing (am_fTracing)  
  { }         
  CTCLVariable (CTCLInterpreter* pInterp, 
		std::string am_sVariable,  TCLPLUS::Bool_t am_fTracing  )  :   
    CTCLInterpreterObject(pInterp),
    m_sVariable (am_sVariable),  
    m_fTracing (am_fTracing)  
  { }        
  virtual ~CTCLVariable();
			//Copy constructor
 
  CTCLVariable (const CTCLVariable& aCTCLVariable )   : 
    CTCLInterpreterObject (aCTCLVariable),
    m_sVariable(" "),
    m_fTracing(TCLPLUS::kfFALSE)
  {   
    DoAssign(aCTCLVariable);
  }                                     

			//Operator= Assignment Operator

  CTCLVariable& operator= (const CTCLVariable& aCTCLVariable)
  { 
    if (this == &aCTCLVariable) return *this;          
    CTCLInterpreterObject::operator=(aCTCLVariable);
    DoAssign(aCTCLVariable);
  
    return *this;                                                                                                 
  }                                     

			//Operator== Equality Operator

  int operator== (const CTCLVariable& aCTCLVariable) const
  { 
    return (
	    (CTCLInterpreterObject::operator== (aCTCLVariable)) &&
	    (m_sVariable == aCTCLVariable.m_sVariable) &&
	    (m_fTracing == aCTCLVariable.m_fTracing) 
	    );
  }                             
  // Selectors

public:

  std::string getVariableName() const
  {
    return m_sVariable;
  }
  TCLPLUS::Bool_t IsTracing() const
  {
    return m_fTracing;
  }
  // Mutators:

public:

  void setVariableName (const std::string am_sVariable)
  { 
    if(IsTracing()) UnTrace();
    m_sVariable = am_sVariable;
  }
protected:
  void setTracing (TCLPLUS::Bool_t am_fTracing)
  { 
    m_fTracing = am_fTracing;
  }
  //  Additional operations:
  //
public:                   
  virtual   char*  operator() (char* pName, 
			       char* pSubscript, 
			       int Flags)  ;

   static  char* TraceRelay (ClientData pObject, Tcl_Interp* pInterpreter, 
			     tclConstCharPtr  pName,
			     tclConstCharPtr pIndex,
			     int flags)  ;

  const char* Set (const char* pValue, int flags=TCL_LEAVE_ERR_MSG | 
		                                 TCL_GLOBAL_ONLY)  ;
  const char* Set (const char* pSubscript, const char* pValue, 
		   int flags=TCL_LEAVE_ERR_MSG | TCL_GLOBAL_ONLY)  ;
  const char* Get (int flags=TCL_LEAVE_ERR_MSG | TCL_GLOBAL_ONLY, 
		   char* pIndex=0)  ;
  int Link (void* pVariable, int Type)  ;
  void Unlink ()  ;
  int Trace (int flags=TCL_TRACE_READS | TCL_TRACE_WRITES | TCL_TRACE_UNSETS,
	     char* pIndex = (char*)TCLPLUS::kpNULL)  ;

  void UnTrace ()  ;
 


  // Protecterd utility functions:
  //
protected:
  void DoAssign(const CTCLVariable& rRhs);
};

#endif
