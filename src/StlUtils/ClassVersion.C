//
// File:        ClassVersion.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     10/04/95 07:41
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:40:18  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  14:48:48  houghton
// New Class Version id method
//
//

#if !defined( CLUE_SHORT_FN )
#include "ClassVersion.hh"
#include <stddef>
#include <cstring>
#else
#include "ClassVer.hh"
#include <stddef>
#include <cstring>
#endif
 
CLUE_VERSION( ClassVersion,
	      "$Id$" );
	 

ClassVersion::ClassVersion(
  const char * className,
  const char * fullVersionString,
  const char * fileName,		    // __FILE__
  const char * compileDateString,	    // __DATE__
  const char * compileTimeString,	    // __TIME__
  const char * versionString,		    // "$Id$"
  const char * prjName,
  const char * prjVer,
  unsigned long prjVerNumber
  )
{
  verString = fullVersionString;
  prjVerNum = prjVerNumber;
  
  size_t bufSize = ( strlen( className ) +
		     strlen( fileName ) +
		     strlen( compileDateString ) +
		     strlen( compileTimeString ) +
		     strlen( versionString ) +
		     50 );

  classVerString = new char[ bufSize ];

  if( ! classVerString )
    return;
  
  strcpy( classVerString, className );
  strcat( classVerString, " - " );
  strcat( classVerString, fileName );
  strcat( classVerString, " - Compiled " );
  strcat( classVerString, compileDateString );
  strcat( classVerString, " " );
  strcat( classVerString, compileTimeString );
  strcat( classVerString, "\n    " );
  strcat( classVerString, versionString );

  bufSize = strlen( prjName ) + strlen( prjVer ) + 10;
  
  prjVerString = new char[ bufSize ];

  if( ! prjVerString )
    return;
  
  strcpy( prjVerString, prjName );
  strcat( prjVerString, " - " );
  strcat( prjVerString, prjVer );
  
};

ClassVersion::~ClassVersion( void )
{
  if( classVerString ) delete classVerString;
  if( prjVerString ) delete prjVerString;
}

const char *
ClassVersion::getVer(
  bool		withPrjVer,
  const char *  baseVerString
  ) const
{
  static char * ver = 0;
  char * tmpVer = new char[ strlen( verString ) +
			    strlen( baseVerString ) + 20 ];

  if( withPrjVer )
    strcpy( tmpVer, verString );
  else
    strcpy( tmpVer, classVerString );
  
  strcat( tmpVer, "\n    " );
  strcat( tmpVer, baseVerString );

  if( ver ) delete ver;
  
  ver = tmpVer;

  return( ver );
}


 
					  


