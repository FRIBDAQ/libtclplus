
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
static const char* Copyright= "(C) Copyright Michigan State University 2002, All rights reserved";
#include <config.h>
#include "CNoSuchObjectException.h"
#include <string.h>

#ifdef HAVE_STD_NAMESPACE
using namespace std;
#endif

const char*
CNoSuchObjectException::ReasonText() const
{
  return m_sReasonText.c_str();
}

void
CNoSuchObjectException::UpdateReasonText()
{
  m_sReasonText = "No such object\n";
  m_sReasonText += "Key was: ";
  m_sReasonText += m_sName;
}
