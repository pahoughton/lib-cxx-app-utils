#ifndef _Log_hh_
#define _Log_hh_
//
// File:        Log.hh
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     03/14/94 10:49
//
// Revision History:
//
//  1/29/95 - pah - split out LogLevel and LogBuf classses into
//  	their own files (LogLevel.(hh C) & LogBuf.(hh C)
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
// Revision 1.1  1994/06/06  13:19:40  houghton
// Lib Clue beta version used for Rating 1.0
//
//

#include <Clue.hh>
#include <LogLevel.hh>
#include <LogBuf.hh>

#include <iostream.h>
#include <iomanip.h>

#include <fstream.h>

#define WHERE  __FILE__ << " (" << __LINE__ << ") "


class Log : public ostream
{

public:

  Log( const char * 	fileName,
       LogLevel::Level 	out,
       int		openMode = ios::app,
       int		stampLevel = ON,
       int		stampTime = ON );

  Log( const char * 	fileName,
       const char *     outLevel,
       int		openMode = ios::app,
       int		stampLevel = ON,
       int		stampTime = ON );

  Log( ostream & 	outstr,
       LogLevel::Level 	out,
       int		stampLevel = ON,
       int		stampTime = ON );

  Log( ostream & 	outstr,
       const char *     outLevel,
       int		stampLevel = ON,
       int		stampTime = ON );

  void 	    	    	tee( ostream & teeStream );
  
  Log & 		level( LogLevel::Level curren = LogLevel::ERROR );
  Log &	    	    	operator()( LogLevel::Level current = LogLevel::ERROR );

  Log & 		level( const char * current );  
  Log &     	    	operator()( const char * current );
  
  void			on( LogLevel::Level output );
  void			off( LogLevel::Level output );
  
  inline LogLevel::Level 	getCurrent( void  ) const;
  inline LogLevel::Level	getOutput( void ) const;


  void			setFileName( const char * outFn, int mode = ios::app );
  void			open( const char * outFn, int mode = ios::app );
  void			close( void );
  
  LogLevel::Level	setOutputLevel( const char * output );
  LogLevel::Level	setOutputLevel( LogLevel::Level output );
  
  inline Bool		setLevelStamp( Bool stamp );
  inline Bool		setTimeStamp( Bool stamp );

  inline LogBuf *  	rdbuf( void );
  inline const LogBuf * rdbuf( void ) const;
  
protected:

private:

  Log( const Log & copyFrom );
  Log & operator=( const Log & assignFrom );

  Bool		timeStamp;
  Bool		levelStamp;
  
};


//
// Inline methods
//



//
// Log Class inlines
//

inline void
Log::on( LogLevel::Level out )
{
  rdbuf()->level().setOutput( (LogLevel::Level) (getOutput() | out) );
}

inline void
Log::off( LogLevel::Level out )
{
  rdbuf()->level().setOutput( (LogLevel::Level) (getOutput() & out) );
}

inline LogLevel::Level
Log::getCurrent( void ) const
{
  return( rdbuf()->level().getCurrent() );
}

inline LogLevel::Level
Log::getOutput( void  ) const
{
  return( rdbuf()->level().getOutput() );
}

inline
Bool
Log::setLevelStamp( int stamp )
{
  Bool old = levelStamp;
  levelStamp = stamp;
  return( old );
}

inline
Bool
Log::setTimeStamp( int stamp )
{
  Bool old = timeStamp;
  timeStamp = stamp;
  return( old );
}

inline Log &
Log::operator()( LogLevel::Level lvl )
{
  return( level( lvl ) );
}

inline Log &
Log::operator()( const char * lvl )
{
  return( level( lvl ) );
}

inline
LogBuf *
Log::rdbuf( void )
{
  return( (LogBuf *)(ios::rdbuf()) );
}

const LogBuf *
Log::rdbuf( void ) const
{
  return( (const LogBuf *)(bp) );
}

#endif // ! def _Log_hh_ 
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
