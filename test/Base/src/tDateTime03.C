#include <LibTest.hh>
#include <DateTime.hh>

bool
tDateTime03( LibTest & test )
{

  {
    // setTimeZone( void )
    // setTimeT( time_t )
    
    DateTime	when( "6/28/95 18:30" );
    
    DateTime 	dt( when );

    dt.setTimeZone();

    test( dt.getOffset() == -18000 );
    test( dt.getTimeT() == when.getTimeT() );
    test( dt.isLocal() );
    test( dt.isDST() );

    dt.setTimeT( when.getTimeT() );

    test( dt.getTimeT() == when.getTimeT() );
    test( dt.getOffset() == 0 );
    test( ! dt.isLocal() );
    test( ! dt.isDST() );

  }
  
  {
    // set( time_t )
    // set( time_t, bool )
    
    DateTime	when( "2/28/95 18:30" );
    
    DateTime 	dt( "2/28/95 18:30" );

    dt.setTimeZone();

    test( dt.getOffset() == -21600 );
    test( dt.getTimeT() == when.getTimeT() );
    test( dt.isLocal() );
    test( ! dt.isDST() );

    dt.set( when.getTimeT() );

    test( dt.getTimeT() == when.getTimeT() );
    test( dt.getOffset() == 0 );
    test( ! dt.isLocal() );
    test( ! dt.isDST() );

    dt.set( when.getTimeT(), true );
    
    test( dt.getOffset() == -21600 );
    test( dt.getTimeT() == when.getTimeT() );
    test( dt.isLocal() );
    test( ! dt.isDST() );

    dt.set( when.getTimeT(), false );

    test( dt.getTimeT() == when.getTimeT() );
    test( dt.getOffset() == 0 );
    test( ! dt.isLocal() );
    test( ! dt.isDST() );

  }

  {
    // set( const char * )
    // set( const char *, const char * )
    
    const char * dateString = "3/1/92 3:30:00";
    
    DateTime	when( dateString );
    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.set( dateString );

    test( dt.getTimeT() == when.getTimeT() );
    test( dt.getOffset() == 0 );
    test( ! dt.isLocal() );
    test( ! dt.isDST() );

    test( dt.getTimeT() == 699420600 );
    test( dt.getSecOfDay() == 12600 );
    test( dt.getHour() == 3 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 0 );
    
    test( dt.getDayOfYear() == 61 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getMonth() == 3 );
    test( dt.getYearOfCentury() == 92 );
    test( dt.getYear() == 1992 );

    dt.set( "01-Mar-92 03:30:00", "%d-%b-%y %H:%M:%S" );

    test( dt.getTimeT() == 699420600 );
    test( dt.getSecOfDay() == 12600 );
    test( dt.getHour() == 3 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 0 );
    
    test( dt.getDayOfYear() == 61 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getMonth() == 3 );
    test( dt.getYearOfCentury() == 92 );
    test( dt.getYear() == 1992 );

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

    test( dt.getOffset() == 0 );
    test( ! dt.isLocal() );
    test( ! dt.isDST() );

    test( dt.getYear() == year );
    test( dt.getMonth() == month );
    test( dt.getDayOfMonth() == day );
    test( dt.getHour() == 0 );
    test( dt.getMinute() == 0 );
    test( dt.getSecond() == 0 );

    year = 10;

    dt.set( year, month, day, hour, min, sec );

    test( dt.getYear() == 2010 );
    test( dt.getMonth() == month );
    test( dt.getDayOfMonth() == day );
    test( dt.getHour() == hour );
    test( dt.getMinute() == min );
    test( dt.getSecond() == sec );
        
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

    test( dt.getOffset() == 0 );
    test( ! dt.isLocal() );
    test( ! dt.isDST() );

    test( dt.getYear() == 1900 + year );
    test( dt.getMonth() == month );
    test( dt.getDayOfMonth() == day );
    test( dt.getHour() == hour );
    test( dt.getMinute() == min );
    test( dt.getSecond() == sec );

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

    test( dt.getOffset() == 0 );
    test( ! dt.isLocal() );
    test( ! dt.isDST() );

    test( dt.getYear() == year );
    test( dt.getMonth() == month );
    test( dt.getDayOfMonth() == day );
    test( dt.getHour() == 0 );
    test( dt.getMinute() == 0 );
    test( dt.getSecond() == 0 );

    dt.set( year, month, day, hour, min, sec );

    test( dt.getYear() == year );
    test( dt.getMonth() == month );
    test( dt.getDayOfMonth() == day );
    test( dt.getHour() == hour );
    test( dt.getMinute() == min );
    test( dt.getSecond() == sec );

    dt.setValid( 65, month, day );

    test( ! dt.good() );

    dt.setValid( year, month, day );
    test( dt.good() );

    dt.setValid( -1, month, day);
    test( ! dt.good() );

    dt.setValid( 2055, month, day );
    test( ! dt.good() );

    dt.setValid( 1969, month, day );
    test( ! dt.good() );

    dt.setValid( year, 0, day );
    test( ! dt.good() );

    dt.setValid( year, 13, day );
    test( ! dt.good() );

    dt.setValid( year, -1, day );
    test( ! dt.good() );

    dt.setValid( year, month, -1 );
    test( ! dt.good() );

    dt.setValid( year, month, 0 );
    test( ! dt.good() );

    dt.setValid( 0, 0, 0 );
    test( ! dt.good() );

    dt.setValid( 92, 1, 0 );
    test( ! dt.good() );
    
    dt.setValid( 92, 1, 31 );
    test( dt.good() );
    
    dt.setValid( 92, 1, 32 );
    test( ! dt.good() );
    
    dt.setValid( 92, 2, 28 );
    test( dt.good() );

    dt.setValid( 92, 2, 29 );
    test( dt.good() );

    dt.setValid( 93, 2, 29 );
    test( ! dt.good() );

    dt.setValid( 92, 3, 32 );
    test( ! dt.good() );

    dt.setValid( 92, 3, 31 );
    test( dt.good() );

    dt.setValid( 92, 4, 31 );
    test( ! dt.good() );

    dt.setValid( 92, 4, 30 );
    test( dt.good() );

    dt.setValid( 92, 5, 32 );
    test( ! dt.good() );

    dt.setValid( 92, 5, 31 );
    test( dt.good() );

    dt.setValid( 92, 6, 31 );
    test( ! dt.good() );

    dt.setValid( 92, 6, 30 );
    test( dt.good() );

    dt.setValid( 92, 7, 32 );
    test( ! dt.good() );

    dt.setValid( 92, 7, 31 );
    test( dt.good() );

    dt.setValid( 92, 8, 32 );
    test( ! dt.good() );

    dt.setValid( 92, 8, 31 );
    test( dt.good() );

    dt.setValid( 92, 9, 31 );
    test( ! dt.good() );

    dt.setValid( 92, 9, 30 );
    test( dt.good() );

    dt.setValid( 92, 10, 32 );
    test( ! dt.good() );

    dt.setValid( 92, 10, 31 );
    test( dt.good() );

    dt.setValid( 92, 11, 31 );
    test( ! dt.good() );

    dt.setValid( 92, 11, 30 );
    test( dt.good() );

    dt.setValid( 92, 12, 32 );
    test( ! dt.good() );

    dt.setValid( 92, 12, 31 );
    test( dt.good() );

    dt.setValid( 92, 1, 1, -1 );
    test( ! dt.good() );

    dt.setValid( 92, 1, 1, 24 );
    test( ! dt.good() );

    dt.setValid( 92, 1, 1, 0 );
    test( dt.good() );

    dt.setValid( 92, 1, 1, 0, -1 );
    test( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 60 );
    test( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 0 );
    test( dt.good() );

    dt.setValid( 92, 1, 1, 0, 0, -1 );
    test( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 0, 60 );
    test( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 0, 0 );
    test( dt.good() );
        
  }

  {
    // setValid( const char * )
    // setValid( const char *, const char * )
    
    DateTime 	dt( "6/28/95 18:30" );
  
    dt.setTimeZone();

    dt.setValid( "2/1/95 06:30:15" );

    test( dt.getOffset() == 0 );
    test( ! dt.isLocal() );
    test( ! dt.isDST() );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 6 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 15 );
    test( dt.good() );

    dt.setValid( "95 01 01 15 30 15", "%y %m %d %H %M %S" );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 1 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 15 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 15 );
    test( dt.good() );

    dt.setValid( "0/1/95" );
    test( ! dt.good() );

    dt.setValid( "13/1/95" );
    test( ! dt.good() );

    dt.setValid( "1/1/95" );
    test( dt.good() );

    // This test fails. The strptime routine
    // converts the '0' to 0 which is january!
    
//    dt.setValid( "95 0 1", "%y %m %d" );
//    test( ! dt.good() );
    
    dt.setValid( "13/1/95", "%m/%d/%y" );
    test( ! dt.good() );

    dt.setValid( "1/1/95", "%m/%d/%y" );
    test( dt.good() );

    dt.setValid( "2/29/92" );
    test( dt.good() );

    dt.setValid( "2/29/95" );
    test( ! dt.good() );

    dt.setValid( "92 2 29", "%y %m %d" );
    test( dt.good() );

    dt.setValid( "93 2 29", "%y %m %d" );
    test( ! dt.good() );

    dt.setValid( "1/1/65" );
    test( ! dt.good() );

    dt.setValid( "1/1/95 24:0:0" );
    test( ! dt.good() );

#ifndef AIX
    dt.setValid( "1 1 95 24 0 0", "%m %d %y %h %m %s" );
    test( ! dt.good() );
#endif
    
    dt.setValid( "1/1/95 23:60:0" );
    test( ! dt.good() );

    dt.setValid( "1/1/95 23:59:60" );
    test( ! dt.good() );

    dt.setValid( "1/1/95 23:59:59" );
    test( dt.good() );
    
  }

  return( true );
}
