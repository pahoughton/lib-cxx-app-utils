#ifndef _StlUtilsConfig_hh_
#define _StlUtilsConfig_hh_
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
// Revision 5.1  2000/05/25 10:33:19  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:11  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:06  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:24:52  houghton
// Changed to Release 3
//
// Revision 2.2  1996/02/29 19:10:05  houghton
// *** empty log message ***
//
// Revision 2.1  1995/11/10 12:43:23  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  16:04:10  houghton
// Revised
//
//

#define STLUTILS_CLASS_T
#define STLUTILS_FUNCT_T
#define STLUTILS_GVAR_T


#if defined( STLUTILS_DEBUG )
#define STLUTILS_SAFETY_ON 1
#endif

#define STLUTILS_STRBUF_CONST_RDBUF
#define STLUTILS_STRBUF_PBASE

#if defined( NPOS )
#error "NPOS already defined"
#else
#define NPOS ((size_t)-1)
#endif

#define STLUTILS_CHAR   char
#define STLUTILS_SCHAR  signed char
#define STLUTILS_UCHAR  unsigned char
#define STLUTILS_16	    short
#define STLUTILS_U16    unsigned short
#define STLUTILS_32	    long
#define STLUTILS_U32    unsigned long
#define STLUTILS_DOUBLE double
#define STLUTILS_BOOL   bool

#if !defined( STLUTILS_DIR_DELIM )
#define STLUTILS_DIR_DELIM '/'
#endif

extern "C" size_t getpagesize( void );

#include <AnsiBool.hh>
#include <StlUtilsVersion.hh>
#include <ClassVersion.hh>
#include <StlUtilsExceptions.hh>

#endif // ! def _UtilsConfig_hh_ 

