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
// Revision 1.1  1995/11/05 13:23:33  houghton
// Initaial implementation
//
//

#include "StrStreambuf.hh"

#ifdef   CLUE_DEBUG
#define  inline
#include <StrStreambuf.ii>
#endif

const char StrStreambuf::version[] =
LIB_CLUE_VERSION
"$Id$";

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
    {
      dest << getClassName() << ":\n";
      dest << getVersion() << '\n';
    }

  dest << prefix << "string:  '" << cstr() << "'\n"
       << prefix << "length:  " << plen() << '\n'
       << prefix << "size:    " << psize() << '\n'
    ;

  return( dest );
}

const char *
StrStreambuf::getVersion( void ) const
{
  return( version );
}

  
  


