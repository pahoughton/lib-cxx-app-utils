//
// File:        tDoubleLink.C
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/14/95 10:47 
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:49:12  houghton
// Change to Version 2
//
// Revision 1.1  1995/02/13  16:12:06  houghton
// Initial libClue test - This has a long way to go.
//
//
static const char * RcsId =
"$Id$";

#include <DoubleLink.hh>


int
tDoubleLink( void )
{

  DoubleLink<char>  strings;

  strings.append( "s1" );
  strings.append( "s2" );
  strings.append( "s3" );

  for( Pix n = strings.first();
      n != 0;
      strings.next(n) )
    {
      if( strcmp( strings(n), "s2" ) == 0 )
	{
	  strings.insert( "s1.5",n );
	}
    }

  cout << strings;

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
