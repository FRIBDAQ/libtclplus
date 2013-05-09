#ifndef __CTCLTCPSERVERINSTANCE_H
#define __CTCLTCPSERVERINSTANCE_H
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

// Headers we absolutely need:

#ifndef __CTCLCHANNELCOMMANDER_H
#include <CTCLChannelCommander.h>
#endif

#ifndef __TCL_H
#include <tcl.h>
#ifndef __TCL_H
#define __TCL_H
#endif
#endif


// forward classes:

class CTCLServer;
class CTCLInterpreter;


/*!
  Server instance for a Tcl TCP server.  
  Subclass of CTCLChannelCommander we supply:
  - onEndFile - so that we can get removed from the 
                listeners list of active instances.
  - returnResult - Which writes the result back at the client.

*/
class CTCLTcpServerInstance : public CTCLChannelCommander
{
private:
  CTCLServer*     m_pListener;

  // Canonicals:
public:
  CTCLTcpServerInstance(CTCLInterpreter*  pInterp,
			Tcl_Channel       connection,
			CTCLServer*       pServer);
  virtual ~CTCLTcpServerInstance();

private:
  CTCLTcpServerInstance(const CTCLTcpServerInstance&);
  CTCLTcpServerInstance& operator=(const CTCLTcpServerInstance&);
  int operator==(const CTCLTcpServerInstance&) const;
  int operator!=(const CTCLTcpServerInstance&) const;

  // Overrides of the base class methods:

public:
  virtual void onEndFile();
  virtual void returnResult();
  
};

#endif
