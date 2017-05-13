// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/Clue.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::Align");
using namespace clue;

bool
v_Align( void )
{
  {
    // Align( value, size_t )

    int	    tInt;
    short   tShort;
    long    tLong;

    tInt = 4096;
    TEST( Align( tInt, 4096 ) == 4096 );
    tInt = 4095;
    TEST( Align( tInt, 4096 ) == 4096 );
    tInt = 1;
    TEST( Align( tInt, 4096 ) == 4096 );
    tShort = 11;
    TEST( Align( tShort, 5 ) == 15 );
    tLong = 0;
    TEST( Align( tLong, 2048 ) == 2048 );
  }

  {
    // Align( value )

    char    tChar  = 41;
    short   tShort = 41;
    int	    tInt   = 41;
    long    tLong  = 41;

    TEST( Align( tChar ) == 41 );
    TEST( ( sizeof( short ) == 1 && Align( tShort ) == 41 ) ||
	  ( sizeof( short ) == 2 && Align( tShort ) == 42 ) ||
	  ( sizeof( short ) == 4 && Align( tShort ) == 44 ) );
    TEST( ( sizeof( int ) == 2 && Align( tInt ) == 42 ) ||
	  ( sizeof( int ) == 4 && Align( tInt ) == 44 ) ||
	  ( sizeof( int ) == 8 && Align( tInt ) == 48 ) );
    TEST( ( sizeof( long ) == 4 && Align( tLong ) == 44 ) ||
	  ( sizeof( long ) == 8 && Align( tLong ) == 48 ) );
  }
  return( verify.is_valid() );
}
