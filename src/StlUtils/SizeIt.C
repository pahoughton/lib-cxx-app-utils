//
// File:        SizeIt.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     03/11/96 06:03
//
// Revision History:
//
// $Log$
// Revision 2.1  1996/03/13 11:28:12  houghton
// Initial Version
//
//

#if !defined( CLUE_SHORT_FN )
#include "SizeIt.hh"
#include <Str.hh>
#else
#include "SizeIt.hh"
#include <Str.hh>
#endif

#if defined( CLUE_DEBUG )
#if !defined( CLUE_SHORT_FN )
#include "SizeIt.ii"
#else
#include "SizeIt.ii"
#endif
#endif

CLUE_VERSION(
  SizeIt,
  "$Id$");


const size_t	SizeIt::factor = CLUE_SIZEIT_SIZE;

SizeIt::~SizeIt( void )
{
}

size_t
SizeIt::setSize( size_t size )
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

  return( errStr.cstr() );
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
SizeIt::toStream( ostream & dest ) const
{
  dest << it;
  return( dest );
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


  return( dest );
}

