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

//  CTCLPackagedCommand.h:
//
//    This file defines the CTCLPackagedCommand class.
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

#ifndef TCLPACKAGEDCOMMAND_H  //Required for current class
#define TCLPACKAGEDCOMMAND_H
                               
                               //Required for 1:1 associated classes
#ifndef TCLCOMMANDPACKAGE_H
#include "TCLCommandPackage.h"
#endif                                                               

#ifndef TCLPROCESSOR_H
#include "TCLProcessor.h"
#endif                                  

#include <string>
             
class CTCLPackagedCommand   : public CTCLProcessor
{
  
  CTCLCommandPackage& m_rMyPackage;
  
public:

			//Constructor with arguments
  CTCLPackagedCommand (const std::string& sCommand, CTCLInterpreter* pInterp,
		       CTCLCommandPackage& rPackage) :
    CTCLProcessor(sCommand, pInterp),
    m_rMyPackage(rPackage)
  { }        
  CTCLPackagedCommand (const char* pCommand, CTCLInterpreter* pInterp,
		       CTCLCommandPackage& rPackage) :
    CTCLProcessor(pCommand, pInterp),
    m_rMyPackage(rPackage)
  { }        
   ~ CTCLPackagedCommand ( ) { }       //Destructor
	
			//Copy constructor [illegal]
private:
  CTCLPackagedCommand (const CTCLPackagedCommand& aCTCLPackagedCommand ) ;
public:
                        // Assignment operator [illegal]
private:
  CTCLPackagedCommand& operator= 
      (const CTCLPackagedCommand& aCTCLPackagedCommand);
  int operator==(const CTCLPackagedCommand& rhs) const;
  int operator!=(const CTCLPackagedCommand& rhs) const;
public:
  // Selectors:

public:
                       //Get accessor function for 1:1 association
  CTCLCommandPackage& getMyPackage()
  {
    return m_rMyPackage;
  }
  // Mutators
                       
public:
  void setMyPackage (CTCLCommandPackage& am_rMyPackage)
  { 
    m_rMyPackage = am_rMyPackage;
  }


};

#endif
