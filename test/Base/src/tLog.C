//
// File:        tLog.C
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     06/23/94 09:04 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/02/13 16:12:06  houghton
// Initial libClue test - This has a long way to go.
//
//
static const char RcsId[] =
"$Id$";

#include <Log.hh>
#include <DateRange.hh>

Log  RLog("The.log","ALL");

char * AVar = "The VAR";

int
main( int argc, char * argv[] )
{

  DateRange  dr(time(NULL),120);

  RLog.setFileName( "good.log" );
  RLog.setOutputLevel( "DEBUG" );

  RLog.level( LogLevel::DEBUG ) << argv[0] << " Params: " << endl
                              << "\t" << "Input: " << AVar << endl
                              << "\t" << "Output: " << AVar << endl
                              << "\t" << "Urate: " << AVar << endl
                              << "\t" << "Hold: " << AVar << endl
                              << "\t" << "Syb Serv: " << AVar << endl
                              << "\t" << "Syb DB: " <<  AVar << endl
                              << "\t" << "Syb User: " << AVar << endl
                              << "\t" << "Syb Pwd: " << AVar << endl;

  RLog.level( LogLevel::ERROR )
    << "This Date Range: " << dr
    << endl;
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
