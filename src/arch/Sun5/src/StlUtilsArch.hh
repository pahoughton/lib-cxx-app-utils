#ifndef _ClueArch_hh_
#define _ClueArch_hh_
//
// File:        ClueArch.hh
// Project:	Clue
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

#define CLUE_HAVE_LONG_ABS 1
#define CLUE_LOG_WHERE 1
#define CLUE_HAS_STR 1
#define CLUE_HAS_DATETIME 1
#define CLUE_HAS_USER 1
#define CLUE_HAS_USERGROUP 1
#define CLUE_HAS_STRPTIME 1
/* #define CLUE_HAS_SEMUN		1 */
/* #define CLUE_HAS_CONST_IOSRDBUF	    1 */
/* #define CLUE_HAS_CONST_IOSRDSTATE	    1 */
/* #define CLUE_HAS_CONST_IOSGOOD	    1 */
/* #define CLUE_THREADS	1 */

#define CLUE_STRBUF_CONST_RDBUF
#define CLUE_STRBUF_PBASE


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

#define NPOS ((size_t)-1)
// Macros
#define CLUE_UNUSED( x )

#include <AnsiBool.hh>
// #include <climits>
#include <cstddef>

extern "C" int getrusage(int who, struct rusage * rusage);

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
// Revision 1.1  1997/07/18 19:55:31  houghton
// Initial Version.
//
//
//
#endif // ! def _ClueArch_hh_ 

