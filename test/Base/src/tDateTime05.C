#include <LibTest.hh>
#include <DateTime.hh>

bool
tDateTime05( LibTest & test )
{
  
  {
    // add( const DateTime & )

    DateTime	dt( 300 );

    DateTime	value( 100 );

    test( dt.add( value ).getTimeT() == 400 );
    
  }

  {
    // add( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    test( dt.add( 100 ).getTimeT() == orig + 100 );
    
  }

  {
    // addSec( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    test( dt.addSec( 100 ).getTimeT() == orig + 100 );
    
  }

  {
    // addMin( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    test( dt.addMin( 30 ).getTimeT() == orig + (30 * 60) );

    test( dt.getHour() == 12 );
    test( dt.getMinute() == 0 );
    test( dt.getSecond() == 30 );
    
  }

  {
    // addHour( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    test( dt.addHour( 30 ).getTimeT() == orig + (30 * 60 * 60) );

    test( dt.getDayOfMonth() == 18 );
    test( dt.getHour() == 17 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );
    
  }

  {
    // addDay( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    test( dt.addDay( 30 ).getTimeT() == orig + (24 * 30 * 60 * 60) );

    test( dt.getMonth() == 3 );
    test( dt.getDayOfMonth() == 19 );
    test( dt.getHour() == 11 );
    test( dt.getMinute() == 30 );
    test( dt.getSecond() == 30 );
    
  }
  return( true );
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
