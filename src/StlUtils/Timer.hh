#ifndef _Timer_hh_
#define _Timer_hh_
//
// File:        Timer.hh
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     10/31/94 13:58
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1995/02/13 16:08:59  houghton
// New Style Avl an memory management. Many New Classes
//
//

#include <DateTime.hh>

class Timer
{

public:

  Timer( time_t startTime = 0 );

  time_t    	start( time_t startTime = 0 );
  time_t    	stop( time_t stopTime = 0 );

  time_t    	getDur( void ) const;
  time_t    	getStart( void ) const;
  time_t    	getStop( void ) const;
  
  friend ostream & operator<<( ostream & dest, const Timer & timer );
  
protected:

private:

  Timer( const Timer & copyFrom );
  Timer & operator=( const Timer & assignFrom );

  time_t    startSec;
  time_t    stopSec;
  
};


//
// Inline methods
//

inline
Timer::Timer( time_t startTime )
{
  startSec = startTime;
  stopSec = 0;
}

inline time_t
Timer::start( time_t startTime )
{
  time_t old = startSec;
  
  if( startTime == 0 )
    {
      startSec = time(0);
    }
  else
    {
      startSec = startTime;
    }
  return( old );
}

inline time_t
Timer::stop( time_t stopTime )
{
  time_t old = stopSec;
  
  if( stopTime == 0 )
    {
      stopSec = time(0);
    }
  else
    {
      stopSec = stopTime;
    }

  return( old );
}

inline time_t
Timer::getDur( void ) const
{
  return( stopSec - startSec );
}

inline time_t
Timer::getStart( void ) const
{
  return( startSec );
}


inline time_t
Timer::getStop( void ) const
{
  return( stopSec );
}


inline ostream &
operator<<( ostream & dest, const Timer & timer )
{
  if( timer.getStart() == 0 || timer.getStop() == 0 )
    {
      dest << "no duration";
    }

  int hours = timer.getDur() / (60 * 60);
  int minutes = MinInTimeT( timer.getDur() );
  int seconds = SecInTimeT( timer.getDur() );

  dest << setfill('0') << setw(2) << hours << ':'
       << setw(2) << minutes << ':'
       << setw(2) << seconds
    ;

  dest << setfill(' ');

  return( dest );
}

      


#endif // ! def _Timer_hh_ 
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
