#include <ThreadTest.hh>
#include <LibLog.hh>


int
main( int argc, char * argv[] )
{

  Log	alog;
  alog.setOutputLevel( LogLevel::All );

  _LibLog = &alog;
  

  ThreadTest * t = new ThreadTest;

  _LLgLock;
  _LLg( LogLevel::Debug ) << "ThreadTest initialized." << endl;
  _LLgUnLock;
  
  t->start();

  _LLgLock;
  _LLg( LogLevel::Debug ) << "ThreadTest started." << endl;
  _LLgUnLock;
  
  t->join();

  _LLgLock;
  _LLg( LogLevel::Debug ) << "ThreadTest finished." << endl;
  _LLgUnLock;
  
  return( 0 );
}

       
