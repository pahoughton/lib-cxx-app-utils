
#include <LibTest.hh>
#include <Clue.hh>

bool
tMemOverlap( LibTest & test )
{
  char   buffer[128];
  size_t size = sizeof( buffer );
  
  char *  t = buffer;
  size_t  ts = size;

  // t = b
  test( MemOverlap( buffer, size, t, ts ) );

  // front 
  ts = 0;
  test( ! MemOverlap( buffer, size, t, ts ) );

  ts = 1;
  test( MemOverlap( buffer, size, t, ts ) );

  ts = 200;
  test( MemOverlap( buffer, size, t, ts ) );
  
  t -= 10;
  ts = 10;
  test( ! MemOverlap( buffer, size, t, ts ) );

  ts++;
  test( MemOverlap( buffer, size, t, ts ) );
  
  ts = 200;
  test( MemOverlap( buffer, size, t, ts ) );

  ts = 9;
  test( ! MemOverlap( buffer, size, t, ts ) );

  t = buffer + 50;
  ts = 10;
  test( MemOverlap( buffer, size, t, ts ) );

  ts = 200;
  test( MemOverlap( buffer, size, t, ts ) );

  t = buffer + (size - 1);
  ts = 0;
  test( ! MemOverlap( buffer, size, t, ts ) );

  ts = 1;
  test( MemOverlap( buffer, size, t, ts ) );
  
  ts = 100;
  test( MemOverlap( buffer, size, t, ts ) );
  
  t++;
  ts = 0;
  test( ! MemOverlap( buffer, size, t, ts ) );
  
  ts = 5;
  test( ! MemOverlap( buffer, size, t, ts ) );

  return( true );
}


