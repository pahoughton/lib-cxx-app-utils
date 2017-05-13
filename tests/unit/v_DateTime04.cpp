// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/DateTime.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::DateTime04");
using namespace clue;

bool
v_DateTime04( void )
{

  char tz[64] = {"TZ=MST"};
  int  tzhrs  = -7;

  putenv( tz );

  {
    // yyyymmdd( const char * )

    DateTime 	dt( "6/28/95 18:30", "%m/%d/%y %H:%M");

    dt.setTz();

    TEST( dt.hour() == 18 + tzhrs );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 0 );

    dt.yyyymmdd( "19920730junk" );

    TEST( dt.tzOffset() == tzhrs * SecPerHour );
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 7 );
    TEST( dt.mday() == 30 );
    TEST( dt.hour() == 18 + tzhrs );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 0 );

    dt.yyyymmdd( "19920221junk" );

    TEST( dt.tzOffset() != 0 );
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 21 );
    TEST( dt.hour() == 18 + tzhrs );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 0 );

  }

  {
    // yymmdd( const char * )

    DateTime 	dt( "2/28/95 18:30", "%m/%d/%y %H:%M" );


    TEST( dt.hour() == 18 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 0 );

    dt.yymmdd( "920330junk" );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 3 );
    TEST( dt.mday() == 30 );
    TEST( dt.hour() == 18 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 0 );

    dt.yymmdd( "920730junk" );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 7 );
    TEST( dt.mday() == 30 );
    TEST( dt.hour() == 18 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 0 );

  }

  {
    // hhmmss( const char * )

    DateTime 	dt( "6/28/95 18:30:00" );

    dt.hhmmss( "120203" );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 6 );
    TEST( dt.mday() == 28 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 2 );
    TEST( dt.second() == 3 );

  }

  {
    // hhmmss( const char * )
    DateTime dt((time_t)0);

    dt.yyyymmdd( "19971003" );
    dt.hhmmss( "175817" );

    TEST( dt.year() == 1997 );
    TEST( dt.month() == 10 );
    TEST( dt.mday() == 3 );
    TEST( dt.hour() == 17 );
    TEST( dt.minute() == 58 );
    TEST( dt.second() == 17 );
  }

  {
    // setYear( short )

    DateTime	dt( "2/29/92 06:30:30" );

    // 2/29 leap -> non-leap
    dt.year( 95 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 3 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    dt.set( "2/29/92 06:30:30" );

    // 2/29 leap -> leap
    dt.year( 96 );

    TEST( dt.year() == 1996 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 29 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 2/1 leap -> non leap

    dt.set( "2/1/92 06:30:30" );

    dt.year( 95 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 2/1 leap -> leap

    dt.set( "2/1/92 06:30:30" );

    dt.year( 96 );

    TEST( dt.year() == 1996 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 2/1 non leap -> leap

    dt.set( "2/1/93 06:30:30" );

    dt.year( 96 );

    TEST( dt.year() == 1996 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 1/1 leap -> non leap

    dt.set( "1/1/92 06:30:30" );

    dt.year( 95 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 1 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 1/1 leap -> leap

    dt.set( "1/1/92 06:30:30" );

    dt.year( 96 );

    TEST( dt.year() == 1996 );
    TEST( dt.month() == 1 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 1/1 non leap -> leap

    dt.set( "1/1/93 06:30:30" );

    dt.year( 96 );

    TEST( dt.year() == 1996 );
    TEST( dt.month() == 1 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 3/1 leap -> non leap

    dt.set( "3/1/92 06:30:30" );

    dt.year( 95 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 3 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 3/1 leap -> leap

    dt.set( "3/1/92 06:30:30" );

    dt.year( 96 );

    TEST( dt.year() == 1996 );
    TEST( dt.month() == 3 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 3/1 non leap -> leap

    dt.set( "3/1/93 06:30:30" );

    dt.year( 96 );

    TEST( dt.year() == 1996 );
    TEST( dt.month() == 3 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 10 -> 2010

    dt.set( "2/10/95 06:30:30" );

    dt.year( 10 );

    TEST( dt.year() == 2010 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 80 -> 1980
    dt.set( "2/10/95 06:30:30" );

    dt.year( 80 );

    TEST( dt.year() == 1980 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );


    // 2010 -> 2010

    dt.set( "2/10/95 06:30:30" );

    dt.year( 2010 );

    TEST( dt.year() == 2010 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 1980 -> 1980
    dt.set( "2/10/95 06:30:30" );

    dt.year( 1980 );

    TEST( dt.year() == 1980 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 06 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // timeZone test

    dt.set( "2/10/95 12:30:30" );

    dt.setTz();


    dt.year( 1980 );

    TEST( dt.tzOffset() == tzhrs * SecPerHour );
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.hour() == 12 + tzhrs );

  }

  {
    // month( short )

    DateTime	    dt( "1/5/92 12:30:30" );

    // leap 1 -> 2

    dt.month( 2 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // leap 2 -> 1
    dt.set( "2/5/92 12:30:30" );

    dt.month( 1 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 1 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // leap 1 -> 6
    dt.set( "1/5/92 12:30:30" );

    dt.month( 6 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 6 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // leap 6 -> 1
    dt.set( "6/5/92 12:30:30" );

    dt.month( 1 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 1 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // leap 2 -> 6
    dt.set( "2/5/92 12:30:30" );

    dt.month( 6 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 6 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // leap 6 -> 2
    dt.set( "6/5/92 12:30:30" );

    dt.month( 2 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    dt.set( "1/5/95 12:30:30" );

    // non-leap 1 -> 2

    dt.month( 2 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // non-leap 2 -> 1
    dt.set( "2/5/95 12:30:30" );

    dt.month( 1 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 1 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // non-leap 1 -> 6
    dt.set( "1/5/95 12:30:30" );

    dt.month( 6 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 6 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // non-leap 6 -> 1
    dt.set( "6/5/95 12:30:30" );

    dt.month( 1 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 1 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // non-leap 2 -> 6
    dt.set( "2/5/95 12:30:30" );

    dt.month( 6 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 6 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // non-leap 6 -> 2
    dt.set( "6/5/95 12:30:30" );

    dt.month( 2 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // 1 -> 12
    dt.set( "1/5/95 12:30:30" );

    dt.month( 12 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 12 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // Day 31 -> set to month with 30 days
    dt.set( "1/31/95 12:30:30" );

    dt.month( 6 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 7 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // Day 29 -> set to month with 29 days
    dt.set( "1/29/92 12:30:30" );

    dt.month( 2 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 29 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // Day 31 -> set to month with 31 days
    dt.set( "1/31/92 12:30:30" );

    dt.month( 7 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 7 );
    TEST( dt.mday() == 31 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    // Day 30 -> set to month with 30 days
    dt.set( "4/30/92 12:30:30" );

    dt.month( 6 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 6 );
    TEST( dt.mday() == 30 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

  }

  {
    // mday( short )

    DateTime	dt( "2/1/92 12:30:30" );

    dt.mday( 29 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 29 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    dt.mday( 5 );

    TEST( dt.year() == 1992 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 5 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

  }

  {
    // hour( short )

    DateTime	dt( "2/10/95 12:30:30" );

    dt.hour( 0 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 0 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    dt.hour( 23 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 23 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

    dt.hour( 14 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 14 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

  }

  {
    // minute( short )

    DateTime	dt( "2/10/95 12:30:30" );

    dt.minute( 0 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 0 );
    TEST( dt.second() == 30 );

    dt.minute( 59 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 59 );
    TEST( dt.second() == 30 );

  }

  {
    // second( short )

    DateTime	dt( "2/10/95 12:30:30" );

    dt.second( 0 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 0 );

    dt.second( 59 );

    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 10 );
    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 59 );

  }

  return( verify.is_valid() );
}
