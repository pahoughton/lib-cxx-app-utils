#ifndef _ClueConfig_hh_
#define _ClueConfig_hh_
//
// File:        UtilsConfig.hh
// Desc:        
//
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     06/16/95 08:01
//
// Revision History:
//
// $Log$
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

#define _ALL_SOURCE_

#define CLUE_THREADS	1

#if defined( CLUE_THREADS )
#include <pthread.h>
#endif

#define CLUE_CLASS_T
#define CLUE_FUNCT_T
#define CLUE_GVAR_T


#if defined( CLUE_DEBUG )
#define CLUE_SAFETY_ON 1
#endif

#define CLUE_STRBUF_CONST_RDBUF
#define CLUE_STRBUF_PBASE

#if defined( NPOS )
#error "NPOS already defined"
#else
#define NPOS ((size_t)-1)
#endif

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

#define CLUE_LOG_WHERE 1

#if !defined( CLUE_DIR_DELIM )
#define CLUE_DIR_DELIM '/'
#endif

#define CLUE_UNUSED( x ) x

#include <climits>

#define CLUE_BAD_FPOS_T	    LONG_MIN


#include <AnsiBool.hh>
#include <ClueVersion.hh>
#include <ClassVersion.hh>
#include <ClueExceptions.hh>

#endif // ! def _UtilsConfig_hh_ 

