#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTimeUtils.hh>
#include <ctime>
#include <cstring>

bool
tDateTimeUtils( LibTest & tester )
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

  return( true );
}
