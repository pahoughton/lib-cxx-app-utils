#ifndef _DateRangeWeekly_hh_
#define _DateRangeWeekly_hh_
//
// File:        DateRangeWeekly.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 09:25
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1994/06/06 13:19:37  houghton
// Lib Clue beta version used for Rating 1.0
//
//


#include <DateRange.hh>

class DateRangeWeekly : public DateRange
{

public:

  DateRangeWeekly( short dayOfWeek, time_t startTime, time_t durSec );

  virtual int	  isValid( void ) const;
  
  virtual time_t  secIn( const DateRange & dateTwo ) const;
  virtual time_t  startsIn( const DateRange & dateTwo ) const;
//  virtual time_t  nextSec( const DateRange & dateTwo, time_t elapsed ) const;

  virtual int   getDayOfWeek( void ) const;

  virtual ostream & streamOutput( ostream & dest ) const;

friend ostream & operator<<( ostream & dest, const DateRange & range );

protected:

private:

  time_t   start;
  
};

inline
DateRangeWeekly::DateRangeWeekly(
    short   dayOfWeek,
    time_t  startTime,
    time_t  durSec
    )
: DateRange( 0, durSec )
{
  start = (dayOfWeek * SEC_PER_DAY) + startTime;
}


#endif // ! def _DateRangeWeekly_hh_ 
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
