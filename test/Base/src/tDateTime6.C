//
// File:        tDateTime5.C
// Desc:        
//
//  Test DateTime 'miscellaneous' methods.
//
//  	void 	    setTm( void ) - NO TEST (tested by other test)
//  	int 	    compare( const DateTime & two ) 
//  	operator time_t()
//  	operator const char *()
//  	operator ==( const DateTime & two )
//  	operator !=( const DateTime & two )
//  	const char * getClassName(void) - NO TEST NEEDED
//  	Bool 	     good( void ) - NO TEST (tested by setValid());
//  	const char * error( void ) - NO TEST NEEDED
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     02/17/95 11:25 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/02/20 14:24:47  houghton
// Complete DateTime class test
//
//
static const char * RcsId =
"$Id$";


#include <ClueTest.hh>

#include <DateTime.hh>

int
tDateTime6( void )
{
    // void setTm( void ) - NO TEST (tested by other test)

  {   
    // int compare( const DateTime & two ) 

    DateTime	d1( "2/17/95 11:30:30" );
    DateTime	d2( "2/17/95 11:30:30" );

    if( d1.compare( d2 ) ) ERROR;

    d1.setTimeZone();

    if( ! (d1.compare( d2 ) < 0 ) ) ERROR;

    d2.setTimeZone();

    if( d1.compare( d2 ) ) ERROR;

    d1.addMin();

    if( ! ( d1.compare( d2 ) > 0 ) ) ERROR;
    
  }

  {   
    // operator time_t()

    DateTime	dt( "2/17/95 11:30:30" );

    if( (time_t)dt != dt.getTimeT() ) ERROR;

  }

  {   
    // operator const char *()

    DateTime	dt( "2/17/95 11:30:30" );

    char    dtBuf[50];

    dt.getString( dtBuf );

    if( strcmp( (const char *)dt, dtBuf ) ) ERROR;
    
  }

  {   
    // operator ==( const DateTime & two )

    DateTime	d1( "2/17/95 11:30:30" );
    DateTime	d2( "2/17/95 11:30:30" );

    if( ! (d1 == d2) ) ERROR;
    d2.addSec();
    if( d1 == d2 ) ERROR;
    
  }

  {   
    // operator !=( const DateTime & two )
    DateTime	d1( "2/17/95 11:30:30" );
    DateTime	d2( "2/17/95 11:30:30" );

    if( d1 != d2 ) ERROR;
    d2.addSec();
    if( ! (d1 != d2) ) ERROR;
    
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
