//
// File:        ThreadBase.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled source for ThreadBase
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     04/25/96 06:17
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

#if !defined( STLUTILS_SHORT_FN )
#include "ThreadBase.hh"
#include <LibLog.hh>
#include <Str.hh>
#else
#include "ThreadBase.hh"
#include <LibLog.hh>
#include <Str.hh>
#endif

#if defined( STLUTILS_DEBUG )
#if !defined( STLUTILS_SHORT_FN )
#include "ThreadBase.ii"
#else
#include "ThreadBase.ii"
#endif
#endif

STLUTILS_VERSION(
  ThreadBase,
  "$Id$ ");

#if defined( STLUTILS_THREADS )

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

  if( ! errorNum && cleanup )
    pthread_detach( threadId );
  
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
  void *    status = 0;
  _LLgLock;
  _LLg( LogLevel::Debug )
    << ThreadBase::getClassName() << "::join() -"
    << " threadId: " << threadId
    << endl;
  _LLgUnLock;
  
  errorNum = pthread_join( threadId, &status );
  
  _LLgLock;
  _LLg( LogLevel::Debug )
    << ThreadBase::getClassName() << "::join() -"
    << " errorNum: " << errorNum
    << " status: " << status
    << endl;
  _LLgUnLock;
  
  return( good() );
}

void *
ThreadBase::threadEntry( void * obj )
{
  ThreadBase * me = (ThreadBase *)obj;

  me->main();

  _LLgLock;
  _LLg( LogLevel::Debug )
    << me->getClassName() << "::threadEntry -"
    << "Thread: " << me->threadId << " completed: "
    << ( me->cleanup ? "deleting me" : "no cleanup" )
    << endl;
  _LLgUnLock;
  
  if( me->cleanup )
    delete me;

  pthread_exit( 0 );
  return( 0 );
}

bool
ThreadBase::good( void ) const
{
  return( errorNum == 0 );
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

      if( errorNum != 0 )
	errStr << ": (" << errorNum << ") " << strerror( errorNum )
	       << " - thread: " << threadId;
      
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


std::ostream &
ThreadBase::dumpInfo(
  std::ostream &	dest,
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

  dest << prefix << "threadId:  " << threadId << '\n'
       << prefix << "cleanup:   " << (cleanup ? "true" : "false" ) << '\n'
    ;
  
  return( dest );
}

#else // ! defined( STLUTILS_THREADS )

ThreadBase::ThreadBase( bool detach )
  : cleanup( detach ),
    errorNum( 0 )
{
}

ThreadBase::~ThreadBase( void )
{
}


bool
ThreadBase::start( void )
{
  return( good() );
}

bool
ThreadBase::join( void )
{
  return( good() );
}

void *
ThreadBase::threadEntry( void * STLUTILS_UNUSED( obj ) )
{
  return( 0 );
}

bool
ThreadBase::good( void ) const
{
  return( errorNum == 0 );
}

const char *
ThreadBase::error( void ) const
{
  static Str errStr;

  errStr = ThreadBase::getClassName();

  if( good() )
    {
       errStr << ": unsupported";
    }
  else
    {
      size_t eSize = errStr.size();

       errStr << ": unsupported";
       
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


std::ostream &
ThreadBase::dumpInfo(
  std::ostream &	dest,
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

  dest << prefix << "cleanup:   " << (cleanup ? "true" : "false" ) << '\n'
    ;
  
  return( dest );
}

#endif // defined( STLUTILS_THREADS )
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.3  2012/04/26 20:08:48  paul
// *** empty log message ***
//
// Revision 6.2  2011/12/30 23:57:22  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:44  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:21:00  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:07  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:57  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:24:25  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 14:34:32  houghton
// Changed to be compilable even if STLUTILS_THREADS is not defined.
//
// Revision 2.3  1996/07/15 12:15:48  houghton
// Bug-Fix: if detach, call pthread_detach so the threads resources
//   will be cleaned up.
//
// Revision 2.2  1996/06/20 15:23:22  houghton
// Added Debugging loging
//
// Revision 2.1  1996/04/27 13:11:51  houghton
// Initial version.
//
//
