//
// File:        LogLevel.C
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 12:45 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/02/13 16:08:46  houghton
// New Style Avl an memory management. Many New Classes
//
//
static const char * RcsId =
"$Id$";

#include "LogLevel.hh"


const char * LogLevel::LevelNames[] =
{
  "NONE",
  "ERROR",
  "WARNING",
  "USER 1",
  "USER 2",
  "USER 3",
  "USER 4",
  "INFO",
  "TEST",
  "DEBUG",
  "FUNCT",
  "ALL",
  0
};

const LogLevel::Level Levels[] =
{
  LogLevel::NONE,
  LogLevel::ERROR,
  LogLevel::WARNING,
  LogLevel::USR_1,
  LogLevel::USR_2,
  LogLevel::USR_3,
  LogLevel::USR_4,
  LogLevel::INFO,
  LogLevel::TEST,
  LogLevel::DEBUG,
  LogLevel::FUNCT,
  LogLevel::ALL
};

#define LAST_LEVEL  ( sizeof( Levels ) / sizeof( Levels[0] ) )
const char *
LogLevel::getName( Level level )
{
  // NONE is always first
  if( level == NONE ) return( LevelNames[0] );
  
  // all is always the last name
  if( level == ALL ) return( LevelNames[ LAST_LEVEL - 1 ] );      
    

  for( int l = 1; l < LAST_LEVEL  - 1; l++ )
    {
      if( level & Levels[l] )
	{
	  return( LevelNames[l] );
	}
    }
  
  return( "unknown" );
}

const char * 
LogLevel::getLevelNames( Level level )
{
  static char  names[512];
  names[0] = 0;
  
  // NONE is always first
  if( level == NONE ) return( LevelNames[0] );
  
  // all is always the last name
  if( level == ALL ) return( LevelNames[ LAST_LEVEL - 1 ] );      

  names[0] = 0;
  
  for( int l = 1; l < LAST_LEVEL  - 1; l++ )
    {
      if( level & Levels[l] )
	{
	  strcat( names, LevelNames[l] );
	  strcat( names, " | " );
	}
    }

  names[ strlen( names ) - 3 ] = 0;
    
  return( names );
}    

LogLevel::Level
LogLevel::setOutput( const char * lvl )
{
  Level old = output;
  output = LogLevel::NONE;

  for( int l = 0;
       LevelNames[l] != 0;
       l++ )
    {
      if( strstr( lvl, LevelNames[l] ) != 0 )
	{
	  setOutput( (LogLevel::Level) (Levels[l] | output) );
	}
    }
  
  return( old );
}
      
LogLevel::Level
LogLevel::setCurrent( const char * lvl )
{
  Level old = current;
  
  for( int l = 0;
       LevelNames[l] != 0;
       l++ )
    {
      if( strstr( lvl, LevelNames[l] ) != 0 )
	{
	  setCurrent( (LogLevel::Level) (Levels[l] | current) );
	}
    }
  
  return( old );
}
      

  
void
LogLevel::setName( Level lvl, const char * name )
{
  if( lvl & USR_1 ) 	LevelNames[3] = name;
  if( lvl & USR_2 ) 	LevelNames[4] = name;
  if( lvl & USR_3 ) 	LevelNames[5] = name;
  if( lvl & USR_4 ) 	LevelNames[6] = name;
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
