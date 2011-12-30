#ifndef _StlUtilsArch_hh_
#define _StlUtilsArch_hh_
/**
  File:		StlUtilsArch.hh
  Project:	StlUtils 
  Desc:

    Architecure specific header for Solaris 5.9
  
  Notes:
    
  Author(s):	Paul Houghton <<paul4hough@gmail.com>>
  Created:	07/19/2003 04:21
  
  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Name$
    $Revision$
    $State$

  $Id$

**/


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
#define STLUTILS_STD_ITERATORS		1
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
#define STLUTILS_LONG_S64_T	long
#define STLUTILS_LONG_U64_T     unsigned long
#define STLUTILS_FLOAT_FP32_T   float
#define STLUTILS_DOUBLE_FP64_T  double
#define STLUTILS_BOOL_T		bool
#define STLUTILS_SSIZE_T	ssize_t
#define STLUTILS_SIZE_T		size_t

#define STLUTILS_S16_T		short
#define STLUTILS_U16_T		unsigned short

#define STLUTILS_S32_T		int
#define STLUTILS_U32_T		unsigned int

#define STLUTILS_S64_T		long
#define STLUTILS_U64_T		unsigned long

#define STLUTILS_64_TIME_T	long
/* #define STLUTILS_64_TIME_T  */
#define STLUTILS_U64_SIZE_T	STLUTILS_LONG_U64_T
#define STLUTILS_S64_SSIZE_T	STLUTILS_LONG_S64_T

#define STLUTILS_ENDIAN	     1234
// #define STLUTILS_LITTLE_ENDIAN	1   // ie 4321
#define STLUTILS_BIG_ENDIAN	1   // ie 1234
#define STLUTILS_DO_NET_CONV	0   // ie do NOT need to do Net2Host & Host2Net

typedef STLUTILS_CHAR_S8_T  type_s8;
typedef STLUTILS_CHAR_U8_T  type_u8;

typedef STLUTILS_S16_T	    type_s16;
typedef STLUTILS_U16_T	    type_u16;

typedef STLUTILS_S32_T	    type_s32;
typedef STLUTILS_U32_T	    type_u32;

typedef STLUTILS_S64_T	    type_s64;
typedef STLUTILS_U64_T	    type_u64;

// Constants
#define STLUTILS_DIR_DELIM	    '/'
#define STLUTILS_BAD_FPOS_T	    LONG_MIN

#define NPOS ((size_t)0xffffffffffffffff)
// Macros
#define STLUTILS_UNUSED( x )

// #include <climits>
using namespace std;

#include <cstddef>

extern "C" int getrusage(int who, struct rusage * rusage);

/**
   Detail Documentation
  
   Configuration Flags:
  
    STLUTILS_HAVE_LONG_ABS	This platform has a long abs function
  			already defined.
  
    STLUTILS_LOG_WHERE	Log macros inclue __FILE__ and __LINE__ so that
  			so that the source locations can be written to the
  			log.
  
   Types:
  
    The following are need by PC Compilers to identify exports. They
    are defined as 'nothing' for this platform.
  
  	STLUTILS_CLASS_T	Class Type:
  	STLUTILS_FUNCT_T	Function Type:
  	STLUTILS_GVAR_T		Global Variable Type:
  
    The following are defined types to insure binary bit size compatiblity
    across platforms.
  
  	STLUTILS_CHAR   char
  	STLUTILS_SCHAR  signed char
  	STLUTILS_UCHAR  unsigned char
  	STLUTILS_16	    short
  	STLUTILS_U16    unsigned short
  	STLUTILS_INT    int
  	STLUTILS_UINT   unsigned int
  	STLUTILS_32	    long
  	STLUTILS_U32    unsigned long
  	STLUTILS_FLOAT  float
  	STLUTILS_DOUBLE double
  	STLUTILS_BOOL   bool
  
   Constants:
  
    STLUTILS_DIR_DELIM  the default directory delimiter.
    STLUTILS_BAD_FPOS_T an invalid fpos_t value
  
   Macros:
  
    STLUTILS_UNUSED( arg )
  	Some compilers output warnings for unused function
  	variables, while other compilers will output
  	an error if the variable is not declared. This
  	macro accomidates both. Just put your unused
  	args inside it.
  
  	Example: void doit( int need, char STLUTILS_UNSED( c ) )
  
   Documented Ver:  2.7
**/ 

#endif /* ! def _StlUtilsArch_hh_ */
