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

static const char* Copyright = "(C) Copyright Michigan State University 2002, All rights reserved";   
//////////////////////////CInvalidPacketStateException.cpp file////////////////////////////////////
#include <config.h>
#include "CInvalidPacketStateException.h"                  

#ifdef HAVE_STD_NAMESPACE
using namespace std;
#endif
/*!
   Default constructor.  This is called when declarations of the form e.g.:
   -  CInvalidPacketStateException  object;
   are performed.
   \param
*/
CInvalidPacketStateException::CInvalidPacketStateException (bool WasOpen,
						       const char* pszAction) :
  CReadoutException(pszAction),
  m_nWasOpen(WasOpen)
{
   BuildReasonText();
} 
/*!
   Copy construction. This is invoked when e.g. an object is passed by value
   to a function.  The copy constructor makes a clone of the rhs object.
   \param rhs - Reference to the objet from which this copy will be 
                constructed.
*/
CInvalidPacketStateException::CInvalidPacketStateException(const CInvalidPacketStateException& rhs) :
  CReadoutException(rhs),
  m_nWasOpen(rhs.m_nWasOpen)
{
   BuildReasonText();
}
/*!
   Assignment operation.  This member function supports assignment of
   an object of this class to an object of the same class.
   \param rhs - The right hand side of the assignment to *this.
   \returns  - a reference to *this
*/
CInvalidPacketStateException& 
CInvalidPacketStateException::operator= (const CInvalidPacketStateException& rhs)
{ 
    if (this != &rhs) {
       CReadoutException::operator= (rhs);
       m_nWasOpen    = rhs.m_nWasOpen;
       BuildReasonText();
    }
    return *this;
}
/*!  
  Equality comparison.
  */
int
CInvalidPacketStateException::operator==(const CInvalidPacketStateException& rhs)
{
  return ( CReadoutException::operator==(rhs)                   &&
	  (m_nWasOpen     == rhs.m_nWasOpen));  // Note that ReasonText is computed from
						// object state variables.
}

/*!
    Returns the state of the open flag in the segment.
    cast to integer.

*/
int 
CInvalidPacketStateException::ReasonCode() const  
{
  return (int)m_nWasOpen;
}  

/*!
    Returns a text string which describes why the exception 
    was thrown.

*/
const char* 
CInvalidPacketStateException::ReasonText() const  
{
  
  return m_sReasonText.c_str();
}
/*!
   Re-computes the reason text from the object's member variables.  The implicit
   inputs to this function include:
   - m_sWasOpen - True if the state was open.
   - getAction() returns the action being performed at the time the exception was 
      detected.
*/
void
CInvalidPacketStateException::BuildReasonText()
{
   m_sReasonText  = "Incorrect handling of a readout packet: ";
   m_sReasonText += getAction();
   m_sReasonText += "requires that the packet be ";
   m_sReasonText += (m_nWasOpen ? " closed.\n " : " open.\n ");
   m_sReasonText += "The actual state was: ";
   m_sReasonText += (m_nWasOpen ? "open.\n" : " closed.\n");

}
