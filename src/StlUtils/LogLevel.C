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
// Revision 2.1  1995/11/10 12:40:46  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  15:28:40  houghton
// Revised
//
// Revision 1.1  1995/02/13  16:08:46  houghton
// New Style Avl an memory management. Many New Classes
//
//

#if !defined( CLUE_SHORT_FN )
#include "LogLevel.hh"
#include "Clue.hh"
#include "Str.hh"
#include <cstring>
#else
#include "LogLvl.hh"
#include "Clue.hh"
#include "Str.hh"
#include <cstring>
#endif

#if defined( CLUE_DEBUG )
#define  inline
#if !defined( CLUE_SHORT_FN )
#include "LogLevel.ii"
#else
#include "LogLvl.ii"
#endif
#endif

CLUE_VERSION(
  LogLevel,
  "$Id$" );

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

size_t
LogLevel::getBinSize( void ) const
{
  return( Sizeof( output ) + Sizeof( current ) );
}

BinStream &
LogLevel::write( BinStream & dest ) const
{
  dest.write( output );
  dest.write( current );
  return( dest );
}

BinStream &
LogLevel::read( BinStream & src )
{
  src.read( output );
  src.read( current );
  return( src );
}

ostream &
LogLevel::write( ostream & dest ) const
{
  output.write( dest );
  current.write( dest );
  return( dest );
}

istream &
LogLevel::read( istream & src )
{
  output.read( src );
  current.read( src );
  return( src );
}

ostream &
LogLevel::toStream( ostream & dest ) const
{
  dest << getName( current );
  return( dest );
}

const char *
LogLevel::getClassName( void ) const
{
  return( "LogLevel" );
}

const char *
LogLevel::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer, output.getVersion( false ) ) );
}
  

ostream &
LogLevel::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << LogLevel::getClassName() << ":\n"
	 << LogLevel::getVersion() << '\n';

  Str pre;
  pre = prefix ;
  pre << "output:" << output.getClassName() << "::";
  output.dumpInfo( dest, pre, false );

  pre = prefix;
  pre << "current:" << current.getClassName() << "::";
  current.dumpInfo( dest, pre, false );
  
  dest << prefix << "output:    " << getLevelNames( output ) << '\n'
       << prefix << "current:   " << getLevelNames( current ) << '\n'
    ;
  
  dest << '\n';

  return( dest  );
}

  
  
