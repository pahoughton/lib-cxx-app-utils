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
// Revision 1.3  1995/11/05 14:44:38  houghton
// Ports and Version ID changes
//
// Revision 1.1  1995/02/13  16:08:46  houghton
// New Style Avl an memory management. Many New Classes
//
//

#include "LogLevel.hh"
#include "Clue.hh"

#include <cstring>

#ifdef   CLUE_DEBUG
#define  inline
#include <LogLevel.ii>
#endif

const char LogLevel::version [] =
LIB_CLUE_VERSION
"$Id$";

const LogLevel::Level	LogLevel::NONE;
const LogLevel::Level	LogLevel::ERROR( 0 );
const LogLevel::Level	LogLevel::ERR( 0 );
const LogLevel::Level	LogLevel::WARNING( 1 );
const LogLevel::Level	LogLevel::WARN( 1 );
const LogLevel::Level	LogLevel::USER_1( 2 );
const LogLevel::Level	LogLevel::USER_2( 3 );
const LogLevel::Level	LogLevel::USER_3( 4 );
const LogLevel::Level	LogLevel::USER_4( 5 );
const LogLevel::Level	LogLevel::INFO( 6 );
const LogLevel::Level	LogLevel::TEST( 7 );
const LogLevel::Level	LogLevel::DEBUG( 8 );
const LogLevel::Level	LogLevel::FUNCT( 9 );
const LogLevel::Level	LogLevel::ALL( 0, true );

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

const char *
LogLevel::getName( const Level level ) const
{
  // NONE is always first
  if( level == NONE ) return( LevelNames[0] );
  
  // all is always the last name
  if( level == ALL ) return( LevelNames[ ArraySize( LevelNames ) - 2 ] );      
    

  for( size_t l = 0; l < (ArraySize( LevelNames )  - 1); l++ )
    {
      if( level.isSet( l ) )
	return( LevelNames[l + 1] );
    }
  
  return( "unknown" );
}

const char * 
LogLevel::getLevelNames( const Level level ) const
{
  static char  names[512];
  names[0] = 0;
  
  // NONE is always first
  if( level == NONE ) return( LevelNames[0] );
  
  // all is always the last name
  if( level == ALL ) return( LevelNames[ ArraySize( LevelNames ) - 2 ] );      

  names[0] = 0;
  
  for( size_t l = 0; l < (ArraySize( LevelNames )  - 1); l++ )
    {
      if( level.isSet( l ) )
	{
	  strcat( names, LevelNames[l + 1] );
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
  output = NONE;

  for( size_t l = 0; LevelNames[l] != 0; l++ )
    {
      if( strstr( lvl, LevelNames[l] ) != 0 )
	{
	  Level  n( l - 1 );
	  setOutput( n | output );
	}
    }
  return( old );
}
      
LogLevel::Level
LogLevel::setCurrent( const char * lvl )
{
  Level old = current;
  
  for( int l = 0; LevelNames[l] != 0; l++ )
    {
      if( strstr( lvl, LevelNames[l] ) != 0 )
	{
	  Level  n( l - 1 );
	  setCurrent( n );
	}
    }
  
  return( old );
}

const char *
LogLevel::getClassName( void ) const
{
  return( "LogLevel" );
}

ostream &
LogLevel::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  dest << "    Output:  " ;
  dest << getLevelNames( getOutput() ) << '\n';
  dest << "    Current: " ;
  dest << getLevelNames( getCurrent() ) << '\n';
  
  dest << "    Output Bits:  " ;
  dest << getOutput() << '\n';
  dest << "    Current Bits: " ;
  dest << getCurrent() << '\n';
  dest << '\n';

  return( dest  );
}
  
  
  
