// 1997-07-08 (cc) <paul4hough@gmail.com>

#include <clue/TimeIt.hpp>
#include <clue/Directory.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <vector>

static valid::verify verify("clue::TimeIt");
using namespace clue;

typedef std::vector<TimeIt>	List;

bool
v_TimeIt01( void )
{
  {
    TimeIt		t;
    List		tList;
    Directory		dir;
    List::size_type	maxTests = 50;

    double	realAvg = 0;
    double      realBest = 5000.0;
    double	realWorst = 0;

    {
      double	real;
      for( List::size_type cnt = 0; cnt < maxTests; ++ cnt )
	{
	  t.start();
	  long loops = (10 + (rand() % 40));
#if defined( SHOW_TIMEIT )
	  tester.getDump() << "Loops: " << loops;
	  tester.getDump().flush();
#endif
	  {
	    for( long l = 0; l < loops; ++ l )
	      {
		dir.set( "." );
	      }
	  }
	  t.stop();

	  real = ( t.getRealDiff().tv_sec +
		   ((double)(t.getRealDiff().tv_usec) / 1000000) );
#if defined( SHOW_TIMEIT )
	  tester.getDump() << " Real: " << real
			   << " "  << t.dump() << endl;
#else
	  TEST( true );
#endif
	  if( real < realBest )
	    realBest = real;
	  if( real > realWorst )
	    realWorst = real;
	  realAvg += real;

	  tList.push_back( t );
	}
    }

    TEST( tList.size() == maxTests );
    realAvg /= tList.size();

    TimeIt  avg( TimeItAverage( tList.begin(), tList.end() ) );
    TimeIt  best( *TimeItBestReal( tList.begin(), tList.end() ) );
    TimeIt  worst( *TimeItWorstReal( tList.begin(), tList.end() ) );

#if defined( SHOW_TIMEIT )
    tester.getDump() << "Avg: " << realAvg << " "  << avg.dump() << endl;
    tester.getDump() << "Best: " << realBest << " " << best.dump() << endl;
    tester.getDump() << "Worst: " << realWorst << " " << worst.dump() << endl;
#endif

    double tAvg;
    double tBest;
    double tWorst;

    tAvg = ( avg.getRealDiff().tv_sec +
	     ( (double)avg.getRealDiff().tv_usec / 1000000 ) );

    tBest = ( best.getRealDiff().tv_sec +
	     ( (double)best.getRealDiff().tv_usec / 1000000 ) );

    tWorst = ( worst.getRealDiff().tv_sec +
	     ( (double)worst.getRealDiff().tv_usec / 1000000 ) );


    Str err;
    err << "realavg: " << realAvg << " tAvg: " << tAvg;

    if( tAvg > 8 )
      {
	TEST( ( tAvg < (realAvg + (realAvg * .1 )) &&
		tAvg > (realAvg - (realAvg * .1 )) ) );
      }
    else
      {
	TEST( ( tAvg < (realAvg + 1) &&
		tAvg > (realAvg - 1) ) );
      }

    TEST( tBest < (realBest + (realBest * .15 )) &&
	  tBest > (realBest - (realBest * .15 )) );

    TEST( tWorst < (realWorst + (realWorst * .15 )) &&
	  tWorst > (realWorst - (realWorst * .15 )) );


  }
  return( verify.is_valid() );
}
