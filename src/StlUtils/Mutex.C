//
// File:        Mutex.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     02/06/96 07:15
//
// Revision History:
//
// $Log$
// Revision 2.3  1996/11/08 11:45:42  houghton
// Changed use of Str to strstream.
//     (as required by Mike Alexander)
//
// Revision 2.2  1996/11/04 14:20:22  houghton
// Changed to work even if CLUE_THREADS is not defined.
//
// Revision 2.1  1996/04/27 13:04:22  houghton
// Initial version.
//
//

#if !defined( CLUE_SHORT_FN )
#include "Mutex.hh"
#include <strstream>
#else
#include "Mutex.hh"
#include <strstream>
#endif

#if defined( CLUE_DEBUG )
#if !defined( CLUE_SHORT_FN )
#include "Mutex.ii"
#else
#include "Mutex.ii"
#endif
#endif

CLUE_VERSION(
  Mutex,
  "$Id$");

#if defined( CLUE_THREADS )

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

#else // ! defined CLUE_THREADS

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
  static strstream errStr;
  errStr.freeze(0);
  errStr.seekp(0);
  errStr.seekg(0);

  errStr << Mutex::getClassName();

  if( good() )
    {
       errStr << ": unsupported";
    }
  else
    {
      streampos eSize = errStr.tellp();

      errStr << ": unsupported";
      
      if( eSize == errStr.tellp() )
        errStr << ": unknown error";
    }

  errStr << ends;
  return( errStr.str() );
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


#endif  // defined( CLUE_THREADS )








