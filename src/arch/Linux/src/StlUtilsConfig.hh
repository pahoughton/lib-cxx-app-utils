#ifndef _ClueConfig_hh_
#define _ClueConfig_hh_
//
// File:        ClueConfig.hh
// Project:	Clue
// Desc:        
//
//  Architecture dependant configuration values for Linux (2.0)
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     06/16/95 08:01
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

// Configuration Flags
#define _BSD_SOURCE	1
#define _SVID_SOURCE	1

#define CLUE_HAVE_LONG_ABS 1
#define CLUE_LOG_WHERE 1
/* #define CLUE_THREADS	1 */

#define CLUE_STRBUF_CONST_RDBUF const

#define CLUE_HAS_USER	1

#if defined( CLUE_DEBUG )
#define CLUE_SAFETY_ON 1
#endif

#if defined( CLUE_THREADS )
#define _MIT_POSIX_THREADS  1
#include <pthread.h>
#endif


// Types
#define CLUE_CLASS_T
#define CLUE_FUNCT_T
#define CLUE_GVAR_T

#define CLUE_CHAR   char
#define CLUE_SCHAR  signed char
#define CLUE_UCHAR  unsigned char
#define CLUE_16	    short
#define CLUE_U16    unsigned short
#define CLUE_INT    int
#define CLUE_UINT   unsigned int
#define CLUE_32	    long
#define CLUE_U32    unsigned long
#define CLUE_FLOAT  float
#define CLUE_DOUBLE double
#define CLUE_BOOL   bool

// Constants
#define CLUE_DIR_DELIM	    '/'
#define CLUE_BAD_FPOS_T	    LONG_MIN

// Macros
#define CLUE_UNUSED( x )

// #include <climits>
#include <stddef>   // for NPOS

#include <ClueVersion.hh>
#include <ClassVersion.hh>

//
// Detail Documentation
//
// Configuration Flags:
//
//  CLUE_HAVE_LONG_ABS	This platform has a long abs function
//			already defined.
//
//  CLUE_LOG_WHERE	Log macros inclue __FILE__ and __LINE__ so that
//			so that the source locations can be written to the
//			log.
//
// Types:
//
//  The following are need by PC Compilers to identify exports. They
//  are defined as 'nothing' for this platform.
//
//	CLUE_CLASS_T	Class Type:
//	CLUE_FUNCT_T	Function Type:
//	CLUE_GVAR_T	Global Variable Type:
//
//  The following are defined types to insure binary bit size compatiblity
//  across platforms.
//
//	CLUE_CHAR   char
//	CLUE_SCHAR  signed char
//	CLUE_UCHAR  unsigned char
//	CLUE_16	    short
//	CLUE_U16    unsigned short
//	CLUE_INT    int
//	CLUE_UINT   unsigned int
//	CLUE_32	    long
//	CLUE_U32    unsigned long
//	CLUE_FLOAT  float
//	CLUE_DOUBLE double
//	CLUE_BOOL   bool
//
// Constants:
//
//  CLUE_DIR_DELIM  the default directory delimiter.
//  CLUE_BAD_FPOS_T an invalid fpos_t value
//
// Macros:
//
//  CLUE_UNUSED( arg )	Some compilers output warnings for unused function
//			variables, while other compilers will output
//			an error if the variable is not declared. This
//			macro accomidates both. Just put your unused
//			args inside it.
//
//			Example: void doit( int need, char CLUE_UNSED( c ) )
//
// Documented Ver:  2.7
// 
// Revision Log:
//
// $Log$
// Revision 3.2  1996/11/19 12:29:19  houghton
// Added CLUE_HAS_USER define.
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
// Change: Defined CLUE_LOG_WHERE to log source file location.
//
// Revision 2.4  1996/05/18 12:57:47  houghton
// Added CLUE_FLOAT
// Cleanup.
//
// Revision 2.3  1996/04/27 13:17:16  houghton
// Changed to use threads.
// Added macro CLUE_UNUSED to eliminate g++ compile errors for unused
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
//
#endif // ! def _UtilsConfig_hh_ 

