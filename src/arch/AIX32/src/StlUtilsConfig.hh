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
// Revision 1.1  1995/11/05 13:52:53  houghton
// Initial Configureation header for AIX
//
//

#define CLUE_CLASS_T
#define CLUE_FUNCT_T

#if defined( CLUE_DEBUG )
#define CLUE_SAFETY_ON 1
#endif

#define CLUE_STRBUF_CONST_RDBUF	const
#define CLUE_STRBUF_PBASE

#if defined( HAVE_BOOL )
#error "HAVE_BOOL already defined"
#else
#define HAVE_BOOL

class bool
{
public:

  bool( int v = 0 ) { value = v; }
  operator int ( void ) const { return( value ); }
  bool & operator = ( int v ) { value = v; return(*this); }
  
private:
  
  int  value;
};

extern bool true;
extern bool false;

#endif

#if defined( NPOS )
#error "NPOS already defined"
#else
#define NPOS ((size_t)-1)
#endif

#include <ClueVersion.hh>
#include <ClassVersion.hh>

#endif // ! def _UtilsConfig_hh_ 

