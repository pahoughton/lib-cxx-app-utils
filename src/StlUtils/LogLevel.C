//
// File:        LogLevel.C
// Project:	StlUtils
// Desc:        
//              
//  Source code for LogLevel methods.
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 12:45 
//
// Revision History: (See end of file for Revision Log)
//

#include "LogLevel.hh"
#include "StlUtilsUtils.hh"
#include "Bit.hh"
#include "StringUtils.hh"
#include "Str.hh"
#include <cstring>

#if defined( STLUTILS_DEBUG )
#include "LogLevel.ii"
#endif

STLUTILS_VERSION(
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
const LogLevel::Level	LogLevel::All( LONG_ALL_BITS );

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

static const char * LLErr  = "ERR";
static const char * LLWarn = "WARN";


const LogLevel::Name2Level LogLevel::Name2LevelList[] =
{
  { &LogLevel::LevelNames[0],	&LogLevel::None },
  { &LogLevel::LevelNames[1],	&LogLevel::Error },
  { &LLErr,			&LogLevel::Error },
  { &LogLevel::LevelNames[2],	&LogLevel::Warning },
  { &LLWarn,			&LogLevel::Warning },
  { &LogLevel::LevelNames[3],	&LogLevel::App1 },
  { &LogLevel::LevelNames[4],	&LogLevel::App2 },
  { &LogLevel::LevelNames[5],	&LogLevel::App3 },
  { &LogLevel::LevelNames[6],	&LogLevel::App4 },
  { &LogLevel::LevelNames[7],	&LogLevel::App5 },
  { &LogLevel::LevelNames[8],	&LogLevel::App6 },
  { &LogLevel::LevelNames[9],	&LogLevel::Lib1 },
  { &LogLevel::LevelNames[10],	&LogLevel::Lib2 },
  { &LogLevel::LevelNames[11],	&LogLevel::Lib3 },
  { &LogLevel::LevelNames[12],	&LogLevel::Lib4 },
  { &LogLevel::LevelNames[13],	&LogLevel::Info },
  { &LogLevel::LevelNames[14],	&LogLevel::Test },
  { &LogLevel::LevelNames[15],	&LogLevel::Debug },
  { &LogLevel::LevelNames[16],	&LogLevel::Funct },
  { &LogLevel::LevelNames[17],	&LogLevel::All },
  { 0, &LogLevel::None },
};

const char *
LogLevel::getName( const Level & level )
{
  // NONE is always first
  if( level == None )
    return( LevelNames[0] );
  
  // all is always the last name
  if( level == All )
    return( LevelNames[ ArraySize( LevelNames ) - 2 ] );      
    
  for( size_t l = 0; l < (ArraySize( LevelNames )  - 3); l++ )
    {
      if( level( l ) )
	return( LevelNames[ l + 1 ] );
    }
  
  return( 0 );
}

const char * 
LogLevel::getLevelNames( const Level & level )
{
  static char  names[512];
  names[0] = 0;
  
  // NONE is always first
  if( level == None ) return( LevelNames[0] );
  
  // all is always the last name
  if( level == All ) return( LevelNames[ ArraySize( LevelNames ) - 2 ] );      


  names[0] = 0;
  
  for( size_t l = 0; l < (ArraySize( LevelNames )  - 3); l++ )
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


bool
LogLevel::setName( const Level & level, const char * name )
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
    
  for( size_t pos = 0; pos < (ArraySize( LevelNames ) - 3) ; pos++ )
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
  return( output.getBinSize() + current.getBinSize() );
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

  {
    Str pre;
    pre = prefix;
    pre += "output:  " ;
    pre += output.getClassName() ;
    pre += "::";
    
    output.dumpInfo( dest, pre, false ) << '\n';
  }

  {
    Str pre;
    pre =  prefix;
    pre += "current: ";
    pre += current.getClassName();
    pre += "::" ;
    current.dumpInfo( dest, pre, false ) << '\n';
  }
  
  dest << prefix << "output:    " << getLevelNames( output ) << '\n';
  dest << prefix << "current:   " << getLevelNames( current ) << '\n';
    
  
  dest << '\n';

  return( dest  );
}

LogLevel::Level
LogLevel::levelFromString( const char * level, Level curLevel )
{
  // check for ALL
  if( StringCaseSearch( level, NPOS, "All", NPOS ) )
    {
      return( All );
    }

  Level	    tmp = None;
  Level	    offBits;
  Level	    onBits;
  
  for( size_t l = 0; l < (ArraySize( Name2LevelList ) - 2 ); l++ )
    {
      const char * pos;

      pos = StringCaseSearch( level, NPOS,
			      *(Name2LevelList[l].name), NPOS );

      if( pos )
	{
	  if( pos > level )
	    {
	      switch( *( pos - 1) )
		{
		case '+':
		  onBits |= *(Name2LevelList[ l ].level);
		  break;

		case '-':
		  offBits |= *(Name2LevelList[l].level);
		  break;

		default:
		  tmp |= *(Name2LevelList[l].level);
		}
	    }
	  else
	    {
	      tmp |= *(Name2LevelList[l].level);
	    }
	}
    }

  if( onBits )
    tmp |= curLevel | onBits;

  if( offBits )
    tmp = (tmp | curLevel) & ~(offBits);
  
  return( tmp );
}

// Revision Log:
//
// $Log$
// Revision 3.7  1997/09/17 11:08:31  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.6  1997/05/02 12:17:06  houghton
// Changed all LogLevel::Level args to const & to avoid copy constructor calls.
//
// Revision 3.5  1997/03/21 15:38:45  houghton
// Bug-Fix: + and - flags in logLevelfromString were not working.
//
// Revision 3.4  1997/03/21 12:24:04  houghton
// Changed string to log level converter to support +level and
//     -level. These will turn the level on or off respectivly without
//     changeing the state of other levels.
//
// Revision 3.3  1997/03/19 16:25:23  houghton
// Bug-Fix: getName* would return all even if not all bits were set.
// Changed getName now returns 0 if name not found.
//
// Revision 3.2  1997/03/03 14:36:41  houghton
// Removed support for RW Tools++
//
// Revision 3.1  1996/11/14 01:23:48  houghton
// Changed to Release 3
//
// Revision 2.11  1996/11/13 16:58:15  houghton
// Changed include lines from "file" to <file"
//     to accomidate rpm.
// Removed support for short file names.
// Bug-Fix: fixed some compile error associated with the change to
//     RWCString.
//
// Revision 2.10  1996/11/11 13:34:53  houghton
// Changed to use RWCString instead of strstream where possible because
//     of an inconsitancy in the public member of strstream.
//
// Revision 2.9  1996/11/04 18:21:40  houghton
// Chaged include becuase StlUtils.hh was renamed to StlUtilsUtils.hh.
//
// Revision 2.8  1996/11/04 14:14:16  houghton
// Restructure header comments layout.
// Added static Name2Level[] to improve name translation support. Now
//     "Err" and "Warn" can be translated.
// Changed getLevelNames to be a const
// Removed BinStream support.
// Changed dumpInfo to use strstream instead of Str.
//     (as required by Mike Alexandar).
// Added private levelFromString method to convert a string
//     representation of the level to a Level mask.
//
// Revision 2.7  1996/06/11 09:52:35  houghton
// Bug-Fix: setOutput now understands any case.
//
// Revision 2.6  1996/05/03 16:13:21  houghton
// Bug-Fix: remove inline statement.
//
// Revision 2.5  1996/02/29 19:05:36  houghton
// Bug Fix: Cant use static class object to construct other static objects
//
// Revision 2.4  1995/12/04 11:17:24  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
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
