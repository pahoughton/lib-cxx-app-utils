//
// File:        Mutex.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled source for Mutex.
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     02/06/96 07:15
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
// $Id$ 

#include "Mutex.hh"
#include "Str.hh"
#include <strstream.h>

#if defined( STLUTILS_DEBUG )
#include "Mutex.ii"
#endif

STLUTILS_VERSION(
  Mutex,
  "$Id$ ");

#if defined( STLUTILS_THREADS )

Mutex::Mutex( void )
  : errorNum( 0 )
{
  errorNum = pthread_mutex_init( &mutex, 0 );
}

Mutex::~Mutex( void )
{
  pthread_mutex_destroy( &mutex );
}

bool
Mutex::lock( void )
{
  errorNum = pthread_mutex_lock( &mutex );
  return( good() );
}

bool
Mutex::trylock( void )
{
  errorNum = pthread_mutex_trylock( &mutex );
  return( good() );
}

bool
Mutex::unlock( void )
{
  errorNum = pthread_mutex_unlock( &mutex );
  return( good() );
  return( true );
}

bool
Mutex::good( void ) const
{
  return( errorNum == 0 );
}

const char *
Mutex::error( void ) const
{
  static strstream errStr;
  errStr.freeze(0);
  errStr.seekp(0);
  errStr.seekg(0);

  errStr << Mutex::getClassName();

  if( good() )
    {
       errStr << ": ok";
    }
  else
    {
      strstream eSize = errStr.tellp();

      errStr << ": " << strerror( errorNum );
      
      if( eSize == errStr.tellp() )
        errStr << ": unknown error";
    }

  errStr << ends;
  return( errStr.cstr() );
}

const char *
Mutex::getClassName( void ) const
{
  return( "Mutex" );
}

const char *
Mutex::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
Mutex::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Mutex::getClassName() << ":\n"
	 << Mutex::getVersion() << '\n';

  if( ! Mutex::good() )
    dest << prefix << "Error: " << Mutex::error() << '\n';
  else
    dest << prefix << "Good" << '\n';


  return( dest );
}

#else // ! defined STLUTILS_THREADS

Mutex::Mutex( void )
  : errorNum( 0 )
{
}

Mutex::~Mutex( void )
{
}

bool
Mutex::lock( void )
{
  return( good() );
}

bool
Mutex::trylock( void )
{
  return( good() );
}

bool
Mutex::unlock( void )
{
  return( good() );
}

bool
Mutex::good( void ) const
{
  return( errorNum == 0 );
}

const char *
Mutex::error( void ) const
{
  static Str errStr;

  errStr = Mutex::getClassName();

  if( good() )
    {
       errStr += ": unsupported";
    }
  else
    {
      size_t eSize = errStr.length();

      errStr += ": unsupported";
      
      if( eSize == errStr.length() )
        errStr += ": unknown error";
    }

  return( errStr );
}

const char *
Mutex::getClassName( void ) const
{
  return( "Mutex" );
}

const char *
Mutex::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
Mutex::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Mutex::getClassName() << ":\n"
	 << Mutex::getVersion() << '\n';

  if( ! Mutex::good() )
    dest << prefix << "Error: " << Mutex::error() << '\n';
  else
    dest << prefix << "Good" << '\n';


  return( dest );
}


#endif  // defined( STLUTILS_THREADS )
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.3  2003/08/09 11:20:59  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:16  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:41  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:34  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/03/03 14:37:11  houghton
// Removed support for RW Tools++.
//
// Revision 3.1  1996/11/14 01:23:51  houghton
// Changed to Release 3
//
// Revision 2.5  1996/11/13 17:00:13  houghton
// Removed support for short file names.
// Bug-Fix: fixed some compile errors associated with the chagne to
//     RWCString.
//
// Revision 2.4  1996/11/11 13:34:57  houghton
// Changed to use RWCString instead of strstream where possible because
//     of an inconsitancy in the public member of strstream.
//
// Revision 2.3  1996/11/08 11:45:42  houghton
// Changed use of Str to strstream.
//     (as required by Mike Alexander)
//
// Revision 2.2  1996/11/04 14:20:22  houghton
// Changed to work even if STLUTILS_THREADS is not defined.
//
// Revision 2.1  1996/04/27 13:04:22  houghton
// Initial version.
//
//
