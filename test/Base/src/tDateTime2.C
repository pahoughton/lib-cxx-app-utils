//
// File:        tDateTime2.C
// Desc:        
//              
//  Test DateTime 'get' methods
//
//   	time_t		getTimeT( void ) const;
//   	long		getSecOfDay( void ) const;
//   	short		getHour( void ) const;
//   	short		getMinute( void ) const;
//   	short		getSecond( void ) const;
//   	int		getDayOfWeek( void ) const;
//    	short  	    	getDayOfYear( void ) const;
//    	short  	    	getDayOfYear( void );
//    	short		getDayOfMonth( void ) const;
//    	short		getDayOfMonth( void );
//    	short		getMonth( void ) const;
//    	short		getMonth( void );
//    	short		getYearOfCentury( void ) const;
//    	short		getYearOfCentury( void );
//    	short		getYear( void ) const;
//    	short		getYear( void );
//    	const char *	getString( char * buffer = 0, const char * fmt = 0 ) const;
//    	const char *	getString( char * buffer = 0, const char * fmt = 0 );
//    	short	    	getOffset( void ) const;
//    	Bool	    	isLocal( void ) const;
//   	Bool	    	isDST( void ) const;
//   	Bool	    	isDST( void );
//    	const char *	getTimeZone( void ) const;
//    	long       	getGmtOffset( const char * timeZone = 0 );
//    	const char *	getSysTimeZone( void );
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     11/03/94 08:56 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/02/20 14:24:45  houghton
// Complete DateTime class test
//
//
//
static const char * RcsId =
"$Id$";

#include <ClueTest.hh>

#include <DateTime.hh>

int
tDateTime2( void )
{
  {
    const DateTime 	dt( "3/1/92 03:30" );
    
    if( dt.getTimeT() != 699420600 ) ERROR;
    if( dt.getSecOfDay() != 12600 ) ERROR;
    if( dt.getHour() != 3 ) ERROR;
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 0 ) ERROR;
  }

  {
    // check every day of week

    const DateTime  sunday(    "3/1/92 03:30" );
    const DateTime  monday(    "3/2/92 03:30" );
    const DateTime  tuesday(   "3/3/92 03:30" );
    const DateTime  wednesday( "3/4/92 03:30" );
    const DateTime  thursday(  "3/5/92 03:30" );
    const DateTime  friday(    "3/6/92 03:30" );
    const DateTime  saturday(  "3/7/92 03:30" );
    
    if( sunday.getDayOfWeek()    != 0 ) ERROR;
    if( monday.getDayOfWeek()    != 1 ) ERROR;
    if( tuesday.getDayOfWeek()   != 2 ) ERROR;
    if( wednesday.getDayOfWeek() != 3 ) ERROR;
    if( thursday.getDayOfWeek()  != 4 ) ERROR;
    if( friday.getDayOfWeek()    != 5 ) ERROR;
    if( saturday.getDayOfWeek()  != 6 ) ERROR;
    
  }

  {
    
    DateTime  	    dt( "3/1/92 03:30" );

    if( dt.getDayOfYear() != 61 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getMonth() != 3 ) ERROR;
    if( dt.getYearOfCentury() != 92 ) ERROR;
    if( dt.getYear() != 1992 ) ERROR;

    cout << dt.getString() << endl;

    char    dtStrBuf[50];

    dt.getString( dtStrBuf );

    cout << dtStrBuf << endl;

    cout << dt.getString( 0, "%a %d-%b-%y %H:%M:%S" ) << endl;
    
    dt.getString( dtStrBuf, "%a %d-%b-%y %H:%M:%S" );

    cout << dtStrBuf << endl;
  }
  
  {
    const DateTime  dt( "3/1/92 03:30" );

    if( dt.getDayOfYear() != 61 ) ERROR;
    if( dt.getDayOfMonth() != 1 ) ERROR;
    if( dt.getMonth() != 3 ) ERROR;
    if( dt.getYearOfCentury() != 92 ) ERROR;
    if( dt.getYear() != 1992 ) ERROR;

    cout << dt.getString() << endl;

    char    dtStrBuf[50];

    dt.getString( dtStrBuf );

    cout << dtStrBuf << endl;

    cout << dt.getString( 0, "%a %d-%b-%y %H:%M:%S" ) << endl;
    
    dt.getString( dtStrBuf, "%a %d-%b-%y %H:%M:%S" );

    cout << dtStrBuf << endl;
  }

  {
    DateTime	    	dt( "2/14/95 07:26:35" );
    const DateTime	dtConst( "2/14/95 07:26:35" );

    if( dt.getOffset() != 0 ) ERROR;
    if( dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dtConst.isDST() ) ERROR;

    if( strcmp( dt.getTimeZone(), "GMT" ) ) ERROR;

  }

  {
    DateTime	    when( "2/14/95 07:26:35" );
    
    DateTime	    	dt( when.getTimeT(), TRUE );
    const DateTime	dtConst( when.getTimeT(), TRUE );

    if( dt.getOffset() != -21600 ) ERROR;
    if( ! dt.isLocal() ) ERROR;
    if( dt.isDST() ) ERROR;
    if( dtConst.isDST() ) ERROR;

    DateTime	summerWhen( "6/1/95 08:00:00" );
    DateTime 	summer( summerWhen.getTimeT(), TRUE );
    const DateTime 	summerConst( summerWhen.getTimeT(), TRUE );

    if( ! summer.isDST() ) ERROR;
    if( ! summerConst.isDST() ) ERROR;
    
    if( strcmp( dt.getTimeZone(), "CST6CDT" ) ) ERROR;
  }

  {
    if( strcmp( DateTime::getSysTimeZone(), "CST6CDT" ) ) ERROR;
    if( DateTime::getGmtOffset() != -21600 ) ERROR;
    if( DateTime::getGmtOffset( "CST6CDT" ) != -21600 ) ERROR;
    if( DateTime::getGmtOffset( "MST7MDT" ) != -25200 ) ERROR;
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
