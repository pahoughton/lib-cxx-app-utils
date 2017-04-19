//
// File:        tTimeIt01.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tTimeIt01
//  
// Author:      Paul A. Houghton - (paul4hough@gmail.com)
// Created:     07/08/97 08:13
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <TestConfig.hh>
#include <TimeIt.hh>
#include <LibTest.hh>
#include <Directory.hh>

#include <vector>

typedef vector<TimeIt>	List;

bool
tTimeIt01( LibTest & tester )
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
	  TESTP( true );
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
	TESTR( err, ( tAvg < (realAvg + (realAvg * .1 )) &&
		      tAvg > (realAvg - (realAvg * .1 )) ) );
      }
    else
      {
	TESTR( err, ( tAvg < (realAvg + 1) &&
		      tAvg > (realAvg - 1) ) );
      }
    
    TEST( tBest < (realBest + (realBest * .15 )) &&
	  tBest > (realBest - (realBest * .15 )) );

    TEST( tWorst < (realWorst + (realWorst * .15 )) &&
	  tWorst > (realWorst - (realWorst * .15 )) );

    
  }

  return( true );
}

	  
// Revision Log:
//
// $Log$
// Revision 6.2  2011/12/30 23:57:48  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:53  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:32  houghton
// Changed Version Num to 5
//
// Revision 4.2  1998/04/02 14:19:26  houghton
// Cleanup and eliminate warnings.
//
// Revision 4.1  1997/09/17 15:14:51  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:10:14  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/07/19 09:34:54  houghton
// Cleanup
// Port(Sun5): adjusted test values.
//
// Revision 3.1  1997/07/11 15:57:11  houghton
// Initial Version.
//
//
