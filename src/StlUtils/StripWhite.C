//
// File:        StripWhite.C
// Project:	Clue
// Desc:        
//
//  	Remove leading and trailing white space from a string.
//  
// Author:      Paul Houghton - (paul_houghton@wcom.com)
// Created:     02/18/95 16:13
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//
//  grabed old 'StripSpaces.c' function and added the ability to
//  specifiy white spaces that are to be striped
//

#if !defined( CLUE_SHORT_FN )
#include "StringUtils.hh"
#else
#include "StrUtil.hh"
#endif

CLUE_FUNCT_VERSION(
  StripWhite,
  "$Id$" );

char *
StripWhite( char * buffer, const char * white, size_t bufSize )
{

  const char *  beg;
  size_t    	len;
  
  if( bufSize == NPOS )
    {
      beg = buffer + strspn( buffer, white );
      len = strlen( buffer );
    }
  else
    {
      // if the buffer has no size, don't touch it.
      if( bufSize == 0 )
	return( buffer );
      
      size_t i;
      for( i = 0; i < bufSize; i++ )
	{
	  if( ! strchr( white, buffer[i] ) )
	    {
	      break;
	    }
	}
      beg = buffer + i;
      len = bufSize - 1;
    }

  for( ; len; len-- )
    {
      if( ! strchr( white, buffer[len] ) )
	{
	  break;
	}
    }

  memmove( buffer, beg, (len - (beg - buffer)) + 1);
  
  buffer[ (len - (beg - buffer)) + 1 ] = 0;
  
  return( buffer );
}

//
// Revision Log:
//
// $Log$
// Revision 2.2  1996/11/04 14:33:59  houghton
// Restructure header comments layout.
// Changed default len to be NPOS instead of 0.
//
// Revision 2.1  1995/11/10 12:41:16  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:53  houghton
// Ports and Version ID changes
//
//
      


 
