#ifndef _StlUtilsArch_hh_
#define _StlUtilsArch_hh_
//
// File:        StlUtilsArch.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     03/03/97 09:26
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#define _ALL_SOURCE_

/* #define STLUTILS_HAVE_LONG_ABS 1 */
#define STLUTILS_HAS_STRPTIME 1
#define STLUTILS_LOG_WHERE 1
#define STLUTILS_HAS_STR 1
#define STLUTILS_HAS_DATETIME 1
/* #define STLUTILS_HAS_SEMUN		1 */
/* #define STLUTILS_HAS_CONST_IOSRDSTATE	    1 */
/* #define STLUTILS_HAS_CONST_IOSGOOD	    1 */

/* #define STLUTILS_THREADS	1 */

#define STLUTILS_STRBUF_CONST_RDBUF
#define STLUTILS_STRBUF_PBASE

#define STLUTILS_HAS_USER	1

#if defined( STLUTILS_DEBUG )
#define STLUTILS_SAFETY_ON 1
#endif

#if defined( STLUTILS_THREADS )
#include <pthread.h>
#endif

// Types
#define STLUTILS_CLASS_T
#define STLUTILS_FUNCT_T
#define STLUTILS_GVAR_T

#define STLUTILS_CHAR   char
#define STLUTILS_SCHAR  signed char
#define STLUTILS_UCHAR  unsigned char
#define STLUTILS_16	    short
#define STLUTILS_U16    unsigned short
#define STLUTILS_INT    int
#define STLUTILS_UINT   unsigned int
#define STLUTILS_32	    long
#define STLUTILS_U32    unsigned long
#define STLUTILS_FLOAT  float
#define STLUTILS_DOUBLE double
#define STLUTILS_BOOL   bool

// Constants
#define STLUTILS_DIR_DELIM	    '/'
#define STLUTILS_BAD_FPOS_T	    LONG_MIN

#define NPOS ((size_t)-1)
// Macros
#define STLUTILS_UNUSED( x ) x

#include <AnsiBool.hh>
#include <unistd.h> // for pid_t


// Revision Log:
//
// $Log$
// Revision 3.4  1997/09/17 11:09:08  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/07/18 19:37:52  houghton
// Added STLUTILS_HAS_SEMUN (not defined)
// Added STLUTILS_HAS_CONST_IOSRDSTATE (not defined)
// Added STLUTILS_HAS_CONST_IOSGOOD (not defined)
//
// Revision 3.2  1997/04/04 20:55:33  houghton
// Added include unistd.h (for pid_t).
//
// Revision 3.1  1997/03/21 15:44:05  houghton
// Changed base version to 3
//
// Revision 1.1  1997/03/03 19:06:38  houghton
// Initial version.
//
//
#endif // ! def _StlUtilsArch_hh_ 

