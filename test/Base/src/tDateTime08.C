#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#include <strstream>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#include <strstream>
#endif

bool
tDateTime08( LibTest & tester )
{
  {
    // good( void ) const
    // error( void  ) const
    // getClassName( void ) const
    // getVersion( bool ) const
    
    strstream out;

    DateTime  t( "7/1/95 07:03:40" );

    TEST( t.good() );
    TEST( t.error() != 0 );
    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );

  }

  {
    // dumpInfo( ostream &, const char *, bool ) const
    // version

    DateTime  t( "7/1/95 07:03:40" );

    tester.getDump() << '\n' << t.getClassName() << " toStream:\n";
    t.toStream( tester.getDump() );
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }

  return( true );
} 
