//
// File:        DateRange.cc
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 08:57 
//
// Revision History:
//
// $Log$
// Revision 1.2  1994/08/15 20:54:51  houghton
// Split Mapped out of mapped avl.
// Fixed a bunch of bugs.
// Fixed for ident of object modules.
// Prep for Rating QA Testing
//
// Revision 1.1  1994/06/06  13:19:35  houghton
// Lib Clue beta version used for Rating 1.0
//
//
static const char * RcsId =
"$Id$";

#include <Clue.hh>

#include "DateRange.hh"

int
DateRange::isValid( void ) const
{
  return( DateTime::isValid() );
}

time_t
DateRange::secIn( const DateRange & dateTwo ) const
{
  time_t   secs = 0;

  return( UnionOf( getTimeT(), dur, dateTwo.getTimeT(), dateTwo.getDur() ) );
  
  return( secs );
}


time_t
DateRange::startsIn( const DateRange & dateTwo ) const
{
  time_t  secs = 0;

  if( dateTwo.getTimeT() >= getTimeT() &&
      dateTwo.getTimeT() <= (getTimeT() + dur ) )
    {
      secs = secIn( dateTwo );
    }
  return( secs );
}


#ifdef NEXT_SEC_WORKS

// it doesn't right now

time_t
DateRange::nextSec( const DateRange & dateTwo, time_t elapsed ) const
{
  time_t  secs = 0;

  if( (dateTwo.getTimeT() + elapsed) >= getTimeT() &&
      (dateTwo.getTimeT() + elapsed) <= (getTimeT() + dur ) )
    {
      secs = secIn(dateTwo) - elapsed;
    }
  return( secs );
}

#endif

time_t
DateRange::setDur( int newDur )
{
  time_t oldDur = dur;
  dur = newDur;
  
  return( oldDur );
}

time_t
DateRange::getDur( void ) const
{
  return( dur );
}

ostream &
DateRange::streamOutput( ostream & dest ) const
{
  dest << "Start: " << (const DateTime)*this << ' '
       << "Dur: "
       << setfill('0')
       << setw(2) << HourInTimeT( dur ) << ':'
       << setw(2) << MinInTimeT( dur ) << ':'
       << setw(2) << SecInTimeT( dur )
       << setfill(' ')
       ;
  return( dest );
}
    
ostream & operator<<( ostream & dest, const DateRange & range )
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
