#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <map>
#include <functional>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <map>
#include <functional>
#endif

// typedef map< Str, size_t, less< Str > >	    TestMap;

// typedef map< size_t, Str, less< size_t > >	    TestMap;

bool
tStrmap( LibTest & tester )
{
  {
    TestMap    t;

    const char * string[] = {"one","two","three","four", 0};

    for( size_t f = 0; string[f]; f++ )
      {
	cout << f << endl;
	//	t[ f ] = string[ f ];
	t[ string[f] ] = f;
      }
    
#if 0
    const char * string = "1one 2two 3three 4four 5five";

    Str tStr( string );

    tStr.scan( " " );

    cout << "inserting" << endl;
    for( size_t f = 0; f < tStr.scanMatchCount(); f++ )
      {
	Str key( tStr.scanMatch( f ) );
	cout << f << endl;
	t[ key ] = f;
 	//	t[ tStr.scanMatch( f ) ] = f;
      }
#endif

    for( TestMap::iterator  them = t.begin();
	 them != t.end();
	 them++ )
      {
	cout << (*them).first << endl;
	cout << (*them).second << endl << endl;
      }
    
  }
  return( true );
}
	
