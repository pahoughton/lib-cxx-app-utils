
#include <SubThread.hh>
#include <LibLog.hh>

#include "AppParam.hh"

extern AppParam * App;

SubThread::~SubThread( void )
{
}

bool
SubThread::main( void )
{
  _LLgLock;
  _LLg( LogLevel::Debug ) << "SubThread Start: " << threadId << endl;
  _LLgUnLock;

  if( App->subLife() ) sleep( App->subLife() );
  
  _LLgLock;
  _LLg( LogLevel::Debug ) << "SubThread Done: " << threadId << endl;
  _LLgUnLock;

  return( true );
}
  
