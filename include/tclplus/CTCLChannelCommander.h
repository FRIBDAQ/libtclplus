#ifndef CTCLCHANNELCOMMANDER_H
#define CTCLCHANNLECOMMANDER_H
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

/* Headers we absolutely must have: */

#include <string>
#include <tcl.h>

// Forward class definitions:

class CTCLInterpreter;

/*!
    A Channel commander is an object that can accept commands on some
    channel in an event driven way, and submit them for processing
    to the interpreter.  Commanders could point to some interactive channel
    (e.g. see CTCLStdioCommander), or something less interactive like
    the socket of CTCLTcpServerInstance.

    This base class is suitable for the generic case but has member functions
    that can be overriden for more specific cases.

*/
class CTCLChannelCommander
{
protected:
  CTCLInterpreter*   m_pInterp;
  Tcl_Channel        m_channel;
  std::string        m_command;


  // constructors and canonicals.

public:
  CTCLChannelCommander(CTCLInterpreter* interp,
		       Tcl_Channel      channel);
  virtual ~CTCLChannelCommander();

private:
  CTCLChannelCommander(const CTCLChannelCommander& rhs);
  CTCLChannelCommander& operator=(const CTCLChannelCommander& rhs);
  int operator==(const CTCLChannelCommander& rhs) const;
  int operator!=(const CTCLChannelCommander& rhs) const;



  // Public interface:
public:
  virtual void start();			// Add to Tcl Event loop.
  virtual void stop();			// Remove from event loop.
  Tcl_Channel  getChannel() const;
  
  // static members:

public:
  static void inputRelay(ClientData pData, int mask);

  // Overridables:

  virtual void onInput();
  virtual void onInputException();
  virtual void onEndFile();
  virtual void onCommand();
  virtual void returnResult();

  virtual void prompt1();
  virtual void prompt2();
  virtual void sendPrompt(std::string prompt);
  bool stopped() const;

  // utilities.

protected:

  std::string prompt1String();
  std::string prompt2String();
  std::string getPromptString(const char* scriptVariable, 
			      const char*  defaultValue);

};

#endif
