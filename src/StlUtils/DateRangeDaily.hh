#ifndef _DateRangeDaily_hh_
#define _DateRangeDaily_hh_
//
// File:        DateRangeDaily.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 11:55
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1994/06/06 13:19:36  houghton
// Lib Clue beta version used for Rating 1.0
//
//

#include <Clue.hh>
#include <DateRange.hh>

class DateRangeDaily : public DateRange
{

public:

  DateRangeDaily( time_t startTime, time_t durSec );

  virtual int	  isValid( void ) const;
  
  virtual time_t  secIn( const DateRange & dateTwo ) const;
  virtual time_t  startsIn( const DateRange & dateTwo ) const;
//  virtual time_t  nextSec( const DateRange & dateTwo, time_t elapsed ) const;

  virtual int   getDayOfWeek( void ) const;

  virtual ostream & streamOutput( ostream & dest ) const;

friend ostream & operator<<( ostream & dest, const DateRangeDaily & range );

protected:

private:

  time_t   start;
  
};
inline
DateRangeDaily::DateRangeDaily(
    time_t  startTime,
    time_t  durSec
    )
: DateRange( 0, durSec )
{
  start = startTime;
}



#endif // ! def _DateRangeDaily_hh_ 
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
