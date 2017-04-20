//
// File:        StringReverseSearch.C
// Project:     StlUtils ()
// Desc:        
//
//    Search a string 'haystack' for the string 'needle' starting
//    from the end of 'haystack'. If 'needle' is found in 'haystack'
//    a pointer to the first char of 'needle' in 'haystack' is
//    returned. If 'needle' is not found, a 0 is returned.
//    Use NPOS for the len parameters if the corisponding string
//    is null (0) terminated.
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     04/29/95 11:56 
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "StringUtils.hh"
#include <cstddef>
#include <cstring>


STLUTILS_FUNCT_VERSION(
  StringReverseSearch,
  "$Id$ " );


const char *
StringReverseSearch(
  const char *  haystack,
  size_t    	hayLen,
  const char *  needle,
  size_t    	needleLen
  )
{

  // check for valid input params
  if( ! haystack ||
      ! hayLen	 ||
      ! needle   ||
      ! needleLen )
    return( 0 );

  
  size_t    nLen = (needleLen != NPOS) ? needleLen : strlen( needle );
  size_t    hLen = (hayLen != NPOS ) ? hayLen : strlen( haystack );

  if( ! hLen || ! nLen || nLen > hLen ) return( 0 );

  const char * hEnd = &(haystack[ hLen - 1 ]);
  const char * nEnd = &(needle[ nLen - 1 ]);

  register const char *     hay = haystack + (nLen - 1);
  register const char 	    ndlEnd = *nEnd;
  
  while( hay <= hEnd )
    {
      // find the first needle char in the remaining haystack
      
      for( ; hay <= hEnd && *hEnd != ndlEnd; hEnd-- );

      // didn't find it bye-bye
      if( hay > hEnd ) return( 0 );

      hEnd--;

      // the rest of the haystack & needle
      
      register const char * rHay = hEnd;	
      register const char * rNdl = nEnd - 1;
      
      // now look for the rest of the needle in the reset of the hay
      
      for( ; *rHay == *rNdl && rNdl >= needle; rHay--, rNdl-- );

	// found it ... bye bye
      if( rNdl < needle ) return( rHay + 1);
    }
  return( 0 );
}

//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.2  2011/12/30 23:57:21  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:43  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:21:00  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:02  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:08:52  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/01/18 17:35:40  houghton
// Changed: removed ifdef STLUTILS_SAFETY_ON. Now always checks args.
//
// Revision 3.2  1996/11/24 19:07:52  houghton
// Removed support for short filenames.
//
// Revision 3.1  1996/11/14 01:24:18  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:31:27  houghton
// Restructure header comments layout.
// Changed default len to be NPOS instead of 0.
//
// Revision 2.1  1995/11/10 12:41:12  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:49  houghton
// Ports and Version ID changes
//
//
