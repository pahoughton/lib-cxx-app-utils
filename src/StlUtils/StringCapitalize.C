//
// File:        StringCapitalize.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/06/95 12:03 
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:41:09  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:47  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include "StringUtils.hh"
#include <cctype>
#include <cstddef>
#else
#include "StrUtil.hh"
#include <cctype>
#include <cstddef>
#endif

CLUE_FUNCT_VERSION(
  StringCapitalize,
  "$Id$" );

char *
StringCapitalize( char * str, size_t len )
{
  if( len )
    {
      const char * end = str + len;
      for( char * s = str; s < end; s++ )
	{
	  int inword = islower(*s);
	  
	  if( inword )
	    *s = toupper( *s );
	  else
	    inword = isupper(*s) || isdigit(*s);
	  
	  if( inword )
	    {
	      for( s++; s < end; s++ )
		{
		  if( isupper(*s) )
		    *s = tolower(*s);
		  else
		    if( ! islower(*s) && ! isdigit(*s) && (*s != '\'' ) )
		      break;
		}
	    }
	}
    }
  else
    {
      for( char * s = str; *s; s++ )
	{
	  int inword = islower(*s);
	  
	  if( inword )
	    *s = toupper( *s );
	  else
	    inword = isupper(*s) || isdigit(*s);
	  
	  if( inword )
	    {
	      for( s++; *s; s++ )
		{
		  if( isupper(*s) )
		    *s = tolower(*s);
		  else
		    if( ! islower(*s) && ! isdigit(*s) && (*s != '\'' ) )
		      break;
		}
	    }
	}
    }
  return( str );
}
