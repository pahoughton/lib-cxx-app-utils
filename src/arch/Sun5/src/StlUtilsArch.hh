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


#if !defined( __SunOS_5_8 )
#define STLUTILS_HAVE_LONG_ABS 1
#endif

#define STLUTILS_HAVE_LONG_LONG	1
#define STLUTILS_LOG_WHERE 1
#define STLUTILS_HAS_STR 1
#define STLUTILS_HAS_DATETIME 1
#define STLUTILS_HAS_USER 1
#define STLUTILS_HAS_USERGROUP 1
#define STLUTILS_HAS_STRPTIME 1
#define STLUTILS_HAS_IOSTREAM_SENTRY 1
// #define STLUTILS_HAS_SEMUN		1 
// #define STLUTILS_THREADS	1 

// #define STLUTILS_STRBUF_PBASE 1

// Standards
// #define STDCXX_PARTIAL_SPECIALIZATION	1
#define STLUTILS_HAS_CONST_IOSRDBUF	1 
#define STLUTILS_HAS_CONST_IOSGOOD	1 
#define STLUTILS_HAS_CONST_IOSRDSTATE	1 
// #define STLUTILS_STD_ITERATORS		1
#define STLUTILS_STRBUF_CONST_RDBUF	const
#define STLUTILS_RELOPS_BROKEN		1
#define STLUTILS_STD_STREAMBUF_STUPID	1
// #define STLUTILS_STR_UNSIGNED		1

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

#define STLUTILS_S16_T		short
#define STLUTILS_U16_T		unsigned short

#define STLUTILS_S32_T		long
#define STLUTILS_U32_T		unsigned long

#define STLUTILS_S64_T		long long
#define STLUTILS_U64_T		unsigned long long

#define STLUTILS_32_TIME_T	long
/* #define STLUTILS_64_TIME_T  */
#define STLUTILS_U32_SIZE_T	STLUTILS_LONG_U32_T
#define STLUTILS_S32_SSIZE_T	STLUTILS_LONG_S32_T

#define STLUTILS_ENDIAN	     1234
// #define STLUTILS_LITTLE_ENDIAN	1   // ie 4321
#define STLUTILS_BIG_ENDIAN	1   // ie 1234
#define STLUTILS_DO_NET_CONV	0   // ie do NOT need to do Net2Host & Host2Net

// Constants
#define STLUTILS_DIR_DELIM	    '/'
#define STLUTILS_BAD_FPOS_T	    LONG_MIN

#define NPOS ((size_t)-1)
// Macros
#define STLUTILS_UNUSED( x )

// #include <climits>
using namespace std;

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
// Revision 5.9  2001/08/07 22:37:04  houghton
// *** empty log message ***
//
// Revision 5.8  2001/08/07 21:47:26  houghton
// *** empty log message ***
//
// Revision 5.7  2001/08/07 19:45:50  houghton
// *** empty log message ***
//
// Revision 5.6  2001/08/07 19:31:49  houghton
// *** empty log message ***
//
// Revision 5.5  2001/08/06 21:09:12  houghton
// *** empty log message ***
//
// Revision 5.4  2001/07/28 01:15:00  houghton
// *** empty log message ***
//
// Revision 5.3  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.2  2000/05/25 17:07:25  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:21  houghton
// Changed Version Num to 5
//
// Revision 4.4  1999/10/07 13:56:43  houghton
// Added STLUTILS_ENDIAN.
//
// Revision 4.3  1999/05/09 13:07:41  houghton
// Added long long support.
//
// Revision 4.2  1997/09/19 11:22:01  houghton
// Cleanup
// Added portable types (STLUTILS*_T).
//
// Revision 4.1  1997/09/17 15:13:27  houghton
// Changed to Version 4
//
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

