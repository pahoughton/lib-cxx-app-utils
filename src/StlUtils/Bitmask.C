//
// File:        Bitmask.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     07/21/95 06:41
//
// Revision History:
//
// $Log$
// Revision 1.4  1995/11/09 18:15:18  houghton
// Fixed bug in toStream. was outputing all 0 on AIX
//
// Revision 1.3  1995/11/05  15:28:31  houghton
// Revised
//
//

#include "Bitmask.hh"
#include "Compare.hh"
#include <climits>

#if defined( CLUE_DEBUG )
#define  inline
#include <Bitmask.ii>
#endif // def( CLUE_DEBUG )

CLUE_VERSION(
  Bitmask,
  "$Id$" );

const size_t Bitmask::maxPos = CHAR_BIT * sizeof( Bitmask::ValueType );

size_t
Bitmask::getBinSize( void ) const
{
  return( Sizeof( value ) );
}

BinStream &
Bitmask::write( BinStream & dest ) const
{
  return( dest.write( value ) );
}

BinStream &
Bitmask::read( BinStream & src )
{
  return( src.read( value ) );
}

ostream &
Bitmask::write( ostream & dest ) const
{
  dest.write( (const char *)&value, Sizeof( value ) );
  return( dest );
}

inline
istream &
Bitmask::read( istream & src )
{
  src.read( (char *)&value, Sizeof( value ) );
  return( src );
}

ostream &
Bitmask::toStream( ostream & dest ) const
{
  for( int p = maxPos - 1; p >= 0; p-- )
    dest << ( isSet( p ) ) ? '1' : '0' );
  
  return( dest );
}

const char *
Bitmask::getClassName( void ) const
{
  return( "Bitmask" );
}

const char *
Bitmask::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
Bitmask::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Bitmask::getClassName() << ":\n"
	 << Bitmask::getVersion() << '\n';
  
  dest << prefix << "bits:    ";
  Bitmask::toStream( dest );
  dest << '\n';

  dest << '\n';

  return( dest  );
}





