//
// File:        Thread.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     02/06/96 09:19
//
// Revision History:
//
// $Log$
// Revision 2.1  1996/02/29 19:07:53  houghton
// Initial Version
//
//

#if !defined( CLUE_SHORT_FN )
#include "Thread.hh"
#include <Str.hh>
#else
#include "Thread.hh"
#include <Str.hh>
#endif

#if defined( CLUE_DEBUG )
#if !defined( CLUE_SHORT_FN )
#include "Thread.ii"
#else
#include "Thread.ii"
#endif
#endif

CLUE_VERSION(
  Thread,
  "$Id$");


Thread::Thread( void )
  : threadId( 0 )
{
}

Thread::~Thread( void )
{
}

bool
Thread::start( void )
{
  //  pthread_create( &threadId, 0, threadEntry, this );
  return( main() );
}

void *
Thread::threadEntry( void * obj )
{
  Thread * me = (Thread *)obj;

  me->main();
  
  return( 0 );
}

  
		  
bool
Thread::good( void ) const
{
  return( true );
}

const char *
Thread::error( void ) const
{
  static Str errStr;

  errStr = Thread::getClassName();

  if( good() )
    {
       errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.cstr() );
}

const char *
Thread::getClassName( void ) const
{
  return( "Thread" );
}

const char *
Thread::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
Thread::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Thread::getClassName() << ":\n"
	 << Thread::getVersion() << '\n';

  if( ! Thread::good() )
    dest << prefix << "Error: " << Thread::error() << '\n';
  else
    dest << prefix << "Good" << '\n';


  return( dest );
}

