//
// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/Clue.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::MemOverlap");
using namespace clue;

bool
v_MemOverlap( void )
{
  char   buffer[128];
  size_t size = sizeof( buffer );

  char *  t = buffer;
  size_t  ts = size;

  // t = b
  TEST( MemOverlap( buffer, size, t, ts ) );

  // front
  ts = 0;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  ts = 1;
  TEST( MemOverlap( buffer, size, t, ts ) );

  ts = 200;
  TEST( MemOverlap( buffer, size, t, ts ) );

  t -= 10;
  ts = 10;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  ts++;
  TEST( MemOverlap( buffer, size, t, ts ) );

  ts = 200;
  TEST( MemOverlap( buffer, size, t, ts ) );

  ts = 9;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  t = buffer + 50;
  ts = 10;
  TEST( MemOverlap( buffer, size, t, ts ) );

  ts = 200;
  TEST( MemOverlap( buffer, size, t, ts ) );

  t = buffer + (size - 1);
  ts = 0;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  ts = 1;
  TEST( MemOverlap( buffer, size, t, ts ) );

  ts = 100;
  TEST( MemOverlap( buffer, size, t, ts ) );

  t++;
  ts = 0;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  ts = 5;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  return( verify.is_valid() );
}
