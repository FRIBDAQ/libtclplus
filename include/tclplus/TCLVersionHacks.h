/*
    This header provides centralizes as many hacks as we can concerning
    TCL API version differences.
*/
#ifndef TCLVERSIONHACKS_H
#define TCLVERSIONHACKS_H

#include <tcl.h>
#include <stdlib.h>


// tclConstCharPtr  - A typedef that's either char* or const char* depending
// on the TCL Version:

#if (TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >3))
typedef const char* tclConstCharPtr;
#else
typedef char* tclConstCharPtr;
#endif

// Some older versions of TCL failed to Tcl_Free everything on unix:


static inline void
tclSplitListFree(void* pointer)
{
#if defined(WIN32) || (TCL_MAJOR_VERSION > 8) || \
    ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION > 3))
  Tcl_Free((char*)pointer);
#else
  free(pointer);
#endif
}

#endif
