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
// Revision 1.1  1996/06/20 15:26:22  houghton
// Initial Version.
//
//

#if !defined( CLUE_SHORT_FN )
#include "ThreadTest.hh"
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

ThreadTest::~ThreadTest( void )
{
}

bool
ThreadTest::main( void )
{
  _LLgLock;
  _LLg( LogLevel::Debug ) << "Start" << endl;
  _LLgUnLock;
  
  for( int i = 0; i < 10; i++ )
    {
      _LLgLock;
      _LLg( LogLevel::Debug ) << "Loop: " << i << endl;
      _LLgUnLock;
      sleep( 10 );
    }
  
  _LLgLock;
  _LLg( LogLevel::Debug ) << "Done" << endl;
  _LLgUnLock;

  return( true );
}

	
