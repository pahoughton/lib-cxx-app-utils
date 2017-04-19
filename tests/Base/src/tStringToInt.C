
#include <LibTest.hh>

#include <Utils.hh>

struct TestVal
{
  const char *  str;
  int	    	value;
};

static struct TestVal TestValues[] =
{
  {" 5 ",    	    5 },
  {" 010 ",    	    010 },
  {"-15",   	    -15 },
  {"0x23",  	    0x23 },
  {"\t-033abc",	    -033 },
  {"-0xabcd",	    -0xabcd },
  {0,0}
};

struct BaseTestVal
{
  unsigned short base;
  const char *   str;
  int	    	value;
};


static struct BaseTestVal BaseTestValues[] =
{
  { 10, " 5 ",    	    5 },
  {  8, " 010 ",    	    010 },
  { 10, "-15",   	    -15 },
  { 16, "23",  	    	    0x23 },
  {  8, "\t-033abc",	    -033 },
  { 16, "-abcd",	    -0xabcd },
  {  2, "10110",    	    22 },
  {0,0}
};

struct LenTestVal
{
  unsigned short len;
  const char *   str;
  int	    	value;
};


static struct LenTestVal LenTestValues[] =
{
  {  3, " 5 ",    	    5 },
  {  5, " 010 15",    	    010 },
  {  5, "-1500123",   	    -1500 },
  {  4, "0x2399",	    0x23 },
  {  4, "-xabcd",	    -0xab },
  {  5, "  11099",    	    110 },
  {0,0}
};

bool
tStringToInt( LibTest & test )
{
  for( int t = 0; TestValues[t].str; t++ )
    {
      int result = StringToInt( TestValues[t].str ) ;
      test( result == TestValues[t].value );
    }
  
  for( int t = 0; BaseTestValues[t].str; t++ )
    {
      int result = StringToInt( BaseTestValues[t].str, BaseTestValues[t].base );
      test( result == BaseTestValues[t].value );
    }
  
  for( int t = 0; LenTestValues[t].str; t++ )
    {
      int result = StringToInt( LenTestValues[t].str, 0, LenTestValues[t].len );
      test( result == LenTestValues[t].value );
    }
  
  return( true );
}

