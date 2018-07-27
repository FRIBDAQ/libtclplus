#ifndef __CTCLSTDIOCOMMANDER_H
#define __CTCLSTDIOCOMMANDER_H

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

#ifndef CTCLCHANNELCOMMANDER_H
#include <CTCLChannelCommander.h>
#endif

#include <string>
#include <tcl.h>

// forward class defs:

class CTCLInterpreter;


/*!
  STDIO channel commander is a channel commander that prompts on stdout, 
  and accepts commands on stdin.  Registering this in the event loop, 
  and then entering the event loop yields a powerful result, tcl
  with an event loop running but still accepting commands on stdin 
  (event loop without the vwait command).

  See also CTCLLiveEventLoop which is a class that can set this all up
  and contains the event loop code itself.

*/
class CTCLStdioCommander : public CTCLChannelCommander
{
  // Data:
private:
  Tcl_Channel              m_stdOut;      // Prompts go here.

  // Canonicals:

public:
  CTCLStdioCommander(CTCLInterpreter* pInterp);
  virtual ~CTCLStdioCommander();

private:
  CTCLStdioCommander(const CTCLStdioCommander&);
  CTCLStdioCommander& operator=(const CTCLStdioCommander&);
  int operator==(const CTCLStdioCommander&) const;
  int operator!=(const CTCLStdioCommander&) const;

  // overrides:

  virtual void sendPrompt(std::string prompt);
  virtual void returnResult();
};

#endif
