#include <LibTest.hh>
#include <StringUtils.hh>

bool
tStringLower( LibTest & test )
{
  {
    // StringLower( char * )
    
    const char sl[] = "this is a 1234567890-=!@#$%^&*()_+[]{};':\",./<>? test";

    char sul[] = "THIS IS A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? TEST";
    char sml[] = "tHIS is A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char sll[] = "this is a 1234567890-=!@#$%^&*()_+[]{};':\",./<>? test";

    StringLower( sul );
    StringLower( sml );
    StringLower( sll );

    test( strcmp( sul, sl ) == 0 );
    test( strcmp( sml, sl ) == 0 );
    test( strcmp( sll, sl ) == 0 );
  }

  {
    // StringLower( char *, size_t )
    
    const char sl[] = "this is aSIZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    //                01234567890
    
    char sul[] = "THIS IS ASIZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char sml[] = "thIS is aSIZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char sll[] = "this is aSIZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";

    StringLower( sul, 9 );
    StringLower( sml, 9 );
    StringLower( sll, 9 );

    test( strcmp( sul, sl ) == 0 );
    test( strcmp( sml, sl ) == 0 );
    test( strcmp( sll, sl ) == 0 );
  }

  return( true );
}

    
      
