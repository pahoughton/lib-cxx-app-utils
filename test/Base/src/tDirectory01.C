#include <LibTest.hh>
#include <Directory.hh>

bool
tDirectory01( LibTest & test )
{
  {
    Directory t( "*" );

    for( Directory::iterator them = t.begin();
	 them != t.end();
	 them++ )
      {
	cout << *them << endl;
      }
  }

  return( true );
}
