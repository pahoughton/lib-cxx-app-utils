#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <set>
#include <functional>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <set>
#include <functional>
#endif

typedef set< Str, less< Str > >	    TestSet;

bool
tStrSet( LibTest & tester )
{
  {
    TestSet    t;
    
    const char * string[] = {"one","two","three","four", 0};

    for( size_t f = 0; string[f]; f++ )
      {
	cout << f << endl;
	t.insert( string[f] );
      }
    
    for( TestSet::iterator  them = t.begin();
	 them != t.end();
	 them++ )
      {
	cout << (*them) << endl;
      }
    
  }
  return( true );
}
	
