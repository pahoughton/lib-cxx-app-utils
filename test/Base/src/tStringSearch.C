#include <LibTest.hh>
#include <StringUtils.hh>

#define HAY "this is the 123 haystack to search in 123 .,? aabbbcc 123"
//           012345678901234567890123456789012345678901234567890123456
//                     1         2         3         4         5

bool
tStringSearch( LibTest & test )
{
  {
    // StringSearch( const char *, size_t, const char *, size_t )
    // StringReverseSearch( const char *, size_t, const char *, size_t )
    // StringCaseSearch( const char *, size_t, const char *, size_t )
    // StringCaseReverseSearch( const char *, size_t, const char *, size_t )

    const char * hay = HAY;
    test( (StringSearch( hay, 53, "123xx", 3 ) - hay) == 12 );
    test( (StringReverseSearch( hay, 53, "123xx", 3 ) - hay) == 38 );
    test( (StringReverseSearch( hay, 0, "123xx", 3 ) - hay) == 54 );
    test( (StringCaseSearch( hay, 53, "HayStackXXX", 8 ) - hay ) == 16 );
    test( (StringCaseReverseSearch( hay, 53, "IsXX", 2 ) - hay ) == 5 );
  }
  return( true );
}

