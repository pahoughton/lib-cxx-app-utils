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
// Revision 1.1  1995/02/13 16:12:05  houghton
// Initial libClue test - This has a long way to go.
//
//
static const char * RcsId =
"$Id$";

#include <DateTime.hh>

int
tDateTime( void )
{
  cout << "*** DateTime Test ***" << endl;
  
  {
    DateTime dt;
    cout << dt << endl;;
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
