#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <strstream.h>
#include <fstream>
#include <cstring>
#include <iomanip>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <HBinStrm.hh>
#include <Str.hh>
#include <fstream>
#include <cstring>
#endif

#define OutStr "This is an output test from SubStr\n"

bool
tSubStr05( LibTest & tester )
{

  {
    // getBinSize( void )
    
    const Str stw( "123" OutStr "junk" );
    const SubStr tw( stw, 3, strlen( OutStr ) );

    TEST( tw.getBinSize() == (sizeof(CLUE_U32) + tw.size() ) );
  }
  
  {
    // write( ostream & dest ) const;
    // read( istream & src )

    const Str stw( "123" OutStr "junk" );
    const SubStr tw( stw, 3, strlen( OutStr ) );

    Str str( "123" "abc" "junk" );
    SubStr tr( str, 3, 3 );

    strstream tStrm;

    tw.write( tStrm );
    tr.read( tStrm );
    
    TEST( tr == tw );
    TEST( str == stw );
  }
  
  {      
    // toStream( ostream & ) const

#if !defined( CLUE_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/SubStr.operator.output.01";
#else
    const char * fn = TEST_DATA_DIR "/ssopot1.txt";
#endif
    ofstream out( fn );
    
    const Str t( "123" OutStr "junk" );    
    
    t.substr( 3, strlen( OutStr ) ).toStream( out );
    out.close();
    tester.file( __FILE__, __LINE__, fn );

  }
  
  {
    // operator << ( ostream &, const Str & )

#if !defined( CLUE_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/SubStr.operator.output.02";
#else
    const char * fn = TEST_DATA_DIR "/ssopot2.txt";
#endif
    ofstream out( fn );
    
    Str t( "123" OutStr "junk" );
    
    out << t.substr( 3, strlen( OutStr ) );

    t = "substr width test";
    out.fill( '#' );
    out << '\'' <<  setw( 20 ) << t.substr( 0, 6 ) << '\'' <<  endl;

    out.setf( ios::left, ios::adjustfield );
    out << '\'' <<  setw(20) << t.substr( 0, 6 ) << '\'' <<  endl;

    out << '\'' <<  t.substr( 0, 6 ) << '\'' << endl;
    out.close();
    tester.file( __FILE__, __LINE__, fn );
  }
  
  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // getVersion( void ) const;
    
    const Str st( "123" OutStr "junk" );
    const SubStr t( st, 3, strlen( OutStr ) );
    
    TEST( t.good() );
    TEST( t.error() != 0 );
    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
  }

  {
    // dumpInfo( ostream &, const char *, bool ) const
    // version
    
    const Str st( "123" OutStr "junk" );
    const SubStr t( st, 3, strlen( OutStr ) );
    
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
