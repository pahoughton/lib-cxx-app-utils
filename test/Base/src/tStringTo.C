#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#endif

#ifndef TRUE
#define FALSE 0
#define TRUE 1
#endif

struct BoolTestVal
{
  const char *  str;
  int	    	useLen;
  size_t    	len;
  int	    	good;
  int	    	value;
};

static struct BoolTestVal BoolTestValues[] = 
{
  { "true", 	FALSE,  0, TRUE,  TRUE },
  { "false",	FALSE,  0, TRUE,  FALSE },
  { "yes",  	FALSE,  0, TRUE,  TRUE },
  { "no",   	FALSE,  0, TRUE,  FALSE },
  { "on",   	FALSE,  0, TRUE,  TRUE },
  { "off",  	FALSE,  0, TRUE,  FALSE },
  { "TRUE", 	FALSE,  0, TRUE,  TRUE },
  { "FALSE",	FALSE,  0, TRUE,  FALSE },
  { "YES",  	FALSE,  0, TRUE,  TRUE },
  { "NO",   	FALSE,  0, TRUE,  FALSE },
  { "ON",   	FALSE,  0, TRUE,  TRUE },
  { "OFF",  	FALSE,  0, TRUE,  FALSE },
  { "True", 	FALSE,  0, TRUE,  TRUE },
  { "False",	FALSE,  0, TRUE,  FALSE },
  { "Yes",  	FALSE,  0, TRUE,  TRUE },
  { "No",   	FALSE,  0, TRUE,  FALSE },
  { "On",   	FALSE,  0, TRUE,  TRUE },
  { "Off",  	FALSE,  0, TRUE,  FALSE },
  { "t", 	FALSE,  0, TRUE,  TRUE },
  { "f",	FALSE,  0, TRUE,  FALSE },
  { "y",  	FALSE,  0, TRUE,  TRUE },
  { "n",   	FALSE,  0, TRUE,  FALSE },
  { "T", 	FALSE,  0, TRUE,  TRUE },
  { "F",	FALSE,  0, TRUE,  FALSE },
  { "Y",  	FALSE,  0, TRUE,  TRUE },
  { "N",   	FALSE,  0, TRUE,  FALSE },
  { "txxx", 	FALSE,  0, FALSE, FALSE },
  { "fxxx",	FALSE,  0, FALSE, FALSE },
  { "yxxx",  	FALSE,  0, FALSE, FALSE },
  { "nxxx",   	FALSE,  0, FALSE, FALSE },
  { "txxx", 	TRUE,   1, TRUE,  TRUE },
  { "fxxx",	TRUE,   1, TRUE,  FALSE },
  { "yxxx",  	TRUE,   1, TRUE,  TRUE },
  { "nxxx",   	TRUE,   1, TRUE,  FALSE },
  { 0, FALSE, 0, FALSE, FALSE }
};

    
struct IntTestVal
{
  const char *      str;
  int	    	    useBase;
  int	    	    useLen;
  unsigned short    base;
  size_t    	    len;
  int	    	    good;
  int	    	    value;
};

static struct IntTestVal IntTestValues[] =
{
  {" 5 ",     	    FALSE, FALSE,  0,  0, TRUE,       5 },
  {" 010 ",    	    FALSE, FALSE,  0,  0, TRUE,      010 },
  {"-15",   	    FALSE, FALSE,  0,  0, TRUE,      -15 },
  {"0x23",  	    FALSE, FALSE,  0,  0, TRUE,     0x23 },
  {"\t-033abc",	    FALSE, FALSE,  0,  0, TRUE,     -033 },
  {"-0xabcd",	    FALSE, FALSE,  0,  0, TRUE,  -0xabcd },
  
  { " 5 ",  	    TRUE,  FALSE, 10,  0, TRUE,        5 },
  { " 010 ",  	    TRUE,  FALSE,  8,  0, TRUE,      010 },
  { "-15", 	    TRUE,  FALSE, 10,  0, TRUE,      -15 },
  { "23", 	    TRUE,  FALSE, 16,  0, TRUE,     0x23 },
  { "\t-033abc",    TRUE,  FALSE,  8,  0, TRUE,     -033 },
  { "-abcd",	    TRUE,  FALSE, 16,  0, TRUE,  -0xabcd },
  { "10110",  	    TRUE,  FALSE,  2,  0, TRUE,       22 },

  { " 5 ",  	    TRUE,  TRUE,   0,  3, TRUE,        5 },
  { " 010 15",      TRUE,  TRUE,   0,  5, TRUE,      010 },
  { "-1500123",     TRUE,  TRUE,   0,  5, TRUE,    -1500 },
  { "0x2399",  	    TRUE,  TRUE,   0,  4, TRUE,     0x23 },
  { "-0xabcd",      TRUE,  TRUE,   0,  5, TRUE,    -0xab },
  { "  11099",      TRUE,  TRUE,   0,  5, TRUE,      110 },
  
  { " 5 ",  	    TRUE,  TRUE,  10,  3, TRUE,        5 },
  { " 010 15",      TRUE,  TRUE,  10,  5, TRUE,       10 },
  { "-1500123",     TRUE,  TRUE,  16,  5, TRUE,    -5376 },
  { "0x2399",  	    TRUE,  TRUE,  16,  4, TRUE,     0x23 },
  { "-0xabcd", 	    TRUE,  TRUE,  16,  5, TRUE,    -0xab },
  { "  11099",      TRUE,  TRUE,   8,  5, TRUE,     0110 },

  { "01012",	    TRUE,  FALSE,  2,  0, FALSE,      -1 },
  { "test", 	    FALSE, FALSE,  0,  0, FALSE,      -1 },
  { "099",  	    FALSE, FALSE,  0,  0, FALSE,      -1 },
  
  {0, FALSE, FALSE, 0, 0, 0}
};

struct ShortTestVal
{
  const char *      str;
  int	    	    useBase;
  int	    	    useLen;
  unsigned short    base;
  size_t    	    len;
  int	    	    good;
  short	    	    value;
};

static struct ShortTestVal ShortTestValues[] =
{
  {" 5 ",     	    FALSE, FALSE,  0,  0, TRUE,       5 },
  {" 010 ",    	    FALSE, FALSE,  0,  0, TRUE,      010 },
  {"-15",   	    FALSE, FALSE,  0,  0, TRUE,      -15 },
  {"0x23",  	    FALSE, FALSE,  0,  0, TRUE,     0x23 },
  {"\t-033abc",	    FALSE, FALSE,  0,  0, TRUE,     -033 },
  {"-0xabcd",	    FALSE, FALSE,  0,  0, TRUE,  -0xabcd },
  
  { " 5 ",  	    TRUE,  FALSE, 10,  0, TRUE,        5 },
  { " 010 ",  	    TRUE,  FALSE,  8,  0, TRUE,      010 },
  { "-15", 	    TRUE,  FALSE, 10,  0, TRUE,      -15 },
  { "23", 	    TRUE,  FALSE, 16,  0, TRUE,     0x23 },
  { "\t-033abc",    TRUE,  FALSE,  8,  0, TRUE,     -033 },
  { "-abcd",	    TRUE,  FALSE, 16,  0, TRUE,  -0xabcd },
  { "10110",  	    TRUE,  FALSE,  2,  0, TRUE,       22 },

  { " 5 ",  	    TRUE,  TRUE,   0,  3, TRUE,        5 },
  { " 010 15",      TRUE,  TRUE,   0,  5, TRUE,      010 },
  { "-1500123",     TRUE,  TRUE,   0,  5, TRUE,    -1500 },
  { "0x2399",  	    TRUE,  TRUE,   0,  4, TRUE,     0x23 },
  { "-0xabcd", 	    TRUE,  TRUE,   0,  5, TRUE,    -0xab },
  { "  11099",      TRUE,  TRUE,   0,  5, TRUE,      110 },
  
  { " 5 ",  	    TRUE,  TRUE,  10,  3, TRUE,        5 },
  { " 010 15",      TRUE,  TRUE,  10,  5, TRUE,       10 },
  { "-1500123",     TRUE,  TRUE,  16,  5, TRUE,    -5376 },
  { "0x2399",  	    TRUE,  TRUE,  16,  4, TRUE,     0x23 },
  { "-0xabcd",      TRUE,  TRUE,  16,  5, TRUE,    -0xab },
  { "  11099",      TRUE,  TRUE,   8,  5, TRUE,     0110 },

  { "01012",	    TRUE,  FALSE,  2,  0, FALSE,      -1 },
  { "test", 	    FALSE, FALSE,  0,  0, FALSE,      -1 },
  { "099",  	    FALSE, FALSE,  0,  0, FALSE,      -1 },
  
  {0, FALSE, FALSE, 0, 0, 0}
};

struct LongTestVal
{
  const char *      str;
  int	    	    useBase;
  int	    	    useLen;
  unsigned short    base;
  size_t    	    len;
  int	    	    good;
  long	    	    value;
};

static struct LongTestVal LongTestValues[] =
{
  {" 5 ",     	    FALSE, FALSE,  0,  0, TRUE,       5L },
  {" 010 ",    	    FALSE, FALSE,  0,  0, TRUE,      010L },
  {"-15",   	    FALSE, FALSE,  0,  0, TRUE,      -15L },
  {"0x23",  	    FALSE, FALSE,  0,  0, TRUE,     0x23L },
  {"\t-033abc",	    FALSE, FALSE,  0,  0, TRUE,     -033L },
  {"-0xabcd",	    FALSE, FALSE,  0,  0, TRUE,  -0xabcdL },

  { " 5 ",  	    TRUE,  FALSE, 10,  0, TRUE,        5L },
  { " 010 ",  	    TRUE,  FALSE,  8,  0, TRUE,      010L },
  { "-15", 	    TRUE,  FALSE, 10,  0, TRUE,      -15L },
  { "23", 	    TRUE,  FALSE, 16,  0, TRUE,     0x23L },
  { "\t-033abc",    TRUE,  FALSE,  8,  0, TRUE,     -033L },
  { "-abcd",	    TRUE,  FALSE, 16,  0, TRUE,  -0xabcdL },
  { "10110",  	    TRUE,  FALSE,  2,  0, TRUE,       22L },

  { " 5 ",  	    TRUE,  TRUE,   0,  3, TRUE,        5L },
  { " 010 15",      TRUE,  TRUE,   0,  5, TRUE,      010L },
  { "-1500123",     TRUE,  TRUE,   0,  5, TRUE,    -1500L },
  { "0x2399",  	    TRUE,  TRUE,   0,  4, TRUE,     0x23L },
  { "-0xabcd",      TRUE,  TRUE,   0,  5, TRUE,    -0xabL },
  { "  11099",      TRUE,  TRUE,   0,  5, TRUE,      110L },

  { " 5 ",  	    TRUE,  TRUE,  10,  3, TRUE,        5L },
  { " 010 15",      TRUE,  TRUE,  10,  5, TRUE,       10L },
  { "-1500123",     TRUE,  TRUE,  16,  5, TRUE,    -5376L },
  { "0x2399",  	    TRUE,  TRUE,  16,  4, TRUE,     0x23L },
  { "-0xabcd", 	    TRUE,  TRUE,  16,  5, TRUE,    -0xabL },
  { "  11099",      TRUE,  TRUE,   8,  5, TRUE,     0110L },
  { "01012",	    TRUE,  FALSE,  2,  0, FALSE,      -1L },
  { "test", 	    FALSE, FALSE,  0,  0, FALSE,      -1L },
  { "099",  	    FALSE, FALSE,  0,  0, FALSE,      -1L },

  { "0x0fffffff",   FALSE, FALSE,  0,  0, TRUE,	0x0fffffffL },
  { "-99999999",    FALSE, FALSE,  0,  0, TRUE,	-99999999L },
  { "99999999",     FALSE, FALSE,  0,  0, TRUE,	 99999999L },
  
  {0, FALSE, FALSE, 0, 0, 0L}
};

struct DoubleTestVal
{
  const char *      str;
  int	    	    useBase;
  int	    	    useLen;
  unsigned short    base;
  size_t    	    len;
  int	    	    good;
  double    	    value;
};

static struct DoubleTestVal DoubleTestValues[] =
{
  {" 5 ",     	    FALSE, FALSE,  0,  0, TRUE,       5.0 },
  {" 010 ",    	    FALSE, FALSE,  0,  0, TRUE,       8.0 },
  {"-15",   	    FALSE, FALSE,  0,  0, TRUE,     -15.0 },
  {"0x23",  	    FALSE, FALSE,  0,  0, TRUE,      35.0 },
  {"\t-033abc",	    FALSE, FALSE,  0,  0, TRUE,     -27.0 },
  {"-0xabcd",	    FALSE, FALSE,  0,  0, TRUE,  -43981.0 },

  {" 5.245 ",  	    FALSE, FALSE,  0,  0, TRUE,       5.245 },
  {" 010.11 ", 	    FALSE, FALSE,  0,  0, TRUE,       8.140625 },
  {"-15.44",   	    FALSE, FALSE,  0,  0, TRUE,     -15.44 },
  {"0x23.23",  	    FALSE, FALSE,  0,  0, TRUE,      35.13671875 },
  
  { " 5 ",  	    TRUE,  FALSE, 10,  0, TRUE,        5.0 },
  { " 010 ",  	    TRUE,  FALSE,  8,  0, TRUE,        8.0 },
  { "-15", 	    TRUE,  FALSE, 10,  0, TRUE,      -15.0 },
  { "23", 	    TRUE,  FALSE, 16,  0, TRUE,       35.0 },
  { "\t-033abc",    TRUE,  FALSE, 10,  0, TRUE,      -33.0 },
  { "-abcd",	    TRUE,  FALSE, 16,  0, TRUE,   -43981.0 },
  { "10110",  	    TRUE,  FALSE,  2,  0, TRUE,       22.0 },

  { " 5.0 ",  	    TRUE,  TRUE,   0,  3, TRUE,        5.0 },
  { " 010 15",      TRUE,  TRUE,   0,  5, TRUE,        8.0 },
  { "-1500123",     TRUE,  TRUE,   0,  5, TRUE,    -1500.0 },
  { "0x2399",  	    TRUE,  TRUE,   0,  4, TRUE,       35.0 },
  { "-0xabcd",      TRUE,  TRUE,   0,  5, TRUE,     -171.0 },
  { "  11099",      TRUE,  TRUE,   0,  5, TRUE,      110.0 },
  
  { " 5 ",  	    TRUE,  TRUE,  10,  3, TRUE,        5.0 },
  { " 010 15",      TRUE,  TRUE,  10,  5, TRUE,       10.0 },
  { "-1500123",     TRUE,  TRUE,  16,  5, TRUE,    -5376.0 },
  { "0x2399",  	    TRUE,  TRUE,  16,  4, TRUE,       35.0 },
  { "-0xabcd", 	    TRUE,  TRUE,  16,  5, TRUE,     -171.0 },
  { "  11099",      TRUE,  TRUE,   8,  5, TRUE,       72.0 },
  { "01012",	    TRUE,  FALSE,  2,  0, FALSE,      -1.0 },
  { "test", 	    FALSE, FALSE,  0,  0, FALSE,      -1.0 },
  { "099",  	    FALSE, FALSE,  0,  0, FALSE,      -1.0 },
  
  {0, FALSE, FALSE, 0, 0, 0}
};

struct UIntTestVal
{
  const char *      str;
  int	    	    useBase;
  int	    	    useLen;
  unsigned short    base;
  size_t    	    len;
  int	    	    good;
  unsigned int 	    value;
};

static struct UIntTestVal UIntTestValues[] =
{
  {" 5 ",     	    FALSE, FALSE,  0,  0, TRUE,       5 },
  {" 010 ",    	    FALSE, FALSE,  0,  0, TRUE,      010 },
  {"0x23",  	    FALSE, FALSE,  0,  0, TRUE,     0x23 },
  
  { " 5 ",  	    TRUE,  FALSE, 10,  0, TRUE,        5 },
  { " 010 ",  	    TRUE,  FALSE,  8,  0, TRUE,      010 },
  { "23", 	    TRUE,  FALSE, 16,  0, TRUE,     0x23 },
  { "10110",  	    TRUE,  FALSE,  2,  0, TRUE,       22 },

  { " 5 ",  	    TRUE,  TRUE,   0,  3, TRUE,        5 },
  { " 010 15",      TRUE,  TRUE,   0,  5, TRUE,      010 },
  { "0x2399",  	    TRUE,  TRUE,   0,  4, TRUE,     0x23 },
  { "  11099",      TRUE,  TRUE,   0,  5, TRUE,      110 },
  
  { " 5 ",  	    TRUE,  TRUE,  10,  3, TRUE,        5 },
  { " 010 15",      TRUE,  TRUE,  10,  5, TRUE,       10 },
  { "0x2399",  	    TRUE,  TRUE,  16,  4, TRUE,     0x23 },
  { "  11099",      TRUE,  TRUE,   8,  5, TRUE,     0110 },

  { "01012",	    TRUE,  FALSE,  2,  0, FALSE,      0 },
  { "test", 	    FALSE, FALSE,  0,  0, FALSE,      0 },
  { "099",  	    FALSE, FALSE,  0,  0, FALSE,      0 },
  
  {0, FALSE, FALSE, 0, 0, 0}
};

struct UShortTestVal
{
  const char *      str;
  int	    	    useBase;
  int	    	    useLen;
  unsigned short    base;
  size_t    	    len;
  int	    	    good;
  unsigned short    value;
};

static struct UShortTestVal UShortTestValues[] =
{
  {" 5 ",     	    FALSE, FALSE,  0,  0, TRUE,       5 },
  {" 010 ",    	    FALSE, FALSE,  0,  0, TRUE,      010 },
  {"0x23",  	    FALSE, FALSE,  0,  0, TRUE,     0x23 },
  
  { " 5 ",  	    TRUE,  FALSE, 10,  0, TRUE,        5 },
  { " 010 ",  	    TRUE,  FALSE,  8,  0, TRUE,      010 },
  { "23", 	    TRUE,  FALSE, 16,  0, TRUE,     0x23 },
  { "10110",  	    TRUE,  FALSE,  2,  0, TRUE,       22 },

  { " 5 ",  	    TRUE,  TRUE,   0,  3, TRUE,        5 },
  { " 010 15",      TRUE,  TRUE,   0,  5, TRUE,      010 },
  { "0x2399",  	    TRUE,  TRUE,   0,  4, TRUE,     0x23 },
  { "  11099",      TRUE,  TRUE,   0,  5, TRUE,      110 },
  
  { " 5 ",  	    TRUE,  TRUE,  10,  3, TRUE,        5 },
  { " 010 15",      TRUE,  TRUE,  10,  5, TRUE,       10 },
  { "0x2399",  	    TRUE,  TRUE,  16,  4, TRUE,     0x23 },
  { "  11099",      TRUE,  TRUE,   8,  5, TRUE,     0110 },

  { "01012",	    TRUE,  FALSE,  2,  0, FALSE,      0 },
  { "test", 	    FALSE, FALSE,  0,  0, FALSE,      0 },
  { "099",  	    FALSE, FALSE,  0,  0, FALSE,      0 },
  
  {0, FALSE, FALSE, 0, 0, 0}
};

struct ULongTestVal
{
  const char *      str;
  int	    	    useBase;
  int	    	    useLen;
  unsigned short    base;
  size_t    	    len;
  int	    	    good;
  unsigned long	    value;
};

static struct ULongTestVal ULongTestValues[] =
{
  {" 5 ",     	    FALSE, FALSE,  0,  0, TRUE,       5L },
  {" 010 ",    	    FALSE, FALSE,  0,  0, TRUE,      010L },
  {"0x23",  	    FALSE, FALSE,  0,  0, TRUE,     0x23L },

  { " 5 ",  	    TRUE,  FALSE, 10,  0, TRUE,        5L },
  { " 010 ",  	    TRUE,  FALSE,  8,  0, TRUE,      010L },
  { "23", 	    TRUE,  FALSE, 16,  0, TRUE,     0x23L },
  { "10110",  	    TRUE,  FALSE,  2,  0, TRUE,       22L },

  { " 5 ",  	    TRUE,  TRUE,   0,  3, TRUE,        5L },
  { " 010 15",      TRUE,  TRUE,   0,  5, TRUE,      010L },
  { "0x2399",  	    TRUE,  TRUE,   0,  4, TRUE,     0x23L },
  { "  11099",      TRUE,  TRUE,   0,  5, TRUE,      110L },

  { " 5 ",  	    TRUE,  TRUE,  10,  3, TRUE,        5L },
  { " 010 15",      TRUE,  TRUE,  10,  5, TRUE,       10L },
  { "0x2399",  	    TRUE,  TRUE,  16,  4, TRUE,     0x23L },
  { "  11099",      TRUE,  TRUE,   8,  5, TRUE,     0110L },
  { "01012",	    TRUE,  FALSE,  2,  0, FALSE,       0L },
  { "test", 	    FALSE, FALSE,  0,  0, FALSE,       0L },
  { "099",  	    FALSE, FALSE,  0,  0, FALSE,       0L },
  
  { "0xffffffff",   FALSE, FALSE,  0,  0, TRUE,	0xffffffffL },
  { "99999999",     FALSE, FALSE,  0,  0, TRUE,	 99999999L },
  
  {0, FALSE, FALSE, 0, 0, 0}
};

bool
tStringTo( LibTest & tester )
{

  {
    // StringToBool( bool &, const char * )
    // StringToBool( bool &, const char *, size_t )

    for( size_t t = 0; BoolTestValues[t].str; t++ )
      {
	if( ! BoolTestValues[t].useLen )
	  {
	    bool result = FALSE;
	    TEST( StringToBool( result, BoolTestValues[t].str ) ==
		  BoolTestValues[t].good );
	    TEST( result == BoolTestValues[t].value );
	  }
	else
	  {
	    bool result = FALSE;
	    TEST( StringToBool( result, BoolTestValues[t].str,
					BoolTestValues[t].len ) ==
		  BoolTestValues[t].good );
	    
	    TEST( result == BoolTestValues[t].value );
	  }
      }
  }

  {
    // StringTo( int &, const char * );
    // StringTo( int &, const char *, unsigned short );
    // StringTo( int &, const char *, unsigned short, size_t );

    for( size_t t = 0; IntTestValues[t].str; t++ )
      {
	if( ! IntTestValues[t].useBase && ! IntTestValues[t].useLen )
	  {
	    int result = -1;
	    TEST( StringTo( result, IntTestValues[t].str ) ==
		  IntTestValues[t].good );
	    TEST( result == IntTestValues[t].value );
	  }

	if( IntTestValues[t].useBase && ! IntTestValues[t].useLen )
	  {
	    int result = -1;
	    TEST( StringTo( result,
			    IntTestValues[t].str,
			    IntTestValues[t].base ) ==
		  IntTestValues[t].good );
	    TEST( result == IntTestValues[t].value );
	  }

	if( IntTestValues[t].useBase && IntTestValues[t].useLen )
	  {
	    int result = -1;
	    TEST( StringTo( result,
			    IntTestValues[t].str,
			    IntTestValues[t].base,
			    IntTestValues[t].len ) ==
		  IntTestValues[t].good );
	    TEST( result == IntTestValues[t].value );
	  }
      }
  }
  
  {
    // StringTo( short &, const char * );
    // StringTo( short &, const char *, unsigned short );
    // StringTo( short &, const char *, unsigned short, size_t );

    for( size_t t = 0; ShortTestValues[t].str; t++ )
      {
	if( ! ShortTestValues[t].useBase && ! ShortTestValues[t].useLen )
	  {
	    short result = -1;
	    TEST( StringTo( result, ShortTestValues[t].str ) ==
		  ShortTestValues[t].good );
	    TEST( result == ShortTestValues[t].value );
	  }

	if( ShortTestValues[t].useBase && ! ShortTestValues[t].useLen )
	  {
	    short result = -1;
	    TEST( StringTo( result,
			    ShortTestValues[t].str,
			    ShortTestValues[t].base ) ==
		  ShortTestValues[t].good );
	    TEST( result == ShortTestValues[t].value );
	  }

	if( ShortTestValues[t].useBase && ShortTestValues[t].useLen )
	  {
	    short result = -1;
	    TEST( StringTo( result,
			    ShortTestValues[t].str,
			    ShortTestValues[t].base,
			    ShortTestValues[t].len ) ==
		  ShortTestValues[t].good );
	    TEST( result == ShortTestValues[t].value );
	  }
      }
  }
  
  {
    // StringTo( long &, const char * );
    // StringTo( long &, const char *, unsigned short );
    // StringTo( long &, const char *, unsigned short, size_t );

    for( size_t t = 0; LongTestValues[t].str; t++ )
      {
	if( ! LongTestValues[t].useBase && ! LongTestValues[t].useLen )
	  {
	    long result = -1;
	    TEST( StringTo( result, LongTestValues[t].str ) ==
		  LongTestValues[t].good );
	    TEST( result == LongTestValues[t].value );
	  }

	if( LongTestValues[t].useBase && ! LongTestValues[t].useLen )
	  {
	    long result = -1;
	    TEST( StringTo( result,
			    LongTestValues[t].str,
			    LongTestValues[t].base ) ==
		  LongTestValues[t].good );
	    TEST( result == LongTestValues[t].value );
	  }

	if( LongTestValues[t].useBase && LongTestValues[t].useLen )
	  {
	    long result = -1;
	    TEST( StringTo( result,
			    LongTestValues[t].str,
			    LongTestValues[t].base,
			    LongTestValues[t].len ) ==
		  LongTestValues[t].good );
	    TEST( result == LongTestValues[t].value );
	  }
      }
  }
  
  {
    // StringTo( double &, const char * );
    // StringTo( double &, const char *, unsigned short );
    // StringTo( double &, const char *, unsigned short, size_t );

    for( size_t t = 0; DoubleTestValues[t].str; t++ )
      {
	if( ! DoubleTestValues[t].useBase && ! DoubleTestValues[t].useLen )
	  {
	    double result = -1;
	    TEST( StringTo( result, DoubleTestValues[t].str ) ==
		  DoubleTestValues[t].good );
	    TEST( result == DoubleTestValues[t].value );
	  }

	if( DoubleTestValues[t].useBase && ! DoubleTestValues[t].useLen )
	  {
	    double result = -1;
	    TEST( StringTo( result,
			    DoubleTestValues[t].str,
			    DoubleTestValues[t].base ) ==
		  DoubleTestValues[t].good );
	    TEST( result == DoubleTestValues[t].value );
	  }

	if( DoubleTestValues[t].useBase && DoubleTestValues[t].useLen )
	  {
	    double result = -1;
	    TEST( StringTo( result,
			    DoubleTestValues[t].str,
			    DoubleTestValues[t].base,
			    DoubleTestValues[t].len ) ==
		  DoubleTestValues[t].good );
	    TEST( result == DoubleTestValues[t].value );
	  }
      }
  }
  
  {
    // StringTo( unsigned int &, const char * );
    // StringTo( unsigned int &, const char *, unsigned short );
    // StringTo( unsigned int &, const char *, unsigned short, size_t );

    for( size_t t = 0; UIntTestValues[t].str; t++ )
      {
	if( ! UIntTestValues[t].useBase && ! UIntTestValues[t].useLen )
	  {
	    unsigned int result = 0;
	    TEST( StringTo( result, UIntTestValues[t].str ) ==
		  UIntTestValues[t].good );
	    TEST( result == UIntTestValues[t].value );
	  }

	if( UIntTestValues[t].useBase && ! UIntTestValues[t].useLen )
	  {
	    unsigned int result = 0;
	    TEST( StringTo( result,
			    UIntTestValues[t].str,
			    UIntTestValues[t].base ) ==
		  UIntTestValues[t].good );
	    TEST( result == UIntTestValues[t].value );
	  }

	if( UIntTestValues[t].useBase && UIntTestValues[t].useLen )
	  {
	    unsigned int result = 0;
	    TEST( StringTo( result,
			    UIntTestValues[t].str,
			    UIntTestValues[t].base,
			    UIntTestValues[t].len ) ==
		  UIntTestValues[t].good );
	    TEST( result == UIntTestValues[t].value );
	  }
      }
  }
  
  {
    // StringTo( unsigned short &, const char * );
    // StringTo( unsigned short &, const char *, unsigned short );
    // StringTo( unsigned short &, const char *, unsigned short, size_t );

    for( size_t t = 0; UShortTestValues[t].str; t++ )
      {
	if( ! UShortTestValues[t].useBase && ! UShortTestValues[t].useLen )
	  {
	    unsigned short result = 0;
	    TEST( StringTo( result, UShortTestValues[t].str ) ==
		  UShortTestValues[t].good );
	    TEST( result == UShortTestValues[t].value );
	  }

	if( UShortTestValues[t].useBase && ! UShortTestValues[t].useLen )
	  {
	    unsigned short result = 0;
	    TEST( StringTo( result,
			    UShortTestValues[t].str,
			    UShortTestValues[t].base ) ==
		  UShortTestValues[t].good );
	    TEST( result == UShortTestValues[t].value );
	  }

	if( UShortTestValues[t].useBase && UShortTestValues[t].useLen )
	  {
	    unsigned short result = 0;
	    TEST( StringTo( result,
			    UShortTestValues[t].str,
			    UShortTestValues[t].base,
			    UShortTestValues[t].len ) ==
		  UShortTestValues[t].good );
	    TEST( result == UShortTestValues[t].value );
	  }
      }
  }
  
  {
    // StringTo( unsigned long &, const char * );
    // StringTo( unsigned long &, const char *, unsigned short );
    // StringTo( unsigned long &, const char *, unsigned short, size_t );

    for( size_t t = 0; ULongTestValues[t].str; t++ )
      {
	if( ! ULongTestValues[t].useBase && ! ULongTestValues[t].useLen )
	  {
	    unsigned long result = 0;
	    TEST( StringTo( result, ULongTestValues[t].str ) ==
		  ULongTestValues[t].good );
	    TEST( result == ULongTestValues[t].value );
	  }

	if( ULongTestValues[t].useBase && ! ULongTestValues[t].useLen )
	  {
	    unsigned long result = 0;
	    TEST( StringTo( result,
			    ULongTestValues[t].str,
			    ULongTestValues[t].base ) ==
		  ULongTestValues[t].good );
	    TEST( result == ULongTestValues[t].value );
	  }

	if( ULongTestValues[t].useBase && ULongTestValues[t].useLen )
	  {
	    unsigned long result = 0;
	    TEST( StringTo( result,
			    ULongTestValues[t].str,
			    ULongTestValues[t].base,
			    ULongTestValues[t].len ) ==
		  ULongTestValues[t].good );
	    TEST( result == ULongTestValues[t].value );
	  }
      }
  }
  
  {
    // StringToBool( const char * )
    // StringToBool( const char *, size_t )

    for( size_t t = 0; BoolTestValues[t].str; t++ )
      {
	if( ! BoolTestValues[t].useLen )
	  {
	    bool result = StringToBool( BoolTestValues[t].str );
	    TEST( result == BoolTestValues[t].value );
	  }
	else
	  {
	    bool result = StringToBool( BoolTestValues[t].str,
					BoolTestValues[t].len );
	    TEST( result == BoolTestValues[t].value );
	  }
      }
  }
  	    
  {
    // StringToInt( const char * );
    // StringToInt( const char *, unsigned short );
    // StringToInt( const char *, unsigned short, size_t );

    for( size_t t = 0; IntTestValues[t].str; t++ )
      {
	if( ! IntTestValues[t].useBase && ! IntTestValues[t].useLen )
	  {
	    int result = StringToInt( IntTestValues[t].str );
	    TEST( result == IntTestValues[t].value );
	  }

	if( IntTestValues[t].useBase && ! IntTestValues[t].useLen )
	  {
	    int result = StringToInt( IntTestValues[t].str,
				      IntTestValues[t].base );
	    TEST( result == IntTestValues[t].value );
	  }

	if( IntTestValues[t].useBase && IntTestValues[t].useLen )
	  {
	    int result = StringToInt( IntTestValues[t].str,
				      IntTestValues[t].base,
				      IntTestValues[t].len );
	    TEST( result == IntTestValues[t].value );
	  }
      }
  }

  {
    // StringToShort( const char * );
    // StringToShort( const char *, unsigned short );
    // StringToShort( const char *, unsigned short, size_t );

    for( size_t t = 0; ShortTestValues[t].str; t++ )
      {
	if( ! ShortTestValues[t].useBase && ! ShortTestValues[t].useLen )
	  {
	    short result = StringToShort( ShortTestValues[t].str );
	    TEST( result == ShortTestValues[t].value );
	  }

	if( ShortTestValues[t].useBase && ! ShortTestValues[t].useLen )
	  {
	    short result = StringToShort( ShortTestValues[t].str,
				      ShortTestValues[t].base );
	    TEST( result == ShortTestValues[t].value );
	  }

	if( ShortTestValues[t].useBase && ShortTestValues[t].useLen )
	  {
	    short result = StringToShort( ShortTestValues[t].str,
				      ShortTestValues[t].base,
				      ShortTestValues[t].len );
	    TEST( result == ShortTestValues[t].value );
	  }
      }
  }

  {
    // StringToLong( const char * );
    // StringToLong( const char *, unsigned short );
    // StringToLong( const char *, unsigned short, size_t );

    for( size_t t = 0; LongTestValues[t].str; t++ )
      {
	if( ! LongTestValues[t].useBase && ! LongTestValues[t].useLen )
	  {
	    long result = StringToLong( LongTestValues[t].str );
	    TEST( result == LongTestValues[t].value );
	  }

	if( LongTestValues[t].useBase && ! LongTestValues[t].useLen )
	  {
	    long result = StringToLong( LongTestValues[t].str,
				      LongTestValues[t].base );
	    TEST( result == LongTestValues[t].value );
	  }

	if( LongTestValues[t].useBase && LongTestValues[t].useLen )
	  {
	    long result = StringToLong( LongTestValues[t].str,
				      LongTestValues[t].base,
				      LongTestValues[t].len );
	    TEST( result == LongTestValues[t].value );
	  }
      }
  }

  {
    // StringToDouble( const char * );
    // StringToDouble( const char *, unsigned short );
    // StringToDouble( const char *, unsigned short, size_t );

    for( size_t t = 0; DoubleTestValues[t].str; t++ )
      {
	if( ! DoubleTestValues[t].useBase && ! DoubleTestValues[t].useLen )
	  {
	    double result = StringToDouble( DoubleTestValues[t].str );
	    TEST( result == DoubleTestValues[t].value );
	  }

	if( DoubleTestValues[t].useBase && ! DoubleTestValues[t].useLen )
	  {
	    double result = StringToDouble( DoubleTestValues[t].str,
				      DoubleTestValues[t].base );
	    TEST( result == DoubleTestValues[t].value );
	  }

	if( DoubleTestValues[t].useBase && DoubleTestValues[t].useLen )
	  {
	    double result = StringToDouble( DoubleTestValues[t].str,
				      DoubleTestValues[t].base,
				      DoubleTestValues[t].len );
	    TEST( result == DoubleTestValues[t].value );
	  }
      }
  }

  {
    // StringToUInt( const char * );
    // StringToUInt( const char *, unsigned short );
    // StringToUInt( const char *, unsigned short, size_t );

    for( size_t t = 0; UIntTestValues[t].str; t++ )
      {
	if( ! UIntTestValues[t].useBase && ! UIntTestValues[t].useLen )
	  {
	    unsigned int result = StringToUInt( UIntTestValues[t].str );
	    TEST( result == UIntTestValues[t].value );
	  }

	if( UIntTestValues[t].useBase && ! UIntTestValues[t].useLen )
	  {
	    unsigned int result = StringToUInt( UIntTestValues[t].str,
				      UIntTestValues[t].base );
	    TEST( result == UIntTestValues[t].value );
	  }

	if( UIntTestValues[t].useBase && UIntTestValues[t].useLen )
	  {
	    unsigned int result = StringToUInt( UIntTestValues[t].str,
				      UIntTestValues[t].base,
				      UIntTestValues[t].len );
	    TEST( result == UIntTestValues[t].value );
	  }
      }
  }
  
  {
    // StringToUShort( const char * );
    // StringToUShort( const char *, unsigned short );
    // StringToUShort( const char *, unsigned short, size_t );

    for( size_t t = 0; UShortTestValues[t].str; t++ )
      {
	if( ! UShortTestValues[t].useBase && ! UShortTestValues[t].useLen )
	  {
	    unsigned short result = StringToUShort( UShortTestValues[t].str );
	    TEST( result == UShortTestValues[t].value );
	  }

	if( UShortTestValues[t].useBase && ! UShortTestValues[t].useLen )
	  {
	    unsigned short result = StringToUShort( UShortTestValues[t].str,
				      UShortTestValues[t].base );
	    TEST( result == UShortTestValues[t].value );
	  }

	if( UShortTestValues[t].useBase && UShortTestValues[t].useLen )
	  {
	    unsigned short result = StringToUShort( UShortTestValues[t].str,
				      UShortTestValues[t].base,
				      UShortTestValues[t].len );
	    TEST( result == UShortTestValues[t].value );
	  }
      }
  }
  
  {
    // StringToULong( const char * );
    // StringToULong( const char *, unsigned short );
    // StringToULong( const char *, unsigned short, size_t );

    for( size_t t = 0; ULongTestValues[t].str; t++ )
      {
	if( ! ULongTestValues[t].useBase && ! ULongTestValues[t].useLen )
	  {
	    unsigned long result = StringToULong( ULongTestValues[t].str );
	    TEST( result == ULongTestValues[t].value );
	  }

	if( ULongTestValues[t].useBase && ! ULongTestValues[t].useLen )
	  {
	    unsigned long result = StringToULong( ULongTestValues[t].str,
				      ULongTestValues[t].base );
	    TEST( result == ULongTestValues[t].value );
	  }

	if( ULongTestValues[t].useBase && ULongTestValues[t].useLen )
	  {
	    unsigned long result = StringToULong( ULongTestValues[t].str,
				      ULongTestValues[t].base,
				      ULongTestValues[t].len );
	    TEST( result == ULongTestValues[t].value );
	  }
      }
  }

  
  return( TRUE );
}

