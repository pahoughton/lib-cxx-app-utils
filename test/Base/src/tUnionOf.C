#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
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

  }

  return( true );
}

    
    
    
    
