//
// File:        tDateTime5.C
// Desc:        
//
//  Test DateTime 'add' methods.
//
//   	DateTime &   	add( const DateTime & dt );
//   	DateTime &   	add( long seconds = 1 );
//   	DateTime &   	addSec( long seconds = 1);
//   	DateTime &   	addMin( long minutes = 1 );
//   	DateTime &   	addHour( long hours = 1 );
//   	DateTime &   	addDay( long days = 1 );  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     02/17/95 11:25 
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:49:08  houghton
// Change to Version 2
//
// Revision 1.1  1995/02/20  14:24:46  houghton
// Complete DateTime class test
//
//
static const char * RcsId =
"$Id$";


#include <ClueTest.hh>

#include <DateTime.hh>

int
tDateTime5( void )
{
  {
    // add( const DateTime & dt );

    DateTime	dt( 300 );

    DateTime	value( 100 );

    if( dt.add( value ).getTimeT() != 400 ) ERROR;
    
  }

  {
    // add( long seconds = 1 );

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    if( dt.add( 100 ).getTimeT() != orig + 100 ) ERROR;
    
  }

  {
    // addSec( long seconds = 1);

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    if( dt.addSec( 100 ).getTimeT() != orig + 100 ) ERROR;
    
  }

  {
    // addMin( long minutes = 1 );

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    if( dt.addMin( 30 ).getTimeT() != orig + (30 * 60) ) ERROR;

    if( dt.getHour() != 12 ) ERROR;    
    if( dt.getMinute() != 0 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;
    
  }

  {
    // addHour( long hours = 1 );

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    if( dt.addHour( 30 ).getTimeT() != orig + (30 * 60 * 60) ) ERROR;

    if( dt.getDayOfMonth() != 18 ) ERROR;
    if( dt.getHour() != 17 ) ERROR;    
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;
    
  }

  {
    // addDay( long days = 1 );

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    if( dt.addDay( 30 ).getTimeT() != orig + (24 * 30 * 60 * 60) ) ERROR;

    if( dt.getMonth() != 3 ) ERROR;
    if( dt.getDayOfMonth() != 19 ) ERROR;
    if( dt.getHour() != 11 ) ERROR;    
    if( dt.getMinute() != 30 ) ERROR;
    if( dt.getSecond() != 30 ) ERROR;
    
  }
  return( 0 );
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
