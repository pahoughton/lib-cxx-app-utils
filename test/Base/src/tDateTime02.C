#include <LibTest.hh>
#include <DateTime.hh>

bool
tDateTime02( LibTest & test )
{
  {
    // getTimeT( void ) const
    // getSecOfDay( void ) const
    // getHour( void ) const
    // getMinute( void ) const
    // getSecond( void ) const
    
    const DateTime 	dt( "3/1/92 03:30" );
    
    test(  dt.getTimeT()  ==  699420600  );
    test(  dt.getSecOfDay()  ==  12600  );
    test(  dt.getHour()  ==  3  );
    test(  dt.getMinute()  ==  30  );
    test(  dt.getSecond()  ==  0  );
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
    
    test(  sunday.getDayOfWeek()     ==  Sunday  );
    test(  monday.getDayOfWeek()     ==  Monday  );
    test(  tuesday.getDayOfWeek()    ==  Tuesday  );
    test(  wednesday.getDayOfWeek()  ==  Wednesday  );
    test(  thursday.getDayOfWeek()   ==  Thursday  );
    test(  friday.getDayOfWeek()     ==  Friday  );
    test(  saturday.getDayOfWeek()   ==  Saturday  );
    
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

    test(  dt.getDayOfYear()  ==  61  );
    test(  dt.getDayOfMonth()  ==  1  );
    test(  dt.getMonth()  ==  3  );
    test(  dt.getYearOfCentury()  ==  92  );
    test(  dt.getYear()  ==  1992  );

    test( ! strcmp( "03/01/92 03:30:00", dt.getString() ) );
	
    char    dtStrBuf[50];

    dt.getString( dtStrBuf );

    test( ! strcmp( "03/01/92 03:30:00", dtStrBuf ) );

    test( ! strcmp( "Sun 01-Mar-92 03:30:00",
		     dt.getString( 0, "%a %d-%b-%y %H:%M:%S" ) ) );
    
    dt.getString( dtStrBuf, "%a %d-%b-%y %H:%M:%S" );

    test( ! strcmp( "Sun 01-Mar-92 03:30:00", dtStrBuf ) );
    
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

    test(  dt.getDayOfYear()  ==  61  );
    test(  dt.getDayOfMonth()  ==  1  );
    test(  dt.getMonth()  ==  3  );
    test(  dt.getYearOfCentury()  ==  92  );
    test(  dt.getYear()  ==  1992  );


    test( ! strcmp( "03/01/92 03:30:00", dt.getString() ) );
	
    char    dtStrBuf[50];

    dt.getString( dtStrBuf );

    test( ! strcmp( "03/01/92 03:30:00", dtStrBuf ) );

    test( ! strcmp( "Sun 01-Mar-92 03:30:00",
		     dt.getString( 0, "%a %d-%b-%y %H:%M:%S" ) ) );
    
    dt.getString( dtStrBuf, "%a %d-%b-%y %H:%M:%S" );

    test( ! strcmp( "Sun 01-Mar-92 03:30:00", dtStrBuf ) );
    
  }

  {
    // getOffset( void )
    // isLocal( void )
    // isDST( void )
    // isDST( void ) const
    // getTimeZone( void )
    
    DateTime	    	dt( "2/14/95 07:26:35" );
    const DateTime	dtConst( "2/14/95 07:26:35" );

    test(   dt.getOffset()  ==  0  );
    test( ! dt.isLocal() );
    test( ! dt.isDST() );
    test( ! dtConst.isDST() );

    test( ! strcmp( dt.getTimeZone(), "GMT" ) );

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

    test( dt.getOffset()  ==  -21600  );
    test( dt.isLocal() );
    test( ! dt.isDST() );
    test( ! dtConst.isDST() );

    DateTime	summerWhen( "6/1/95 08:00:00" );
    DateTime 	summer( summerWhen.getTimeT(), true );
    const DateTime 	summerConst( summerWhen.getTimeT(), true );

    test( summer.isDST() );
    test( summerConst.isDST() );
    
    test( ! strcmp( dt.getTimeZone(), "CST6CDT" ) );
  }

  {
    // timezone checks
    // getSysTimeZone( void )
    // getGmtOffset( void )
    // getGmtOffset( const char * )
    
    test( ! strcmp( DateTime::getSysTimeZone(), "CST6CDT" ) );
    test(  DateTime::getGmtOffset()  ==  -21600  );
    test(  DateTime::getGmtOffset( "CST6CDT" )  ==  -21600  );
    test(  DateTime::getGmtOffset( "MST7MDT" )  ==  -25200  );
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
