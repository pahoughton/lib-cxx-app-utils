//
// File:        tDateTime4.C
// Desc:        
//
//  Test DateTime 'set' Component Methods
//
//    	time_t		setYYYYMMDD( const char * yyyymmdd);
//    	time_t		setYYMMDD( const char * yymmdd);
//    	time_t		setHHMMSS( const char * hhmmss);  
//   	time_t		setYear( short year );
//   	time_t		setMonth( short month );
//    	time_t		setDayOfYear( short dayOfYear );
//    	time_t		setDayOfMonth( short dayOfMonth );
//    	time_t		setHour( short hour );
//    	time_t		setMinute( short minute );
//    	time_t		setSecond( short second );  
//    	long	    	setTimeZone( const char * zone = 0 );
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     11/03/94 08:56 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/02/20 14:24:46  houghton
// Complete DateTime class test
//
//
static const char * RcsId =
"$Id$";

#include <ClueTest.hh>

#include <DateTime.hh>

int
tDateTime4( void )
{

  {
    // setYYYYMMDD( const char * yyyymmdd
    
    DateTime 	dt( "6/28/95 18:30" );

    dt.setTimeZone();

    if( dt.getHour() != 13 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;

    dt.setYYYYMMDD( "19920730junk" );
    
    if( dt.getOffset() == 0 ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;

    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 7 ) ERROR;
    if( dt.getDayOfMonth() != 30 ) ERROR;
    if( dt.getHour() != 13 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;

    dt.setYYYYMMDD( "19920221junk" );
    
    if( dt.getOffset() == 0 ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 21 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;

  }

  {
    // setYYMMDD( const char * yyyymmdd

    DateTime 	dt( "2/28/95 18:30" );
  
    dt.setTimeZone();

    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;

    dt.setYYMMDD( "920330junk" );

    if( dt.getOffset() == 0 ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 3 ) ERROR;
    if( dt.getDayOfMonth() != 30 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;
    
    dt.setYYMMDD( "920730junk" );

    if( dt.getOffset() == 0 ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;

    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 7 ) ERROR;
    if( dt.getDayOfMonth() != 30 ) ERROR;
    if( dt.getHour() != 13 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;
    
  }
  
  {
    // setHHMMSS( const char * hhmmss);  

    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.setHHMMSS( "120203" );
    
    if( dt.getOffset() == 0 ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 6 ) ERROR;
    if( dt.getDayOfMonth() != 28 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 2 ) ERROR;
    if( dt.getSecond() != 3 ) ERROR;
    
  }

  {
    // setYear( short year );

    DateTime	dt( "2/29/92 06:30:30" );

    // 2/29 leap -> non-leap
    dt.setYear( 95 );

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 3 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    dt.set( "2/29/92 06:30:30" );

    // 2/29 leap -> leap
    dt.setYear( 96 );
    
    if( dt.getYear() != 1996 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 29 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 2/1 leap -> non leap
    
    dt.set( "2/1/92 06:30:30" );

    dt.setYear( 95 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 2/1 leap -> leap
    
    dt.set( "2/1/92 06:30:30" );

    dt.setYear( 96 );
    
    if( dt.getYear() != 1996 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 2/1 non leap -> leap
    
    dt.set( "2/1/93 06:30:30" );

    dt.setYear( 96 );
    
    if( dt.getYear() != 1996 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 1/1 leap -> non leap
    
    dt.set( "1/1/92 06:30:30" );

    dt.setYear( 95 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 1 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 1/1 leap -> leap
    
    dt.set( "1/1/92 06:30:30" );

    dt.setYear( 96 );
    
    if( dt.getYear() != 1996 ) ERROR;
    if( dt.getMonth() != 1 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 1/1 non leap -> leap
    
    dt.set( "1/1/93 06:30:30" );

    dt.setYear( 96 );
    
    if( dt.getYear() != 1996 ) ERROR;
    if( dt.getMonth() != 1 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 3/1 leap -> non leap
    
    dt.set( "3/1/92 06:30:30" );

    dt.setYear( 95 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 3 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 3/1 leap -> leap
    
    dt.set( "3/1/92 06:30:30" );

    dt.setYear( 96 );
    
    if( dt.getYear() != 1996 ) ERROR;
    if( dt.getMonth() != 3 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 3/1 non leap -> leap
    
    dt.set( "3/1/93 06:30:30" );

    dt.setYear( 96 );
    
    if( dt.getYear() != 1996 ) ERROR;
    if( dt.getMonth() != 3 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 10 -> 2010
    
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 10 );

    if( dt.getYear() != 2010 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 80 -> 1980
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 80 );

    if( dt.getYear() != 1980 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;


    // 2010 -> 2010
    
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 2010 );

    if( dt.getYear() != 2010 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 1980 -> 1980
    dt.set( "2/10/95 06:30:30" );

    dt.setYear( 1980 );

    if( dt.getYear() != 1980 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 06 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // timeZone test
    
    dt.set( "2/10/95 12:30:30" );

    dt.setTimeZone();

    if( dt.getHour() != 6 ) ERROR;
    
    dt.setYear( 1980 );

    if( dt.getOffset() == 0 ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;

    // dst test
    
    dt.set( "6/10/95 12:30:30" );

    dt.setTimeZone();

    if( dt.getHour() != 7 ) ERROR;
    if( ! dt.isDST() ) ERROR;
    
    dt.setYear( 1980 );

    if( dt.getOffset() == 0 ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;
    if( dt.getHour() != 7 ) ERROR;

  }

  {
    // setMonth( short month );

    DateTime	    dt( "1/5/92 12:30:30" );

    // leap 1 -> 2

    dt.setMonth( 2 );
    
    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // leap 2 -> 1
    dt.set( "2/5/92 12:30:30" );

    dt.setMonth( 1 );
    
    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 1 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // leap 1 -> 6
    dt.set( "1/5/92 12:30:30" );

    dt.setMonth( 6 );
    
    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 6 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // leap 6 -> 1
    dt.set( "6/5/92 12:30:30" );

    dt.setMonth( 1 );
    
    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 1 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // leap 2 -> 6
    dt.set( "2/5/92 12:30:30" );

    dt.setMonth( 6 );
    
    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 6 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // leap 6 -> 2
    dt.set( "6/5/92 12:30:30" );

    dt.setMonth( 2 );
    
    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    dt.set( "1/5/95 12:30:30" );

    // non-leap 1 -> 2

    dt.setMonth( 2 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // non-leap 2 -> 1
    dt.set( "2/5/95 12:30:30" );

    dt.setMonth( 1 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 1 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // non-leap 1 -> 6
    dt.set( "1/5/95 12:30:30" );

    dt.setMonth( 6 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 6 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // non-leap 6 -> 1
    dt.set( "6/5/95 12:30:30" );

    dt.setMonth( 1 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 1 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // non-leap 2 -> 6
    dt.set( "2/5/95 12:30:30" );

    dt.setMonth( 6 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 6 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // non-leap 6 -> 2
    dt.set( "6/5/95 12:30:30" );

    dt.setMonth( 2 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // 1 -> 12
    dt.set( "1/5/95 12:30:30" );

    dt.setMonth( 12 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 12 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // Day 31 -> set to month with 30 days
    dt.set( "1/31/95 12:30:30" );

    dt.setMonth( 6 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 7 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // Day 29 -> set to month with 29 days
    dt.set( "1/29/92 12:30:30" );

    dt.setMonth( 2 );
    
    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 29 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // Day 31 -> set to month with 31 days
    dt.set( "1/31/92 12:30:30" );

    dt.setMonth( 7 );
    
    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 7 ) ERROR;
    if( dt.getDayOfMonth() != 31 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // Day 30 -> set to month with 30 days
    dt.set( "4/30/92 12:30:30" );

    dt.setMonth( 6 );
    
    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 6 ) ERROR;
    if( dt.getDayOfMonth() != 30 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    // TimeZone
    
    // non-dst -> non-dst
    dt.set( "3/5/92 12:30:30" );
    
    dt.setTimeZone();

    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    
    dt.setMonth( 1 );
    
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    
    // non-dst -> dst
    dt.set( "3/5/92 12:30:30" );
    
    dt.setTimeZone();

    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    
    dt.setMonth( 6 );
    
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;
    if( dt.getHour() != 7 ) ERROR;
    
    // dst -> non-dst
    dt.set( "6/5/92 12:30:30" );
    
    dt.setTimeZone();

    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;
    if( dt.getHour() != 7 ) ERROR;
    
    dt.setMonth( 11 );
    
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    
    // dst -> dst
    dt.set( "6/5/92 12:30:30" );
    
    dt.setTimeZone();

    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;
    if( dt.getHour() != 7 ) ERROR;
    
    dt.setMonth( 7 );
    
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;
    if( dt.getHour() != 7 ) ERROR;
    

  }

  {
    // setDayOfYear( short dayOfYear );

    DateTime 	dt( "1/25/95 12:30:30" );

    if( dt.getDayOfYear() != 25 ) ERROR;

    dt.setDayOfYear( 166 );

    if( dt.getDayOfYear() != 166 ) ERROR;

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 6 ) ERROR;
    if( dt.getDayOfMonth() != 15 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    dt.setDayOfYear( 20 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 1 ) ERROR;
    if( dt.getDayOfMonth() != 20 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    dt.setTimeZone();

    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;

    dt.setDayOfYear( 166 );

    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;
   
    if( dt.getDayOfYear() != 166 ) ERROR;

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 6 ) ERROR;
    if( dt.getDayOfMonth() != 15 ) ERROR;
    if( dt.getHour() != 7 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

     dt.setDayOfYear( 20 );
    
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 1 ) ERROR;
    if( dt.getDayOfMonth() != 20 ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

  }

  {
    // setDayOfMonth( short dayOfMonth );

    DateTime	dt( "2/1/92 12:30:30" );

    dt.setDayOfMonth( 29 );

    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 29 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    dt.setDayOfMonth( 5 );

    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 5 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    dt.setTimeZone();

    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    
    dt.setDayOfMonth( 15 );

    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    if( dt.getYear() != 1992 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 15 ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    dt.set( "4/1/95 12:30:30" );

    dt.setTimeZone();

    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;

    dt.setDayOfMonth( 30 );
    
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 4 ) ERROR;
    if( dt.getDayOfMonth() != 30 ) ERROR;
    if( dt.getHour() != 7 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;
    
  }

  {
    // setHour( short hour );

    DateTime	dt( "2/10/95 12:30:30" );

    dt.setHour( 0 );

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 0 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;
    
    dt.setHour( 23 );

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 23 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;
    
    dt.setHour( 14 );

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 14 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    dt.setTimeZone();
    
    if( ! dt.isLocal() ) ERROR;
    if( dt.getHour() != 8 ) ERROR;

    dt.setHour(20);

    if( ! dt.isLocal() ) ERROR;
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 20 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;
    
  }

  {
    // setMinute( short minute );

    DateTime	dt( "2/10/95 12:30:30" );

    dt.setMinute( 0 );

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 0 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    dt.setMinute( 59 );

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 59 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    dt.setTimeZone();

    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    if( dt.getMinute() != 59 ) ERROR;
    
    dt.setMinute( 30 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;

    
  }

  {
    // setSecond( short second );  

    DateTime	dt( "2/10/95 12:30:30" );

    dt.setSecond( 0 );

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;

    dt.setSecond( 59 );

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 12 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 59 ) ERROR;

    dt.setTimeZone();

    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    if( dt.getSecond() != 59 ) ERROR;
    
    dt.setSecond( 30 );
    
    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 10 ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;
    
  }

  {
    // setTimeZone( const char * zone = 0 );

    DateTime	dt( "2/1/95 12:30:30" );

    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 12 ) ERROR;

    dt.setTimeZone();

    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;

    dt.setTimeZone( "MST7MDT" );
    
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 5 ) ERROR;

    dt.setTimeZone( "CST6CDT" );
    
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;

    dt.set( "6/1/95 12:30:30" );

    dt.setTimeZone();
    
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;
    if( dt.getHour() != 7 ) ERROR;

    dt.setTimeZone( "MST7MDT" );
    
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;
    if( dt.getHour() != 6 ) ERROR;

    dt.setTimeZone( "CST6CDT" );
    
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;
    if( dt.getHour() != 7 ) ERROR;

    dt.setTimeZone( "GMT" );
    
    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dt.getHour() != 12 ) ERROR;

  }    
  return( 0 );
}

//
//              This software is the sole property of
// 
//                 The Williams Companies, Inc.
//                        1 Williams Center
//                          P.O. Box 2400
//        Copyright (c) 1994 by The Williams Companies, Inc.
// 
//                      All Rights Reserved.  
// 
//
