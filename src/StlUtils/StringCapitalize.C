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
// Revision 1.1  1995/11/05 13:23:35  houghton
// Initaial implementation
//
//

#include <StringUtils.hh>

#include <cctype>
#include <cstddef>

static const char * RcsId =
LIB_CLUE_VERSION
"$Id$";

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
