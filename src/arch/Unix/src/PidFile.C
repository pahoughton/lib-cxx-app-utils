//
// File:        PidFile.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for PidFile
//  
// Author:      Paul A. Houghton - (paul.houghton@mci.com)
// Created:     04/15/97 06:29
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "PidFile.hh"
#include <Str.hh>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <errno.h>

#if defined( STLUTILS_DEBUG )
#include "PidFile.ii"
#endif

STLUTILS_VERSION(
  PidFile,
  "$Id$ ");


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
// 
// %PL%
// 
// $Log$
// Revision 5.3  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:22  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:34  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:09:22  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/07/18 20:05:33  houghton
// Cleanup.
//
// Revision 3.2  1997/04/21 09:57:33  houghton
// Port: include errno.h.
//
// Revision 3.1  1997/04/19 09:53:03  houghton
// Initial Version.
//
//
