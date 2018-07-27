/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2005.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

*/

#ifndef CLANGUAGETRACECALLBACKS_H
#define CLANGUAGETRACECALLBACKS_H


#ifndef VARIABLETRACECALLBACKS_H
#include "VariableTraceCallback.h"
#endif


#include <tcl.h>

class CTCLInterpreter;

// This is what a callback's signature looks like.

typedef char* (VariableTraceCallback)(Tcl_Interp*, char*, char*, int, void*);

/*!
    This is a variable trace callback that interfaces to unbound
    functions (e.g. those written in C).
*/
class CLanguageTraceCallback : public CVariableTraceCallback
{
 private:
  VariableTraceCallback*    m_pCallback;
  void*                     m_pClientData;
  
 public:
  CLanguageTraceCallback(VariableTraceCallback* pCallback,
			  void*                  pClientData);
  virtual ~CLanguageTraceCallback();

  virtual char* operator()(CTCLInterpreter* pInterp,
			   char*            pVariable, 
			   char*            pElement, 
			   int              flags);
};




#endif
