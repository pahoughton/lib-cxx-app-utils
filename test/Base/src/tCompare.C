
#include <LibTest.hh>
#include <limits.h>

bool tCompare1( LibTest & test );
bool tCompare2( LibTest & test );

int CompCount;

bool
tCompare( LibTest & test )
{
  CompCount = 7;
  
  test( tCompare1( test ), true );
  test( tCompare2( test ), true );

  return( true );
}

char 	    	CompChar[] =
{
  CHAR_MIN,  
  0,
  5,
  10,
  15,
  20,
  CHAR_MAX,
};
  
signed char 	CompSChar[] =
{
  SCHAR_MIN,
  -10
  -5,
  0,
  5,
  10,
  SCHAR_MAX,
};

unsigned char	CompUChar[] =
{
  0,
  5,
  10,
  15,
  20,
  25,
  UCHAR_MAX,
};

short	    	CompShort[] =
{
  SHRT_MIN,
  -10
  -5,
  0,
  5,
  10,
  SHRT_MAX,
};

unsigned short	CompUShort[] =
{
  0,
  5,
  10,
  15,
  20,
  25,
  USHRT_MAX,
};

int	    	CompInt[] =
{
  INT_MIN,
  -10
  -5,
  0,
  5,
  10,
  INT_MAX,
};
unsigned int	CompUInt[] =
{
  0,
  5,
  10,
  15,
  20,
  25,
  UINT_MAX,
};

long	    	CompLong[] =
{
  LONG_MIN,
  -10
  -5,
  0,
  5,
  10,
  LONG_MAX,
};

unsigned long	CompULong[] =
{
  0,
  5,
  10,
  15,
  20,
  25,
  ULONG_MAX,
};

float	    	CompFloat[] =
{
  -9999999999.99,
  -5.5,
  -0.5,
  0.0,
  0.5,
  5.5,
  9999999999.99,
};
  
double	    	CompDouble[] =
{
  -9999999999.99,
  -5.5,
  -0.5,
  0.0,
  0.5,
  5.5,
  9999999999.99,
};
  

