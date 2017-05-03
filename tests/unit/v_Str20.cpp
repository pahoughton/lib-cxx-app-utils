#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#endif

bool
tStr20( LibTest & tester )
{
  {
    // wrap( void )
    
    const char * from =
      "This is a test of the Str::wrap method. It should refomat this string "
      "by word wraping it. This means it will insert newline characters "
      "between the words where they would extend beyone the 'width' value. "
      "This should make it easy to format text data for screen output. "
      "Lets see how it works!" ;

    const char * to =       
"This is a test of the Str::wrap method. It should refomat this string by\n"
"word wraping it. This means it will insert newline characters between\n"
"the words where they would extend beyone the 'width' value. This should\n"
"make it easy to format text data for screen output. Lets see how it\n"
"works!\n" ;

    const char * to_60 = 
"This is a test of the Str::wrap method. It should refomat\n"
"this string by word wraping it. This means it will insert\n"
"newline characters between the words where they would extend\n"
"beyone the 'width' value. This should make it easy to format\n"
"text data for screen output. Lets see how it works!\n";


    const char * to_60_4 = 
"    This is a test of the Str::wrap method. It should\n"
"    refomat this string by word wraping it. This means it\n"
"    will insert newline characters between the words where\n"
"    they would extend beyone the 'width' value. This should\n"
"    make it easy to format text data for screen output. Lets\n"
"    see how it works!\n";

    const char * to_60_4_8 = 
"        This is a test of the Str::wrap method. It should\n"
"    refomat this string by word wraping it. This means it\n"
"    will insert newline characters between the words where\n"
"    they would extend beyone the 'width' value. This should\n"
"    make it easy to format text data for screen output. Lets\n"
"    see how it works!\n";

    Str t( from );

    t.wrap();

    TEST( t == to );

    t = from;
    t.wrap( 60 );
    TEST( t == to_60 );
    
    t = from;
    t.wrap( 60, 4 );
    TEST( t == to_60_4 );
    
    t = from;
    t.wrap( 60, 4, 8 );
    TEST( t == to_60_4_8 );
  }
  
  return( true );
}

