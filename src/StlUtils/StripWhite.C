//
// File:        StripWhite.C
// Project:	StlUtils ()
// Desc:        
//
//  	Remove leading and trailing white space from a string.
//  
// Author:      Paul Houghton - (paul_houghton@mci.com)
// Created:     02/18/95 16:13
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
// $Id$ 
//
//  grabed old 'StripSpaces.c' function and added the ability to
//  specifiy white spaces that are to be striped
//

#include "StringUtils.hh"

STLUTILS_FUNCT_VERSION(
  StripWhite,
  "$Id$ " );

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
// 
// %PL%
// 
// $Log$
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
// Revision 4.1  1997/09/17 15:13:05  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:55  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1996/11/24 19:09:42  houghton
// Removed support for short filenames.
//
// Revision 3.1  1996/11/14 01:24:22  houghton
// Changed to Release 3
//
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
      


 
