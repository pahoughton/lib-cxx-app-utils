//
// File:        tDateTime3.C
// Desc:        
//
//  Test DateTime 'set' Methods
//
//    	time_t     	setTimeT( time_t timeSec = 0 );
//    	time_t		set( time_t timeSec, Bool addLocal = FALSE );
//    	time_t	    	set( const char * dateString, const char * fmt = 0 );
//    	time_t      	set( int year, int month, int day,
// 			     int hour = 0, int min = 0, int sec = 0 );
//    	time_t		set( const struct tm & tmTime );
//   	time_t          setValid( int year, int month, int day,
// 				  int hour = 0, int min = 0, int sec = 0 );
//   	time_t	    	setValid( const char * dateString, const char * fmt = 0 );  
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     11/03/94 08:56 
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:49:07  houghton
// Change to Version 2
//
// Revision 1.1  1995/02/20  14:24:46  houghton
// Complete DateTime class test
//
//
//
static const char * RcsId =
"$Id$";

#include <ClueTest.hh>

#include <DateTime.hh>

int
tDateTime3( void )
{

  {
    DateTime	when( "6/28/95 18:30" );
    
    DateTime 	dt( "6/28/95 18:30" );

    dt.setTimeZone();

    if( dt.getOffset() != -18000 ) ERROR;
    if( dt.getTimeT() + 18000 != when.getTimeT() ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( ! dt.isDST() ) ERROR;

    dt.setTimeT( when.getTimeT() );

    if( dt.getTimeT() != when.getTimeT() ) ERROR;
    if( dt.getOffset() != 0 ) ERROR;
    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

  }
  
  {
    DateTime	when( "2/28/95 18:30" );
    
    DateTime 	dt( "2/28/95 18:30" );

    dt.setTimeZone();

    if( dt.getOffset() != -21600 ) ERROR;
    if( dt.getTimeT() + 21600 != when.getTimeT() ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    dt.set( when.getTimeT() );

    if( dt.getTimeT() != when.getTimeT() ) ERROR;
    if( dt.getOffset() != 0 ) ERROR;
    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    dt.set( when.getTimeT(), TRUE );
    
    if( dt.getOffset() != -21600 ) ERROR;
    if( dt.getTimeT() + 21600 != when.getTimeT() ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    dt.set( when.getTimeT(), FALSE );

    if( dt.getTimeT() != when.getTimeT() ) ERROR;
    if( dt.getOffset() != 0 ) ERROR;
    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

  }

  {
    const char * dateString = "3/1/92 3:30:00";
    
    DateTime	when( dateString );
    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.set( dateString );

    if( dt.getTimeT() != when.getTimeT() ) ERROR;
    if( dt.getOffset() != 0 ) ERROR;
    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    if( dt.getTimeT() != 699420600 ) ERROR;
    if( dt.getSecOfDay() != 12600 ) ERROR;
    if( dt.getHour() != 3 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;
    
    if( dt.getDayOfYear() != 61 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getMonth() != 3 ) ERROR;
    if( dt.getYearOfCentury() != 92 ) ERROR;
    if( dt.getYear() != 1992 ) ERROR;

    dt.set( "01-Mar-92 03:30:00", "%d-%b-%y %H:%M:%S" );

    if( dt.getTimeT() != 699420600 ) ERROR;
    if( dt.getSecOfDay() != 12600 ) ERROR;
    if( dt.getHour() != 3 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;
    
    if( dt.getDayOfYear() != 61 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getMonth() != 3 ) ERROR;
    if( dt.getYearOfCentury() != 92 ) ERROR;
    if( dt.getYear() != 1992 ) ERROR;

  }

  {
    int	    year = 1992;
    int     month = 3;
    int     day = 1;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;

    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.set( year, month, day );

    if( dt.getOffset() != 0 ) ERROR;
    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    if( dt.getYear() != year ) ERROR;
    if( dt.getMonth() != month ) ERROR;
    if( dt.getDayOfMonth() != day ) ERROR;
    if( dt.getHour() != 0 ) ERROR;
    if( dt.getMinute() != 0 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;

    year = 10;

    dt.set( year, month, day, hour, min, sec );

    if( dt.getYear() != 2010 ) ERROR;
    if( dt.getMonth() != month ) ERROR;
    if( dt.getDayOfMonth() != day ) ERROR;
    if( dt.getHour() != hour ) ERROR;
    if( dt.getMinute() != min ) ERROR;
    if( dt.getSecond() != sec ) ERROR;
        
  }

  {
    
    int	    year = 92;
    int     month = 3;
    int     day = 1;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;

    struct tm tm;

    tm.tm_year = year;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;
  
    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.set( tm );

    if( dt.getOffset() != 0 ) ERROR;
    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    if( dt.getYear() != 1900 + year ) ERROR;
    if( dt.getMonth() != month ) ERROR;
    if( dt.getDayOfMonth() != day ) ERROR;
    if( dt.getHour() != hour ) ERROR;
    if( dt.getMinute() != min ) ERROR;
    if( dt.getSecond() != sec ) ERROR;

  }

  {
    int	    year = 1992;
    int     month = 3;
    int     day = 1;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;

    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.setValid( year, month, day );

    if( dt.getOffset() != 0 ) ERROR;
    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    if( dt.getYear() != year ) ERROR;
    if( dt.getMonth() != month ) ERROR;
    if( dt.getDayOfMonth() != day ) ERROR;
    if( dt.getHour() != 0 ) ERROR;
    if( dt.getMinute() != 0 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;

    dt.set( year, month, day, hour, min, sec );

    if( dt.getYear() != year ) ERROR;
    if( dt.getMonth() != month ) ERROR;
    if( dt.getDayOfMonth() != day ) ERROR;
    if( dt.getHour() != hour ) ERROR;
    if( dt.getMinute() != min ) ERROR;
    if( dt.getSecond() != sec ) ERROR;

    dt.setValid( 65, month, day );

    if( dt.good() ) ERROR;

    dt.setValid( year, month, day );
    if( ! dt.good() ) ERROR;

    dt.setValid( -1, month, day);
    if( dt.good() ) ERROR;

    dt.setValid( 2055, month, day );
    if( dt.good() ) ERROR;

    dt.setValid( 1969, month, day );
    if( dt.good() ) ERROR;

    dt.setValid( year, 0, day );
    if( dt.good() ) ERROR;

    dt.setValid( year, 13, day );
    if( dt.good() ) ERROR;

    dt.setValid( year, -1, day );
    if( dt.good() ) ERROR;

    dt.setValid( year, month, -1 );
    if( dt.good() ) ERROR;

    dt.setValid( year, month, 0 );
    if( dt.good() ) ERROR;

    dt.setValid( 0, 0, 0 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 1, 0 );
    if( dt.good() ) ERROR;
    
    dt.setValid( 92, 1, 31 );
    if( ! dt.good() ) ERROR;
    
    dt.setValid( 92, 1, 32 );
    if( dt.good() ) ERROR;
    
    dt.setValid( 92, 2, 28 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 2, 29 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 93, 2, 29 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 3, 32 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 3, 31 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 4, 31 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 4, 30 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 5, 32 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 5, 31 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 6, 31 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 6, 30 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 7, 32 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 7, 31 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 8, 32 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 8, 31 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 9, 31 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 9, 30 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 10, 32 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 10, 31 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 11, 31 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 11, 30 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 12, 32 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 12, 31 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 1, 1, -1 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 1, 1, 24 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 1, 1, 0 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 1, 1, 0, -1 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 1, 1, 0, 60 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 1, 1, 0, 0 );
    if( ! dt.good() ) ERROR;

    dt.setValid( 92, 1, 1, 0, 0, -1 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 1, 1, 0, 0, 60 );
    if( dt.good() ) ERROR;

    dt.setValid( 92, 1, 1, 0, 0, 0 );
    if( ! dt.good() ) ERROR;
        
  }

  {
    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.setValid( "2/1/95 06:30:15" );

    if( dt.getOffset() != 0 ) ERROR;
    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 2 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 6 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 15 ) ERROR;
    if( ! dt.good() ) ERROR;

    dt.setValid( "95 01 01 15 30 15", "%y %m %d %H %M %S" );

    if( dt.getYear() != 1995 ) ERROR;
    if( dt.getMonth() != 1 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getHour() != 15 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 15 ) ERROR;
    if( ! dt.good() ) ERROR;

    dt.setValid( "0/1/95" );
    if( dt.good() ) ERROR;

    dt.setValid( "13/1/95" );
    if( dt.good() ) ERROR;

    dt.setValid( "1/1/95" );
    if( ! dt.good() ) ERROR;

    // This test fails. The strptime routine
    // converts the '0' to 0 which is january!
    
//    dt.setValid( "95 0 1", "%y %m %d" );
//    if( dt.good() ) ERROR;
    
    dt.setValid( "13/1/95", "%m/%d/%y" );
    if( dt.good() ) ERROR;

    dt.setValid( "1/1/95", "%m/%d/%y" );
    if( ! dt.good() ) ERROR;

    dt.setValid( "2/29/92" );
    if( ! dt.good() ) ERROR;

    dt.setValid( "2/29/95" );
    if( dt.good() ) ERROR;

    dt.setValid( "92 2 29", "%y %m %d" );
    if( ! dt.good() ) ERROR;

    dt.setValid( "93 2 29", "%y %m %d" );
    if( dt.good() ) ERROR;

    dt.setValid( "1/1/65" );
    if( dt.good() ) ERROR;

    dt.setValid( "1/1/95 24:0:0" );
    if( dt.good() ) ERROR;

    dt.setValid( "1 1 95 24 0 0", "%m %d %y %h %m %s" );
    if( dt.good() ) ERROR;

    dt.setValid( "1/1/95 23:60:0" );
    if( dt.good() ) ERROR;

    dt.setValid( "1/1/95 23:59:60" );
    if( dt.good() ) ERROR;

    dt.setValid( "1/1/95 23:59:59" );
    if( ! dt.good() ) ERROR;
    
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
