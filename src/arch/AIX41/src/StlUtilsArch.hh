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

//
// the AIX compiler does not support 'typename'
//
#define typename

/* #define STLUTILS_HAVE_LONG_ABS 1 */
#define STLUTILS_HAS_STRPTIME	1
#define STLUTILS_LOG_WHERE	1
#define STLUTILS_HAS_STR	1
#define STLUTILS_HAS_DATETIME	1
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

#define STLUTILS_CHAR_8_T	char
#define STLUTILS_CHAR_S8_T	signed char
#define STLUTILS_CHAR_U8_T	unsigned char
#define STLUTILS_SHORT_S16_T	short
#define STLUTILS_SHORT_U16_T    unsigned short
#define STLUTILS_SINT_T		int
#define STLUTILS_UINT_T         unsigned int
#define STLUTILS_LONG_S32_T	long
#define STLUTILS_LONG_U32_T     unsigned long
#define STLUTILS_FLOAT_FP32_T   float
#define STLUTILS_DOUBLE_FP64_T  double
#define STLUTILS_BOOL_T		bool

#define STLUTILS_32_TIME_T	long
/* #define STLUTILS_64_TIME_T  */
#define STLUTILS_U32_SIZE_T	STLUTILS_LONG_U32_T
#define STLUTILS_S32_SSIZE_T	STLUTILS_LONG_S32_T

// #define STLUTILS_LITTLE_ENDIAN	1   ie 1234
#define STLUTILS_BIG_ENDIAN	1   // ie 4321 
#define STLUTILS_DO_NET_CONV	0   // ie do NOT need to do Net2Host & Host2Net


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
// Revision 5.1  2000/05/25 10:33:19  houghton
// Changed Version Num to 5
//
// Revision 4.3  1998/10/13 15:25:22  houghton
// Added define for 'typename'.
//
// Revision 4.2  1997/09/19 11:21:49  houghton
// Cleanup
// Added portable types (STLUTILS*_T).
//
// Revision 4.1  1997/09/17 15:13:14  houghton
// Changed to Version 4
//
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

