//
// File:        StripTrailing.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for StripTrailing
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     12/20/97 08:02
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "StringUtils.hh"

STLUTILS_FUNCT_VERSION(
  StripTrailing,
  "$Id$" );


char *
StripTrailing( char * buffer, const char * white, size_t bufferSize )
{
  long      len = ( bufferSize == NPOS ? strlen( buffer ) : bufferSize );
  long	    pos = len;
  
  for( ; pos >= 0 ; -- pos )
    if( ! strchr( white, buffer[pos] ) )
      break;

  if( pos < len )
    buffer[ pos + 1 ] = 0;
  
  return( buffer );
}


// Revision Log:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 1.1  1997/12/20 16:07:58  houghton
// Initial Version.
//
//
