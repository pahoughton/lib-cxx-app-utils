//
// File:        DateRangeDaily.cc
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 11:59 
//
// Revision History:
//
// $Log$
// Revision 1.1  1994/06/06 13:19:36  houghton
// Lib Clue beta version used for Rating 1.0
//
//
static const char RcsId[] =
"$Id$";


#include "DateRangeDaily.hh"

int
DateRangeDaily::isValid( void ) const
{
  return( start >= 0 && start < SEC_PER_DAY &&
	  dur > 0 );
}

time_t
DateRangeDaily::secIn( const DateRange & dateTwo ) const
{
  return( UnionOf( start, dur,
		   dateTwo.getSecOfDay(), dateTwo.getDur(),
		   SEC_PER_DAY ) );
}


time_t
DateRangeDaily::startsIn( const DateRange & dateTwo ) const
{
  time_t  secs = 0;
  
  if( dateTwo.getSecOfDay() >= start &&
      dateTwo.getSecOfDay() <= start + dur )
    {
      secs = UnionOf( start, dur, dateTwo.getSecOfDay(), dateTwo.getDur() );
    }
  return( secs );
}


#ifdef NEXT_SEC_WORKS

// it doesn't right now

time_t
DateRangeDaily::nextSec( const DateRange & dateTwo, time_t elapsed ) const
{
  time_t  secs = 0;

  time_t  secOfWeek = dateTwo.getDayOfWeek() * SEC_PER_DAY;
  
  if( secOfWeek + elapsed >= start &&
      secOfWeek + elapsed <= start + dur )
    {
      secs = UnionOf( start, dur, dateTwo.getSecOfDay(), dateTwo.getDur() ) - elapsed;
    }
  
  return( secs );
}

#endif

int
DateRangeDaily::getDayOfWeek( void ) const
{
  return( -1 );
}

ostream &
DateRangeDaily::streamOutput( ostream & dest ) const
{
  dest << "Start: "
       << setfill('0')
       << setw(2) << HourInTimeT( start ) << ':'
       << setw(2) << MinInTimeT( start ) << ':'
       << setw(2) << SecInTimeT( start ) << ' '
       << "Dur: "
       << setw(2) << HourInTimeT( dur ) << ':'
       << setw(2) << MinInTimeT( dur ) << ':'
       << setw(2) << SecInTimeT( dur )
       << setfill(' ')
       ;
  return( dest );
}

ostream & operator<<( ostream & dest, const DateRangeDaily & range )
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
