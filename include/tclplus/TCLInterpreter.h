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

//  CTCLInterpreter.h:
//
//    This file defines the CTCLInterpreter class.
//    Most of the manipulator functions follow quite closely the calling
//    sequences of the TCL functions as described in 
//     "TCL and the TK Toolkit" by Ousterhout... .with the interpreter 
//    parameter taken from the object's attribute.  Refer to that, or another
//    TCL book for documentation on the purpose and parameters of each function
//
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



#ifndef TCLInterpreter_H  //Reuired for current class
#define TCLInterpreter_H

#ifndef TCLSTRING_H
#include "TCLString.h"
#endif

#ifndef TCLPLUSTYPES_H
#include <libtclplusdatatypes.h>
#endif


#include <tcl.h>
#include <string>
#include <vector>

class CTCLObject;

                     
class CTCLInterpreter      
{
  Tcl_Interp* m_pInterpreter;  // // Pointer to the interpreter.
  
public:
			//Default constructor - Create new interpreter.

  CTCLInterpreter () :  
    m_pInterpreter(Tcl_CreateInterp())   { } 
  virtual  ~CTCLInterpreter ( ) { // Destructor.
    Tcl_DeleteInterp(m_pInterpreter);
  }

			//Constructor with arguments - Bind to existing interp.
  CTCLInterpreter (  Tcl_Interp* am_pInterpreter  )  :
    m_pInterpreter (am_pInterpreter)  { }        
	
			//Copy constructor -- not allowed.
private:
  CTCLInterpreter (const CTCLInterpreter& aCTCLInterpreter ) ;
public:
			//Operator= Assignment Operator -- not allowed
private:
  CTCLInterpreter operator= (const CTCLInterpreter& aCTCLInterpreter);
public:

			//Operator== Allowed but not so useful.
			//Update to access 1:M associated class attributes      
  int operator== (const CTCLInterpreter& aCTCLInterpreter)
  { 
    return (
	    (m_pInterpreter == aCTCLInterpreter.m_pInterpreter) 
	    );
  }                             
  // Selectors -- note that to allow these objects to interact with other
  //              objects and C code, the read selector for m_pInterpreter
  //              doesn't return a const pointer.
public:
  Tcl_Interp* getInterpreter()
  {
    return m_pInterpreter;
  }
  // Mutator - Allowed only be derived classes:
protected:
  void setInterpreter (Tcl_Interp* am_pInterpreter)
  { 
    m_pInterpreter = am_pInterpreter;
  }
  //  The remainder of the operations are actual TCL interfaces through the
  //  interpreter encpsulated by this class.

public:                       
  // Evaluate script from a string:

  std::string Eval (const char* pScript) ;
  std::string Eval(const CTCLString& rScript)  {
    return Eval((const char*)rScript);
  }
  std::string Eval(const std::string& rScript)  {
    return Eval(rScript.c_str()); 
  }
  //
  // Evaluate a scripts stored in a file.
  //
  std::string EvalFile (const char* pFilename)   ;
  std::string EvalFile(const CTCLString& rFilename)  {
    return EvalFile((const char*)(rFilename));
  }
  std::string EvalFile(const std::string& rFilename)  {
    return EvalFile(rFilename.c_str());
  }
  //  Evaluate a script at the global level (stack empty context).
  //
  std::string GlobalEval (const char* pScript)   ;
  std::string GlobalEval (const CTCLString& rScript)  {
    return GlobalEval((const char*)rScript);
  }
  std::string GlobalEval(const std::string& rScript)  {
    return GlobalEval(rScript.c_str());
  }
  // Evaluate a script and store it it's commands in the 
  // history list for later retrieval
  //
  std::string RecordAndEval (const char* pScript, TCLPLUS::Bool_t fEval=TCLPLUS::kfFALSE);
  std::string RecordAndEval(const CTCLString& rScript, 
			    TCLPLUS::Bool_t fEval=TCLPLUS::kfFALSE)  {
    return RecordAndEval((const char*)(rScript), fEval);
  }
  std::string RecordAndEval(const std::string& rScript,
			    TCLPLUS::Bool_t fEval = TCLPLUS::kfFALSE)  {
    return RecordAndEval(rScript.c_str(), fEval);
  }
  //
  // Evaluate and expression with a string result:
  //
  std::string ExprString (const char* pExpression)   ;
  std::string ExprString(const CTCLString& rExpr)  {
    return ExprString((const char*)(rExpr));
  }
  std::string ExprString(const std::string& rExpr)  {
    return ExprString(rExpr.c_str());
  }
  //  Evaluate string 
  //
  TCLPLUS::Long_t ExprLong (const char* pExpression)   ;
  TCLPLUS::Long_t ExprLong (std::string& rExpression) {
    return ExprLong(rExpression.c_str());
  }
  TCLPLUS::Long_t ExprLong (const CTCLString& rExpr)  {
    return ExprLong((const char*)(rExpr));
  }
  // Evaluate a double:
  //
  TCLPLUS::DFloat_t ExprDouble (const char* pExpression)   ;
  TCLPLUS::DFloat_t ExprDouble (const CTCLString& rExpression)  {
    return ExprDouble ((const char*)(rExpression));
  }
  TCLPLUS::DFloat_t ExprDouble(const std::string& rExpression)  {
    return ExprDouble(rExpression.c_str());
  }
  // Evaluate a boolean:
  //
  TCLPLUS::Bool_t ExprBoolean (const char*  pExpression)   ;
  TCLPLUS::Bool_t ExprBoolean (const CTCLString& rExpression)  {
    return ExprBoolean((const char*)(rExpression));
  }
  TCLPLUS::Bool_t ExprBoolean(const std::string& rExpression)  {
    return ExprBoolean(rExpression.c_str());
  }
  // Substitute for tilde in some filename.
  // 
  std::string TildeSubst (const char* pFilename) const  ;
  std::string TildeSubst (const CTCLString& rName) const {
    return TildeSubst((const char*)(rName));
  }
  std::string TildeSubst (const std::string& rName) const {
    return TildeSubst(rName.c_str());
  }
  
  std::string PosixError () const  ;
  static  std::string ErrnoId ()   ;
  static  std::string SignalId (TCLPLUS::UInt_t nSignal)   ;
  static  std::string SignalMsg (TCLPLUS::UInt_t nSignal)   ;
  void DetachProcess (const std::vector<TCLPLUS::UInt_t>& rPids) const  ;
  void DetachProcess(TCLPLUS::UInt_t nPids, TCLPLUS::Int_t* pPids) const {
    Tcl_DetachPids(nPids, (Tcl_Pid*)pPids);
  }
  void ReapDetachedProcesses () const {
    Tcl_ReapDetachedProcs();
  }
  void AddCommand (const char* pCommandName, 
		   Tcl_CmdProc* pCommandProcessor, 
		   ClientData pData, 
		   Tcl_CmdDeleteProc* pDeleteProcessor=
		   reinterpret_cast<Tcl_CmdDeleteProc*>(reinterpret_cast<size_t>(TCLPLUS::kpNULL))) const  ;
  void AddCommand(const std::string& rCommandName,
		  Tcl_CmdProc* pCommandProcessor,
		  ClientData pData,
		  Tcl_CmdDeleteProc* pDeleteProcessor = 
		                    reinterpret_cast<Tcl_CmdDeleteProc*>(reinterpret_cast<size_t>(TCLPLUS::kpNULL))) const {
    AddCommand(rCommandName.c_str(), pCommandProcessor, pData, 
	       pDeleteProcessor);
  }
  void AddCommand(const CTCLString& rCommandName,
		  Tcl_CmdProc* pCommandProcessor,
		  ClientData pData,
		  Tcl_CmdDeleteProc* pDeleteProcessor = 
		                       reinterpret_cast<Tcl_CmdDeleteProc*>(reinterpret_cast<size_t>(TCLPLUS::kpNULL))) const {
    AddCommand((const char*)(rCommandName), pCommandProcessor,
	       pData, pDeleteProcessor);
  }
  void UnregisterCommand (const char* pCommandName) const  ;
  void UnregisterCommand (const std::string& rCommandName) const {
    UnregisterCommand(rCommandName.c_str());
  }
  void UnregisterCommand (const CTCLString& rCommandName) const {
    UnregisterCommand((const char*)(rCommandName));
  }
  std::string GetResultString () const  ;

  // Access to Tcl Channels inquiry:
  //
  Tcl_Channel GetChannel(
    const std::string& rName,
    TCLPLUS::Int_t* pMode=(TCLPLUS::Int_t*)TCLPLUS::kpNULL
  );
  std::vector<std::string> GetChannelNames(const std::string& rPattern);


  //
  // These two support access to the interpreter:
  //
  Tcl_Interp* operator-> ()	// Access interp->struct elements.
  { return m_pInterpreter; }
  //
  // Supports casts to Tcl_Interp*
  //
  operator Tcl_Interp* () { 
    return m_pInterpreter; 
  }
  // Modern support to set the interpreter result:

  void setResult(const char* resultString);
  void setResult(std::string resultString);
  void setResult(Tcl_Obj*    resultObj);
  void setResult(CTCLObject& resultObj);
};



#endif
