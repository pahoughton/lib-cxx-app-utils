#ifndef _LogBuf_hh_
#define _LogBuf_hh_
//
// File:        LogBuf.hh
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 12:32
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1995/02/13 16:08:46  houghton
// New Style Avl an memory management. Many New Classes
//
//

#include <LogLevel.hh>
#include <iostream.h>
#include <fstream.h>

class LogBuf : public streambuf
{
  
public:
  
  LogBuf( LogLevel::Level   outLevel = LogLevel::ERROR, 
	  streambuf * 	    outStream = 0 );

  LogBuf( const char * 	outLevel,
	  streambuf * 	outStream = 0 );

  virtual ~LogBuf( void );
  
  inline streambuf *	tee( streambuf * teeStreambuf );
  
  inline Bool		isFile( void ) const;
  
  filebuf *	open(const char * name, int om, int prot = filebuf::openprot);
  void          close (void);

  LogLevel &	    level( void );
  const LogLevel &  level( void ) const;

  virtual int	overflow(int=EOF);
  virtual int	underflow();
  virtual int	sync() ;
  
protected:
  
private:

  void initbuf( streambuf * outStream = 0 );
  
  char *    	buffer;
  streambuf *	stream;
  streambuf * 	teeStream;
  Bool		streamIsFile;
  
  LogLevel 	logLevel;
  
};


//
// Inline methods
//

inline
LogBuf::LogBuf(
  LogLevel::Level   outLevel,
  streambuf *	    outStream
  )
  : logLevel( outLevel )
{
  initbuf( outStream );
}

inline
LogBuf::LogBuf(
  const char * 	outLevel,
  streambuf *	outStream
  )
  : logLevel( outLevel )
{
  initbuf( outStream );
}


inline
streambuf *
LogBuf::tee( streambuf * teeStreambuf )
{
  streambuf * old = teeStream;
  teeStream = teeStreambuf;
  return( old );
}

inline Bool
LogBuf::isFile( void ) const
{
  return( streamIsFile );
}

inline
LogLevel &
LogBuf::level( void )
{
  return( logLevel );
}

inline
const LogLevel &
LogBuf::level( void ) const
{
  return( logLevel );
}





#endif // ! def _LogBuf_hh_ 
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
