#include <LibTest.hh>
#include <FileStat.hh>

#include <strstream>

bool
tFileStat06( LibTest & test )
{
  {
    // compare( const FileStat & ) const
    // operator == ( const FileStat & ) const
    // operator <  ( const FileStat & ) const
    // operator >  ( const FileStat & ) const
    
    const FileStat tl( "data/FileStat.01" );
    const FileStat tm( "data/FileStat.l1" );

    test( tl.compare( tl ) == 0 );
    test( tl == tl );
    test( tl.compare( tm ) <  0 );
    test( tl < tm );
    test( tm.compare( tl ) >  0 );
    test( tm > tl );
  }

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // toStream( ostream & ) const
    // dumpInfo( ostream & ) const
    // version

    const FileStat t( "data/FileStat.01" );

    test( t.good() );
    test( t.error() != 0 );
    test( t.getClassName() != 0 );

    strstream tStream;

    t.toStream( tStream );
    t.dumpInfo( tStream );

    test( t.version != 0 );
  }

  {
    // ::compare( const FileStat &, const FileStat & ) 
      
    const FileStat tl( "data/FileStat.01" );
    const FileStat tm( "data/FileStat.l1" );

    test( compare( tl, tl ) == 0 );
    test( compare( tl, tm ) <  0 );
    test( compare( tm, tl ) >  0 );
  }

  {
    // operator << ( ostream &, const FileStat & )
    
    const FileStat t( "data/FileStat.01" );

    strstream tStream;

    tStream << t;
  }

  return( true );
}
