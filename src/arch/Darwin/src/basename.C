//
// File:        basename.C
// Project:	StlUtils
// Desc:        
//
//	const char *
//	basename( const char * fn );
//	    Returns a pointer to the filename from part of 'fn'
//	    without the directory part.
//	
//	char *
//	basename( char * fn );
//	    Returns a pointer to the filename from part of 'fn'
//	    without the directory part.
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     06/16/95 04:43 
//
// Revision History: (See end of file for Revision Log)
//

#include "StringUtils.hh"
#include <cstring>

STLUTILS_FUNCT_VERSION(
  basename,
  "$Id$" );


const char *
basename( const char * fn )
{
  if( ! fn ) return( fn );

  const char * name = strrchr( fn, STLUTILS_DIR_DELIM );

  if( name )
    return( name + 1 );
  else
    return( fn );
}

char *
basename( char * fn )
{
  if( ! fn ) return( fn );

  char * name = strrchr( fn, STLUTILS_DIR_DELIM );

  if( name )
    return( name + 1 );
  else
    return( fn );
}

//
// Revision Log:
//
// $Log$
// Revision 1.1  2012/05/07 16:25:16  paul
// *** empty log message ***
//
// Revision 6.2  2011/12/30 23:57:26  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:45  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:20  houghton
// Changed Version Num to 5
//
// Revision 1.1  1998/07/20 11:28:20  houghton
// Initial Version.
//
//
