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
// Created:     07/09/98 11:13
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#define STLUTILS_HAVE_LONG_ABS		1
#define STLUTILS_LOG_WHERE		1
#define STLUTILS_HAS_STR		1
#define STLUTILS_HAS_DATETIME		1
#define STLUTILS_HAS_STRPTIME		1
#define STLUTILS_HAS_USER		1
#define STLUTILS_HAS_USERGROUP		1
// #define STLUTILS_HAS_SEMUN		1 
// #define STLUTILS_HAS_CONST_IOSRDBUF	1  
#define STLUTILS_HAS_CONST_IOSRDSTATE   1
#define STLUTILS_HAS_CONST_IOSGOOD	1

/* #define STLUTILS_THREADS	1 */

#define STLUTILS_STRBUF_CONST_RDBUF
#define STLUTILS_STRBUF_PBASE

#define STLUTILS_HAS_USER	1

#if defined( STLUTILS_DEBUG )
#define STLUTILS_SAFETY_ON 1
#endif

#if defined( STLUTILS_THREADS )
#define _MIT_POSIX_THREADS  1
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

#define STLUTILS_LITTLE_ENDIAN	1   // ie 1234
// #define STLUTILS_BIG_ENDIAN  1   ie 4321 
#define STLUTILS_DO_NET_CONV	1   // ie need to do Net2Host & Host2Net


// Constants
#define STLUTILS_DIR_DELIM	    '/'
#define STLUTILS_BAD_FPOS_T	    LONG_MIN

// Macros
#define STLUTILS_UNUSED( x )

// #include <climits>
#include <stdcomp.h>
#include <cstddef>   // for NPOS

const size_t NPOS = (size_t)(-1);

#include <unistd.h> // for pid_t

//
// Detail Documentation
//
// Configuration Flags:
//
//  STLUTILS_HAVE_LONG_ABS	This platform has a long abs function
//			already defined.
//
//  STLUTILS_LOG_WHERE	Log macros inclue __FILE__ and __LINE__ so that
//			so that the source locations can be written to the
//			log.
//
// Types:
//
//  The following are need by PC Compilers to identify exports. They
//  are defined as 'nothing' for this platform.
//
//	STLUTILS_CLASS_T	Class Type:
//	STLUTILS_FUNCT_T	Function Type:
//	STLUTILS_GVAR_T	Global Variable Type:
//
//  The following are defined types to insure binary bit size compatiblity
//  across platforms.
//
//	STLUTILS_CHAR   char
//	STLUTILS_SCHAR  signed char
//	STLUTILS_UCHAR  unsigned char
//	STLUTILS_16	    short
//	STLUTILS_U16    unsigned short
//	STLUTILS_INT    int
//	STLUTILS_UINT   unsigned int
//	STLUTILS_32	    long
//	STLUTILS_U32    unsigned long
//	STLUTILS_FLOAT  float
//	STLUTILS_DOUBLE double
//	STLUTILS_BOOL   bool
//
// Constants:
//
//  STLUTILS_DIR_DELIM  the default directory delimiter.
//  STLUTILS_BAD_FPOS_T an invalid fpos_t value
//
// Macros:
//
//  STLUTILS_UNUSED( arg )	Some compilers output warnings for unused function
//			variables, while other compilers will output
//			an error if the variable is not declared. This
//			macro accomidates both. Just put your unused
//			args inside it.
//
//			Example: void doit( int need, char STLUTILS_UNSED( c ) )
//
// Documented Ver:  2.7
// 
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:19  houghton
// Changed Version Num to 5
//
// Revision 1.2  1998/08/13 10:54:02  houghton
// Added STLUTILS_STRBUF_PBASE define.
//
// Revision 1.1  1998/07/20 11:28:20  houghton
// Initial Version.
//
//
#endif // ! def _StlUtilsArch_hh_ 

