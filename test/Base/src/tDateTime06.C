#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#include <functional>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#include <functional>
#endif

bool
tDateTime06( LibTest & tester )
{
    // void setTm( void ) - NO TEST (tested by other test)

  {   
    // compare( const DateTime & ) 

    DateTime	d1( "2/17/95 11:30:30" );
    DateTime	d2( d1 );

    TEST( d1 == d2 );
    TEST( ! d1.compare( d2 ) );
    TEST( ! compare( d1, d2 ) );

    d1.setTimeZone();

    TEST( d1 == d2 );
    TEST( ! d1.compare( d2 ) );
    TEST( ! compare( d1, d2 ) );

    d2.setTimeZone();

    TEST( d1 == d2 );
    TEST( ! d1.compare( d2 ) );
    TEST( ! compare( d1, d2 ) );

    d1.addMin();

    TEST( d1.compare( d2 ) > 0 );
    TEST( d1 > d2 );
    TEST( compare( d1, d2 ) > 0 );
    
  }

  {   
    // operator time_t ( void ) const

    DateTime	dt( "2/17/95 11:30:30" );

    TEST( (time_t)dt == dt.getTimeT() );

  }

  {   
    // operator const char * ( void ) const

    DateTime	dt( "2/17/95 11:30:30" );

    char    dtBuf[50];

    dt.getString( dtBuf );

    TEST( ! strcmp( (const char *)dt, dtBuf ) );
    
  }

  {   
    // operator == ( const DateTime & ) const

    DateTime	d1( "2/17/95 11:30:30" );
    DateTime	d2( "2/17/95 11:30:30" );

    TEST( d1 == d2 );
    d2.addSec();
    TEST( d1 != d2 );
    
  }

  {   
    // operator !=( const DateTime & ) const
    
    DateTime	d1( "2/17/95 11:30:30" );
    DateTime	d2( "2/17/95 11:30:30" );

    TEST( d1 == d2 );
    d2.addSec();
    TEST( d1 != d2 );
    
  }

  {   
    // const char * getClassName(void) - NO TEST NEEDED

  }

  {   
    // Bool 	     good( void ) - NO TEST (tested by setValid());

  }

  {   
    // const char * error( void ) - NO TEST NEEDED
    
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









