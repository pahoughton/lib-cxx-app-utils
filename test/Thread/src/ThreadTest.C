//
// File:        ThreadTest.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     06/19/96 06:49
//
// Revision History:
//
// $Log$
// Revision 1.2  1996/07/16 13:54:08  houghton
// *** empty log message ***
//
// Revision 1.1  1996/06/20 15:26:22  houghton
// Initial Version.
//
//

#if !defined( CLUE_SHORT_FN )
#include "ThreadTest.hh"
#include "SubThread.hh"
#include "AppParam.hh"
#include <LibLog.hh>
#include <Str.hh>
#else
#include "ThreadTest.hh"
#include <Str.hh>
#endif

#if defined( CLUE_DEBUG )
#if !defined( CLUE_SHORT_FN )
#include "ThreadTest.ii"
#else
#include "ThreadTest.ii"
#endif
#endif

extern AppParam * App;

ThreadTest::~ThreadTest( void )
{
}

bool
ThreadTest::main( void )
{
  _LLgLock;
  _LLg( LogLevel::Debug ) << "Start: " << threadId << endl;
  _LLgUnLock;

  for( long s = 0; s < App->subThreads(); ++ s )
    {
      SubThread * s = new SubThread( App->subDetach() );
      s->start();
      if( App->subSleep() ) sleep( App->subSleep() );
    }
  
  _LLgLock;
  _LLg( LogLevel::Debug ) << "Done: " << threadId << endl;
  _LLgUnLock;

  return( true );
}

	
