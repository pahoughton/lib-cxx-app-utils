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

#define _BSD_SOURCE	1
#define _SVID_SOURCE	1

#define CLUE_THREADS	1

#define CLUE_CLASS_T
#define CLUE_FUNCT_T
#define CLUE_GVAR_T

#if defined( CLUE_DEBUG )
#define CLUE_SAFETY_ON 1
#endif

#define CLUE_HAVE_LONG_ABS 1

#define CLUE_STRBUF_CONST_RDBUF const

#define CLUE_CHAR   char
#define CLUE_SCHAR  signed char
#define CLUE_UCHAR  unsigned char
#define CLUE_16	    short
#define CLUE_U16    unsigned short
#define CLUE_INT    int
#define CLUE_UINT   unsigned int
#define CLUE_32	    long
#define CLUE_U32    unsigned long
#define CLUE_DOUBLE double
#define CLUE_BOOL   bool

#if !defined( CLUE_DIR_DELIM )
#define CLUE_DIR_DELIM '/'
#endif

#define CLUE_UNUSED( x )

#if defined( CLUE_THREADS )
#define _MIT_POSIX_THREADS  1
#include <pthread.h>
#endif

#if !defined( CLUE_SHORT_FN )
#include <ClueVersion.hh>
#include <ClueExceptions.hh>
#include <ClassVersion.hh>
#else
#include <ClueVer.hh>
#include <ClueExcp.hh>
#include <ClassVer.hh>
#endif

#endif // ! def _UtilsConfig_hh_ 

