//
// File:        tUnionOf.C
// Project:	Clue
// Desc:        
//
//  Test for UnionOf & UnionOfDur functions.
//
// Source Header Version: 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/31/96 07:19
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <ClueUtils.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#endif

bool
tUnionOf( LibTest & tester )
{
  {
    // UnionOf( long, long, long, long )

    long start1 = 25;
    long end1	= 50;
    long start2 = 55;
    long end2	= 75;

    // ( )
    //     ( )
    TEST( UnionOf( start1, end1, start2, end2 ) == 0 );

    // ( )
    //   ( )
    start2 = 50;
    TEST( UnionOf( start1, end1, start2, end2 ) == 0 );


    // (  )
    //   (   )
    end1 = 51;
    TEST( UnionOf( start1, end1, start2, end2 ) == 1 );

    // (   )
    //   (    )
    end1 = 60;
    TEST( UnionOf( start1, end1, start2, end2 ) == 10 );
    
    // (     )
    //   (    )
    end1 = 74;
    TEST( UnionOf( start1, end1, start2, end2 ) == 24 );

    // (      )
    //   (    )
    end1 = 75;
    TEST( UnionOf( start1, end1, start2, end2 ) == 25 );

    // (       )
    //   (    )
    end1 = 76;
    TEST( UnionOf( start1, end1, start2, end2 ) == 25 );

    // (        )
    //   (    )
    end1 = 100;
    TEST( UnionOf( start1, end1, start2, end2 ) == 25 );

    //  (       )
    //   (    )
    start1 = 49;
    TEST( UnionOf( start1, end1, start2, end2 ) == 25 );

    //   (      )
    //   (    )
    start1 = 50;
    TEST( UnionOf( start1, end1, start2, end2 ) == 25 );

    //    (     )
    //   (    )
    start1 = 51;
    TEST( UnionOf( start1, end1, start2, end2 ) == 24 );

    //     (    )
    //   (    )
    start1 = 55;
    TEST( UnionOf( start1, end1, start2, end2 ) == 20 );

    //     (  )
    //   (    )
    end1 = 75;
    TEST( UnionOf( start1, end1, start2, end2 ) == 20 );

    //     ( )
    //   (     )
    end1 = 70;
    TEST( UnionOf( start1, end1, start2, end2 ) == 15 );

    TEST( UnionOf( 25, 50, 40, 60 ) == 10 ); // doc example
  }

  {
    // UnionOfDur( long, long, long, long )

    long start1 = 25;
    long dur1	= 25;
    long start2 = 55;
    long dur2	= 20;

    // ( )
    //     ( )
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 0 );

    // ( )
    //   ( )
    start2 = 50;
    dur2 = 25;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 0 );


    // (  )
    //   (   )
    dur1 = 26;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 1 );

    // (   )
    //   (    )
    dur1 = 35;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 10 );
    
    // (     )
    //   (    )
    dur1 = 49;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 24 );

    // (      )
    //   (    )
    dur1 = 50;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 25 );

    // (       )
    //   (    )
    dur1 = 51;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 25 );

    // (        )
    //   (    )
    dur1 = 75;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 25 );

    //  (       )
    //   (    )
    start1 = 49;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 25 );

    //   (      )
    //   (    )
    start1 = 50;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 25 );

    //    (     )
    //   (    )
    start1 = 51;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 24 );

    //     (    )
    //   (    )
    start1 = 55;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 20 );

    //     (  )
    //   (    )
    dur1 = 20;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 20 );

    //     ( )
    //   (     )
    dur1 = 15;
    TEST( UnionOfDur( start1, dur1, start2, dur2 ) == 15 );

    TEST( UnionOfDur( 15, 20, 10, 10 ) == 5 ); // doc example
    
  }

  {
    // UnionOfDur( unsigned long, unsigned long,
    //		   unsigned long, unsigned long,
    //		   unsigned long )

    unsigned long   sOne;
    unsigned long   dOne;
    unsigned long   sTwo;
    unsigned long   dTwo;
    unsigned long   freq;

    sOne = 5;
    dOne = 10;
    sTwo = 10;
    dTwo = 200;
    freq = 20;

    TEST( UnionOfDur( sOne, dOne, sTwo, dTwo, freq ) == 100 );
    TEST( UnionOfDur( 10, 5, 5, 100, 10 ) == 50 );
  }
    
  return( true );
}

//
// $Log$
// Revision 2.3  1996/11/04 18:22:54  houghton
// Chaged include because Clue.hh renamed to ClueUtils.hh.
//
// Revision 2.2  1996/11/04 14:53:50  houghton
// Added header comments.
// Added more test to verify function.
//
//
    
    
    
    
