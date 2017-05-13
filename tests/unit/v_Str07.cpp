// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::Str07");
using namespace clue;


// Str::iterators

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
v_Str07( void )
{
  {
    // begin( void )
    // end( void )

    const char str[] = "123456";

    Str s( str );

    int i = 0;
    {
      for( Str::iterator t = s.begin();
	  t != s.end();
	  t++ )
	{
	  TEST( *t == str[i] );
	  i++;
	}
    }
    TEST( i == 6 );

    Str::iterator t = s.begin();

    t++; t++;
    *t = 'a';

    TEST( s == "12a456" );

  }

  {
    // begin( void ) const
    // end( void ) const

    const char str[] = "123456";

    Str s( str );

    int i = 0;
    for( Str::const_iterator t = s.begin();
	t != s.end();
	t++ )
      {
	TEST( *t == str[i] );
	i++;
      }
    TEST( i == 6 );
  }

  {
    // rbegin( void )
    // rend( void )

    const char str[] = "123456";

    Str s( str );

    int i = 5;
    {
      for( Str::reverse_iterator t = s.rbegin();
	  t != s.rend();
	  t++ )
	{
	  TEST( *t == str[i] );
	  i--;
	}
    }

    TEST( i == -1 );

    Str::reverse_iterator t = s.rbegin();

    t++; t++;
    *t = 'a';

    TEST( s == "123a56" );
  }

  {
    // rbegin( void ) const
    // rend( void ) const

    const char str[] = "123456";

    const Str s( str );

    int i = 5;
    for( Str::const_reverse_iterator t = s.rbegin();
	t != s.rend();
	t++ )
      {
	TEST( *t == str[i] );
	i--;
      }

    TEST( i == -1 );
  }

  return( verify.is_valid() );
}
