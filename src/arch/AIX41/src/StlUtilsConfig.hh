#ifndef _ClueConfig_hh_
#define _ClueConfig_hh_
//
// File:        ClueConfig.hh
// Project:	Clue
// Desc:        
//
//  Architecture dependant configuration values for AIX41
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     06/16/95 08:01
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

// Configuration Flags

#define _ALL_SOURCE_

/* #define CLUE_HAVE_LONG_ABS 1*/
#define CLUE_LOG_WHERE 1
/* #define CLUE_THREADS	1 */

#define CLUE_STRBUF_CONST_RDBUF
#define CLUE_STRBUF_PBASE

#if defined( CLUE_THREADS )
#include <pthread.h>
#endif

#if defined( CLUE_DEBUG )
#define CLUE_SAFETY_ON 1
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
#define CLUE_DIR_DELIM '/'
#define CLUE_BAD_FPOS_T	    LONG_MIN

#if defined( NPOS )
#error "NPOS already defined"
#else
#define NPOS ((size_t)-1)
#endif

// Macros
#define CLUE_UNUSED( x ) x

#include <AnsiBool.hh>
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
// Revision 1.7  1996/11/06 18:09:27  houghton
// Rework and verified header comments.
// Rework orginization of defines and macros.
//
// Revision 1.6  1996/10/22 22:07:46  houghton
// Change: Defined CLUE_LOG_WHERE to log source file location.
//
// Revision 1.5  1996/05/21 10:32:21  houghton
// Added CLUE_FLOAT.
//
// Revision 1.4  1996/05/18 12:57:01  houghton
// Added include climits
// Added CLUE_BAD_FPOS_T
//
// Revision 1.3  1996/05/03 16:14:55  houghton
// AIX port fixes.
//
// Revision 1.2  1996/04/27 13:15:29  houghton
// Changed to make sure pthreads.h is included first.
//
// Revision 1.1  1996/02/29 19:10:22  houghton
// Initial Version
//
// Revision 2.1  1995/11/10 12:43:23  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  16:04:10  houghton
// Revised
//
//
#endif // ! def _UtilsConfig_hh_ 

