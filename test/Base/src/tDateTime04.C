#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#endif

bool
tDateTime04( LibTest & tester )
{
  {
    // setYYYYMMDD( const char * ) 
    
    DateTime 	dt( "6/28/95 18:30" );

    dt.setTimeZone();

    TEST( dt.getHour() == 13 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 0 );

    dt.setYYYYMMDD( "19920730junk" );
    
    TEST( dt.getOffset() != 0 );
    TEST( dt.isLocal() );
    TEST( dt.isDST() );

    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 7 );
    TEST( dt.getDayOfMonth() == 30 );
    TEST( dt.getHour() == 13 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 0 );

    dt.setYYYYMMDD( "19920221junk" );
    
    TEST( dt.getOffset() != 0 );
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 21 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 0 );

  }

  {
    // setYYMMDD( const char * )

    DateTime 	dt( "2/28/95 18:30" );
  
    dt.setTimeZone();

    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 0 );

    dt.setYYMMDD( "920330junk" );

    TEST( dt.getOffset() != 0 );
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 3 );
    TEST( dt.getDayOfMonth() == 30 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 0 );
    
    dt.setYYMMDD( "920730junk" );

    TEST( dt.getOffset() != 0 );
    TEST( dt.isLocal() );
    TEST( dt.isDST() );

    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 7 );
    TEST( dt.getDayOfMonth() == 30 );
    TEST( dt.getHour() == 13 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 0 );
    
  }
  
  {
    // setHHMMSS( const char * )

    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.setHHMMSS( "120203" );
    
    TEST( dt.getOffset() != 0 );
    TEST( dt.isLocal() );
    TEST( dt.isDST() );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 6 );
    TEST( dt.getDayOfMonth() == 28 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 2 );
    TEST( dt.getSecond() == 3 );
    
  }

  {
    // setYear( short )

    DateTime	dt( "2/29/92 06:30:30" );

    // 2/29 leap -> non-leap
    dt.setYear( 95 );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 3 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    dt.set( "2/29/92 06:30:30" );

    // 2/29 leap -> leap
    dt.setYear( 96 );
    
    TEST( dt.getYear() == 1996 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 29 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 2/1 leap -> non leap
    
    dt.set( "2/1/92 06:30:30" );

    dt.setYear( 95 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 2/1 leap -> leap
    
    dt.set( "2/1/92 06:30:30" );

    dt.setYear( 96 );
    
    TEST( dt.getYear() == 1996 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 2/1 non leap -> leap
    
    dt.set( "2/1/93 06:30:30" );

    dt.setYear( 96 );
    
    TEST( dt.getYear() == 1996 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 1/1 leap -> non leap
    
    dt.set( "1/1/92 06:30:30" );

    dt.setYear( 95 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 1 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 1/1 leap -> leap
    
    dt.set( "1/1/92 06:30:30" );

    dt.setYear( 96 );
    
    TEST( dt.getYear() == 1996 );
    TEST( dt.getMonth() == 1 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 1/1 non leap -> leap
    
    dt.set( "1/1/93 06:30:30" );

    dt.setYear( 96 );
    
    TEST( dt.getYear() == 1996 );
    TEST( dt.getMonth() == 1 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 3/1 leap -> non leap
    
    dt.set( "3/1/92 06:30:30" );

    dt.setYear( 95 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 3 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 3/1 leap -> leap
    
    dt.set( "3/1/92 06:30:30" );

    dt.setYear( 96 );
    
    TEST( dt.getYear() == 1996 );
    TEST( dt.getMonth() == 3 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 3/1 non leap -> leap
    
    dt.set( "3/1/93 06:30:30" );

    dt.setYear( 96 );
    
    TEST( dt.getYear() == 1996 );
    TEST( dt.getMonth() == 3 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 10 -> 2010
    
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 10 );

    TEST( dt.getYear() == 2010 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 80 -> 1980
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 80 );

    TEST( dt.getYear() == 1980 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );


    // 2010 -> 2010
    
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 2010 );

    TEST( dt.getYear() == 2010 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 1980 -> 1980
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 1980 );

    TEST( dt.getYear() == 1980 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 06 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // timeZone test
    
    dt.set( "2/10/95 12:30:30" );

    dt.setTimeZone();

    TEST( dt.getHour() == 6 );
    
    dt.setYear( 1980 );

    TEST( dt.getOffset() != 0 );
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );

    // dst test
    
    dt.set( "6/10/95 12:30:30" );

    dt.setTimeZone();

    TEST( dt.getHour() == 7 );
    TEST( dt.isDST() );
    
    dt.setYear( 1980 );

    TEST( dt.getOffset() != 0 );
    TEST( dt.isLocal() );
    TEST( dt.isDST() );
    TEST( dt.getHour() == 7 );

  }

  {
    // setMonth( short )

    DateTime	    dt( "1/5/92 12:30:30" );

    // leap 1 -> 2

    dt.setMonth( 2 );
    
    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // leap 2 -> 1
    dt.set( "2/5/92 12:30:30" );

    dt.setMonth( 1 );
    
    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 1 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // leap 1 -> 6
    dt.set( "1/5/92 12:30:30" );

    dt.setMonth( 6 );
    
    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 6 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // leap 6 -> 1
    dt.set( "6/5/92 12:30:30" );

    dt.setMonth( 1 );
    
    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 1 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // leap 2 -> 6
    dt.set( "2/5/92 12:30:30" );

    dt.setMonth( 6 );
    
    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 6 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // leap 6 -> 2
    dt.set( "6/5/92 12:30:30" );

    dt.setMonth( 2 );
    
    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    dt.set( "1/5/95 12:30:30" );

    // non-leap 1 -> 2

    dt.setMonth( 2 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // non-leap 2 -> 1
    dt.set( "2/5/95 12:30:30" );

    dt.setMonth( 1 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 1 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // non-leap 1 -> 6
    dt.set( "1/5/95 12:30:30" );

    dt.setMonth( 6 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 6 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // non-leap 6 -> 1
    dt.set( "6/5/95 12:30:30" );

    dt.setMonth( 1 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 1 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // non-leap 2 -> 6
    dt.set( "2/5/95 12:30:30" );

    dt.setMonth( 6 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 6 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // non-leap 6 -> 2
    dt.set( "6/5/95 12:30:30" );

    dt.setMonth( 2 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // 1 -> 12
    dt.set( "1/5/95 12:30:30" );

    dt.setMonth( 12 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 12 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // Day 31 -> set to month with 30 days
    dt.set( "1/31/95 12:30:30" );

    dt.setMonth( 6 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 7 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // Day 29 -> set to month with 29 days
    dt.set( "1/29/92 12:30:30" );

    dt.setMonth( 2 );
    
    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 29 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // Day 31 -> set to month with 31 days
    dt.set( "1/31/92 12:30:30" );

    dt.setMonth( 7 );
    
    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 7 );
    TEST( dt.getDayOfMonth() == 31 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // Day 30 -> set to month with 30 days
    dt.set( "4/30/92 12:30:30" );

    dt.setMonth( 6 );
    
    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 6 );
    TEST( dt.getDayOfMonth() == 30 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    // TimeZone
    
    // non-dst -> non-dst
    dt.set( "3/5/92 12:30:30" );
    
    dt.setTimeZone();

    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );
    
    dt.setMonth( 1 );
    
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );
    
    // non-dst -> dst
    dt.set( "3/5/92 12:30:30" );
    
    dt.setTimeZone();

    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );
    
    dt.setMonth( 6 );
    
    TEST( dt.isLocal() );
    TEST( dt.isDST() );
    TEST( dt.getHour() == 7 );
    
    // dst -> non-dst
    dt.set( "6/5/92 12:30:30" );
    
    dt.setTimeZone();

    TEST( dt.isLocal() );
    TEST( dt.isDST() );
    TEST( dt.getHour() == 7 );
    
    dt.setMonth( 11 );
    
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );
    
    // dst -> dst
    dt.set( "6/5/92 12:30:30" );
    
    dt.setTimeZone();

    TEST( dt.isLocal() );
    TEST( dt.isDST() );
    TEST( dt.getHour() == 7 );
    
    dt.setMonth( 7 );
    
    TEST( dt.isLocal() );
    TEST( dt.isDST() );
    TEST( dt.getHour() == 7 );
    

  }

  {
    // setDayOfYear( short )

    DateTime 	dt( "1/25/95 12:30:30" );

    TEST( dt.getDayOfYear() == 25 );

    dt.setDayOfYear( 166 );

    TEST( dt.getDayOfYear() == 166 );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 6 );
    TEST( dt.getDayOfMonth() == 15 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    dt.setDayOfYear( 20 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 1 );
    TEST( dt.getDayOfMonth() == 20 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    dt.setTimeZone();

    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );

    dt.setDayOfYear( 166 );

    TEST( dt.isLocal() );
    TEST( dt.isDST() );
   
    TEST( dt.getDayOfYear() == 166 );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 6 );
    TEST( dt.getDayOfMonth() == 15 );
    TEST( dt.getHour() == 7 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

     dt.setDayOfYear( 20 );
    
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 1 );
    TEST( dt.getDayOfMonth() == 20 );
    TEST( dt.getHour() == 6 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

  }

  {
    // setDayOfMonth( short )

    DateTime	dt( "2/1/92 12:30:30" );

    dt.setDayOfMonth( 29 );

    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 29 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    dt.setDayOfMonth( 5 );

    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    dt.setTimeZone();

    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );
    
    dt.setDayOfMonth( 15 );

    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.getYear() == 1992 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 15 );
    TEST( dt.getHour() == 6 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    dt.set( "4/1/95 12:30:30" );

    dt.setTimeZone();

    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );

    dt.setDayOfMonth( 30 );
    
    TEST( dt.isLocal() );
    TEST( dt.isDST() );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 4 );
    TEST( dt.getDayOfMonth() == 30 );
    TEST( dt.getHour() == 7 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );
    
  }

  {
    // setHour( short )

    DateTime	dt( "2/10/95 12:30:30" );

    dt.setHour( 0 );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 0 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );
    
    dt.setHour( 23 );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 23 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );
    
    dt.setHour( 14 );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 14 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    dt.setTimeZone();
    
    TEST( dt.isLocal() );
    TEST( dt.getHour() == 8 );

    dt.setHour(20);

    TEST( dt.isLocal() );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 20 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );
    
  }

  {
    // setMinute( short )

    DateTime	dt( "2/10/95 12:30:30" );

    dt.setMinute( 0 );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 0 );
    TEST( dt.getSecond() == 30 );

    dt.setMinute( 59 );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 59 );
    TEST( dt.getSecond() == 30 );

    dt.setTimeZone();

    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );
    TEST( dt.getMinute() == 59 );
    
    dt.setMinute( 30 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 6 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );

    
  }

  {
    // setSecond( short )

    DateTime	dt( "2/10/95 12:30:30" );

    dt.setSecond( 0 );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 0 );

    dt.setSecond( 59 );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 59 );

    dt.setTimeZone();

    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );
    TEST( dt.getSecond() == 59 );
    
    dt.setSecond( 30 );
    
    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 10 );
    TEST( dt.getHour() == 6 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );
    
  }

  {
    // setTimeZone( void )
    // setTimeZone( const char * )

    DateTime	dt( "2/1/95 12:30:30" );

    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 12 );

    dt.setTimeZone();

    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );

    dt.setTimeZone( "MST7MDT" );
    
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 5 );

    dt.setTimeZone( "CST6CDT" );
    
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 6 );

    dt.set( "6/1/95 12:30:30" );

    dt.setTimeZone();
    
    TEST( dt.isLocal() );
    TEST( dt.isDST() );
    TEST( dt.getHour() == 7 );

    dt.setTimeZone( "MST7MDT" );
    
    TEST( dt.isLocal() );
    TEST( dt.isDST() );
    TEST( dt.getHour() == 6 );

    dt.setTimeZone( "CST6CDT" );
    
    TEST( dt.isLocal() );
    TEST( dt.isDST() );
    TEST( dt.getHour() == 7 );

    dt.setTimeZone( "GMT" );
    
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( dt.getHour() == 12 );

  }    
  return( true );
}

