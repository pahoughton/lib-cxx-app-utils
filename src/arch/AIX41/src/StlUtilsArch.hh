#ifndef _ClueArch_hh_
#define _ClueArch_hh_
//
// File:        ClueArch.hh
// Project:	Clue
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

/* #define CLUE_HAVE_LONG_ABS 1 */
#define CLUE_HAS_STRPTIME 1
#define CLUE_LOG_WHERE 1
#define CLUE_HAS_STR 1
#define CLUE_HAS_DATETIME 1
/* #define CLUE_HAS_SEMUN		1 */
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
#define CLUE_UNUSED( x ) x

#include <AnsiBool.hh>
#include <unistd.h> // for pid_t


// Revision Log:
//
// $Log$
// Revision 3.3  1997/07/18 19:37:52  houghton
// Added CLUE_HAS_SEMUN (not defined)
// Added CLUE_HAS_CONST_IOSRDSTATE (not defined)
// Added CLUE_HAS_CONST_IOSGOOD (not defined)
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
#endif // ! def _ClueArch_hh_ 

