//
// File:        tDateTime.C
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     11/03/94 08:56 
//
// Revision History:
//
// $Log$
// Revision 1.2  1995/02/20 14:24:44  houghton
// Complete DateTime class test
//
// Revision 1.1  1995/02/13  16:12:05  houghton
// Initial libClue test - This has a long way to go.
//
//
static const char * RcsId =
"$Id$";

#include <ClueTest.hh>

#include <DateTime.hh>

int tDateTime1( void );
int tDateTime2( void );
int tDateTime3( void );
int tDateTime4( void );
int tDateTime5( void );
int tDateTime6( void );

int
tDateTime( void )
{
  cout << "*** DateTime Test ***" << endl;
  
  putenv( "TZ=CST6CDT" );
  
  return( tDateTime1() ||
	  tDateTime2() ||
	  tDateTime3() ||
	  tDateTime4() ||
	  tDateTime5() ||
	  tDateTime6() );
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
