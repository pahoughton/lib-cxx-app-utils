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
// Revision 1.3  1995/02/13 16:08:45  houghton
// New Style Avl an memory management. Many New Classes
//
// Revision 1.2  1994/08/15  20:54:55  houghton
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

Log::Log(
    const char * 	fileName,
    LogLevel::Level 	out,
    int			openMode,
    int			stampLevel,
    int			stampTime
    )
: ios( new LogBuf(out) )
{
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
  : ios( new LogBuf( out ) )
{
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
: ios( new LogBuf( out, outstr.rdbuf() ) )
{
  tie( &outstr );
        
  timeStamp = stampTime;
  levelStamp = stampLevel;
}

Log::Log(
    ostream & 		outstr,
    const char *	out,
    int			stampLevel,
    int			stampTime
    )
: ios( new LogBuf( out, outstr.rdbuf() ) )
{

  tie( &outstr );
          
  timeStamp = stampTime;
  levelStamp = stampLevel;
}

void
Log::tee( ostream & teeStream )
{
  rdbuf()->tee( teeStream.rdbuf() );
}

void
Log::open( const char * outFn, int mode )
{
  rdbuf()->close();
  if( rdbuf()->open( outFn, mode ) == 0 )
    {
      setstate( failbit );
    }
}

void
Log::setFileName( const char * outFn, int mode )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate( eofbit | failbit );
    }
  open( outFn, mode );
}

void
Log::close( void )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate( eofbit | failbit );
    }
  
  rdbuf()->close();
}

Log &
Log::level( LogLevel::Level lvl )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate(failbit|eofbit);
    }
  
  rdbuf()->level().setCurrent( lvl );

  if( timeStamp != OFF )
    {
      DateTime  now( time(0), TRUE );

      *this << now << ' ';
    }

  if( levelStamp != OFF )
    {
      *this << rdbuf()->level().getName( lvl ) << ' ';
    }
  
  return( *this );
}

Log &
Log::level( const char * lvl )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate( failbit | eofbit );
    }
  
  rdbuf()->level().setCurrent( lvl );

  if( timeStamp != OFF )
    {
      DateTime  now( time(0), TRUE );

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
  return( rdbuf()->level().setOutput( level ) );
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
