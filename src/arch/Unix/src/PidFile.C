//
// File:        PidFile.C
// Project:	Clue
// Desc:        
//
//  Compiled sources for PidFile
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     04/15/97 06:29
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "PidFile.hh"
#include <Str.hh>
#include <fstream>
#include <cstdio>

#include <errno.h>

#if defined( CLUE_DEBUG )
#include "PidFile.ii"
#endif

CLUE_VERSION(
  PidFile,
  "$Id$");


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

  errStr = PidFile::getClassName();

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

const char *
PidFile::getClassName( void ) const
{
  return( "PidFile" );
}

const char *
PidFile::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
PidFile::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << PidFile::getClassName() << ":\n"
	 << PidFile::getVersion() << '\n';

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

  ofstream pidFile( fileName );

  if( ! pidFile.good() )
    {
      osErrno = errno;
    }
  else
    {
      pidFile << getpid() << endl;
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


// Revision Log:
//
// $Log$
// Revision 3.2  1997/04/21 09:57:33  houghton
// Port: include errno.h.
//
// Revision 3.1  1997/04/19 09:53:03  houghton
// Initial Version.
//
//
