
#include <LibTest.hh>
#include <Compare.hh>

extern int  	    	CompCount;
extern char  	    	CompChar[];
extern signed char   	CompSChar[];
extern unsigned char  	CompUChar[];
extern short  	    	CompShort[];
extern unsigned short  	CompUShort[];
extern int  	    	CompInt[];
extern unsigned int  	CompUInt[];
extern long  	    	CompLong[];
extern unsigned long  	CompULong[];
extern float  	    	CompFloat[];
extern double  	    	CompDouble[];


#define CHECK_TYPE( t1 )						      \
  for( two = 0; two < CompCount; two++ )				      \
    {									      \
									      \
      if( t1[ one ] < t1[ two ] )					      \
	test( compare( t1[ one ], t1[ two ] ) < 0 );			      \
      else								      \
	test( ! ( compare( t1[ one ], t1[ two ] ) < 0 ) );		      \
      									      \
      if( t1[ one ] == t1[ two ] )					      \
	test( compare( t1[ one ], t1[ two ] ) == 0 );			      \
      else								      \
	test( ! ( compare( t1[ one ], t1[ two ] ) == 0 ) );		      \
      									      \
      if( t1[ one ] > t1[ two ] )					      \
	test( compare( t1[ one ], t1[ two ] ) > 0 );			      \
      else								      \
	test( ! ( compare( t1[ one ], t1[ two ] ) > 0 ) );		      \
      									      \
    }


bool
tCompare2( LibTest & test )
{

  {
    int two;
    
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
    // compare( char *, char * )
    char * l = less;
    char * m = more;
    
    test( compare( l, l ) == 0 );
    test( compare( l, m ) < 0 );
    test( compare( m, l ) > 0 );
  }
  
  {
    // compare( const char *, const char * )
    const char * l = less;
    const char * m = more;
    
    test( compare( l, l ) == 0 );
    test( compare( l, m ) < 0 );
    test( compare( m, l ) > 0 );
  }
  
  {
    // compare( char *, const char * )
    // compare( const char *, char * )
    char * l = less;
    char * m = more;
    
    const char * cl = less;
    const char * cm = more;
    
    test( compare( cl, l ) == 0 );
    test( compare( cl, m ) < 0 );
    test( compare( cm, l ) > 0 );

    test( compare( l, cl ) == 0 );
    test( compare( l, cm ) < 0 );
    test( compare( m, cl ) > 0 );
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

    // compare( char **, char ** )
    test( compare( pl, pl ) == 0 );
    test( compare( pl, pm ) < 0 );
    test( compare( pm, pl ) > 0 );

    // compare( char **, const char ** )
    test( compare( pl, cpl ) == 0 );
    test( compare( pl, cpm ) < 0 );
    test( compare( pm, cpl ) > 0 );

    // compare( char **, char * const * )
    test( compare( pl, pcl ) == 0 );
    test( compare( pl, pcm ) < 0 );
    test( compare( pm, pcl ) > 0 );

    // compare( char **, const char * const * )
    test( compare( pl, cpcl ) == 0 );
    test( compare( pl, cpcm ) < 0 );
    test( compare( pm, cpcl ) > 0 );


    // compare( const char **, char ** )
    test( compare( cpl, pl ) == 0 );
    test( compare( cpl, pm ) < 0 );
    test( compare( cpm, pl ) > 0 );

    // compare( const char **, const char ** )
    test( compare( cpl, cpl ) == 0 );
    test( compare( cpl, cpm ) < 0 );
    test( compare( cpm, cpl ) > 0 );

    // compare( const char **, char * const * )
    test( compare( cpl, pcl ) == 0 );
    test( compare( cpl, pcm ) < 0 );
    test( compare( cpm, pcl ) > 0 );

    // compare( const char **, const char * const * )
    test( compare( cpl, cpcl ) == 0 );
    test( compare( cpl, cpcm ) < 0 );
    test( compare( cpm, cpcl ) > 0 );

    
    // compare( char * const *, char ** )
    test( compare( pcl, pl ) == 0 );
    test( compare( pcl, pm ) < 0 );
    test( compare( pcm, pl ) > 0 );

    // compare( char * const *, const char ** )
    test( compare( pcl, cpl ) == 0 );
    test( compare( pcl, cpm ) < 0 );
    test( compare( pcm, cpl ) > 0 );

    // compare( char * const *, char * const * )
    test( compare( pcl, pcl ) == 0 );
    test( compare( pcl, pcm ) < 0 );
    test( compare( pcm, pcl ) > 0 );

    // compare( char * const *, const char * const * )
    test( compare( pcl, cpcl ) == 0 );
    test( compare( pcl, cpcm ) < 0 );
    test( compare( pcm, cpcl ) > 0 );

    
    // compare( const char * const *, char ** )
    test( compare( cpcl, pl ) == 0 );
    test( compare( cpcl, pm ) < 0 );
    test( compare( cpcm, pl ) > 0 );

    // compare( const char * const *, const char ** )
    test( compare( cpcl, cpl ) == 0 );
    test( compare( cpcl, cpm ) < 0 );
    test( compare( cpcm, cpl ) > 0 );

    // compare( const char * const *, char * const * )
    test( compare( cpcl, pcl ) == 0 );
    test( compare( cpcl, pcm ) < 0 );
    test( compare( cpcm, pcl ) > 0 );

    // compare( const char * const *, const char * const * )
    test( compare( cpcl, cpcl ) == 0 );
    test( compare( cpcl, cpcm ) < 0 );
    test( compare( cpcm, cpcl ) > 0 );

  }
  return( true );
}
