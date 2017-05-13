// 1997-11-04 (cc) <paul4hough@gmail.com>

#include <clue/VectorResync.hpp>
#include <clue/compare>
#include <vector>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::AbsLong");
using namespace clue;

typedef std::vector< long >	    TestVector;

class TestCompare
{
public:

  int operator () ( const TestVector & a,
		    TestVector::size_type aRec,
		    const TestVector & b,
		    TestVector::size_type bRec ) const {
#if defined( DEBUG )
    std::cout << "checking " << aRec << " to " << bRec
	      << "  (" << a[aRec] << ") (" << b[bRec] << ")" << endl;
#endif
    return( ::compare( a[aRec], b[bRec] ) );
  };
};


bool
v_VectorResync( void )
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
#if defined( DEBUG )
	      std::cout << "resynced: " << asr <<  ',' << bsr << endl;
#endif
	      ar = asr;
	      br = bsr;
	    }
	}
    }

  }
  return( verify.is_valid() );
}
