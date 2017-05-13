#ifndef _clue_VectorResync_hpp_
#define _clue_VectorResync_hpp_
/* 1997-11-04 (cc) Paul Houghton - (paul4hough@gmail.com)

   The VectorResync template function will modify the record indexes for
   two vectors so that they both point to the same 'key' value. The 'key'
   is determined by the 'Compare' object.
*/

#include <clue/DumpInfo.hpp>
#include <iostream>

template< class TA, class SizeTypeA, class TB, class SizeTypeB, class Compare >
inline
bool
VectorResync(
  const TA &		a,
  SizeTypeA	&	aRec,
  const TB &		b,
  SizeTypeB	&	bRec,
  const Compare &	compare
  )
{
  if( compare( a, aRec, b, bRec ) == 0 )
    return( true );

  SizeTypeA asr = aRec;
  SizeTypeB bsr = bRec;

  for( SizeTypeA end = 1;
       aRec + end < a.size() || bRec + end < b.size() ;
       ++ end )
    {

      for( SizeTypeA beg = 0; beg < end; ++ beg )
	{
	  if( bsr + end < b.size()
	      && asr + beg < a.size()
	      && compare( a, asr + beg, b, bsr + end ) == 0 )
	    {
	      aRec = asr + beg;
	      bRec = bsr + end;
	      return( true );
	    }

	  if( asr + end < a.size()
	      && bsr + beg < b.size()
	      && compare( a, asr + end, b, bsr + beg ) == 0 )
	    {
	      aRec = asr + end;
	      bRec = bsr + beg;
	      return( true );
	    }
	}

      if( asr + end < a.size()
	  && bsr+ end < b.size()
	  && compare( a, asr + end, b, bsr + end ) == 0 )
	{
	  aRec = asr + end;
	  bRec = bsr + end;
	  return( true );
	}
    }
  return( false );
}

#endif // ! def _clue_VectorResync_hpp_
