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
#ifndef TCLOBJECTPACKAGE_H
#define TCLOBJECTPACKAGE_H

// includes:

#include <list>


// forward defs

class CTCLPackagedObjectProcessor;

/*!
    A TCL Object Package contains functionality that may be
    shared by a set of related TCL commands...where the commands
    are implemented via CTCLPackagedObjectProcessor objects.


    This is normally a base class.
*/
class CTCLObjectPackage
{
public:
  typedef std::list<CTCLPackagedObjectProcessor*> Commands;
  typedef Commands::iterator CommandIterator;
private:
  Commands  m_commands;

  // Common services for all packages:

public:
  void addCommand(CTCLPackagedObjectProcessor* processor);
  CommandIterator begin();
  CommandIterator end();



};
   

#endif
