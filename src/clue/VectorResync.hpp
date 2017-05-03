#ifndef _VectorResync_hh_
#define _VectorResync_hh_
//
// File:        VectorResync.hh
// Project:	StlUtils ()
// Desc:        
//
//  The VectorResync template function will modify the record indexes for
//  two vectors so that they both point to the same 'key' value. The 'key'
//  is determined by the 'Compare' object. 
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     11/04/97 07:36
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
//  $Id$ 
//

#include <StlUtilsConfig.hh>
#include <DumpInfo.hh>
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
  


//
// Detail Documentation
//
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.5  2011/12/30 23:57:23  paul
// First go at Mac gcc Port
//
// Revision 6.4  2005/09/24 19:33:11  houghton
// Bug-Fix.
//
// Revision 6.3  2005/07/13 17:16:25  houghton
// Bug-Fix: max checking was not correct.
//
// Revision 6.2  2005/07/13 16:33:40  houghton
// Bug-Fix: max checking was not correct.
//
// Revision 6.1  2003/08/09 11:22:44  houghton
// Changed to version 6
//
// Revision 5.4  2003/08/09 11:21:00  houghton
// Changed ver strings.
//
// Revision 5.3  2001/07/29 19:56:38  houghton
// *** empty log message ***
//
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 1.3  1999/06/10 11:45:50  houghton
// Changed to support two different types of vectors.
//
// Revision 1.2  1998/01/22 18:44:21  houghton
// Port(Sun5): the compiler does not understand T::size_type.
//
// Revision 1.1  1998/01/05 13:08:35  houghton
// Initial Version.
//
//
#endif // ! def _VectorResync_hh_ 

