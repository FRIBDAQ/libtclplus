#ifndef TCLLIVEEVENTLOOP_H
#define TCLLIVEEVENTLOOP_H
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
// Includes


#include <string>



// Forward definitions:

class CTCLInterpreter;
class CTCLVariable;
class CTCLStdioCommander;


/*!
  tclsh does not run the Tcl event loop unless, the script
  blocks.  In that case it's not possible to continue processing
  commands from stdin until the event loop exits.  This is not
  always a desireable situation in the NSCLDAQ. Sometimes we'd like to
  have events (like timers e.g.) in the background, or socket servers running
  while being live to events.

  The CTCLLiveEventLoop is a class that can support this operation.
  It is a singleton class, since A Tcl application can only have
  a single event loop, however since a Tcl application may have more
  than one interpreter it is necessary to start the event loop
  on a specific interpreter.  That interpreter is the one that will receive
  interactive commands.  If the interpreter is not passed in when the event loop
  is started, the interpreter associated with the application is used (gpApplication).
 
  Differnences from tclsh's input loop: prompt1 is: "% " while prompt2 is "-- " if
  there are no tcl_prompt1/tcl_prompt2 procs defined.  If defined, those are honored.


  NOTE: This class is unix specific.  It uses file events which are not implemented on Windows.
        It \em ought to work just fine on Macs but has not been tested there.
*/
class CTCLLiveEventLoop {
  // private data:
private:

  static CTCLLiveEventLoop* m_pTheInstance;
  CTCLInterpreter*         m_pStdinTarget;
  bool                     m_isRunning;
  long                     m_stopLatency;
  CTCLStdioCommander*      m_pEventCommander;

  // constructors are private to support singleton enforcement:

private:
  CTCLLiveEventLoop();
  ~CTCLLiveEventLoop();

  // Cut off other attempts to create copies of the event loop object:

  CTCLLiveEventLoop(const CTCLLiveEventLoop&);
  CTCLLiveEventLoop& operator=(const CTCLLiveEventLoop&);
  int operator==(const CTCLLiveEventLoop&) const;
  int operator!=(const CTCLLiveEventLoop&) const;

  // Obtaining the singleton:

public:
  static CTCLLiveEventLoop*  getInstance();

  // Operators on the object:

  void start();			        // Event loop targeting gpApplication's interpreter.
  void start(CTCLInterpreter* pInterp); // Event loop targeting some other interp. 
  void stop();

  long setStopLatency(long ms);
  long getStopLatency() const;

  // Utilities:

private:

  void eventLoop();		// The event loop itself.
  void stopEvents();

};


#endif
