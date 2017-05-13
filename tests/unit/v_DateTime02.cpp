// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/DateTime.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <cstring>
#include <cstdlib>

static valid::verify verify("clue::DateTime02");
using namespace clue;

bool
v_DateTime02( void )
{
  {
    // timet( void ) const
    // secOfDay( void ) const
    // hour( void ) const
    // minute( void ) const
    // second( void ) const

    const DateTime 	dt( "3/1/92 03:30:00",
			    "%m/%d/%y %H:%M:%S"  );

    TEST(  dt.timet()  ==  699420600  );
    TEST(  dt.secOfDay()  ==  12600  );
    TEST(  dt.hour()  ==  3  );
    TEST(  dt.minute()  ==  30  );
    TEST(  dt.second()  ==  0  );
  }

  {
    // dayOfWeek( void ) const
    // check every day of week

    const DateTime  sunday(    "3/1/92 03:30:00" );
    const DateTime  monday(    "3/2/92 03:30:00" );
    const DateTime  tuesday(   "3/3/92 03:30:00" );
    const DateTime  wednesday( "3/4/92 03:30:00" );
    const DateTime  thursday(  "3/5/92 03:30:00" );
    const DateTime  friday(    "3/6/92 03:30:00" );
    const DateTime  saturday(  "3/7/92 03:30:00" );

    TEST(  sunday.dayOfWeek()     ==  Sunday  );
    TEST(  monday.dayOfWeek()     ==  Monday  );
    TEST(  tuesday.dayOfWeek()    ==  Tuesday  );
    TEST(  wednesday.dayOfWeek()  ==  Wednesday  );
    TEST(  thursday.dayOfWeek()   ==  Thursday  );
    TEST(  friday.dayOfWeek()     ==  Friday  );
    TEST(  saturday.dayOfWeek()   ==  Saturday  );

  }

  {
    // dayOfYear( void )
    // mday( void )
    // month( void )
    // yearOfCentury( void )
    // year( void )
    // string( viod )
    // string( 0, const char * )
    // string( char * )
    // string( char *, const char * )


    DateTime  	    dt( "3/1/92 03:30:00" );

    TEST(  dt.dayOfYear()  ==  61  );
    TEST(  dt.mday()  ==  1  );
    TEST(  dt.month()  ==  3  );
    TEST(  dt.yearOfCentury()  ==  92  );
    TEST(  dt.year()  ==  1992  );


    TEST( dt.str() == "03/01/92 03:30:00" );
  }

  {
    // dayOfYear( void ) const
    // mday( void ) const
    // month( void ) const
    // yearOfCentury( void ) const
    // year( void ) const
    // string( void ) const
    // string( char * )  const
    // string( char *, const char * ) const

    const DateTime  dt( "3/1/92 03:30:00" );

    TEST(  dt.dayOfYear()  ==  61  );
    TEST(  dt.mday()  ==  1  );
    TEST(  dt.month()  ==  3  );
    TEST(  dt.yearOfCentury()  ==  92  );
    TEST(  dt.year()  ==  1992  );


    TEST( dt.str() == "03/01/92 03:30:00" );

  }

  {
    // offset( void )
    // isLocal( void )
    // isDST( void )
    // isDST( void ) const
    // timeZone( void )

    DateTime	    	dt( "2/14/95 07:26:35" );
    const DateTime	dtConst( "2/14/95 07:26:35" );

    TEST(   dt.tzOffset()  ==  0  );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( ! dtConst.isDST() );
  }

  {
    // timezone & dst checks

    // offset()
    // isLocal()
    // isDst()
    // isDST() const
    // timeZone
    DateTime	    when( "2/14/95 07:26:35" );

    DateTime	    	dt( when.timet(), false );
    const DateTime	dtConst( when.timet(), false );

    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( ! dtConst.isDST() );

    TEST( dt.tzOffset()  !=  0  );

  }
  return( verify.is_valid() );
}
