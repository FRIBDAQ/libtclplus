/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2014.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Authors:
             Ron Fox
             Jeromy Tompkins 
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/

#ifndef TCL_CHANNEL_H
#define TCL_CHANNEL_H

// Headers:

#include <tcl.h>

#ifndef TCLINTERPRETEROBJECT_H
#include <TCLInterpreterObject.h>
#endif

#include <string>

/*!
   This class defines a class that encapsulates a TCL Channel.
   TCL channels in turn abstract the I/O subsystem of the 
   underlying operating system.  
   TCL Channels are represented in TCL by an opaque pointer
   typedef'd as a Tcl_Channel. This pointer contains all
   the state required for a channel.

   We support the following types of construction:
   - Construction of a file channel given a filename, mode string
     and permissions.
   - Construction of a command channel Given an argc/argv array and
     redirection flags.
   - Construction of a client Tcp/Ip channel given a remote port, and hostname.
   - Construction of a Tcp/Ip server listener channel given a
     port, a client connection handler procedure and an application specific
     parameter to pass to that procedure.
   - Construction of a channel object given an existing Tcl_Channel.
   - Copy construction

   Notes:
     - In all cases except constuction from an exsting Tcl_Channel or
       Copy Constructed objects, or objects filled in via assignment,
       destruction implies channel close.
     - Copy construction is supported but only for objects with shorter lifetime
       than the original.
     - Assignment implies closure of the original channel if it would close on 
       destruction and the creation of an object that will not close on destroy.
       (in other words, only the original object closes on destroy).
     - The behavior of this object in the presence of a Tcl close command that
       closes the underlying channel (or for that matter a call to Tcl_Close
       outside of this object), is then undefined.


*/
class CTCLChannel : public CTCLInterpreterObject
{
  // Member data:

private:
  Tcl_Channel   m_Channel;
  bool          m_fCloseOnDestroy;
  bool          m_fRegistered;


  // Constructors and Destructor.

public:

  CTCLChannel(CTCLInterpreter* pInterp, 
	      std::string      Filename,
	      const char*      pMode,
	      int              permissions) ; //!< Construct file channel.
  CTCLChannel(CTCLInterpreter* pInterp,
	      int              argc,
	      const char**           pargv,
	      int              flags); //!< Construct command pipeline. 
  CTCLChannel(CTCLInterpreter* pInterp,
	      int              port,
	      std::string      host) ; //!< Construct a TCP/Client channel.
  CTCLChannel(CTCLInterpreter* pInterp,
	      int              port,
	      Tcl_TcpAcceptProc* proc,
	      ClientData       AppData) ;     //!< Create a TCP/IP server listener.
  CTCLChannel(CTCLInterpreter* pInterp,
	      Tcl_Channel      Channel);     //!< Construct from existing channel.
  CTCLChannel(const CTCLChannel& rhs);   //!< Copy construction.
  virtual ~CTCLChannel();

  // Canonical operations (assignment and (in)equality comparison.


private:
  CTCLChannel& operator=(const CTCLChannel& rhs); //!< assignment.

  int operator==(const CTCLChannel& rhs) const;     //!< Equality comparison.
  int operator!=(const CTCLChannel& rhs) const;     //!< Inequality comparison.
public:
  // Selectors:

public:
  Tcl_Channel getChannel() const {
    return m_Channel;
  }
  bool ClosesOnDestroy() const {
    return m_fCloseOnDestroy;
  }
  // Mutators:

protected:
  void setChannel(Tcl_Channel Channel) {
    m_Channel = Channel;
  }
  void CloseOnDestroy(bool state) {
    m_fCloseOnDestroy = state;
  }

  // Operations on a channel:

public:
  int Read( void** pData, int nChars); //!< Read data from the channel.
  int Write(const void* pData, int nBytes); //!< Write data to the channel.

  bool atEof();			//!< True if EOF on channel.
  void Flush();			//!< Flush channel data buffers.
  void Close();			//!< Close channel (dangerous!!!).
  void Register();	//!< Expose channel name to scripts (dangerous!!)
  void SetEncoding(std::string Name);
  std::string GetEncoding();
};
#endif
