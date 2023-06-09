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
#include <TCLObjectProcessor.h>
#include <TCLInterpreter.h>
#include <TCLException.h>
#include <StateException.h>	// TODO:

#include <string.h>


using namespace std;


////////////////////////////////////////////////////////////////////////
/*!
   Construct an object command:
   \param interp  : CTCLInterpreter&
         Refers to the interpreter on which this will be eventually registered.
   \param name    : std::string
        Name to be used to register the command (command keyword).
   \param registerMe: bool (true)
       If true, the constructor registers if not an explicit register must be done
       later on  (could not use register as that's a C/C++ keyword).

*/
CTCLObjectProcessor::CTCLObjectProcessor(CTCLInterpreter& interp,
					  string           name,
					  bool             registerMe) : 
  CTCLInterpreterObject(&interp),
  m_Token(0),
  m_fRegistered(false),
  m_Name(name)
{
  Bind(interp);
  if (registerMe) {
    Register();
  }

}
////////////////////////////////////////////////////////////////////////////
/*!
   Destruction just requires unregistering the command.  The
   deletion callback will undoubtably be triggered.
*/
CTCLObjectProcessor::~CTCLObjectProcessor()
{
  if (m_fRegistered) {
    unregister();
  }
}
//////////////////////////////////////////////////////////////////////////////
/*!
    Register this object as an object command.  Note that if the
    command is already registered, we throw a CStateException.

    \throw CStateException thrown if already registered.
*/
void
CTCLObjectProcessor::Register()
{
  if(m_fRegistered) {
    throw CStateException("true", "false", 
			  "Registering a CTCLObjectCommand - already registered");
  }
  else {
    m_Token = RegisterAs(m_Name);
    m_fRegistered = true;
  }
}
/*!
  Register the command with a specific name.  This allows objects to field
  more than one command.
*/
Tcl_Command CTCLObjectProcessor::RegisterAs(string name)
{
  CTCLInterpreter* pInterp = getInterpreter();
  return  Tcl_CreateObjCommand(pInterp->getInterpreter(),
			       name.c_str(),
			       CTCLObjectProcessor::commandRelay,
			       static_cast<ClientData>(this),
			       CTCLObjectProcessor::unregisterRelay);
}


//////////////////////////////////////////////////////////////////////////
/*!
    Delete a command.   
    \throw CStateException  - if the object is not deleted.
    \throw CTCLException    - if the delete failed.
*/
void
CTCLObjectProcessor::unregister()
{
  if(m_fRegistered) {
    unregisterAs(m_Token);
    m_fRegistered = false;
				   
  }
  else {
    throw CStateException("false", "true",
			  "Unregistering a CTCLObjectCommand - not registered");
  }
}
/*!
   Unregister the command object from a specific command name
   \param name - THe name to unregister as.
*/
void
CTCLObjectProcessor::unregisterAs(Tcl_Command token)
{
    CTCLInterpreter* pInterp = getInterpreter();
    int status = Tcl_DeleteCommandFromToken(pInterp->getInterpreter(),
					    token);
    if(status != TCL_OK) {
      throw CTCLException(*pInterp, status,
			  "Unregistering object command");
    }
}
///////////////////////////////////////////////////////////////////////////////
/*!
   Return the name of the command.  If not registered, it's safe just to
   return m_Name, if registered, some script might have renamed us so 
   we'll ask Tcl to tell us what our command name is.
*/
string
CTCLObjectProcessor::getName() const
{
  if (m_fRegistered) {
    CTCLInterpreter* pInterp = getInterpreter();
    Tcl_Obj*  pName = Tcl_NewStringObj("", 0);
    Tcl_GetCommandFullName(pInterp->getInterpreter(), m_Token, pName);
    return std::string(Tcl_GetString(pName));
  }
  else {
    return m_Name;		// Not registered.
  }
}
/////////////////////////////////////////////////////////////////////////////
/*!
    Return information about this command from the Tcl interpreter.
    
    \return Tcl_CmdInfo  
    \retval copy of struct from Tcl_GetCmdInfo().

    \throws CStateException - If not registered.
    \throws CTCLException   - If Tcl_GetCommandInfo fails.
*/
Tcl_CmdInfo
CTCLObjectProcessor::getInfo() const
{
  Tcl_CmdInfo      info;

  if(m_fRegistered) {
    CTCLInterpreter* pInterp = getInterpreter();

    const char*       pCurrentName = Tcl_GetCommandName(pInterp->getInterpreter(),
						  m_Token);
    if(!Tcl_GetCommandInfo(pInterp->getInterpreter(), pCurrentName, &info)) {

      // Failed to get info:
      throw CTCLException(*pInterp,
			  TCL_ERROR,
			  "CTCLObjectProcessor::getInfo()");
    }

  }
  else {
    throw CStateException("false", "true",
			  "CTCLObjectProcessor::getInfo - command not registered");
  }
  return info;
}
/*--------------------------------------------------------------------
** Utilities for derived classes:
*/

/**
 * bindAll 
 *   Binds all the objects in a vector to an interpreter.
 *
 * @param interp - reference to the interpreter.
 * @param objv   - reference to vector of objecgts.
 */
void
CTCLObjectProcessor::bindAll(CTCLInterpreter& interp, std::vector<CTCLObject>& objv)
{
  for (int i = 0; i < objv.size(); i++) {
    objv[i].Bind(interp);
  }
}
/**
 * requireAtLeast
 *    Thrown std::string exception if the size of an objv is less than
 *    the specified number of parameters.
 *
 * @param objv - command object vector.
 * @param n   - Minimmum size required of objv
 * @param msg - Pointer to the message string to use if the default is not
 *              desired.
 */
void
CTCLObjectProcessor::requireAtLeast(std::vector<CTCLObject>& objv,
				    unsigned n, const char* msg) const
{
  const char* pMessage = "Insufficient number of parameters";
  if (msg) pMessage = msg;

  if (objv.size() < n) {
    throw std::string(pMessage);
  }
}
/**
 * requireAtMost
 *   Same as requireAtLeast but there can be no more than n parameters.
 *
 * @param objv - command object vector.
 * @param n   - Maximum size required of objv
 * @param msg - Pointer to the message string to use if the default is not
 *              desired.
 */ 
void CTCLObjectProcessor::requireAtMost(std::vector<CTCLObject>& objv,
				     unsigned n, const char* msg) const
{
  const char* pMessage = "Too many parameters";
  if (msg) pMessage = msg;

  if (objv.size() > n) {
    throw std::string(pMessage);
  }
}
/**
 * requireExactly 
 *    Same as above but there must be exactly the requested number of params.
 *
 * @param objv - command object vector.
 * @param n   - exact size required of objv
 * @param msg - Pointer to the message string to use if the default is not
 *              desired.
 */ 
void CTCLObjectProcessor::requireExactly(std::vector<CTCLObject>& objv,
				     unsigned n, const char* msg) const 
{
  const char* pMessage = "Too many parameters";
  if (msg) pMessage = msg;

  if (objv.size() != n) {
    throw std::string(pMessage);
  }
}


////////////////////////////////////////////////////////////////////////
/*!
   Called when the command is being unregistered.  This is overridable,
   but not necessary.  Our default action is to do nothing.
*/
void
CTCLObjectProcessor::onUnregister()
{

}
///////////////////////////////////////////////////////////////////////
/*!
     Called when the command 'fires'  we just relay to the operator()

     \param pObject  : ClientData
        Actually a pointer to the object whose command fired.
     \param pInterp   : Tcl_Interp*
        Pointer to the interpreter that is running this command.
     \param objc     : int
        count of objects in the command string.
     \param objv     : Tcl_Obj* const*
        The comman objects.

     \return int
     \retval TCL_OK Command executed properly.
     \retval TCL_ERROR command failed.
     \retval (other) only relevant for control constructs... See
             the Tcl docs for information on which ones  are relevant.

*/
int
CTCLObjectProcessor::commandRelay(ClientData    pObject,
				Tcl_Interp*   pInterp,
				int           objc,
				Tcl_Obj* const* objv)
{
  
  // The objv array becomes a vector of CTCLObject...

  vector<CTCLObject>  command;
  for(int i = 0; i < objc; i++) {
    command.push_back(CTCLObject(objv[i]));
  }
  // Now cast the object to the TCLOBjectProcessor and away we go:

  // Need to get the interpreter object from the command
  // else it will get destroyed on exit!!

  CTCLObjectProcessor* pProcessor = static_cast<CTCLObjectProcessor*>(pObject);
  CTCLInterpreter*     pInterpObj = pProcessor->getInterpreter();

  int status;
  try {
    status = (*pProcessor)(*pInterpObj, command);
  }
  catch (string msg) {
    Tcl_SetResult(pInterp, (char*)msg.c_str(), TCL_VOLATILE);
    return TCL_ERROR;
  }
  catch (const char* msg) {
    Tcl_SetResult(pInterp, (char*)msg, TCL_VOLATILE);
    return TCL_ERROR;
  }
  catch (CException& e) {
    Tcl_SetResult(pInterp, (char*)e.ReasonText(), TCL_VOLATILE);
    return TCL_ERROR;
  }
  catch (...) {
    Tcl_SetResult(pInterp, const_cast<char*>("Unexpected exception type processing a Tcl command"),
		  TCL_STATIC);
    return TCL_ERROR;
  }
  return status;
}
////////////////////////////////////////////////////////////////////////
/*!
    Call the onUnregister
    \param pObject : ClientData
       Client data that is really an object pointer.
*/
void
CTCLObjectProcessor::unregisterRelay(ClientData pObject)
{
  CTCLObjectProcessor* processor = static_cast<CTCLObjectProcessor*>(pObject);
  processor->onUnregister();
}
