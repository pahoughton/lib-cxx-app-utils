#ifndef _StlUtilsArch_hh_
#define _StlUtilsArch_hh_
//
// File:        StlUtilsArch.hh
// Project:	StlUtils
// Desc:        
//
//  Architecture specific header for Linux
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     01/17/97 11:06
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

// Configuration Flags
#define _BSD_SOURCE	1
#define _SVID_SOURCE	1

#define STDCXX_PARTIAL_SPECIALIZATION	1

// #define STLUTILS_HAS_BASENAME		1
#define STLUTILS_HAVE_LONG_ABS		1
#define STLUTILS_LOG_WHERE		1

#define STLUTILS_HAS_TM_GMTOFF		1
#define STLUTILS_HAS_RELOPS		1
#define STLUTILS_HAS_STR		1
#define STLUTILS_HAS_DATETIME		1
#define STLUTILS_HAS_STRPTIME		1
#define STLUTILS_HAS_USER		1
#define STLUTILS_HAS_USERGROUP		1
// #define STLUTILS_HAS_SEMUN		1 
#define STLUTILS_HAS_CONST_IOSRDBUF	1 
#define STLUTILS_HAS_CONST_IOSRDSTATE   1
#define STLUTILS_HAS_CONST_IOSGOOD	1

/* #define STLUTILS_THREADS	1 */

#define STLUTILS_STRBUF_CONST_RDBUF const

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
#define NPOS			    static_cast<size_t>(-1)

// Macros
#define STLUTILS_UNUSED( x )

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
// Revision 4.4  1999/05/14 11:34:01  houghton
// Port(Linux): port for Gnu Libc 2
//
// Revision 4.3  1998/10/13 16:32:08  houghton
// Reworked for latest version of Compiler.
//
// Revision 4.2  1997/09/19 11:21:53  houghton
// Cleanup
// Added portable types (STLUTILS*_T).
//
// Revision 4.1  1997/09/17 15:13:17  houghton
// Changed to Version 4
//
// Revision 3.7  1997/09/17 11:09:10  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.6  1997/08/08 13:25:11  houghton
// Adde STLUTILS_HAS_STRPTIME.
//
// Revision 3.5  1997/07/18 19:38:40  houghton
// Cleanup
// Added STLUTILS_HAS_SEMUN (defined)
// Added STLUTILS_HAS_CONST_IOSRDSTATE (defined)
// Added STLUTILS_HAS_CONST_IOSGOOD (defined)
//
// Revision 3.4  1997/04/04 20:55:37  houghton
// Added include unistd.h (for pid_t).
//
// Revision 3.3  1997/03/03 19:08:17  houghton
// Added defines for HAS_USER and HAS_USERGROUP.
//
// Revision 3.2  1997/03/02 13:20:51  houghton
// Added defineds for Str and DateTime.
//
// Revision 3.1  1997/01/18 17:40:59  houghton
// Inital Version based on old StlUtilsConfig.hh. Now StlUtilsConfig.hh is not
//     arch specific and has been moved to 'StlUtils/'. It includes this header
//     for arch specfic info.
//
// Revision 3.2  1996/11/19 12:29:19  houghton
// Added STLUTILS_HAS_USER define.
//
// Revision 3.1  1996/11/14 01:25:05  houghton
// Changed to Release 3
//
// Revision 2.9  1996/11/06 18:09:37  houghton
// Rework orginization of defines and macros.
//
// Revision 2.8  1996/11/04 14:35:19  houghton
// Added include stddef to get NPOS
//
// Revision 2.7  1996/10/28 12:12:27  houghton
// Edit Documentation.
//
// Revision 2.6  1996/10/28 12:10:50  houghton
// Cleanup: reorder defines and macros.
// Added Documentation.
//
// Revision 2.5  1996/10/22 22:08:00  houghton
// Change: Defined STLUTILS_LOG_WHERE to log source file location.
//
// Revision 2.4  1996/05/18 12:57:47  houghton
// Added STLUTILS_FLOAT
// Cleanup.
//
// Revision 2.3  1996/04/27 13:17:16  houghton
// Changed to use threads.
// Added macro STLUTILS_UNUSED to eliminate g++ compile errors for unused
//   function/method arguments.
// Cleanup.
//
// Revision 2.2  1996/02/29 19:10:55  houghton
// Added define for abs(long)
//
// Revision 2.1  1995/11/10 12:46:43  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  15:29:33  houghton
// Revised
//
// Revision Log:
//
// $Log$
// Revision 4.4  1999/05/14 11:34:01  houghton
// Port(Linux): port for Gnu Libc 2
//
// Revision 4.3  1998/10/13 16:32:08  houghton
// Reworked for latest version of Compiler.
//
// Revision 4.2  1997/09/19 11:21:53  houghton
// Cleanup
// Added portable types (STLUTILS*_T).
//
// Revision 4.1  1997/09/17 15:13:17  houghton
// Changed to Version 4
//
// Revision 3.7  1997/09/17 11:09:10  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.6  1997/08/08 13:25:11  houghton
// Adde STLUTILS_HAS_STRPTIME.
//
// Revision 3.5  1997/07/18 19:38:40  houghton
// Cleanup
// Added STLUTILS_HAS_SEMUN (defined)
// Added STLUTILS_HAS_CONST_IOSRDSTATE (defined)
// Added STLUTILS_HAS_CONST_IOSGOOD (defined)
//
// Revision 3.4  1997/04/04 20:55:37  houghton
// Added include unistd.h (for pid_t).
//
// Revision 3.3  1997/03/03 19:08:17  houghton
// Added defines for HAS_USER and HAS_USERGROUP.
//
// Revision 3.2  1997/03/02 13:20:51  houghton
// Added defineds for Str and DateTime.
//
// Revision 3.1  1997/01/18 17:40:59  houghton
// Inital Version based on old StlUtilsConfig.hh. Now StlUtilsConfig.hh is not
//     arch specific and has been moved to 'StlUtils/'. It includes this header
//     for arch specfic info.
//
//
#endif // ! def _StlUtilsArch_hh_ 

