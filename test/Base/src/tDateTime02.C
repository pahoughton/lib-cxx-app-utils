#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#include <DateTimeUtils.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#endif

bool
tDateTime02( LibTest & tester )
{
  {
    // getTimeT( void ) const
    // getSecOfDay( void ) const
    // getHour( void ) const
    // getMinute( void ) const
    // getSecond( void ) const
    
    const DateTime 	dt( "3/1/92 03:30" );
    
    TEST(  dt.getTimeT()  ==  699420600  );
    TEST(  dt.getSecOfDay()  ==  12600  );
    TEST(  dt.getHour()  ==  3  );
    TEST(  dt.getMinute()  ==  30  );
    TEST(  dt.getSecond()  ==  0  );
  }

  {
    // getDayOfWeek( void ) const
    // check every day of week

    const DateTime  sunday(    "3/1/92 03:30" );
    const DateTime  monday(    "3/2/92 03:30" );
    const DateTime  tuesday(   "3/3/92 03:30" );
    const DateTime  wednesday( "3/4/92 03:30" );
    const DateTime  thursday(  "3/5/92 03:30" );
    const DateTime  friday(    "3/6/92 03:30" );
    const DateTime  saturday(  "3/7/92 03:30" );
    
    TEST(  sunday.getDayOfWeek()     ==  Sunday  );
    TEST(  monday.getDayOfWeek()     ==  Monday  );
    TEST(  tuesday.getDayOfWeek()    ==  Tuesday  );
    TEST(  wednesday.getDayOfWeek()  ==  Wednesday  );
    TEST(  thursday.getDayOfWeek()   ==  Thursday  );
    TEST(  friday.getDayOfWeek()     ==  Friday  );
    TEST(  saturday.getDayOfWeek()   ==  Saturday  );
    
  }

  {
    // getDayOfYear( void )
    // getDayOfMonth( void )
    // getMonth( void )
    // getYearOfCentury( void )
    // getYear( void )
    // getString( viod )
    // getString( 0, const char * )
    // getString( char * )
    // getString( char *, const char * )

    
    DateTime  	    dt( "3/1/92 03:30" );

    TEST(  dt.getDayOfYear()  ==  61  );
    TEST(  dt.getDayOfMonth()  ==  1  );
    TEST(  dt.getMonth()  ==  3  );
    TEST(  dt.getYearOfCentury()  ==  92  );
    TEST(  dt.getYear()  ==  1992  );

    TEST( ! strcmp( "03/01/92 03:30:00", dt.getString() ) );
	
    char    dtStrBuf[50];

    dt.getString( dtStrBuf );

    TEST( ! strcmp( "03/01/92 03:30:00", dtStrBuf ) );

    TEST( ! strcmp( "Sun 01-Mar-92 03:30:00",
		     dt.getString( 0, "%a %d-%b-%y %H:%M:%S" ) ) );
    
    dt.getString( dtStrBuf, "%a %d-%b-%y %H:%M:%S" );

    TEST( ! strcmp( "Sun 01-Mar-92 03:30:00", dtStrBuf ) );
    
  }
  
  {
    // getDayOfYear( void ) const
    // getDayOfMonth( void ) const
    // getMonth( void ) const
    // getYearOfCentury( void ) const
    // getYear( void ) const
    // getString( void ) const
    // getString( char * )  const
    // getString( char *, const char * ) const

    const DateTime  dt( "3/1/92 03:30" );

    TEST(  dt.getDayOfYear()  ==  61  );
    TEST(  dt.getDayOfMonth()  ==  1  );
    TEST(  dt.getMonth()  ==  3  );
    TEST(  dt.getYearOfCentury()  ==  92  );
    TEST(  dt.getYear()  ==  1992  );


    TEST( ! strcmp( "03/01/92 03:30:00", dt.getString() ) );
	
    char    dtStrBuf[50];

    dt.getString( dtStrBuf );

    TEST( ! strcmp( "03/01/92 03:30:00", dtStrBuf ) );

    TEST( ! strcmp( "Sun 01-Mar-92 03:30:00",
		     dt.getString( 0, "%a %d-%b-%y %H:%M:%S" ) ) );
    
    dt.getString( dtStrBuf, "%a %d-%b-%y %H:%M:%S" );

    TEST( ! strcmp( "Sun 01-Mar-92 03:30:00", dtStrBuf ) );
    
  }

  {
    // getOffset( void )
    // isLocal( void )
    // isDST( void )
    // isDST( void ) const
    // getTimeZone( void )
    
    DateTime	    	dt( "2/14/95 07:26:35" );
    const DateTime	dtConst( "2/14/95 07:26:35" );

    TEST(   dt.getOffset()  ==  0  );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( ! dtConst.isDST() );

    TEST( ! strcmp( dt.getTimeZone(), "GMT" ) );

  }

  {
    // timezone & dst checks
    
    // getOffset()
    // isLocal()
    // isDst()
    // isDST() const
    // getTimeZone
    DateTime	    when( "2/14/95 07:26:35" );
    
    DateTime	    	dt( when.getTimeT(), true );
    const DateTime	dtConst( when.getTimeT(), true );

    TEST( ! strcmp( dt.getTimeZone(), "CST6CDT" ) );
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );
    TEST( ! dtConst.isDST() );

    TEST( dt.getOffset()  ==  -21600  );
    
    DateTime		summerWhen( "6/1/95 08:00:00" );
    DateTime		summer( summerWhen.getTimeT(), true );
    const DateTime 	summerConst( summerWhen.getTimeT(), true );

    TEST( ! strcmp( summer.getTimeZone(), "CST6CDT" ) );
    TEST( summer.isDST() );
    TEST( summerConst.isDST() );
    
    TEST( summer.getOffset()  ==  -18000  );
    
  }

  {
    // timezone checks
    // getSysTimeZone( void )
    // getGmtOffset( void )
    // getGmtOffset( const char * )
    
    TEST( ! strcmp( DateTime::getSysTimeZone(), "CST6CDT" ) );
    TEST(  DateTime::getGmtOffset()  ==  -21600  );
    TEST(  DateTime::getGmtOffset( "CST6CDT" )  ==  -21600  );
    TEST(  DateTime::getGmtOffset( "MST7MDT" )  ==  -25200  );
  }


  return( true );
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
