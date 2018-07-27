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
// TCLTest.cpp:
//    Test of the TCL/TK object stuff:
//
// 

#include <config.h>
#include <tk.h>

#include "TCLApplication.h"
#include "TCLVariable.h"
#include "TCLProcessor.h"
#include <Iostream.h>
#include <string>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef HAVE_STD_NAMESPACE
using namespace std;
#endif

extern "C" {
  char* tcl_RcFileName;
}

class MyEcho : public CTCLProcessor
{
public:
  MyEcho() :
    CTCLProcessor("MyEcho", (CTCLInterpreter*)kpNULL)
  {}
 
  virtual int operator()(CTCLInterpreter& rInt,
			 CTCLResult&      rResult,
			 int              nArgs,
			 char**            pArgs);
};

class MyApp : public CTCLApplication
{

public:
  virtual int operator()();
protected:
  void RegisterCommands();
};

MyApp app;
CTCLApplication* gpTCLApplication = &app;

CTCLVariable Rcfile(std::string("tcl_rcFileName"),
		    kfFALSE);

MyEcho echocmd;

int MyApp::operator()()
{
  Rcfile.Bind(getInterpreter());
  Rcfile.Set("~/.wishrc", TCL_GLOBAL_ONLY);

  echocmd.Bind(getInterpreter());
  echocmd.Register();


  return TCL_OK;
}


int
MyEcho::operator()(CTCLInterpreter& rInt,
		   CTCLResult&      rResult,
		   int              nArgs,
		   char**            pArgs)
{
  for(int i = 0; i < nArgs; i++) {
    cerr << pArgs[i] << " ";
  }
  cerr << endl;

  return TCL_OK;
}









