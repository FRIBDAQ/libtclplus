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


/*
**++
**  FACILITY:
**
**      Data types
**
**  ABSTRACT:
**
**      Data types for the host processor.
**
**  AUTHORS:
**
**      Ron Fox
**
**
**  CREATION DATE:     7-Oct-1987
**
**  MODIFICATION HISTORY:
**--
**/

#ifndef TCLPLUSTYPES_H
#define TCLPLUSTYPES_H


#include <sys/types.h>

#if __cplusplus
#if __cplusplus > 199711L // i.e. C++98
// stdint.h is deprecated as of C++11 in favor of <cstdint>
// The difference is that the types are brought into the std namespace.
// We can mimic the old behavior by including cstdint and then bringing
// them into the global scope with the using operator. This is a kludge 
// but is the best solution for the moment.

#include <cstdint>
using std::int8_t;
using std::uint8_t;
using std::int16_t;
using std::uint16_t;
using std::int32_t;
using std::uint32_t;
using std::int64_t;
using std::uint64_t;
#else
// When compiled with a C++ compiler that is not C++11 compatible
// cstdint does not exist. Furthermore, stdint.h only includes the 
// limit macros if __STDC_LIMIT_MACROS variables is defined. 
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#endif /* __cplusplus */
#else
// macros are part of the c standard
# include <stdint.h>
#endif /* C++ or C */


namespace TCLPLUS {

	typedef int Int_t;
	typedef unsigned int UInt_t;
	
	typedef short Short_t;
	typedef unsigned short UShort_t;
	
	typedef long Long_t;
	typedef unsigned long ULong_t;
	
	typedef float Float_t;
	typedef double DFloat_t;
	
	
	
	typedef char Char_t;
	typedef unsigned char UChar_t;
	
	typedef char (*Textsz_t);             // Null terminated string.
	typedef UInt_t Size_t;
	
	typedef void (*Address_t);           // Typical pointer.
	
	static const Address_t kpNULL = (Address_t)0;  // Null pointer.
	
	
	typedef UChar_t Bool_t;
	static const Bool_t kfTRUE = 0xff; // TRUE boolean.
	static const Bool_t kfFALSE= 0;	  // FALSE boolean. 
	
}

#define __DAQTYPES_H
#endif
