//
// File:        LogBuf.C
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 13:06 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/02/13 16:08:46  houghton
// New Style Avl an memory management. Many New Classes
//
//
static const char * RcsId =
"$Id$";

#include "LogBuf.hh"

#define LOGBUF_SIZE 512


//
// LogBuf is the streambuf for the log
//

LogBuf::~LogBuf( void )
{
  if( streamIsFile )
    {
      close();
    }

  if( buffer )
    {
      delete buffer;
    }
}

void
LogBuf::initbuf( streambuf * outStream )
{
  stream    	= outStream;  
  streamIsFile 	= FALSE;
  teeStream 	= 0;  

  buffer = new char[LOGBUF_SIZE];
  
  setb( buffer, buffer+LOGBUF_SIZE );
  setp( buffer, buffer+LOGBUF_SIZE );
  
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
  sync();
  if( teeStream )
    {
      teeStream->overflow(c);
    }
  return( stream->overflow(c) );
}

int
LogBuf::underflow( void )
{
  return( stream->underflow() );
}

int
LogBuf::sync( void )
{
  char *    base = pbase();
  int	    len = pptr() - pbase();

  if( logLevel.shouldOutput() && len != 0 && base != 0)
    {
      for( int cnt = stream->sputn( base, len );
	   cnt < len && cnt != 0 && len != 0;
	   len -= cnt, base += cnt );

      if( teeStream )
	{
	  for( int cnt = teeStream->sputn( base, len );
	      cnt < len && cnt != 0 && len != 0;
	      len -= cnt, base += cnt );
	  teeStream->sync();
	}
    }

  setp( pbase(), epptr() );
  
  return( stream->sync() );
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
