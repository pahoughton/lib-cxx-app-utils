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
// Revision 2.1  1996/04/27 13:04:22  houghton
// Initial version.
//
//

#if !defined( CLUE_SHORT_FN )
#include "Mutex.hh"
#include <Str.hh>
#else
#include "Mutex.hh"
#include <Str.hh>
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
  static Str errStr;

  errStr = Mutex::getClassName();

  if( good() )
    {
       errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      errStr << ": " << strerror( errorNum );
      
      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

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

