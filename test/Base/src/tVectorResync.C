//
// File:        tVectorResync.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tVectorResync
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     11/04/97 08:30
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <TestConfig.hh>
#include <LibTest.hh>
#include <VectorResync.hh>
#include <Compare.hh>
#include <vector>

typedef vector< long >	    TestVector;

class TestCompare
{
public:

  int operator () ( const TestVector & a,
		    TestVector::size_type aRec,
		    const TestVector & b,
		    TestVector::size_type bRec ) const {
    cout << "checking " << aRec << " to " << bRec
	 << "  (" << a[aRec] << ") (" << b[bRec] << ")" << endl;
    return( ::compare( a[aRec], b[bRec] ) );
  };
};
  
    
bool
tVectorResync( LibTest & tester )
{
  {
    TestVector a;
    TestVector b;

    long num;
    
    for( num = 0;
	 num < 10;
	 ++ num )
      {
	a.push_back( num );
	b.push_back( num );
      }

    for( ; num < 15; ++ num )
      {
	a.push_back( num );
      }

    for( ; num < 20; ++ num )
      {
	a.push_back( num );
	b.push_back( num );
      }

    {
      TestVector::size_type ar = 0;
      TestVector::size_type br = 0;
      
      TestVector::size_type asr = 0;
      TestVector::size_type bsr = 0;

      TestCompare   comp;
      
      for( ; ar <  a.size(); ++ ar, ++ br )
	{
	  asr = ar;
	  bsr = br;

	  TEST( VectorResync( a, asr, b, bsr, comp ) );

	  if( asr != ar || bsr != br )
	    {
	      cout << "resynced: " << asr <<  ',' << bsr << endl;
	      ar = asr;
	      br = bsr;
	    }
	}
    }

  }
	  
  return( true );

}

// Revision Log:
//
// $Log$
// Revision 6.2  2005/07/13 17:16:35  houghton
// added output.
//
// Revision 6.1  2003/08/09 11:22:53  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:32  houghton
// Changed Version Num to 5
//
// Revision 1.1  1998/01/05 13:09:46  houghton
// Initial Version.
//
//
