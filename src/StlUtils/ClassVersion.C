//
// File:        ClassVersion.C
// Desc:        
//
//  Define non-inline ClassVersion methods.
//
//  See ClassVersion.hh for method declaration and documentation
//  See ClassVersion.ii for inline methods
//
// Notes:
//
//  Methods are defined in order of declaration
//
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     10/04/95 07:41
//
// Revision History: (See end of file for Revision Log)
//

#include "ClassVersion.hh"
#include <cstring>


STLUTILS_VERSION( ClassVersion,
	      "$Id$" );
	 

ClassVersion::ClassVersion(
  const char * className,
  const char * fullVersionString,
  const char * fileName,		    // __FILE__
  const char * compileDateString,	    // __DATE__
  const char * compileTimeString,	    // __TIME__
  const char * versionString,		    // Id:
  const char * prjName,
  const char * prjVer,
  unsigned long prjVerNumber,
  const char * prjVerTag
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
  strcat( classVerString, " - Compiled: " );
  strcat( classVerString, compileDateString );
  strcat( classVerString, " " );
  strcat( classVerString, compileTimeString );
  strcat( classVerString, "\n    " );
  strcat( classVerString, versionString );

  bufSize = strlen( prjName ) + strlen( prjVer ) + 10 + strlen( prjVerTag );
  
  prjVerString = new char[ bufSize ];

  if( ! prjVerString )
    return;
  
  strcpy( prjVerString, prjName );
  strcat( prjVerString, " - " );
  strcat( prjVerString, prjVer );
  strcat( prjVerString, " - " );
  strcat( prjVerString, prjVerTag );
  
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

  const char * verToUse = ( withPrjVer ? verString : classVerString );
  
  char * tmpVer = new char[ strlen( verToUse ) + 
			    strlen( baseVerString ) + 20 ];

  strcpy( tmpVer, verToUse );
  
  strcat( tmpVer, "\n    " );
  strcat( tmpVer, baseVerString );

  if( ver ) delete ver;
  
  ver = tmpVer;

  return( ver );
}


// $Log$
// Revision 4.1  1997/09/17 15:12:11  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:08:10  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/04/26 14:40:47  houghton
// Added project tag support.
//
// Revision 3.2  1996/11/19 12:20:18  houghton
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
//
// Revision 3.1  1996/11/14 01:23:27  houghton
// Changed to Release 3
//
// Revision 2.5  1996/11/11 13:32:17  houghton
// Bug-Fix: getVer( bool, const char * ) const - was not
//     allocating the correct size for the string.
//
// Revision 2.4  1996/10/28 11:56:50  houghton
// Cleanup.
//
// Revision 2.3  1996/04/27 12:52:21  houghton
// Removed unneeded includes.
//
// Revision 2.2  1995/12/04 11:16:52  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:18  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  14:48:48  houghton
// New Class Version id method
//
//
 
					  


