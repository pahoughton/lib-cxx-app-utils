//
// File:        DateRangeWeekly.cc
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 09:30 
//
// Revision History:
//
// $Log$
// Revision 1.1  1994/06/06 13:19:37  houghton
// Lib Clue beta version used for Rating 1.0
//
//
static const char RcsId[] =
"$Id$";

#include <Clue.hh>

#include "DateRangeWeekly.hh"

int
DateRangeWeekly::isValid( void ) const
{
  return( start >= 0 && start < (SEC_PER_DAY * 7) &&
	  dur > 0 );
}

time_t
DateRangeWeekly::secIn( const DateRange & dateTwo ) const
{
  time_t   secOfWeek = ( (dateTwo.getDayOfWeek() * SEC_PER_DAY) +
       	 	         dateTwo.getSecOfDay() );

  return( UnionOf( start, dur, secOfWeek, dateTwo.getDur(), 7 * SEC_PER_DAY ) );
}


time_t
DateRangeWeekly::startsIn( const DateRange & dateTwo ) const
{
  time_t  secs = 0;
  time_t  secOfWeek = ( (dateTwo.getDayOfWeek() * SEC_PER_DAY) +
    		      	dateTwo.getSecOfDay() );
  
  if( secOfWeek >= start &&
      secOfWeek <= start + dur )
    {
      secs = secIn( dateTwo );
    }
  return( secs );
}

#ifdef NEXT_SEC_WORKS

// it doesn't right now

time_t
DateRangeWeekly::nextSec( const DateRange & dateTwo, time_t elapsed ) const
{
  time_t  secs = 0;

  time_t  secOfWeek = ( (dateTwo.getDayOfWeek() * SEC_PER_DAY) +
			dateTwo.getSecOfDay() );
  
  if( secOfWeek + elapsed >= start &&
      secOfWeek + elapsed <= start + dur )
    {
      secs = secIn( dateTwo ) - elapsed;
    }
  
  return( secs );
}

#endif

int
DateRangeWeekly::getDayOfWeek( void ) const
{
  return( getTimeT() / 7 );
}

    
ostream &
DateRangeWeekly::streamOutput( ostream & dest ) const
{
  dest << "Start: "
       << AbbrWeekDays[ DaysInTimeT( start ) ] << ' '
       << setfill('0')
       << setw(2) << HourInTimeT( start ) << ':'
       << setw(2) << MinInTimeT( start ) << ':'
       << setw(2) << SecInTimeT( start ) << ' '
       << "Dur: "
       << setw(2) <<  dur / SEC_PER_HOUR << ':'
       << setw(2) << MinInTimeT( dur ) << ':'
       << setw(2) << SecInTimeT( dur )
       << setfill(' ')
       ;
  return( dest );
}

ostream & operator<<( ostream & dest, const DateRangeWeekly & range )
{
  return( range.streamOutput( dest ) );
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
