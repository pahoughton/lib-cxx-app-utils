#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#endif

bool
tDateTime03( LibTest & tester )
{

  {
    // setTimeZone( void )
    // setTimeT( time_t )
    
    DateTime	when( "6/28/95 18:30" );
    
    DateTime 	dt( when );

    dt.setTimeZone();

    TEST( dt.getOffset() == -18000 );
    TEST( dt.getTimeT() == when.getTimeT() );
    TEST( dt.isLocal() );
    TEST( dt.isDST() );

    dt.setTimeT( when.getTimeT() );

    TEST( dt.getTimeT() == when.getTimeT() );
    TEST( dt.getOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

  }
  
  {
    // set( time_t )
    // set( time_t, bool )
    
    DateTime	when( "2/28/95 18:30" );
    
    DateTime 	dt( "2/28/95 18:30" );

    dt.setTimeZone();

    TEST( dt.getOffset() == -21600 );
    TEST( dt.getTimeT() == when.getTimeT() );
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );

    dt.set( when.getTimeT() );

    TEST( dt.getTimeT() == when.getTimeT() );
    TEST( dt.getOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    dt.set( when.getTimeT(), true );
    
    TEST( dt.getOffset() == -21600 );
    TEST( dt.getTimeT() == when.getTimeT() );
    TEST( dt.isLocal() );
    TEST( ! dt.isDST() );

    dt.set( when.getTimeT(), false );

    TEST( dt.getTimeT() == when.getTimeT() );
    TEST( dt.getOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

  }

  {
    // set( const char * )
    // set( const char *, const char * )
    
    const char * dateString = "3/1/92 3:30:00";
    
    DateTime	when( dateString );
    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.set( dateString );

    TEST( dt.getTimeT() == when.getTimeT() );
    TEST( dt.getOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.getTimeT() == 699420600 );
    TEST( dt.getSecOfDay() == 12600 );
    TEST( dt.getHour() == 3 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 0 );
    
    TEST( dt.getDayOfYear() == 61 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getMonth() == 3 );
    TEST( dt.getYearOfCentury() == 92 );
    TEST( dt.getYear() == 1992 );

    dt.set( "01-Mar-92 03:30:00", "%d-%b-%y %H:%M:%S" );

    TEST( dt.getTimeT() == 699420600 );
    TEST( dt.getSecOfDay() == 12600 );
    TEST( dt.getHour() == 3 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 0 );
    
    TEST( dt.getDayOfYear() == 61 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getMonth() == 3 );
    TEST( dt.getYearOfCentury() == 92 );
    TEST( dt.getYear() == 1992 );

    dt.set( "06/26/1776", "%m/%d/%Y" );
    TEST( dt.getTimeT() == MinTimeT );
    
    dt.set( "06/26/2076", "%m/%d/%Y" );
    
    TESTR( dt.getString(), dt.getTimeT() == MaxTimeT );
    
  }

  {
    // set( int, int, int )
    // set( int, int, int, int, int, int )
    
    int	    year = 1992;
    int     month = 3;
    int     day = 1;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;

    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.set( year, month, day );

    TEST( dt.getOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.getYear() == year );
    TEST( dt.getMonth() == month );
    TEST( dt.getDayOfMonth() == day );
    TEST( dt.getHour() == 0 );
    TEST( dt.getMinute() == 0 );
    TEST( dt.getSecond() == 0 );

    year = 10;

    dt.set( year, month, day, hour, min, sec );
    
    TEST( dt.getYear() == 2010 );
    TEST( dt.getMonth() == month );
    TEST( dt.getDayOfMonth() == day );
    TEST( dt.getHour() == hour );
    TEST( dt.getMinute() == min );
    TEST( dt.getSecond() == sec );

    year = 1920;
    month = 1;
    day = 1;
    hour = 0;
    min = 0;
    sec = 0;

    dt.set( year, month, day, hour, min, sec );

    TEST( dt.getYear() == year );
    TEST( dt.getMonth() == month );
    TEST( dt.getDayOfMonth() == day );
    TEST( dt.getHour() == hour );
    TEST( dt.getMinute() == min );
    TEST( dt.getSecond() == sec );


    year = 2000;
    
    dt.set( year, month, day, hour, min, sec );

    TEST( dt.getYear() == year );
    TEST( dt.getMonth() == month );
    TEST( dt.getDayOfMonth() == day );
    TEST( dt.getHour() == hour );
    TEST( dt.getMinute() == min );
    TEST( dt.getSecond() == sec );

    year = 2030;
    
    dt.set( year, month, day, hour, min, sec );

    TEST( dt.getYear() == year );
    TEST( dt.getMonth() == month );
    TEST( dt.getDayOfMonth() == day );
    TEST( dt.getHour() == hour );
    TEST( dt.getMinute() == min );
    TEST( dt.getSecond() == sec );

    year = MinYear - 1;

    dt.set( year, month, day, hour, min, sec );

    TEST( dt.getTimeT() == MinTimeT );

    year = MaxYear + 1;
    
    dt.set( year, month, day, hour, min, sec );

    TEST( dt.getTimeT() == MaxTimeT );

  }

  {
    // set( const struct tm & )
    
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

    TEST( dt.getOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.getYear() == 1900 + year );
    TEST( dt.getMonth() == month );
    TEST( dt.getDayOfMonth() == day );
    TEST( dt.getHour() == hour );
    TEST( dt.getMinute() == min );
    TEST( dt.getSecond() == sec );

  }

  {
    // setValid( int, int, int )
    // setValid( int, int, int, int, int, int )
    
    int	    year = 1992;
    int     month = 3;
    int     day = 1;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;

    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.setValid( year, month, day );

    TEST( dt.getOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.getYear() == year );
    TEST( dt.getMonth() == month );
    TEST( dt.getDayOfMonth() == day );
    TEST( dt.getHour() == 0 );
    TEST( dt.getMinute() == 0 );
    TEST( dt.getSecond() == 0 );

    dt.set( year, month, day, hour, min, sec );

    TEST( dt.getYear() == year );
    TEST( dt.getMonth() == month );
    TEST( dt.getDayOfMonth() == day );
    TEST( dt.getHour() == hour );
    TEST( dt.getMinute() == min );
    TEST( dt.getSecond() == sec );

    dt.setValid( year, month, day );
    TEST( dt.good() );

    dt.setValid( -1, month, day);
    TEST( ! dt.good() );

    dt.setValid( 2055, month, day );
    TEST( ! dt.good() );

    dt.setValid( 1969, month, day );
    TEST( dt.good() );

    dt.setValid( year, 0, day );
    TEST( ! dt.good() );

    dt.setValid( year, 13, day );
    TEST( ! dt.good() );

    dt.setValid( year, -1, day );
    TEST( ! dt.good() );

    dt.setValid( year, month, -1 );
    TEST( ! dt.good() );

    dt.setValid( year, month, 0 );
    TEST( ! dt.good() );

    dt.setValid( 0, 0, 0 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 0 );
    TEST( ! dt.good() );
    
    dt.setValid( 92, 1, 31 );
    TEST( dt.good() );
    
    dt.setValid( 92, 1, 32 );
    TEST( ! dt.good() );
    
    dt.setValid( 92, 2, 28 );
    TEST( dt.good() );

    dt.setValid( 92, 2, 29 );
    TEST( dt.good() );

    dt.setValid( 93, 2, 29 );
    TEST( ! dt.good() );

    dt.setValid( 92, 3, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 3, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 4, 31 );
    TEST( ! dt.good() );

    dt.setValid( 92, 4, 30 );
    TEST( dt.good() );

    dt.setValid( 92, 5, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 5, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 6, 31 );
    TEST( ! dt.good() );

    dt.setValid( 92, 6, 30 );
    TEST( dt.good() );

    dt.setValid( 92, 7, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 7, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 8, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 8, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 9, 31 );
    TEST( ! dt.good() );

    dt.setValid( 92, 9, 30 );
    TEST( dt.good() );

    dt.setValid( 92, 10, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 10, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 11, 31 );
    TEST( ! dt.good() );

    dt.setValid( 92, 11, 30 );
    TEST( dt.good() );

    dt.setValid( 92, 12, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 12, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 1, 1, -1 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 24 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 0 );
    TEST( dt.good() );

    dt.setValid( 92, 1, 1, 0, -1 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 60 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 0 );
    TEST( dt.good() );

    dt.setValid( 92, 1, 1, 0, 0, -1 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 0, 60 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 0, 0 );
    TEST( dt.good() );
        
  }

  {
    // setValid( const char * )
    // setValid( const char *, const char * )
    
    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.setValid( "2/1/95 06:30:15" );

    TEST( dt.getOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 6 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 15 );
    TEST( dt.good() );

    dt.setValid( "95 01 01 15 30 15", "%y %m %d %H %M %S" );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 1 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 15 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 15 );
    TEST( dt.good() );

    dt.setValid( "0/1/95" );
    TEST( ! dt.good() );

    dt.setValid( "13/1/95" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/95" );
    TEST( dt.good() );

    // This test fails. The strptime routine
    // converts the '0' to 0 which is january!
    
//    dt.setValid( "95 0 1", "%y %m %d" );
//    TEST( ! dt.good() );
    
    dt.setValid( "13/1/95", "%m/%d/%y" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/95", "%m/%d/%y" );
    TEST( dt.good() );

    dt.setValid( "2/29/92" );
    TEST( dt.good() );

    dt.setValid( "2/29/95" );
    TEST( ! dt.good() );

    dt.setValid( "92 2 29", "%y %m %d" );
    TEST( dt.good() );

    dt.setValid( "93 2 29", "%y %m %d" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/65" );
    TEST( dt.good() );

    dt.setValid( "1/1/95 24:0:0" );
    TEST( ! dt.good() );

#ifndef AIX
    // FIXME - fails.
    //    dt.setValid( "1 1 95 24 0 0", "%m %d %y %h %m %s" );
    //    TESTR( dt.getString(), ! dt.good() );
#endif
    
    dt.setValid( "1/1/95 23:60:0" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/95 23:59:60" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/95 23:59:59" );
    TEST( dt.good() );
    
  }

  {
    // setVaidYYMMDD( const char * yymmdd );

    DateTime dt;

    dt.setValidYYMMDD( "970204" );

    TEST( dt.good() );

    // FIXME - need more extensive testing.
    
    // cout << "\n" <<  dt << " - 970204 '" << dt.getYYYYMMDD() << "'." <<  endl;
  }
  
    

    
  return( true );
}
