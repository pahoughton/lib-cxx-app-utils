#include <LibTest.hh>
#include <Str.hh>

#include <fstream>

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

#define T1u "FIRST part"
#define T2u " second PART"
#define T3u " THIRD part"
#define T4u " forth PART"
#define T5u " FIFTH part"

#define OutStr "This is an output test from SubStr\n"

bool
tSubStr05( LibTest & test )
{

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // toStream( ostream & ) const

    ofstream out( "data/SubStr.operator.output" );
    
    const Str t( "123" OutStr "junk" );

    test( t.good() );
    test( t.error() != 0 );
    test( t.getClassName() != 0 );
    
    
    t.substr( 3, strlen( OutStr ) ).toStream( out );
    out.close();
    test.file( "data/SubStr.operator.output" );

  }
  
  {
    // dumpInfo( ostream & ) const
    
    ofstream out( "data/SubStr.operator.output" );
    const Str t( "123" OutStr "junk" );

    t.substr( 3, strlen( OutStr ) ).dumpInfo( out );
    out.close();
  }
    
  {
    // operator << ( ostream &, const Str & )

    ofstream out( "data/SubStr.operator.output" );
    
    Str t( "123" OutStr "junk" );
    
    out << t.substr( 3, strlen( OutStr ) );
    out.close();
    test.file( "data/SubStr.operator.output" );
  }
  
  {
    // ::compare( const SubStr &, const char * )
    // ::compare( const SubStr &, const char *, size_t )

    Str t( T1 T2 T3 T4 );
    
    test( compare( t.substr( strlen(T1), strlen( T2 T3 ) ), T2 T3 ) == 0 );
    test( compare( t.substr( strlen(T1), strlen( T2 T3 ) + 1), T2 T3 ) > 0 );
    test( compare( t.substr( strlen(T1), strlen( T2 T3 ) - 1 ), T2 T3 ) < 0 );
    test( compare( t.substr( strlen( T1 ), strlen( T2 ) ), T1 ) < 0 );

    test( compare( t.substr( strlen(T1), strlen( T2 T3 ) ),
		   T2 T3 T4,
		   strlen( T2 T3 ) ) == 0 );
    test( compare( t.substr( strlen(T1), strlen( T2 T3 ) + 1),
		   T2 T3 T4,
		   strlen( T2 T3 ) ) == 0 );
    test( compare( t.substr( strlen(T1), strlen( T2 T3 ) - 1 ),
		   T2 T3 T4,
		   strlen( T2 T3 ) ) < 0 );
     test( compare( t.substr( strlen( T1 ), strlen( T2 ) ),
		    T1 T4,
		    strlen( T1 ) ) < 0 );
  }
      
  {
    // ::fcompare( const SubStr &, const char * )
    // ::fcompare( const SubStr &, const char *, size_t )

    Str t( T1 T2 T3 T4 );
    
    test( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) ), T2u T3 ) == 0 );
    test( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) + 1), T2u T3u ) > 0 );
    test( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) - 1 ), T2 T3u ) < 0 );
    test( fcompare( t.substr( strlen(T1), strlen( T2 ) ), T1u ) < 0 );

    test( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) ),
		   T2u T3 T4,
		   strlen( T2 T3 ) ) == 0 );
    test( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) + 1),
		   T2 T3u T4,
		   strlen( T2 T3 ) ) == 0 );
    test( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) - 1 ),
		   T2u T3u T4u,
		   strlen( T2 T3 ) ) < 0 );
    test( fcompare( t.substr( strlen( T1 ), strlen( T2 ) ),
		    T1u T4,
		    strlen( T1 ) ) < 0 );
  }

  return( true );
}
