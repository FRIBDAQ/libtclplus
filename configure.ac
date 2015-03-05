AC_PREREQ(2.61)
AC_INIT(libtclplus, 2.0-000, fox@nscl.msu.edu)

AC_CONFIG_SRCDIR([tclplus/TCLInterpreter.cpp])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.11 subdir-objects])


# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LIBTOOL

LT_INIT
AC_SUBST([LIBTOOL_DEPS])

# Makefile exports:
SOVERSION="2:0:0"
AC_SUBST(SOVERSION)

# specfic checks
AC_HEADER_STDC


##
# C++ unit test framework, defines:
#   CPPUNIT_CFLAGS - Compilation flags.
#   CPPUNIT_LIBS   - ld flags.
#

AM_PATH_CPPUNIT

##
#  Tcl this defines
#  TCL_DEFS - flags used to compile Tcl (don't need these usually).
#  TCL_LIBS - ld flags for building with Tcl libraries.
#  TCL_CPPFLAGS - Compilation flags for C/C++
#  tclsh    - tclsh.

AX_TCL

##
#  Define pThread stuff.. (we want to build the libs threadable):
#
# PTHREAD_LIBS    - linker flags.
# PTHREAD_CLFAGS - compilation flags.
# PTHREAD_CC      - C compiler required (not sure how to replace that for autotools makefiles now.
#                   besides we compile C++ code....
#
AX_PTHREAD


# what to generate
AC_CONFIG_FILES([Makefile
                 exception/Makefile
                 tclplus/Makefile])

# do it
AC_OUTPUT
