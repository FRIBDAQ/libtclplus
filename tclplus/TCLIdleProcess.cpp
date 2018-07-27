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
//
//  TCLIdleProcess.cpp:
//     This file provides implementions for the non trivial member functions
//     of the CTCLIdleProcess class.  This class provides an object oriented
//     encapsulation of the Tk Idle process object.  Idle processes are
//     called once and only once when the Tk Event loop has no events to
//     process.
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
/////////////////////////////////////////////////////////////////////////////

#include <config.h>

using namespace std;

#include "TCLIdleProcess.h"


