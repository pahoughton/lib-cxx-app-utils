// 1997-04-15 (cc) Paul Houghton <paul4hough@gmail.com>

#include "PidFile.hpp"
#include "Str.hpp"

#include <fstream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <errno.h>

namespace clue {

PidFile::PidFile( const char * fullName )
  : fileName( fullName ),
    osErrno( 0 )
{
  createPidFile();
}

PidFile::PidFile(
  const char * path,
  const char * name,
  const char * ext
  )
  : fileName( path, name, ext ),
    osErrno( 0 )
{
  createPidFile();
}


PidFile::~PidFile( void )
{
  removePidFile();
}

bool
PidFile::good( void ) const
{
  return( osErrno == 0 );
}

const char *
PidFile::error( void ) const
{
  static Str errStr;

  errStr = "PidFile";

  if( good() )
    {
       errStr += ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( osErrno != 0 )
	errStr << ": '" << fileName << "' " << strerror( osErrno );

      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}

std::ostream &
PidFile::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! PidFile::good() )
    dest << prefix << "Error: " << PidFile::error() << '\n';
  else
    dest << prefix << "Good" << '\n';


  dest << prefix << "fileName:   " << fileName << '\n'
       << prefix << "pid:        " << getpid() << '\n'
    ;

  return( dest );
}

bool
PidFile::createPidFile( void )
{

  remove( fileName );

  std::ofstream pidFile( fileName );

  if( ! pidFile.good() )
    {
      osErrno = errno;
    }
  else
    {
      pidFile << getpid() << std::endl;
    }

  if( ! pidFile.good() )
    osErrno = errno;

  pidFile.close();

  return( good() );

}

bool
PidFile::removePidFile( void )
{
  remove( fileName );
  return( true );
}

};
