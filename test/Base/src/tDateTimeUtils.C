//
// File:        tDateTimeUtils.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/10/95 05:19 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:44:16  houghton
// Revised Test sources
//
//
static const char * RcsId =
"$Id$";

#include <LibTest.hh>

#include <DateTimeUtils.hh>

#include <time.h>

bool
tDateTimeUtils( LibTest & test )
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

    test( SecInTimeT( now ) == gmt.tm_sec );
    test( SecOfDay( now ) == ( (gmt.tm_hour * 60 * 60) +
			       (gmt.tm_min * 60) +
			       gmt.tm_sec ));
    test( MinInTimeT( now ) == gmt.tm_min );
    test( HourInTimeT( now ) == gmt.tm_hour );
    test( HoursInTimeT( now ) == (now / (60 * 60) ) );
    test( DaysInTimeT( now ) == ( now / (60 * 60 * 24 ) ) );
    test( DateInTimeT( now ) == (now - ( ( gmt.tm_hour * 60 * 60 ) +
					 ( gmt.tm_min * 60 ) +
					 gmt.tm_sec ) ) );

    test( IsLeapYear( 2000 ) );
    test( IsLeapYear( 1996 ) );
    test( IsLeapYear( 1980 ) );
    test( IsLeapYear( 1984 ) );
    test( ! IsLeapYear( 1995 ) );
    test( ! IsLeapYear( 1994 ) );
    test( ! IsLeapYear( 1993 ) );
    test( ! IsLeapYear( 1900 ) );
  }

  return( true );
}
