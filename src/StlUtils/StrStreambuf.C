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
// Revision 1.3  1995/11/05 15:28:49  houghton
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


StrStreambuf::StrStreambuf( void )
{
}

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

  
  


