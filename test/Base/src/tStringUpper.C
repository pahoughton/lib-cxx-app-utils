#include <LibTest.hh>
#include <StringUtils.hh>

bool
tStringUpper( LibTest & test )
{
  {
    const char su[] = "THIS IS A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? TEST";

    char sul[] = "THIS IS A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? TEST";
    char sml[] = "tHIS is A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char sll[] = "this is a 1234567890-=!@#$%^&*()_+[]{};':\",./<>? test";

    StringUpper( sul );
    StringUpper( sml );
    StringUpper( sll );

    test( strcmp( sul, su ) == 0 );
    test( strcmp( sml, su ) == 0 );
    test( strcmp( sll, su ) == 0 );
  }

  {
    const char su[] = "THIS IS AsiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    //                01234567890

    char suu[] = "THIS IS AsiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char smu[] = "thIS IS AsiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char slu[] = "this is asiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    
    StringUpper( slu, 9 );
    StringUpper( smu, 9 );
    StringUpper( suu, 9 );

    test( strcmp( slu, su ) == 0 );
    test( strcmp( smu, su ) == 0 );
    test( strcmp( suu, su ) == 0 );
  }

  return( true );
}

    
      
