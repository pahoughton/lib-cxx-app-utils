
#include <LibTest.hh>
#include <Clue.hh>


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

bool tArraySize( LibTest & test )
{
  test( ArraySize( CharArray ) 	 == 4 );
  test( ArraySize( IntArray )  	 == 6 );
  test( ArraySize( ShortArray )  == 7 );
  test( ArraySize( LongArray ) 	 == 9 );
  test( ArraySize( StringArray ) == 6 );
  test( ArraySize( TestArray ) 	 == 5 );
  
  return( true );
}

