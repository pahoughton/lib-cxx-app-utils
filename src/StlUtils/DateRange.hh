#ifndef _DateRange_hh_
#define _DateRange_hh_
//
// File:        DateRange.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 08:46
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1994/06/06 13:19:36  houghton
// Lib Clue beta version used for Rating 1.0
//
//


#include "DateTime.hh"

class DateRange : public DateTime
{
public:

  DateRange( time_t startTime, time_t durSec );
  DateRange( const DateTime & startTime, time_t durSec );
  DateRange( const DateTime & startTime, const DateTime & stopTime );

  virtual int     isValid( void ) const;
  
  virtual time_t  secIn( const DateRange & dateTwo ) const;
  virtual time_t  startsIn( const DateRange & dateTwo ) const;
//  virtual time_t  nextSec( const DateRange & dateTwo, time_t elapsed ) const;

  virtual time_t  setDur( int newDur );

  virtual time_t  getDur( void ) const;
  
  virtual ostream & streamOutput( ostream & dest ) const;

friend ostream & operator<<( ostream & dest, const DateRange & range );
  
protected:

  time_t     dur;

private:

};

inline
DateRange::DateRange( 
    time_t	startTime,
    time_t	durSec
    )
: DateTime( startTime )
{
  dur = durSec;
}

inline
DateRange::DateRange(
    const DateTime & startTime,
    time_t           durSec
    )
: DateTime( startTime )
{
  dur = durSec;
}

inline
DateRange::DateRange(
    const DateTime & startTime,
    const DateTime & stopTime
    )
: DateTime( startTime )
{
  dur = stopTime - startTime;
}

#endif // ! def _DateRange_hh_ 
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
