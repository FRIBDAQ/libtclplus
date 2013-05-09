#ifndef __CTCLSERVER_H
#define __CTCLSERVER_H
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

#ifndef __TCL_H
#include <tcl.h>
#ifndef __TCL_H
#define __TCL_H
#endif
#endif

#ifndef __STL_STRING
#include <string>
#ifndef __STL_STRING
#define __STL_STRING
#endif
#endif

#ifndef __STL_LIST
#include <list>
#ifndef __STL_LIST
#define __STL_LIST
#endif
#endif

// forward class definitions:

class CTCLInterpreter;
class CTCLTcpServerInstance;

/*!
   This class is a Tcp/ip listener.  It is part of the TclPlus
   class library because when a connection arrives, a CTCLServerInstance
   object is created that accepts readable events on the client channel
   assembles them into commands and executes them in our interpreter.
   This effectively allows any event driven interpreter to incorporate
   a Tcl server as a component.

   Hooks exist for an authentication mechanism via the allowConnection
   virtual method.  By default, this returns true only if the 
   connecting host is localhost or 127.0.0.1, the IP address equivalent.
   System designers  should think very carefully about how authentication should
   work as allowing connections by unscrupulous people allows them via the
   Tcl exec command, to do anything the server user could do.  Consider, for
   example a client sending the command:
   "exec bash -c rm -rf ~"
   It may be wisest to run the Tcl Server in a slave interpreter that is 
   appropriately constrained (a safe interpreter).

*/
class CTCLServer
{
  // Member data:
private:
  CTCLInterpreter*               m_pInterpreter;
  int                            m_nPort;
  Tcl_Channel                    m_listenChannel;
  std::list<CTCLTcpServerInstance*> m_serverInstances;

  // canonicals:
  
public:
  CTCLServer(CTCLInterpreter* pInterp, int port);
  virtual ~CTCLServer();

private:
  CTCLServer(const CTCLServer&);
  CTCLServer& operator=(const CTCLServer&);
  int operator==(const CTCLServer&) const;
  int operator!=(const CTCLServer&) const;

  // Static members:

private:
  static void connectionRelay(ClientData  pData, 
			      Tcl_Channel connection, 
			      char*       pHostname,
			      int         port);

  // Public interface:
public:
  void instanceExit(CTCLTcpServerInstance* pInstance);
  void shutdown();

protected:
  void onConnection(Tcl_Channel connection,
			    std::string host);

  // Overridables.

  virtual bool allowConnection(Tcl_Channel   connection,
			       std::string   hostname);
  virtual CTCLTcpServerInstance* createInstance(Tcl_Channel connection,
						std::string hostname);


};

#endif
