//
// File:        tLruSash01.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tLruSash01
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     10/29/98 05:20
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "LruSash.hh"

#include "TestConfig.hh"
#include "LibTest.hh"
#include <iomanip>

typedef vector< unsigned long >	AllocList;

AllocList   AllocCount( 20, 0 );

struct TestObj
{
  long	k;

  TestObj( unsigned long lruKey ) : k( lruKey ) {
    ++ AllocCount[ k ];
  };
};

struct HashFunct
{
  inline unsigned long    operator () ( long k ) const {
    return( k );
  };
};

struct MaxObj
{
  inline unsigned long	operator () ( void ) {
    return( 5 );
  };
};

typedef LruSash< TestObj, long, HashFunct, MaxObj >	TestLru;

bool
tLruSash01( LibTest & tester )
{
  HashFunct lruFunct;
  MaxObj    lruMax;
  
  {
    TestLru	t( lruFunct, lruMax, 1 );

    long v( 0 );

    {
      for( long l = 0 ; l < 20; ++ l )
	{
	  v = t.obj( l ).k;
	}
    }

    {
      for( long l = 19; l >= 0; -- l )
	{
	  v = t.obj( l ).k;
	}
    }

    {
      v = t.obj( 5 ).k;
      v = t.obj( 11 ).k;
      v = t.obj( 16 ).k;
      v = t.obj( 3 ).k;
      v = t.obj( 7 ).k;
      v = t.obj( 8 ).k;      
      v = t.obj( 11 ).k;
      v = t.obj( 16 ).k;
      v = t.obj( 3 ).k;
      v = t.obj( 7 ).k;
      v = t.obj( 5 ).k;
      v = t.obj( 11 ).k;
      v = t.obj( 11 ).k;
      v = t.obj( 11 ).k;
      v = t.obj( 5 ).k;
      v = t.obj( 5 ).k;
      v = t.obj( 5 ).k;
      v = t.obj( 5 ).k;
    }

    {
      for( long l = 0; l < 20; ++ l )
	{
	  cout << setw( 5 ) << l << " " << AllocCount[ l ] << endl;
	}
    }
    
  }
  
  return( true );
}

// Revision Log:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:29  houghton
// Changed Version Num to 5
//
// Revision 4.1  1998/11/02 15:28:50  houghton
// Initial Version.
//
//
