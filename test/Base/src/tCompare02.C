//
// File:        tCompare02.C
// Project:	StlUtils
// Desc:        
//
//  Test for Compare functions in Compare.hh
//
// Source Header Version: 2.3
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/27/96 04:15
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Compare.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Compare.hh>
#endif


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
	{ TEST( compare( t1[ one ], t1[ two ] ) < 0 ); }		      \
      else								      \
	{ TEST( ! ( compare( t1[ one ], t1[ two ] ) < 0 ) ); }		      \
      									      \
      if( t1[ one ] == t1[ two ] )					      \
	{ TEST( compare( t1[ one ], t1[ two ] ) == 0 ); }		      \
      else								      \
	{ TEST( ! ( compare( t1[ one ], t1[ two ] ) == 0 ) ); }		      \
      									      \
      if( t1[ one ] > t1[ two ] )					      \
	{ TEST( compare( t1[ one ], t1[ two ] ) > 0 ); }		      \
      else								      \
	{ TEST( ! ( compare( t1[ one ], t1[ two ] ) > 0 ) ); }		      \
      									      \
    }


bool
tCompare02( LibTest & tester )
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
    // compare( const char *, const char * )
    const char * l = less;
    const char * m = more;
    
    TEST( compare( l, l ) == 0 );
    TEST( compare( l, m ) < 0 );
    TEST( compare( m, l ) > 0 );
  }
  
  {
    // compare( const char *, char * )
    // compare( char *, const char * )
    char * l = less;
    char * m = more;
    
    const char * cl = less;
    const char * cm = more;
    
    TEST( compare( cl, l ) == 0 );
    TEST( compare( cl, m ) < 0 );
    TEST( compare( cm, l ) > 0 );

    TEST( compare( l, cl ) == 0 );
    TEST( compare( l, cm ) < 0 );
    TEST( compare( m, cl ) > 0 );
  }
  
  {
    // compare( char *, char * )
    char * l = less;
    char * m = more;
    
    TEST( compare( l, l ) == 0 );
    TEST( compare( l, m ) < 0 );
    TEST( compare( m, l ) > 0 );
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

    // compare( const char * const *, const char * const * )
    TEST( compare( cpcl, cpcl ) == 0 );
    TEST( compare( cpcl, cpcm ) < 0 );
    TEST( compare( cpcm, cpcl ) > 0 );

    // compare( const char * const *, const char * * )
    TEST( compare( cpcl, cpl ) == 0 );
    TEST( compare( cpcl, cpm ) < 0 );
    TEST( compare( cpcm, cpl ) > 0 );

    // compare( const char * const *, char * const * )
    TEST( compare( cpcl, pcl ) == 0 );
    TEST( compare( cpcl, pcm ) < 0 );
    TEST( compare( cpcm, pcl ) > 0 );

    // compare( const char * const *, char * * )
    TEST( compare( cpcl, pl ) == 0 );
    TEST( compare( cpcl, pm ) < 0 );
    TEST( compare( cpcm, pl ) > 0 );
    

    
    // compare( const char * *, const char * const * )
    TEST( compare( cpl, cpcl ) == 0 );
    TEST( compare( cpl, cpcm ) < 0 );
    TEST( compare( cpm, cpcl ) > 0 );

    // compare( const char * *, const char * * )
    TEST( compare( cpl, cpl ) == 0 );
    TEST( compare( cpl, cpm ) < 0 );
    TEST( compare( cpm, cpl ) > 0 );

    // compare( const char * *, char * const * )
    TEST( compare( cpl, pcl ) == 0 );
    TEST( compare( cpl, pcm ) < 0 );
    TEST( compare( cpm, pcl ) > 0 );

    // compare( const char * *, char * * )
    TEST( compare( cpl, pl ) == 0 );
    TEST( compare( cpl, pm ) < 0 );
    TEST( compare( cpm, pl ) > 0 );


    
    // compare( char * const *, const char * const * )
    TEST( compare( pcl, cpcl ) == 0 );
    TEST( compare( pcl, cpcm ) < 0 );
    TEST( compare( pcm, cpcl ) > 0 );

    // compare( char * const *, const char * * )
    TEST( compare( pcl, cpl ) == 0 );
    TEST( compare( pcl, cpm ) < 0 );
    TEST( compare( pcm, cpl ) > 0 );

    // compare( char * const *, char * const * )
    TEST( compare( pcl, pcl ) == 0 );
    TEST( compare( pcl, pcm ) < 0 );
    TEST( compare( pcm, pcl ) > 0 );

    // compare( char * const *, char * * )
    TEST( compare( pcl, pl ) == 0 );
    TEST( compare( pcl, pm ) < 0 );
    TEST( compare( pcm, pl ) > 0 );



    // compare( char * *, const char * const * )
    TEST( compare( pl, cpcl ) == 0 );
    TEST( compare( pl, cpcm ) < 0 );
    TEST( compare( pm, cpcl ) > 0 );
    
    // compare( char * *, const char ** )
    TEST( compare( pl, cpl ) == 0 );
    TEST( compare( pl, cpm ) < 0 );
    TEST( compare( pm, cpl ) > 0 );

    // compare( char * *, char * const * )
    TEST( compare( pl, pcl ) == 0 );
    TEST( compare( pl, pcm ) < 0 );
    TEST( compare( pm, pcl ) > 0 );

    // compare( char * *, char * * )
    TEST( compare( pl, pl ) == 0 );
    TEST( compare( pl, pm ) < 0 );
    TEST( compare( pm, pl ) > 0 );

    
  }
  return( true );
}

//
// $Log$
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:27  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:07  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:39  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:27  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:47:35  houghton
// Added header comments.
// Reorder test to match header.
//
//
