/**
  File:		basename.C
  Project:	StlUtils 
  Desc:

	const char *
	basename( const char * fn );
	    Returns a pointer to the filename from part of 'fn'
	    without the directory part.
	
	char *
	basename( char * fn );
	    Returns a pointer to the filename from part of 'fn'
	    without the directory part.    
  
  Notes:
    
  Author(s):	Paul Houghton <<paul.houghton@mci.com>>
  Created:	06/16/95 04:43 
  
  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Name$
    $Revision$
    $State$


**/


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

