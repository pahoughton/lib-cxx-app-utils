//
// File:        DateTime.cc
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     02/24/94 06:46 
//
// Revision History:
//
// $Log$
// Revision 1.2  1994/08/15 20:54:53  houghton
// Split Mapped out of mapped avl.
// Fixed a bunch of bugs.
// Fixed for ident of object modules.
// Prep for Rating QA Testing
//
// Revision 1.1  1994/06/06  13:19:37  houghton
// Lib Clue beta version used for Rating 1.0
//
//
static const char * RcsId =
"$Id$";

#include <iostream.h>

#include "DateTime.hh"


DateTime::~DateTime( void )
{
}

//
// Note: the epoch (1/1/1970) was a thursday
//
int
DateTime::getDayOfWeek( void ) const
{
  return( ((seconds / SEC_PER_DAY) + 4) % 7  );
}



ostream & operator<<( ostream & dest, const DateTime & time )
{

  int fill = dest.fill();
  
  dest << setw(2) << setfill('0') << time.getMonth() << '/' 
       << setw(2) << setfill('0') << time.getDayOfMonth() << '/' 
       << setw(2) << setfill('0') << time.getYearOfCentury() << ' '
       << setw(2) << setfill('0') << time.getHour() << ':'
       << setw(2) << setfill('0') << time.getMinute() << ':'
       << setw(2) << setfill('0') << time.getSecond()
       ;
  dest << setfill(fill);
  
  return( dest );
}

ostream & operator<<( ostream & dest, DateTime & time )
{

  int fill = dest.fill();
  
  dest << setw(2) << setfill('0') << time.getMonth() << '/' 
       << setw(2) << setfill('0') << time.getDayOfMonth() << '/' 
       << setw(2) << setfill('0') << time.getYearOfCentury() << ' '
       << setw(2) << setfill('0') << time.getHour() << ':'
       << setw(2) << setfill('0') << time.getMinute() << ':'
       << setw(2) << setfill('0') << time.getSecond()
       ;
  dest << setfill(fill);
  
  return( dest );
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
