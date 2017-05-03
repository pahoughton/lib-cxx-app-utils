#include "TestConfig.hh"
#include "LibTest.hh"
#include "FileStat.hh"
#include <strstream.h>

bool
tFileStat06( LibTest & tester )
{
  {
    // compare( const FileStat & ) const
    // operator == ( const FileStat & ) const
    // operator <  ( const FileStat & ) const
    // operator >  ( const FileStat & ) const
    
    const FileStat tl( TEST_DATA_DIR "/FileStat.01" );
    const FileStat tm( TEST_DATA_DIR "/FileStat.l1" );

    TEST( tl.compare( tl ) == 0 );
    TEST( tl == tl );
    TEST( tl.compare( tm ) <  0 );
    TEST( tl < tm );
    TEST( tm.compare( tl ) >  0 );
    TEST( tm > tl );
  }

  {
    // toStream( ostream & ) const
    // operator << ( ostream &, const FilePath & )

    strstream tStrm;
    const FileStat t( TEST_DATA_DIR "/FileStat.01" );

    t.toStream( tStrm );
    tStrm << t;
  }
    
  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    const FileStat t( TEST_DATA_DIR "/FileStat.01" );

    TESTR( t.error(), t.good() );
    TEST( t.error() != 0 );
    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( false ) != 0 );
    
  }

  {
    // dumpInfo( ostream & ) const
    // version

    const FileStat t( TEST_DATA_DIR "/FileStat.01" );

    tester.getDump() << '\n' << t.getClassName() << " toStream:\n";
    t.toStream( tester.getDump() );
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }
    
  {
    // ::compare( const FileStat &, const FileStat & ) 
      
    const FileStat tl( TEST_DATA_DIR "/FileStat.01" );
    const FileStat tm( TEST_DATA_DIR "/FileStat.l1" );

    TEST( compare( tl, tl ) == 0 );
    TEST( compare( tl, tm ) <  0 );
    TEST( compare( tm, tl ) >  0 );
  }

  return( true );
}
