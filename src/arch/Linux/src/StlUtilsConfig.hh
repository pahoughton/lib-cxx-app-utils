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
// Revision 1.2  1995/11/05 15:29:33  houghton
// Revised
//
//

#define CLUE_CLASS_T
#define CLUE_FUNCT_T
#define CLUE_GVAR_T

#if defined( CLUE_DEBUG )
#define CLUE_SAFETY_ON 1
#endif

#define CLUE_STRBUF_CONST_RDBUF const


#define CLUE_CHAR   char
#define CLUE_SCHAR  signed char
#define CLUE_UCHAR  unsigned char
#define CLUE_16	    short
#define CLUE_U16    unsigned short
#define CLUE_32	    long
#define CLUE_U32    unsigned long
#define CLUE_DOUBLE double
#define CLUE_BOOL   bool

#if !defined( CLUE_DIR_DELIM )
#define CLUE_DIR_DELIM '/'
#endif

#include <ClueVersion.hh>
#include <ClassVersion.hh>
#include <ClueExceptions.hh>

#endif // ! def _UtilsConfig_hh_ 

