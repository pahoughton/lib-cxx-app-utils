//
// File:        StringCaseReverseSearch.C
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//    Search the string 'haystack' for the string 'needle' starting
//    from the end of 'haystack' and ignoring case. If 'needle' is
//    found in 'haystack' a pointer to the first char of 'needle'
//    in 'haystack' is returned. If 'needle' is not found, a 0 is
//    returned. Use NPOS for the len parameters if the corisponding
//    string is null (0) terminated.
//    
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     04/29/95 11:56 
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//
// %PID%

#include "StringUtils.hh"
#include <cstddef>
#include <cstring>
#include <cctype>

STLUTILS_FUNCT_VERSION(
  StringCaseReverseSearch,
  "%PID%" );

const char *
StringCaseReverseSearch(
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
  register const char 	    ndlEnd = tolower( *nEnd );
  
  while( hay <= hEnd )
    {
      // find the first needle char in the remaining haystack
      
      for( ; hay <= hEnd && tolower(*hEnd) != ndlEnd; hEnd-- );

      // didn't find it bye-bye
      if( hay > hEnd ) return( 0 );

      hEnd--;

      // the rest of the haystack & needle
      
      register const char * rHay = hEnd;	
      register const char * rNdl = nEnd - 1;
      
      // now look for the rest of the needle in the reset of the hay
      
      for( ; tolower( *rHay ) == tolower( *rNdl ) && rNdl >= needle;
	     rHay--, rNdl-- );

	// found it ... bye bye
      if( rNdl < needle ) return( rHay + 1 );
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
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:17  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:00  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:08:51  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/01/18 17:35:40  houghton
// Changed: removed ifdef STLUTILS_SAFETY_ON. Now always checks args.
//
// Revision 3.2  1996/11/24 19:05:41  houghton
// Removed support for short filenames.
//
// Revision 3.1  1996/11/14 01:24:16  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:30:09  houghton
// Restructure header comments layout.
// Changed default len to be NPOS instead of 0.
//
// Revision 2.1  1995/11/10 12:41:10  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:48  houghton
// Ports and Version ID changes
//
//


     
