
//  CTCLFileHandler.h:
//
//    This file defines the CTCLFileHandler class.
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

#ifndef TCLFILEHANDLER_H	//Required for current class
#define TCLFILEHANDLER_H
				//Required for base classes
#ifndef TCLINTERPRETEROBJECT_H
#include "TCLInterpreterObject.h"
#endif                            

#ifndef HISTOTYPES_H
#include <libtclplusdatatypes.h>
#endif

#include <unistd.h>
#include <stdio.h>
  

class CTCLFileHandler  : public CTCLInterpreterObject        
{
  UInt_t m_nFid;  // File descriptor associated with the object.
  
public:
			//Default constructor

  CTCLFileHandler (CTCLInterpreterObject* pInterp,  
		   UInt_t am_nFid = STDIN_FILENO) :       
    CTCLInterpreterObject(pInterp->getInterpreter()),
    m_nFid (am_nFid)  
  { }        
  CTCLFileHandler(CTCLInterpreterObject* pInterp,
		  FILE* pFile) :
    CTCLInterpreterObject(pInterp->getInterpreter()),
    m_nFid(fileno(pFile))
  { }
  CTCLFileHandler(CTCLInterpreter* pInterp,
		   UInt_t am_nFid = STDIN_FILENO) :       
    CTCLInterpreterObject(pInterp),
    m_nFid(am_nFid)
  { }
  CTCLFileHandler(CTCLInterpreter* pInterp,
		  FILE* pFile) :
    CTCLInterpreterObject(pInterp),
    m_nFid(fileno(pFile))
  { }
  ~CTCLFileHandler ( ) {Clear(); }       //Destructor	
			//Copy constructor

  CTCLFileHandler (const CTCLFileHandler& aCTCLFileHandler )   : 
    CTCLInterpreterObject (aCTCLFileHandler) 
  {   
    m_nFid = aCTCLFileHandler.m_nFid;
                
  }                                     

			//Operator= Assignment Operator

  CTCLFileHandler& operator= (const CTCLFileHandler& aCTCLFileHandler)
  { 
    if (this == &aCTCLFileHandler) return *this;          
    CTCLInterpreterObject::operator= (aCTCLFileHandler);
    m_nFid = aCTCLFileHandler.m_nFid;
    return *this;
  }                                     

			//Operator== Equality Operator

  int operator== (const CTCLFileHandler& aCTCLFileHandler) const
  { return (
	    (CTCLInterpreterObject::operator== (aCTCLFileHandler)) &&
	    (m_nFid == aCTCLFileHandler.m_nFid) 
	    );
  }                             
  // Readonly selectors:        

public:
  UInt_t getFid() const
  {
    return m_nFid;
  }
  // Mutators:

public:                       
  void setFid (UInt_t am_nFid)
  { 
    m_nFid = am_nFid;
  }
  // operations and overridables:

public:
  virtual   void operator() (int mask)   = 0;
  static  void CallbackRelay (ClientData pObject, int mask)  ;  
  void Set (int mask)  ;
  void Clear ()  ;
  

};

#endif
