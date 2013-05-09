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
#ifndef __TCLPACKAGEDOBJECTPROCESSOR_H
#define __TCLPACKAGEDOBJECTPROCESSOR_H

// includes

#ifndef __TCLOBJECTPROCESSOR_H
#include "TCLObjectProcessor.h"
#endif

#ifndef __STL_STRING
#include <string>
#ifndef __STL_STRING
#define __STL_STRING
#endif
#endif

// forward definitions:

class CTCLObjectPackage;
class CTCLInterpreter;

/*!
  A packaged command is one that has at its disposal the services of some 
  shared set of functions (its package).  This class is the base class for all such
  commands.

  In normal usage, the user derives the actual desired class from this.
  The life of a pacakged command is versy similar to any object command, however at some point
  it is attached to the package and its onAttach member is invoked to ensure access to the
  package object.
*/
class CTCLPackagedObjectProcessor : public CTCLObjectProcessor
{
private:
  CTCLObjectPackage*   m_package;

  // We need constructors and so on so that we can pass the
  // specification of the command on to the base class:
public:
  CTCLPackagedObjectProcessor(CTCLInterpreter&  interp,
			      std::string       command,
			      bool              registerMe = true);
  virtual ~CTCLPackagedObjectProcessor();

  // These are illegal in the base class so illegal here too:

private:
  CTCLPackagedObjectProcessor(const CTCLPackagedObjectProcessor& rhs);
  CTCLPackagedObjectProcessor& operator=(const CTCLPackagedObjectProcessor& rhs);
  int operator==(const CTCLPackagedObjectProcessor& rhs);
  int operator!=(const CTCLPackagedObjectProcessor& rhs);

  // Two members support knowledge of the package.
  // a virtual function provides the derived class with a chance to do initialization
  // that requires knowledge of the package:

public:
  void onAttach(CTCLObjectPackage* package);
protected:
  CTCLObjectPackage*  getPackage();
  virtual void Initialize();


};
#endif
