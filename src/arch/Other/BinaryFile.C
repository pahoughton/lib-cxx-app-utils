//
// File:        BinaryFile.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/14/95 10:27 
//
// Revision History:
//
// $Log$
// Revision 3.1  1996/11/14 01:25:16  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:04  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  13:11:27  houghton
// Major rework
//
//

#include "BinaryFile.hh"

#include <Str.hh>
#include <Clue.hh>

#include <unistd.h>
#include <fcntl.h>
#include <cerrno>

#ifdef   CLUE_DEBUG
#define  inline
#include <BinaryFile.ii>
#endif

const char BinaryFile::version[] =
LIB_CLUE_VERSION
"$Id$";

const char iBinaryFile::version[] =
LIB_CLUE_VERSION
"$Id$";

const char oBinaryFile::version[] =
LIB_CLUE_VERSION
"$Id$";

const char ioBinaryFile::version[] =
LIB_CLUE_VERSION
"$Id$";

BinaryFile::~BinaryFile( void )
{
  close();
}

bool
BinaryFile::open( const char * fn, ios::open_mode mode, int perm )
{
  osError = 0;
  state = 0;
  fileStat( fn );
  
  if( (fd = ::open( fileName, OpenFlags( mode ), perm ) ) < 0 )
    {
      osError = errno;
      state |= ios::badbit;
    }
  
  return( good() );
}

			 
// getClassName - return the name of this class
const char *
BinaryFile::getClassName( void ) const
{
  return( "BinaryFile" );
}


// error - return a string describing the current state
const char *
BinaryFile::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName();

  if( good() )
    {
       errStr << ": '" << fileName << "' ok.";
    }
  else
    {
      if( osError != 0 )
	errStr << ": '" << fileName << "' - " << strerror( osError );
      else
	errStr << ": '" << fileName << "' - unknown error";
    }

  return( errStr.cstr() );
}

ostream &
BinaryFile::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << "    fd:          " << fd << '\n'
       << "    state:       " << state << '\n'
       << "    osError:     " << osError << '\n'
    ;

  dest << getClassName() << "::";
  fileStat.dumpInfo( dest );
  
  dest << '\n';

  return( dest );
}


bool
iBinaryFile::open( const char * fileName )
{
  return( BinaryFile::open( fileName, ios::in ) );
}

// iBinaryFile

iBinaryFile &
iBinaryFile::read(
  void *    dest,
  size_t    amount
  )
{
  if( ! good() )
    return( *this );
  
  if( (bytesRead = ::read( fd, dest, amount )) == (long)amount )
    return( *this );

  if( bytesRead == 0 )
    {
      state |= ios::eofbit;
      state |= ios::failbit;
      return( *this );
    }
	
  if( bytesRead < 0 )
    {
      state |= ios::badbit;
      osError = errno;
      return( *this );
    }

  char * rDest = (char *) dest;
  
  for( int once; bytesRead < (long)amount; bytesRead += once )
    {
      if( (once = ::read( fd, rDest + bytesRead, amount - bytesRead )) <= 0 )
	{
	  if( once == 0 )
	    {
	      state |= ios::eofbit;
	      state |= ios::failbit;
	      break;
	    }
	  else
	    {
	      state |= ios::badbit;
	      osError = errno;
	      break;
	    }
	}
    } 

  return( *this );

}

const char *
iBinaryFile::getClassName( void ) const
{
  return( "iBinaryFile" );
}

ostream &
iBinaryFile::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << "    bytesRead:   " << bytesRead << '\n'
    ;

  dest << getClassName() << "::";
  BinaryFile::dumpInfo( dest );
  
  dest << '\n';

  return( dest );
}

bool
oBinaryFile::open(
  const char * 	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
{
  return( BinaryFile::open( fileName, mode, perm ) );
}

oBinaryFile &
oBinaryFile::write( const void * src, size_t amount )
{
  if( ! good() )
    return( *this );
  
  int w = ::write( fd, src, amount );

  if( w == (long)amount )
    return( *this );

  if( w == -1 )
    {
      state |= ios::badbit;
      osError = errno;
      return( *this );
    }

  const char * wSrc = (const char *)src;
  
  for( int once; w < (long)amount; w += once )
    {
      if( (once = ::write( fd, wSrc + w, amount - w ) ) < 0 )
	{
	  state |= ios::badbit;
	  osError = errno;
	  break;
	}
    }
  
  return( *this );
}

const char *
oBinaryFile::getClassName( void ) const
{
  return( "oBinaryFile" );
}

ostream &
oBinaryFile::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << getClassName() << "::";
  BinaryFile::dumpInfo( dest );
  
  dest << '\n';

  return( dest );
}


const char *
ioBinaryFile::getClassName( void ) const
{
  return( "ioBinaryFile" );
}


bool
ioBinaryFile::open(
  const char * 	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
{
  return( BinaryFile::open( fileName, mode, perm ) );
}

ostream &
ioBinaryFile::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << getClassName() << "::";
  BinaryFile::dumpInfo( dest );
  
  dest << '\n';

  return( dest );
}

  
  
  


  
  
  


