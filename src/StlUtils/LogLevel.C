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
// Revision 2.5  1996/02/29 19:05:36  houghton
// Bug Fix: Cant use static class object to construct other static objects
//
// Revision 2.4  1995/12/04 11:17:24  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.3  1995/11/12  22:08:05  houghton
// Bug fix - setName() - junk code from copy (cut out).
//
// Revision 2.2  1995/11/12  18:04:21  houghton
// Change LogLevel::XXXX to LogLevel::Xxxxx.
// Bug fix - setOutput( const char * ) was not detecting 'ALL' correctly.
//
// Revision 2.1  1995/11/10  12:40:46  houghton
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
#include "Bit.hh"
#include <cstring>
#else
#include "LogLvl.hh"
#include "Clue.hh"
#include "Str.hh"
#include "Bit.hh"
#include <cstring>
#endif

#if defined( CLUE_DEBUG )
#if !defined( CLUE_SHORT_FN )
#include "LogLevel.ii"
#else
#include "LogLvl.ii"
#endif
#endif

CLUE_VERSION(
  LogLevel,
  "$Id$" );

const LogLevel::Level	LogLevel::None;
const LogLevel::Level	LogLevel::Error( Bit(0) );
const LogLevel::Level	LogLevel::Err( Bit(0) );
const LogLevel::Level	LogLevel::Warning( Bit(1) );
const LogLevel::Level	LogLevel::Warn( Bit(1) );
const LogLevel::Level	LogLevel::App1( Bit(2) );
const LogLevel::Level	LogLevel::App2( Bit(3) );
const LogLevel::Level	LogLevel::App3( Bit(4) );
const LogLevel::Level	LogLevel::App4( Bit(5) );
const LogLevel::Level	LogLevel::App5( Bit(6) );
const LogLevel::Level	LogLevel::App6( Bit(7) );
const LogLevel::Level	LogLevel::Lib1( Bit(8) );
const LogLevel::Level	LogLevel::Lib2( Bit(9) );
const LogLevel::Level	LogLevel::Lib3( Bit(10) );
const LogLevel::Level	LogLevel::Lib4( Bit(11) );
const LogLevel::Level	LogLevel::Info( Bit(12) );
const LogLevel::Level	LogLevel::Test( Bit(13) );
const LogLevel::Level	LogLevel::Debug( Bit(14) );
const LogLevel::Level	LogLevel::Funct( Bit(15) );
const LogLevel::Level	LogLevel::All( ~0UL );

const char * LogLevel::LevelNames[] =
{
  "NONE",
  "ERROR",
  "WARNING",
  "APP1",
  "APP2",
  "APP3",
  "APP4",
  "APP5",
  "APP6",
  "LIB1",
  "LIB2",
  "LIB3",
  "LIB4",
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
  if( level == None ) return( LevelNames[0] );
  
  // all is always the last name
  if( level == All ) return( LevelNames[ ArraySize( LevelNames ) - 2 ] );      
    

  for( size_t l = 0; l < (ArraySize( LevelNames )  - 1); l++ )
    {
      if( level( l ) )
	return( LevelNames[ l + 1 ] );
    }
  
  return( "unknown" );
}

const char * 
LogLevel::getLevelNames( const Level level ) const
{
  static char  names[512];
  names[0] = 0;
  
  // NONE is always first
  if( level == None ) return( LevelNames[0] );
  
  // all is always the last name
  if( level == All ) return( LevelNames[ ArraySize( LevelNames ) - 2 ] );      


  names[0] = 0;
  
  for( size_t l = 0; l < (ArraySize( LevelNames )  - 1); l++ )
    {
      if( level.test( l ) )
	{
	  strcat( names, LevelNames[l + 1] );
	  strcat( names, " | " );
	}
    }

  names[ strlen( names ) - 3 ] = 0;
    
  return( names );
}    

LogLevel::Level
LogLevel::setOutput( const char * level )
{
  Level old = output;
  output = None;

  // check for ALL
  if( strstr( level, LevelNames[ ArraySize( LevelNames ) - 2 ] ) != 0 )
    {
      setOutput( All );
      return( old );
    }
  
  for( size_t l = 0; l < (ArraySize( LevelNames ) - 2 ); l++ )
    {
      if( strstr( level, LevelNames[l] ) != 0 )
	{
	  Level  n( Bit( l - 1 ) );
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
	  Level  n( Bit( l - 1 ) );
	  setCurrent( n );
	}
    }
  
  return( old );
}

inline
bool
LogLevel::setName( const Level level, const char * name )
{
  // NONE is always first
  if( level == None )
    {
      LevelNames[0] = name;
      return( true );
    }
  
  // all is always the last name
  if( level == All )
    {
      LevelNames[ ArraySize( LevelNames ) - 2 ] = name;
      return( true );
    }
    
  for( size_t pos = 0; pos < (ArraySize( LevelNames ) - 1) ; pos++ )
    {
      if( level( pos ) )
	{
	  LevelNames[ pos + 1 ] = name;
	  return( true );
	}
    }

  return( false );
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

  
  
