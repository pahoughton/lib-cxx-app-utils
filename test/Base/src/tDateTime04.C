#include <LibTest.hh>
#include <DateTime.hh>

bool
tDateTime04( LibTest & test )
{
  {
    // setYYYYMMDD( const char * ) 
    
    DateTime 	dt( "6/28/95 18:30" );

    dt.setTimeZone();

    test( dt.getHour() == 13 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 0 );

    dt.setYYYYMMDD( "19920730junk" );
    
    test( dt.getOffset() != 0 );
    test( dt.isLocal() );
    test( dt.isDST() );

    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 7 );
    test( dt.getDayOfMonth() == 30 );
    test( dt.getHour() == 13 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 0 );

    dt.setYYYYMMDD( "19920221junk" );
    
    test( dt.getOffset() != 0 );
    test( dt.isLocal() );
    test( ! dt.isDST() );

    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 21 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 0 );

  }

  {
    // setYYMMDD( const char * )

    DateTime 	dt( "2/28/95 18:30" );
  
    dt.setTimeZone();

    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 0 );

    dt.setYYMMDD( "920330junk" );

    test( dt.getOffset() != 0 );
    test( dt.isLocal() );
    test( ! dt.isDST() );

    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 3 );
    test( dt.getDayOfMonth() == 30 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 0 );
    
    dt.setYYMMDD( "920730junk" );

    test( dt.getOffset() != 0 );
    test( dt.isLocal() );
    test( dt.isDST() );

    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 7 );
    test( dt.getDayOfMonth() == 30 );
    test( dt.getHour() == 13 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 0 );
    
  }
  
  {
    // setHHMMSS( const char * )

    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.setHHMMSS( "120203" );
    
    test( dt.getOffset() != 0 );
    test( dt.isLocal() );
    test( dt.isDST() );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 6 );
    test( dt.getDayOfMonth() == 28 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 2 );
    test( dt.getSecond() == 3 );
    
  }

  {
    // setYear( short )

    DateTime	dt( "2/29/92 06:30:30" );

    // 2/29 leap -> non-leap
    dt.setYear( 95 );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 3 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    dt.set( "2/29/92 06:30:30" );

    // 2/29 leap -> leap
    dt.setYear( 96 );
    
    test( dt.getYear() == 1996 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 29 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 2/1 leap -> non leap
    
    dt.set( "2/1/92 06:30:30" );

    dt.setYear( 95 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 2/1 leap -> leap
    
    dt.set( "2/1/92 06:30:30" );

    dt.setYear( 96 );
    
    test( dt.getYear() == 1996 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 2/1 non leap -> leap
    
    dt.set( "2/1/93 06:30:30" );

    dt.setYear( 96 );
    
    test( dt.getYear() == 1996 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 1/1 leap -> non leap
    
    dt.set( "1/1/92 06:30:30" );

    dt.setYear( 95 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 1 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 1/1 leap -> leap
    
    dt.set( "1/1/92 06:30:30" );

    dt.setYear( 96 );
    
    test( dt.getYear() == 1996 );
    test( dt.getMonth() == 1 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 1/1 non leap -> leap
    
    dt.set( "1/1/93 06:30:30" );

    dt.setYear( 96 );
    
    test( dt.getYear() == 1996 );
    test( dt.getMonth() == 1 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 3/1 leap -> non leap
    
    dt.set( "3/1/92 06:30:30" );

    dt.setYear( 95 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 3 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 3/1 leap -> leap
    
    dt.set( "3/1/92 06:30:30" );

    dt.setYear( 96 );
    
    test( dt.getYear() == 1996 );
    test( dt.getMonth() == 3 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 3/1 non leap -> leap
    
    dt.set( "3/1/93 06:30:30" );

    dt.setYear( 96 );
    
    test( dt.getYear() == 1996 );
    test( dt.getMonth() == 3 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 10 -> 2010
    
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 10 );

    test( dt.getYear() == 2010 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 80 -> 1980
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 80 );

    test( dt.getYear() == 1980 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );


    // 2010 -> 2010
    
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 2010 );

    test( dt.getYear() == 2010 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 1980 -> 1980
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 1980 );

    test( dt.getYear() == 1980 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 06 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // timeZone test
    
    dt.set( "2/10/95 12:30:30" );

    dt.setTimeZone();

    test( dt.getHour() == 6 );
    
    dt.setYear( 1980 );

    test( dt.getOffset() != 0 );
    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );

    // dst test
    
    dt.set( "6/10/95 12:30:30" );

    dt.setTimeZone();

    test( dt.getHour() == 7 );
    test( dt.isDST() );
    
    dt.setYear( 1980 );

    test( dt.getOffset() != 0 );
    test( dt.isLocal() );
    test( dt.isDST() );
    test( dt.getHour() == 7 );

  }

  {
    // setMonth( short )

    DateTime	    dt( "1/5/92 12:30:30" );

    // leap 1 -> 2

    dt.setMonth( 2 );
    
    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // leap 2 -> 1
    dt.set( "2/5/92 12:30:30" );

    dt.setMonth( 1 );
    
    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 1 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // leap 1 -> 6
    dt.set( "1/5/92 12:30:30" );

    dt.setMonth( 6 );
    
    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 6 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // leap 6 -> 1
    dt.set( "6/5/92 12:30:30" );

    dt.setMonth( 1 );
    
    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 1 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // leap 2 -> 6
    dt.set( "2/5/92 12:30:30" );

    dt.setMonth( 6 );
    
    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 6 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // leap 6 -> 2
    dt.set( "6/5/92 12:30:30" );

    dt.setMonth( 2 );
    
    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    dt.set( "1/5/95 12:30:30" );

    // non-leap 1 -> 2

    dt.setMonth( 2 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // non-leap 2 -> 1
    dt.set( "2/5/95 12:30:30" );

    dt.setMonth( 1 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 1 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // non-leap 1 -> 6
    dt.set( "1/5/95 12:30:30" );

    dt.setMonth( 6 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 6 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // non-leap 6 -> 1
    dt.set( "6/5/95 12:30:30" );

    dt.setMonth( 1 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 1 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // non-leap 2 -> 6
    dt.set( "2/5/95 12:30:30" );

    dt.setMonth( 6 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 6 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // non-leap 6 -> 2
    dt.set( "6/5/95 12:30:30" );

    dt.setMonth( 2 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // 1 -> 12
    dt.set( "1/5/95 12:30:30" );

    dt.setMonth( 12 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 12 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // Day 31 -> set to month with 30 days
    dt.set( "1/31/95 12:30:30" );

    dt.setMonth( 6 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 7 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // Day 29 -> set to month with 29 days
    dt.set( "1/29/92 12:30:30" );

    dt.setMonth( 2 );
    
    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 29 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // Day 31 -> set to month with 31 days
    dt.set( "1/31/92 12:30:30" );

    dt.setMonth( 7 );
    
    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 7 );
    test( dt.getDayOfMonth() == 31 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // Day 30 -> set to month with 30 days
    dt.set( "4/30/92 12:30:30" );

    dt.setMonth( 6 );
    
    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 6 );
    test( dt.getDayOfMonth() == 30 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    // TimeZone
    
    // non-dst -> non-dst
    dt.set( "3/5/92 12:30:30" );
    
    dt.setTimeZone();

    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );
    
    dt.setMonth( 1 );
    
    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );
    
    // non-dst -> dst
    dt.set( "3/5/92 12:30:30" );
    
    dt.setTimeZone();

    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );
    
    dt.setMonth( 6 );
    
    test( dt.isLocal() );
    test( dt.isDST() );
    test( dt.getHour() == 7 );
    
    // dst -> non-dst
    dt.set( "6/5/92 12:30:30" );
    
    dt.setTimeZone();

    test( dt.isLocal() );
    test( dt.isDST() );
    test( dt.getHour() == 7 );
    
    dt.setMonth( 11 );
    
    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );
    
    // dst -> dst
    dt.set( "6/5/92 12:30:30" );
    
    dt.setTimeZone();

    test( dt.isLocal() );
    test( dt.isDST() );
    test( dt.getHour() == 7 );
    
    dt.setMonth( 7 );
    
    test( dt.isLocal() );
    test( dt.isDST() );
    test( dt.getHour() == 7 );
    

  }

  {
    // setDayOfYear( short )

    DateTime 	dt( "1/25/95 12:30:30" );

    test( dt.getDayOfYear() == 25 );

    dt.setDayOfYear( 166 );

    test( dt.getDayOfYear() == 166 );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 6 );
    test( dt.getDayOfMonth() == 15 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    dt.setDayOfYear( 20 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 1 );
    test( dt.getDayOfMonth() == 20 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    dt.setTimeZone();

    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );

    dt.setDayOfYear( 166 );

    test( dt.isLocal() );
    test( dt.isDST() );
   
    test( dt.getDayOfYear() == 166 );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 6 );
    test( dt.getDayOfMonth() == 15 );
    test( dt.getHour() == 7 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

     dt.setDayOfYear( 20 );
    
    test( dt.isLocal() );
    test( ! dt.isDST() );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 1 );
    test( dt.getDayOfMonth() == 20 );
    test( dt.getHour() == 6 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

  }

  {
    // setDayOfMonth( short )

    DateTime	dt( "2/1/92 12:30:30" );

    dt.setDayOfMonth( 29 );

    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 29 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    dt.setDayOfMonth( 5 );

    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    dt.setTimeZone();

    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );
    
    dt.setDayOfMonth( 15 );

    test( dt.isLocal() );
    test( ! dt.isDST() );

    test( dt.getYear() == 1992 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 15 );
    test( dt.getHour() == 6 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    dt.set( "4/1/95 12:30:30" );

    dt.setTimeZone();

    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );

    dt.setDayOfMonth( 30 );
    
    test( dt.isLocal() );
    test( dt.isDST() );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 4 );
    test( dt.getDayOfMonth() == 30 );
    test( dt.getHour() == 7 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );
    
  }

  {
    // setHour( short )

    DateTime	dt( "2/10/95 12:30:30" );

    dt.setHour( 0 );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 0 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );
    
    dt.setHour( 23 );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 23 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );
    
    dt.setHour( 14 );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 14 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    dt.setTimeZone();
    
    test( dt.isLocal() );
    test( dt.getHour() == 8 );

    dt.setHour(20);

    test( dt.isLocal() );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 20 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );
    
  }

  {
    // setMinute( short )

    DateTime	dt( "2/10/95 12:30:30" );

    dt.setMinute( 0 );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 0 );
    test( dt.getSecond() == 30 );

    dt.setMinute( 59 );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 59 );
    test( dt.getSecond() == 30 );

    dt.setTimeZone();

    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );
    test( dt.getMinute() == 59 );
    
    dt.setMinute( 30 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 6 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );

    
  }

  {
    // setSecond( short )

    DateTime	dt( "2/10/95 12:30:30" );

    dt.setSecond( 0 );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 0 );

    dt.setSecond( 59 );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 12 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 59 );

    dt.setTimeZone();

    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );
    test( dt.getSecond() == 59 );
    
    dt.setSecond( 30 );
    
    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 10 );
    test( dt.getHour() == 6 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );
    
  }

  {
    // setTimeZone( void )
    // setTimeZone( const char * )

    DateTime	dt( "2/1/95 12:30:30" );

    test( ! dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 12 );

    dt.setTimeZone();

    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );

    dt.setTimeZone( "MST7MDT" );
    
    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 5 );

    dt.setTimeZone( "CST6CDT" );
    
    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 6 );

    dt.set( "6/1/95 12:30:30" );

    dt.setTimeZone();
    
    test( dt.isLocal() );
    test( dt.isDST() );
    test( dt.getHour() == 7 );

    dt.setTimeZone( "MST7MDT" );
    
    test( dt.isLocal() );
    test( dt.isDST() );
    test( dt.getHour() == 6 );

    dt.setTimeZone( "CST6CDT" );
    
    test( dt.isLocal() );
    test( dt.isDST() );
    test( dt.getHour() == 7 );

    dt.setTimeZone( "GMT" );
    
    test( ! dt.isLocal() );
    test( ! dt.isDST() );
    test( dt.getHour() == 12 );

  }    
  return( true );
}

