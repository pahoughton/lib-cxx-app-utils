// 1996-10-27 (cc) <paul4hough@gmail.com>

#include <clue/compare>
#include <climits>

#define VALID_VALIDATOR verify
#include <valid/verify>

static valid::verify verify("clue::compare02");

int  	    	CompCount = 7;

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

#define CHECK_TYPE( t1 )						\
  for( two = 0; two < CompCount; two++ )				\
    {									\
									\
      if( t1[ one ] < t1[ two ] )					\
	{ VVTRUE( clue::compare( t1[ one ], t1[ two ] ) < 0 ); }		\
      else								\
	{ VVTRUE( ! ( clue::compare( t1[ one ], t1[ two ] ) < 0 ) ); }	\
									\
      if( t1[ one ] == t1[ two ] )					\
	{ VVTRUE( clue::compare( t1[ one ], t1[ two ] ) == 0 ); }		\
      else								\
	{ VVTRUE( ! ( clue::compare( t1[ one ], t1[ two ] ) == 0 ) ); }	\
									\
      if( t1[ one ] > t1[ two ] )					\
	{ VVTRUE( clue::compare( t1[ one ], t1[ two ] ) > 0 ); }		\
      else								\
	{ VVTRUE( ! ( clue::compare( t1[ one ], t1[ two ] ) > 0 ) ); }	\
									\
    }


bool
v_compare02( void )
{

  {
    int two = 0;

    for( int one = 0; one < CompCount; one++ )
      {
	CHECK_TYPE( CompChar );
	CHECK_TYPE( CompSChar );
	CHECK_TYPE( CompUChar );
	CHECK_TYPE( CompShort );
	CHECK_TYPE( CompUShort );
	CHECK_TYPE( CompInt );
	CHECK_TYPE( CompUInt );
	CHECK_TYPE( CompLong );
	CHECK_TYPE( CompULong );
	CHECK_TYPE( CompFloat );
	CHECK_TYPE( CompDouble );
      }

  }

  char less[] = "a test";
  char more[] = "z test";

  {
    // clue::compare( const char *, const char * )
    const char * l = less;
    const char * m = more;

    VVTRUE( clue::compare( l, l ) == 0 );
    VVTRUE( clue::compare( l, m ) < 0 );
    VVTRUE( clue::compare( m, l ) > 0 );
  }

  {
    // clue::compare( const char *, char * )
    // clue::compare( char *, const char * )
    char * l = less;
    char * m = more;

    const char * cl = less;
    const char * cm = more;

    VVTRUE( clue::compare( cl, l ) == 0 );
    VVTRUE( clue::compare( cl, m ) < 0 );
    VVTRUE( clue::compare( cm, l ) > 0 );

    VVTRUE( clue::compare( l, cl ) == 0 );
    VVTRUE( clue::compare( l, cm ) < 0 );
    VVTRUE( clue::compare( m, cl ) > 0 );
  }

  {
    // clue::compare( char *, char * )
    char * l = less;
    char * m = more;

    VVTRUE( clue::compare( l, l ) == 0 );
    VVTRUE( clue::compare( l, m ) < 0 );
    VVTRUE( clue::compare( m, l ) > 0 );
  }

  {
    char * l = less;
    char * m = more;

    const char * cl = less;
    const char * cm = more;

    char ** pl = &l;
    char ** pm = &m;

    const char ** cpl = &cl;
    const char ** cpm = &cm;

    char * const * pcl = (char * const *) &cl;
    char * const * pcm = (char * const *) &cm;

    const char * const * cpcl = &cl;
    const char * const * cpcm = &cm;

    // clue::compare( const char * const *, const char * const * )
    VVTRUE( clue::compare( cpcl, cpcl ) == 0 );
    VVTRUE( clue::compare( cpcl, cpcm ) < 0 );
    VVTRUE( clue::compare( cpcm, cpcl ) > 0 );

    // clue::compare( const char * const *, const char * * )
    VVTRUE( clue::compare( cpcl, cpl ) == 0 );
    VVTRUE( clue::compare( cpcl, cpm ) < 0 );
    VVTRUE( clue::compare( cpcm, cpl ) > 0 );

    // clue::compare( const char * const *, char * const * )
    VVTRUE( clue::compare( cpcl, pcl ) == 0 );
    VVTRUE( clue::compare( cpcl, pcm ) < 0 );
    VVTRUE( clue::compare( cpcm, pcl ) > 0 );

    // clue::compare( const char * const *, char * * )
    VVTRUE( clue::compare( cpcl, pl ) == 0 );
    VVTRUE( clue::compare( cpcl, pm ) < 0 );
    VVTRUE( clue::compare( cpcm, pl ) > 0 );



    // clue::compare( const char * *, const char * const * )
    VVTRUE( clue::compare( cpl, cpcl ) == 0 );
    VVTRUE( clue::compare( cpl, cpcm ) < 0 );
    VVTRUE( clue::compare( cpm, cpcl ) > 0 );

    // clue::compare( const char * *, const char * * )
    VVTRUE( clue::compare( cpl, cpl ) == 0 );
    VVTRUE( clue::compare( cpl, cpm ) < 0 );
    VVTRUE( clue::compare( cpm, cpl ) > 0 );

    // clue::compare( const char * *, char * const * )
    VVTRUE( clue::compare( cpl, pcl ) == 0 );
    VVTRUE( clue::compare( cpl, pcm ) < 0 );
    VVTRUE( clue::compare( cpm, pcl ) > 0 );

    // clue::compare( const char * *, char * * )
    VVTRUE( clue::compare( cpl, pl ) == 0 );
    VVTRUE( clue::compare( cpl, pm ) < 0 );
    VVTRUE( clue::compare( cpm, pl ) > 0 );



    // clue::compare( char * const *, const char * const * )
    VVTRUE( clue::compare( pcl, cpcl ) == 0 );
    VVTRUE( clue::compare( pcl, cpcm ) < 0 );
    VVTRUE( clue::compare( pcm, cpcl ) > 0 );

    // clue::compare( char * const *, const char * * )
    VVTRUE( clue::compare( pcl, cpl ) == 0 );
    VVTRUE( clue::compare( pcl, cpm ) < 0 );
    VVTRUE( clue::compare( pcm, cpl ) > 0 );

    // clue::compare( char * const *, char * const * )
    VVTRUE( clue::compare( pcl, pcl ) == 0 );
    VVTRUE( clue::compare( pcl, pcm ) < 0 );
    VVTRUE( clue::compare( pcm, pcl ) > 0 );

    // clue::compare( char * const *, char * * )
    VVTRUE( clue::compare( pcl, pl ) == 0 );
    VVTRUE( clue::compare( pcl, pm ) < 0 );
    VVTRUE( clue::compare( pcm, pl ) > 0 );



    // clue::compare( char * *, const char * const * )
    VVTRUE( clue::compare( pl, cpcl ) == 0 );
    VVTRUE( clue::compare( pl, cpcm ) < 0 );
    VVTRUE( clue::compare( pm, cpcl ) > 0 );

    // clue::compare( char * *, const char ** )
    VVTRUE( clue::compare( pl, cpl ) == 0 );
    VVTRUE( clue::compare( pl, cpm ) < 0 );
    VVTRUE( clue::compare( pm, cpl ) > 0 );

    // clue::compare( char * *, char * const * )
    VVTRUE( clue::compare( pl, pcl ) == 0 );
    VVTRUE( clue::compare( pl, pcm ) < 0 );
    VVTRUE( clue::compare( pm, pcl ) > 0 );

    // clue::compare( char * *, char * * )
    VVTRUE( clue::compare( pl, pl ) == 0 );
    VVTRUE( clue::compare( pl, pm ) < 0 );
    VVTRUE( clue::compare( pm, pl ) > 0 );

  }
  return( verify.is_valid() );
}
