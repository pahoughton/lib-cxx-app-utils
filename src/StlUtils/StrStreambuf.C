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
// Revision 4.2  1998/08/13 10:52:44  houghton
// Port(Hpux10): expaded dumpInfo output.
//
// Revision 4.1  1997/09/17 15:12:58  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:49  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:24:13  houghton
// Changed to Release 3
//
// Revision 2.2  1995/12/04 11:18:28  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:41:07  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  16:04:05  houghton
// Revised
//
//

#if !defined( STLUTILS_SHORT_FN )
#include "StrStreambuf.hh"
#else
#include "StrSbuf.hh"
#endif

#if defined( STLUTILS_DEBUG )
#if !defined( STLUTILS_SHORT_FN )
#include "StrStreambuf.ii"
#else
#include "StrSbuf.ii"
#endif
#endif

STLUTILS_VERSION(
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

  dest << prefix << "length:  " << plen() << '\n'
       << prefix << "base():  " << (void *) base() << '\n'
       << prefix << "ebuf():  " << (void *) ebuf() << '\n'
       << prefix << "pbase(): " << (void *) pbase() << '\n'
       << prefix << "pptr():  " << (void *) pptr() << '\n'
       << prefix << "epptr(): " << (void *) epptr() << '\n'
       << prefix << "eback(): " << (void *) eback() << '\n'
       << prefix << "gptr():  " << (void *) gptr() << '\n'
       << prefix << "egptr(): " << (void *) egptr() << '\n'
       << prefix << "n - b:   " << pptr() - pbase() << '\n'
       << prefix << "string:  '" << (void *)cstr() << "'\n"
       << prefix << "pbase(): " << (void *) pbase() << '\n'
       << prefix << "pptr():  " << (void *) pptr() << '\n'
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

  
  


