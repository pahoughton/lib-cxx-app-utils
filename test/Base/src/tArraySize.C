#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#endif

struct TestValue
{
  long  a;
  char  b;
  short c;
};

static char 	CharArray[] =  	{ '1', '2', '3', '4' };
static int 	IntArray[] = 	{ 1, 2, 3, 4, 5, 6 };
static short 	ShortArray[] =  { 1, 2, 3, 4, 5, 6, 7 };
static long 	LongArray[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
static char *	StringArray[] = { "1", "2", "3", "4", "5", 0 };

static TestValue TestArray[] =
{
  { 1, 'a', 1 },
  { 2, 'b', 2 },
  { 3, 'c', 3 },
  { 4, 'd', 4 },
  { 5, 'e', 5 }
};

bool tArraySize( LibTest & tester )
{
  TEST( ArraySize( CharArray ) 	 == 4 );
  TEST( ArraySize( IntArray )  	 == 6 );
  TEST( ArraySize( ShortArray )  == 7 );
  TEST( ArraySize( LongArray ) 	 == 9 );
  TEST( ArraySize( StringArray ) == 6 );
  TEST( ArraySize( TestArray ) 	 == 5 );
  
  return( true );
}

