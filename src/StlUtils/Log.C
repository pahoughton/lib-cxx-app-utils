//
// File:        Log.C
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     03/14/94 12:22 
//
// Revision History:
//
// $Log$
// Revision 1.2  1994/08/15 20:54:55  houghton
// Split Mapped out of mapped avl.
// Fixed a bunch of bugs.
// Fixed for ident of object modules.
// Prep for Rating QA Testing
//
// Revision 1.1  1994/06/06  13:19:39  houghton
// Lib Clue beta version used for Rating 1.0
//
//
static const char * RcsId =
"$Id$";

#include "Log.hh"
#include <DateTime.hh>

const char * LogLevel::LevelNames[] =
{
  "NONE",
  "ERROR",
  "WARNING",
  "USER 1",
  "USER 2",
  "USER 3",
  "USER 4",
  "TEST",
  "DEBUG",
  "FUNCT",
  "ALL",
  NULL
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
  LogLevel::TEST,
  LogLevel::DEBUG,
  LogLevel::FUNCT,
  LogLevel::ALL
};

LogLevel::LogLevel( const char * out )
{
  current = NONE;
  setOutput( out );
}

const char *
LogLevel::getName( Level lvl )
{
  if( lvl == 0 ) 	return( LevelNames[0] );
  if( lvl == ALL ) 	return( LevelNames[10] );
  if( lvl & ERROR ) 	return( LevelNames[1] );
  if( lvl & WARNING ) 	return( LevelNames[2] );
  if( lvl & USR_1 ) 	return( LevelNames[3] );
  if( lvl & USR_2 ) 	return( LevelNames[4] );
  if( lvl & USR_3 ) 	return( LevelNames[5] );
  if( lvl & USR_4 ) 	return( LevelNames[6] );
  if( lvl & TEST ) 	return( LevelNames[7] );
  if( lvl & DEBUG ) 	return( LevelNames[8] );
  if( lvl & FUNCT ) 	return( LevelNames[9] );

  return( "unknown" );
}    

const char * 
LogLevel::getLevelNames( Level lvl )
{
  static char  names[512];
  names[0] = 0;
  
  if( lvl == 0 )
    {
      strcpy( names, LevelNames[0] );
      return( names );
    }
  
  if( lvl == ALL )
    {
      strcpy( names, LevelNames[10] );
      return( names );
    }
  
  if( lvl & ERROR ) 	strcat( names, LevelNames[1] );
  if( lvl & WARNING )
    {
      if( names[0] != 0 ) strcat( names," | " );
      strcat( names, LevelNames[2] );
    }
  
  if( lvl & USR_1 )
    {
      if( names[0] != 0 ) strcat( names," | " );
      strcat( names, LevelNames[3] );
    }
  
  if( lvl & USR_2 )
    {
      if( names[0] != 0 ) strcat( names," | " );
      strcat( names, LevelNames[4] );
    }
  if( lvl & USR_3 )
    {
      if( names[0] != 0 ) strcat( names," | " );
      strcat( names, LevelNames[5] );
    }
  if( lvl & USR_4 )
    {
      if( names[0] != 0 ) strcat( names," | " );
      strcat( names, LevelNames[6] );
    }
  if( lvl & TEST )
    {
      if( names[0] != 0 ) strcat( names," | " );
      strcat( names, LevelNames[7] );
    }
  if( lvl & DEBUG )
    {
      if( names[0] != 0 ) strcat( names," | " );
      strcat( names, LevelNames[8] );
    }
  if( lvl & FUNCT )
    {
      if( names[0] != 0 ) strcat( names," | " );
      strcat( names, LevelNames[9] );
    }
  
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
  
LogBuf::LogBuf( const LogLevel * lvl  )
{
  setbuf( new char[512], 512 );
  needToDelete = 1;
  stream = 0;

  streamIsFile = FALSE;
  level = lvl;
}

LogBuf::LogBuf(
    streambuf * 	buf,
    const LogLevel * 	lvl  )
{
  setbuf( new char[512], 512 );

  needToDelete = 0;
  stream = buf;
  
  streamIsFile = FALSE;
  level = lvl;
}

filebuf *
LogBuf::open(
    const char * name,
    int          om,
    int          prot )
{
  if( stream != 0 && isFile() )
    {
      close();
    }


  filebuf * file = new filebuf();

  stream = file;

  streamIsFile = TRUE;
  return( file->open( name, om, prot ) );
  
}


void
LogBuf::close( void )
{
  if( isFile() )
    {
      if( stream != 0 )
	{
	  filebuf * file = (filebuf *)stream;
  
	  file->close();
	  delete file;
	}
    }
  streamIsFile = FALSE;
  stream = 0;
}

int 
LogBuf::overflow( int c )
{
  char * 	base = pbase();
  int	len = pptr() - pbase();
  
  if( level->checkCurrent() && len != 0 && base != 0)
    {

      for( int cnt = stream->sputn( base, len );
	   cnt < len && cnt != 0 && len != 0;
	   len -= cnt, base += cnt );

      setp( pbase(), epptr() );
      int ret = stream->overflow(c);
      return( ret );
    }
  else
    {
      setp( pbase(), epptr() );
      return( 255 );
    }
}

int
LogBuf::underflow( void )
{
  return( stream->underflow() );
}

int
LogBuf::sync( void )
{
  return( stream->sync() );
}


//
// Log Class
//

Log::Log(
    const char * 	fileName,
    LogLevel::Level 	out,
    int			openMode,
    int			stampLevel,
    int			stampTime
    )
: buf( &logLevel ), logLevel( out )
{
  init( &buf );
  open( fileName, openMode );
  timeStamp = stampTime;
  levelStamp = stampLevel;
  
}

Log::Log(
    const char * 	fileName,
    const char *	out,
    int			openMode,
    int			stampLevel,
    int			stampTime
    )
: buf( &logLevel ), logLevel( out )
{
  init( &buf );
  open( fileName, openMode );
  timeStamp = stampTime;
  levelStamp = stampLevel;
  
}

Log::Log(
    ostream & 		outstr,
    LogLevel::Level 	out,
    int			stampLevel,
    int			stampTime
    )
: buf( outstr.rdbuf(), &logLevel ), logLevel( out )
{
  init( &buf );
  timeStamp = stampTime;
  levelStamp = stampLevel;
}

void
Log::open( const char * outFn, int mode )
{
  buf.close();
  if( buf.open( outFn, mode ) == 0 )
    {
      setstate( failbit );
    }
}

void
Log::setFileName( const char * outFn, int mode )
{
  if( buf.sync() == EOF )
    {
      setstate( eofbit | failbit );
    }
  open( outFn, mode );
}

void
Log::close( void )
{
  if( buf.sync() == EOF )
    {
      setstate( eofbit | failbit );
    }
  
  buf.close();
}

Log &
Log::level( LogLevel::Level lvl )
{
  if( buf.sync() == EOF )
    {
      setstate(failbit|eofbit);
    }
  
  logLevel.setCurrent( lvl );

  if( timeStamp != OFF )
    {
      DateTime  now( time(0) );

      *this << now << ' ';
    }

  if( levelStamp != OFF )
    {
      *this << logLevel.getName( lvl ) << ' ';
    }
  
  return( *this );
}

Log &
Log::level( const char * lvl )
{
  if( buf.sync() == EOF )
    {
      setstate( failbit | eofbit );
    }
  
  logLevel.setCurrent( lvl );

  if( timeStamp != OFF )
    {
      DateTime  now( time(0) );

      *this << now << ' ';
    }

  if( levelStamp != OFF )
    {
      *this << lvl  << ' ';
    }
  
  return( *this );
}

LogLevel::Level
Log::setOutputLevel( const char * level )
{
  return( logLevel.setOutput( level ) );
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
