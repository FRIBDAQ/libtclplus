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

#ifndef TCLOBJECTPROCESSOR_H
#define TCLOBJECTPROCESSOR_H

#ifndef TCLINTERPRETEROBJECT_H
#include <TCLInterpreterObject.h>
#endif

#ifndef TCLOBJECT_H
#include <TCLObject.h>
#endif

#include <tcl.h>
#include <vector>

// Forward class definitions:

class  CTCLInterpreter;

/*!
  This class encapsulates the Tcl_Obj command processor interface.
  we needed to start doing this because my understanding is that the argc/argv
  version of the interface is getting deprecated when Tcl/Tk 9.0 comes out.
  If you already  have extensive command sets that use the argc/argv interface,
  fear not, as an adpator has been written to allow these to pretty much work
  once recompiled.

*/
class CTCLObjectProcessor : public CTCLInterpreterObject
{
  // Attributes:

private:
  Tcl_Command m_Token;		// Command token.
  bool        m_fRegistered;	// True if command was registered.
  std::string m_Name;		// Initial name of the command.
public:
  // Constructors and other canonical operations:

  CTCLObjectProcessor(CTCLInterpreter& interp,
		      std::string      name,
		      bool             registerMe=true);
  virtual ~CTCLObjectProcessor();
  // Illegal canonicals:
private:
  CTCLObjectProcessor(const CTCLObjectProcessor& rhs);
  CTCLObjectProcessor& operator=(const CTCLObjectProcessor& rhs);
  int operator==(const CTCLObjectProcessor& rhs) const;
  int operator!=(const CTCLObjectProcessor& rhs) const;
public:

  // class operations:

public:
  void Register();		// Register command on the interpreter.
  Tcl_Command RegisterAs(std::string name); // register with a specific name.
  void unregister();		// Unregister command from the interp.
  void unregisterAs(Tcl_Command token); // unregister given command token.
  std::string getName() const;	// Return the name of the object.
  Tcl_CmdInfo getInfo() const;	// Return info about the command.

  // Replaceable functionality:0

protected:
  virtual int operator()(CTCLInterpreter& interp,
			 std::vector<CTCLObject>& objv) = 0;
  virtual void onUnregister();

  // Useful methods for derived classes:

protected:
  void bindAll(CTCLInterpreter& interp, std::vector<CTCLObject>& objv);
  void requireAtLeast(std::vector<CTCLObject>& objv, unsigned n, const char* msg=0) const;
  void requireAtMost(std::vector<CTCLObject>& objv, unsigned n, const char* msg=0) const;
  void requireExactly(std::vector<CTCLObject>& objv, unsigned n, const char* msg=0) const;


  // Static callback relays:

private:
  static int commandRelay(ClientData pObject, Tcl_Interp* pInterp,
			  int objc, Tcl_Obj* const* objv);
  static void unregisterRelay(ClientData pObject);
  
};


#endif
