#include <LibTest.hh>
#include <Directory.hh>

bool
tDirectory01( LibTest & tester )
{
  {
    Directory t( "*" );

    cout << "\nNo Sort\n";
    
    for( Directory::iterator them = t.begin();
	 them != t.end();
	 them++ )
      {
	cout << *them << endl;
      }
    TEST( true );
  }

  {
    Directory t( "*", Directory::SortTime );

    cout << "\nSort Time\n";
    
    for( Directory::iterator them = t.begin();
	 them != t.end();
	 them++ )
      {
	cout << *them << endl;
      }
    TEST( true );
  }
  
  return( true );
}
