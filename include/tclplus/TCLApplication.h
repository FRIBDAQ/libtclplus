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

//  CTCLApplication.h:
//
//    This file defines the CTCLApplication class.
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

#ifndef __TCLAPPLICATION_H  //Required for current class
#define __TCLAPPLICATION_H
                               //Required for base classes
#ifndef __TCLINTERPRETEROBJECT_H
#include "TCLInterpreterObject.h"
#endif                               


                               
class CTCLApplication  : public CTCLInterpreterObject        
{
  void*        m_pInit;	  // Ensure app init pulled out of link.
  Tcl_ThreadId m_thread;
public:
			//Default constructor

  CTCLApplication ();
				                  // is linked.
  ~CTCLApplication ( ) { }       //Destructor

	
			//Copy constructor

  CTCLApplication (const CTCLApplication& aCTCLApplication )   : 
    CTCLInterpreterObject (aCTCLApplication) 
  { 
                
  }                                     

			//Operator= Assignment Operator

  CTCLApplication& operator= (const CTCLApplication& aCTCLApplication)
  { 
    if (this == &aCTCLApplication) return *this;          
    CTCLInterpreterObject::operator= (aCTCLApplication);
  
    return *this;
  }                                     

			//Operator== Equality Operator

  int operator== (const CTCLApplication& aCTCLApplication)
  { 
    return (
	    (CTCLInterpreterObject::operator== (aCTCLApplication))

	    );
  }                             
                       
  virtual   int operator() ()  =0;

  void getProgramArguments(int& argc, char**& argv);

  Tcl_ThreadId getThread() const;
 
};

#endif
