//
// File:        StrStreambuf.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/30/95 11:32 
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:41:07  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  16:04:05  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include "StrStreambuf.hh"
#else
#include "StrSbuf.hh"
#endif

#if defined( CLUE_DEBUG )
#define  inline
#if !defined( CLUE_SHORT_FN )
#include "StrStreambuf.ii"
#else
#include "StrSbuf.ii"
#endif
#endif

CLUE_VERSION(
  StrStreambuf,
  "$Id$" );


const char *
StrStreambuf::getClassName( void ) const
{
  return( "StrStreambuf" );
}

ostream &
StrStreambuf::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  )
{
  if( showVer )
    dest << StrStreambuf::getClassName() << ":\n"
	 << StrStreambuf::getVersion() << '\n';

  dest << prefix << "string:  '" << cstr() << "'\n"
       << prefix << "length:  " << plen() << '\n'
       << prefix << "size:    " << psize() << '\n'
    ;

  return( dest );
}

const char *
StrStreambuf::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}

  
  


