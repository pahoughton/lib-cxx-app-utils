#include <ThreadTest.hh>
#include <LibLog.hh>
#include <AppParam.hh>

AppParam * App = 0;

int
main( int argc, char * argv[] )
{

  App = new AppParam( argc, argv );

  if( App->help() || ! App->good() )
    {
      cerr << *App << endl;
      exit(1);
    }

  {
    for( long l = 0; l < App->threads(); ++ l )
      {

	ThreadTest * t = new ThreadTest( App->detach() );
	
	//_LLgLock;
	//_LLg( LogLevel::Debug ) << "ThreadTest initialized." << endl;
	//_LLgUnLock;
	
	t->start();
	if( App->sleep() ) sleep( App->sleep() );
      }

  }
  
  _LLgLock;
  _LLg( LogLevel::Debug ) << "ThreadTest started: " << App->threads() << " threads." << endl;
  _LLgUnLock;

  for( ;; ) sleep( 120 );
  
  //  t->join();

  _LLgLock;
  _LLg( LogLevel::Debug ) << "ThreadTest finished." << endl;
  _LLgUnLock;
  
  return( 0 );
}

       
