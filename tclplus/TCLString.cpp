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

static const char* Copyright = "(C) Copyright Michigan State University 2015, All rights reserved";
//  CTCLString.cpp
// Encapsulates the TCL dynamic string type.
// NOTE: This is present for completeness and
// because some TCL utilities may require it.
// For the most part, the user should instead use
// the standard C++ std::string data type for
// dynamic strings as these are even portable outside
// the TCL/Tk environment.
//
//
//   Author:
//      Ron Fox
//      NSCL
//      Michigan State University
//      East Lansing, MI 48824-1321
//      mailto:fox@nscl.msu.edu
//
//////////////////////////.cpp file///////////////////////////////////////////

//
// Header Files:
//
#include <config.h>
#include "TCLString.h"                               

using namespace std;


// Functions for class CTCLString

//////////////////////////////////////////////////////////////////////////
//
//  Function:   
//    CTCLString& Append ( const std::string& rString, Int_t nLength=-1 )
//  Operation Type:
//     mutator
//
CTCLString& 
CTCLString::Append(const char* pString, TCLPLUS::Int_t nLength) 
{
// Appends the first nLength characters of contents of the
// rString parameter to the TCL Dstring object
// encapsulated by this class.  If nLength is zero,
// the entire string is appended.
//
//  Formal Parameters:
//       const CTCLString& rString
//       const std::string& rString
//       const char* rString
//       const Tcl_DString* pString:
//            Refers to the string to append to this.
//            These are alternatives, not conjunctions.
//       Int_t nLength = -1;
//            Number of chars to append (defaults to
//            entire string).
//
// Returns itself.

  Tcl_DStringAppend(&m_String, pString, nLength);
  return *this;
  
}
//////////////////////////////////////////////////////////////////////////
//
//  Function:   
//    CTCLString& AppendElement ( const CTCLString& rRhs )
//  Operation Type:
//     mutator.
//
CTCLString& 
CTCLString::AppendElement(const char* pRhs) 
{
// Converts the right hand side of the string to a proper list element
// and appends it to the string.  Returns *this.
// Note that the parameters below are alternative
// formulations of the rhs parameter:
//
// Formal Parameters:
//    const CTCLString&   rRhs,
//    const char*              pRhs,
//    const std::string&     rRhs:
//              The string to append as a list element
//              to this.
// Returns:
//   *this
//  

  Tcl_DStringAppendElement(&m_String, pRhs);
  return *this;

}
/*!
   Append a double as an element of a string.
  
   \param value   - The value to append.
   \param pFormat - an sprintf formatting string (defaults to "%f")
                    that describes how the float is to be formatted.
   \return CTCLString&
   \retval Reference to *this.
*/
CTCLString&
CTCLString::AppendElement(TCLPLUS::DFloat_t value, const char* pFormat)
{
  char buffer[100];
  sprintf(buffer, pFormat, value);
  return AppendElement(buffer);

}

/*!
   Append an integer as element of a list
   
   \param value   - The value to append
   \param pFormat - A sprintf formatting string (defaults to "%i")
                    that describes how the int should be formatted.

   \return CTCLString&
   \retval Reference to *this
*/
CTCLString&
CTCLString::AppendElement(long value, const char* pFormat) 
{
  char buffer[100];
  sprintf(buffer, pFormat, value);
  return AppendElement(buffer);

}
//////////////////////////////////////////////////////////////////////////
//
//  Function:   
//    CTCLString& StartSublist (  )
//  Operation Type:
//     mutator
//
CTCLString& 
CTCLString::StartSublist() 
{
// Appends a sublist begin character to
// the string "{".
// 
// Returns:
//   *this.

  Tcl_DStringStartSublist(&m_String);
  return *this;

}
//////////////////////////////////////////////////////////////////////////
//
//  Function:   
//    CTCLString& EndSublist (  )
//  Operation Type:
//     mutator
//
CTCLString& 
CTCLString::EndSublist() 
{
// Ends a sublist by appending e.g. "}".
//
// Returns
//   *this

  Tcl_DStringEndSublist(&m_String);
  return *this;

}

//////////////////////////////////////////////////////////////////////////
//
//  Function:   
//    UInt_t& Length (  )
//  Operation Type:
//     selector.
//
TCLPLUS::UInt_t
CTCLString::Length() const 
{
// Returns the number of characters in the string.
// Exceptions:  

  return Tcl_DStringLength(&m_String);
}
//////////////////////////////////////////////////////////////////////////
//
//  Function:   
//    CTCLString& Truncate ( UInt_t nNewLength )
//  Operation Type:
//     mutator
//
CTCLString& 
CTCLString::Truncate(TCLPLUS::UInt_t nNewLength) 
{
// Shortens the string to the designated number
// of characters.
//
// Formal Parameters:
//     UInt_t nNewLength:
//         New number of characters which will be
//         contained by the string.
//  Returns:
//      *this

  Tcl_DStringTrunc(&m_String, nNewLength);
  return *this;

}
//////////////////////////////////////////////////////////////////////////
//
//  Function:   
//    Bool_t isCommand (  )
//  Operation Type:
//     Parser
//
TCLPLUS::Bool_t 
CTCLString::isCommand() const 
{
// Determines if the string constitutes a complete command

  TCLPLUS::Int_t i =  (Tcl_CommandComplete(Tcl_DStringValue(&m_String)));
  return ((i == 1) ? TCLPLUS::kfTRUE : TCLPLUS::kfFALSE);
}
//////////////////////////////////////////////////////////////////////////
//
//  Function:   
//    Bool_t Match ( const CTCLString& rPattern )
//  Operation Type:
//     Parser
//
TCLPLUS::Bool_t 
CTCLString::Match(const char* pPattern) const 
{
// Returns kfTRUE if the string matches
// pattern using glob-style rules for pattern
// matching.
//
//  Formal Parameters:
//      Note that these are alternative parameter
//      representations:
//          const CTCLString& rPattern
//          const char*            pPattern
//          const std::string&   rPattern:
//              Pattern to match.
//
//  Returns:
//       kfTRUE  - if matched.
//       kfFALSE - if didn't match.
// Exceptions:  

 TCLPLUS::Int_t i = Tcl_StringMatch(Tcl_DStringValue(&m_String),
			   (char*)pPattern);
 return ((i == 1) ? TCLPLUS::kfTRUE : TCLPLUS::kfFALSE);

}

//////////////////////////////////////////////////////////////////////////
//
//  Function:   
//    CTCLString operator+ ( const CTCLString& rRhs )
//  Operation Type:
//     concatenate
//
CTCLString 
CTCLString::operator+(const CTCLString& rRhs) 
{
// Returns a temporary operator which is the 
// concatenation of this and the right hand
// side.  This is like:
//    CTCLString temp = this;
//    temp+= rhs;
//    return temp;
//  and in fact is implemented that way,
//  rhs has all of the parameter possibilities
//  of Append().
//

  CTCLString temp(*this);
  temp += rRhs;
  return temp;

}
//////////////////////////////////////////////////////////////////////////
//
// Function:
//     void DoAssign(const CTCLString& rRhs)
// Operation Type:
//     protected utility.
//
void
CTCLString::DoAssign(const CTCLString& rRhs)
{
  Tcl_DStringFree(&m_String);
  Tcl_DStringInit(&m_String);
  *this += rRhs;
}
