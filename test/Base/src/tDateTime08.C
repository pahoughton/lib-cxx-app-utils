#include <LibTest.hh>
#include <DateTime.hh>

#include <strstream>

bool
tDateTime08( LibTest & test )
{
  {
    // good( void ) const
    // error( void  ) const
    // getClassName( void ) const
    // toStream( ostream & ) const
    // dumpInfo( ostream & ) const
    // version

    strstream out;

    DateTime  t( "7/1/95 07:03:40" );

    test( t.good() );
    test( t.error() != 0 );
    test( t.getClassName() != 0 );

    t.toStream( out );
    t.dumpInfo( out );

    test( t.version != 0 );
  }

  return( true );
} 
