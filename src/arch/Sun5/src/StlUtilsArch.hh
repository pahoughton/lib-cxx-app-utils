#ifndef _StlUtilsArch_hh_
#define _StlUtilsArch_hh_
//
// File:        StlUtilsArch.hh
// Project:	StlUtils
// Desc:        
//
//  Architecture specific header for Sun5
//
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     07/17/97 11:04
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#define __EXTENSIONS__

// Configuration Flags

#define STLUTILS_HAVE_LONG_ABS 1
#define STLUTILS_LOG_WHERE 1
#define STLUTILS_HAS_STR 1
#define STLUTILS_HAS_DATETIME 1
#define STLUTILS_HAS_USER 1
#define STLUTILS_HAS_USERGROUP 1
#define STLUTILS_HAS_STRPTIME 1
/* #define STLUTILS_HAS_SEMUN		1 */
/* #define STLUTILS_HAS_CONST_IOSRDBUF	    1 */
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
#define _MIT_POSIX_THREADS  1
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
#define STLUTILS_UNUSED( x )

#include <AnsiBool.hh>
// #include <climits>
#include <cstddef>

extern "C" int getrusage(int who, struct rusage * rusage);

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
// Revision Log:
//
// $Log$
// Revision 3.2  1997/09/17 11:09:17  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/07/25 12:26:25  houghton
// Changed version number to 3.
//
// Revision 1.1  1997/07/18 19:55:31  houghton
// Initial Version.
//
//
//
#endif // ! def _StlUtilsArch_hh_ 

