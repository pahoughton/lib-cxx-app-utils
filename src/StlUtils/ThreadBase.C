//
// File:        ThreadBase.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     04/25/96 06:17
//
// Revision History:
//
// $Log$
// Revision 2.1  1996/04/27 13:11:51  houghton
// Initial version.
//
//

#if !defined( CLUE_SHORT_FN )
#include "ThreadBase.hh"
#include <LibLog.hh>
#include <Str.hh>
#else
#include "ThreadBase.hh"
#include <LibLog.hh>
#include <Str.hh>
#endif

#if defined( CLUE_DEBUG )
#if !defined( CLUE_SHORT_FN )
#include "ThreadBase.ii"
#else
#include "ThreadBase.ii"
#endif
#endif

CLUE_VERSION(
  ThreadBase,
  "$Id$");

ThreadBase::ThreadBase( bool detach )
  : threadId( 0 ),
    cleanup( detach ),
    errorNum( 0 )
{
}

ThreadBase::~ThreadBase( void )
{
}


bool
ThreadBase::start( void )
{
  errorNum = pthread_create( &threadId, 0, threadEntry, this );

  _LLgLock;
  _LLg( LogLevel::Debug )
    << ThreadBase::getClassName() << "::start -"
    << "Thread: " << threadId << ( (errorNum == 0) ?
				   " started. " :
				   " failed to start." )
    << endl;
  _LLgUnLock;
  
  return( good() );
}

bool
ThreadBase::join( void )
{
  void *    status;
  errorNum = pthread_join( threadId, &status );
  return( good() );
}

void *
ThreadBase::threadEntry( void * obj )
{
  ThreadBase * me = (ThreadBase *)obj;

  me->main();

  if( me->cleanup )
    delete me;
  
  return( 0 );
}

bool
ThreadBase::good( void ) const
{
  return( true );
}

const char *
ThreadBase::error( void ) const
{
  static Str errStr;

  errStr = ThreadBase::getClassName();

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
ThreadBase::getClassName( void ) const
{
  return( "ThreadBase" );
}

const char *
ThreadBase::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
ThreadBase::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << ThreadBase::getClassName() << ":\n"
	 << ThreadBase::getVersion() << '\n';

  if( ! ThreadBase::good() )
    dest << prefix << "Error: " << ThreadBase::error() << '\n';
  else
    dest << prefix << "Good" << '\n';


  return( dest );
}

