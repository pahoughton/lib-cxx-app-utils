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
// 
// $Log$
// Revision 1.1  1994/06/06 13:19:40  houghton
// Lib Clue beta version used for Rating 1.0
//
//

#include <Common.h>
#include <iostream.h>
#include <iomanip.h>

#include <fstream.h>

#define WHERE  __FILE__ << " (" << __LINE__ << ") "

class LogLevel 
{
public:
  
  enum Level {
    NONE	= 0x0000,
    ERROR	= 0x0001,
    WARNING	= 0x0002,
    USR_1	= 0x0100,
    USR_2	= 0x0200,
    USR_3	= 0x0400,
    USR_4	= 0x0800,
    TEST       	= 0x2000,
    DEBUG	= 0x4000,
    FUNCT	= 0x8000,
    ALL		= 0xffff
  };

  LogLevel( Level out = NONE );
  LogLevel( const char * out );
  
  
  inline Level 	setOutput( Level lvl );
  Level		setOutput( const char * lvl );
  
  inline Level 	setCurrent( Level lvl );
  Level		setCurrent( const char * lvl );

  inline Level		getOutput( void ) const;
  inline Level		getCurrent( void  ) const;
  
  const char *	getName( Level lvl );
  const char * 	getLevelNames( Level lvl );
  
  void		setName( Level lvl, const char * name );
  int 		checkCurrent( void ) const;
  
private:

  static const char * LevelNames[];
  Level	output;
  Level current;
  
};

    
class LogBuf : public streambuf
{
  
public:
  LogBuf( const LogLevel * lvl);
  LogBuf( streambuf * buf, const LogLevel * lvl );
  
  LogBuf(int fd);
  LogBuf(int fd, char*  p, int l) ;

  filebuf *	open(const char * name, int om, int prot=filebuf::openprot);
  void          close (void);
  
  virtual int	overflow(int=EOF);
  virtual int	underflow();
  virtual int	sync() ;
  
  streambuf *	rdbuf();
  
  
protected:
  
private:

  int			needToDelete;
  streambuf *		stream;
  
  const LogLevel *	level;
  
};


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

  Log & 		level( LogLevel::Level lvl );
  Log & 		level( const char * lvl );

  void			on( LogLevel::Level out );
  void			off( LogLevel::Level out );
  
  inline LogLevel::Level 	getCurrent( void  ) const;
  inline LogLevel::Level	getOutput( void ) const;


  void			setFileName( const char * outFn, int mode = ios::app );
  void			open( const char * outFn, int mode = ios::app );
  void			close( void );
  
  LogLevel::Level	setOutputLevel( const char * outLevel );
  inline int		setLevelStamp( int stamp );
  inline int		setTimeStamp( int stamp );

  
protected:

private:

  Log( const Log & copyFrom );
  Log & operator=( const Log & assignFrom );

  LogBuf	buf;
  
  LogLevel	logLevel;
  int		timeStamp;
  int		levelStamp;
  
};


//
// Inline methods
//

//
// LogLevel Class
//

inline
LogLevel::LogLevel( Level out )
{
  current = NONE;
  output = out;
}


inline LogLevel::Level
LogLevel::setCurrent( LogLevel::Level level )
{
  Level	prev = current;
  current = level;
  return( prev );
}

inline LogLevel::Level
LogLevel::setOutput( LogLevel::Level level )
{
  Level	prev = output;
  output = level;
  return( prev );
}

inline  LogLevel::Level
LogLevel::getOutput( void ) const
{
  return( output );
}

inline LogLevel::Level
LogLevel::getCurrent( void  ) const
{
  return( current );
}


inline int
LogLevel::checkCurrent( void ) const
{
//  cout << "out: " << output << " cur: " << current << endl;
  return( output & current );
}
  

//
// Log Class inlines
//

inline void
Log::on( LogLevel::Level out )
{
  logLevel.setOutput( (LogLevel::Level) (getOutput() | out) );
}

inline void
Log::off( LogLevel::Level out )
{
  logLevel.setOutput( (LogLevel::Level) (getOutput() & out) );
}

inline LogLevel::Level
Log::getCurrent( void ) const
{
  return( logLevel.getCurrent() );
}

inline LogLevel::Level
Log::getOutput( void  ) const
{
  return( logLevel.getOutput() );
}

inline int
Log::setLevelStamp( int stamp )
{
  int prev = levelStamp;
  levelStamp = stamp;
  return( prev );
}

inline int
Log::setTimeStamp( int stamp )
{
  int prev = timeStamp;
  timeStamp = stamp;
  return( prev );
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
