//
// File:        SizeIt.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for SizeIt
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     03/11/96 06:03
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "SizeIt.hh"
#include <Str.hh>

#if defined( STLUTILS_DEBUG )
#include "SizeIt.ii"
#endif

STLUTILS_VERSION(
  SizeIt,
  "$Id$");


const size_t	SizeIt::factor = STLUTILS_SIZEIT_SIZE;

SizeIt::~SizeIt( void )
{
}

ostream &
SizeIt::toStream( ostream & dest ) const
{
  dest << it;
  return( dest );
}

istream &
SizeIt::fromStream( istream & src )
{
  src >> it;
  return( src );
}

ostream &
SizeIt::write( ostream & dest ) const
{
  return( dest.write( (const char *)&it, sizeof( it ) ) );
}

istream &
SizeIt::read( istream & src )
{
  return( src.read( (char *)&it, sizeof( it ) ) );
}

bool
SizeIt::good( void ) const
{
  return( true );
}

const char *
SizeIt::error( void ) const
{
  static Str errStr;

  errStr = SizeIt::getClassName();

  if( good() )
    {
      errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}

const char *
SizeIt::getClassName( void ) const
{
  return( "SizeIt" );
}

const char *
SizeIt::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
SizeIt::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << SizeIt::getClassName() << ":\n"
	 << SizeIt::getVersion() << '\n';

  if( ! SizeIt::good() )
    dest << prefix << "Error: " << SizeIt::error() << '\n';
  else
    dest << prefix << "Good" << '\n';

  dest << prefix << "size:   " << it << '\n';
  
  return( dest );
}

SizeIt::size_type
SizeIt::setSize( size_type size )
{

  if( ! size )
    {
      it = 0;
    }
  else
    {
      if( it < factor )
	it = factor;
      for( ; it > size; it >>= 1 );
      for( ; it < size; it <<= 1 );
    }
  return( it );
}


// Revision Log:
//
// $Log$
// Revision 4.2  1998/11/02 15:28:15  houghton
// Added SizeIt::size_type type.
// Cleanup.
//
// Revision 4.1  1997/09/17 15:12:47  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:40  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:23:58  houghton
// Changed to Release 3
//
// Revision 2.1  1996/03/13 11:28:12  houghton
// Initial Version
//

