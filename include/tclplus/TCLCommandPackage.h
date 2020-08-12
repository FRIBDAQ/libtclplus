/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2017.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Authors:
             Ron Fox
             Giordano Cerriza
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/

/** @file:  
 *  @brief: 
 */
// Typically this class should be overridden, but not necessarily.
//  CTCLCommandPackage.h:
//
//    This file defines the CTCLCommandPackage class.
//
// Author:
//    Ron Fox
//    NSCL
//    Michigan State University
//    East Lansing, MI 48824-1321
//    mailto:fox@nscl.msu.edu
//
//  Copyright 1999 NSCL, All Rights Reserved.
//
/////////////////////////////////////////////////////////////

#ifndef TCLCOMMANDPACKAGE_H  //Required for current class
#define TCLCOMMANDPACKAGE_H
                               //Required for base classes
#ifndef TCLINTERPRETEROBJECT_H
#include "TCLInterpreterObject.h"
#endif                               
                               
#ifndef TCLINTERPRETER_H
#include "TCLInterpreter.h"
#endif
                               //Required for 1:M associated classes
#ifndef TCLPROCESSOR_H
#include "TCLProcessor.h"
#endif                                                               

#ifndef DAQTYPES_H
#include <libtclplusdatatypes.h>
#endif

#include <list>
#include <string>


typedef std::list<CTCLProcessor*>   CommandList;
typedef CommandList::iterator  CommandListIterator;

class CTCLCommandPackage  : public CTCLInterpreterObject        
{
  std::string m_sSignon;    // Package signon message.  
  CommandList m_lCommands;  // List of references to command objects
                            // which implement package.
  
public:
  // Constructors with parameters:
  //
  CTCLCommandPackage (CTCLInterpreter* pInterp, 
		      const std::string& rSignon=std::string("Unnamed pkg")) :
    CTCLInterpreterObject(pInterp),
    m_sSignon(rSignon)
  {}
  CTCLCommandPackage(CTCLInterpreter* pInterp,
		     const char* pSignon = "Unnamed pkg") :
    CTCLInterpreterObject(pInterp),
    m_sSignon(pSignon)
  {}
  virtual ~ CTCLCommandPackage ( ) { /* Unregster(); */ }       //Destructor

			//Copy constructor

  CTCLCommandPackage (const CTCLCommandPackage& aCTCLCommandPackage )   : 
    CTCLInterpreterObject (aCTCLCommandPackage),
    m_sSignon(aCTCLCommandPackage.m_sSignon),
    m_lCommands(aCTCLCommandPackage.m_lCommands)
  {}                                     

			//Operator= Assignment Operator

  CTCLCommandPackage& operator= (const CTCLCommandPackage& aCTCLCommandPackage)
  { 
    if (this == &aCTCLCommandPackage) return *this;          
    CTCLInterpreterObject::operator= (aCTCLCommandPackage);
    m_sSignon   = aCTCLCommandPackage.m_sSignon;
    m_lCommands = aCTCLCommandPackage.m_lCommands;
        
    return *this;
  }                                     

			//Operator== Equality Operator

  int operator== (const CTCLCommandPackage& aCTCLCommandPackage)
  { return (
	    (CTCLInterpreterObject::operator== (aCTCLCommandPackage)) &&
	    (m_sSignon   == aCTCLCommandPackage.m_sSignon)              &&
	    (m_lCommands == aCTCLCommandPackage.m_lCommands)
	    );
  }                             
  // Selectors:

public:
  std::string getSignon() const
  {
    return m_sSignon;
  }
  CommandList getCommandList() const
  {
    return m_lCommands;
  }
  // Mutators:

protected:                    
  void setSignon (std::string am_sSignon)
  { 
    m_sSignon = am_sSignon;
  }
  void setCommandList(CommandList& rList)
  {
    m_lCommands = rList;
  }
  // Operations:

public:                       
  void Register ()  ; 
  void Unregister ()  ;

  // inline functions:

  void AddProcessor (CTCLProcessor* pProcessor) {
    m_lCommands.push_back(pProcessor);
  }
  void AddProcessors(CommandList& rList) 
  {
    m_lCommands.insert(end(), rList.begin(), rList.end());
  }
  CommandListIterator begin () {
    return m_lCommands.begin();
  }
  CommandListIterator end () {
    return m_lCommands.end();
  }

};

#endif
