// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/DateTimeUtils.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <ctime>
#include <cstring>
#include <cstdio>

static valid::verify verify("clue::DateTimeUtils");
using namespace clue;


bool
v_DateTimeUtils( void )
{
  {
    // SecIntTimeT( time_t )
    // SecOfDay( time_t )
    // MinInTimeT( time_t )
    // HourInTimeT( time_t )
    // HoursInTimeT( time_t )
    // DaysInTimeT( time_t )
    // DateInTimeT( time_t )
    // IsLeapYear( int )

    time_t  	now = time(0);
    struct tm	gmt;

    memcpy( &gmt, gmtime( &now ), sizeof( struct tm ) );

    TEST( SecInTimeT( now ) == gmt.tm_sec );
    TEST( SecOfDay( now ) == ( (gmt.tm_hour * 60 * 60) +
			       (gmt.tm_min * 60) +
			       gmt.tm_sec ));
    TEST( MinInTimeT( now ) == gmt.tm_min );
    TEST( HourInTimeT( now ) == gmt.tm_hour );
    TEST( HoursInTimeT( now ) == (now / (60 * 60) ) );
    TEST( DaysInTimeT( now ) == ( now / (60 * 60 * 24 ) ) );
    TEST( DateInTimeT( now ) == (now - ( ( gmt.tm_hour * 60 * 60 ) +
					 ( gmt.tm_min * 60 ) +
					 gmt.tm_sec ) ) );

    TEST( IsLeapYear( 2000 ) );
    TEST( IsLeapYear( 1996 ) );
    TEST( IsLeapYear( 1980 ) );
    TEST( IsLeapYear( 1984 ) );
    TEST( ! IsLeapYear( 1995 ) );
    TEST( ! IsLeapYear( 1994 ) );
    TEST( ! IsLeapYear( 1993 ) );
    TEST( ! IsLeapYear( 1900 ) );
  }

  {
    // YYMMDDtoYYYYMMDD( char * dest, const char * src )

    char t[10];
    memset( t, 'x', sizeof( t ) );
    t[9] = 0;

    const char * s1 = "500101";
    const char * e1 = "19500101x";

    YYMMDDtoYYYYMMDD( t, s1 );
    TEST( strcmp( t, e1 ) == 0 );

    const char * s2 = "991231";
    const char * e2 = "19991231x";

    YYMMDDtoYYYYMMDD( t, s2 );
    TEST( strcmp( t, e2 ) == 0 );

    const char * s3 = "000101";
    const char * e3 = "20000101x";

    YYMMDDtoYYYYMMDD( t, s3 );
    TEST( strcmp( t, e3 ) == 0 );

    const char * s4 = "491231";
    const char * e4 = "20491231x";

    YYMMDDtoYYYYMMDD( t, s4 );
    TEST( strcmp( t, e4 ) == 0 );

    const char * s5 = "      ";
    const char * e5 = "        x";

    YYMMDDtoYYYYMMDD( t, s5 );
    TEST( strcmp( t, e5 ) == 0 );

  }

  return( verify.is_valid() );
}
