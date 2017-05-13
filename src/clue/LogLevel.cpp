// 1995-01-29 (cc) <paul4hough@gmail.com>

#include "LogLevel.hpp"
#include "Clue.hpp"
#include "bit"
#include "StringUtils.hpp"
#include <cstring>
#include <string>

namespace clue {

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
const LogLevel::Level	LogLevel::All( INT_ALL_BITS );

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

  for( size_type l = 0; l < (ArraySize( LevelNames )  - 3); l++ )
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

std::ostream &
LogLevel::toStream( std::ostream & dest ) const
{
  dest << getName( current );
  return( dest );
}

const char *
LogLevel::getClassName( void ) const
{
  return( "LogLevel" );
}


std::ostream &
LogLevel::dumpInfo(
  std::ostream & dest,
  const char *   prefix
  ) const
{
  {
    std::string pre;
    pre = prefix;
    pre += "output:  " ;
    pre += "LogLevel::";

    output.dumpInfo( dest, pre.c_str() ) << '\n';
  }

  {
    std::string pre;
    pre =  prefix;
    pre += "current: ";
    pre += "LogLevel::" ;
    current.dumpInfo( dest, pre.c_str() ) << '\n';
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

  if( onBits == true )
    tmp |= curLevel | onBits;

  if( offBits == true )
    tmp = (tmp | curLevel) & ~(offBits);

  return( tmp );
}

} // namespace clue
