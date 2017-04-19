//
// File:        main.C
// Project:	StlUtils
// Desc:        
//
//  Application entry point.
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     10/02/98 07:50
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include "StlUtilsConfig.hh"
// #include "AppParam.hh"

// #include <Directory.hh>
#include <DateTime.hh>

#include <iostream>
#include <cstdlib>

// AppParam * App = 0;

STLUTILS_FUNCT_VERSION(
  main,
  "$Id$");

#if defined( DIRTEST )
int
test( void )
{
  Directory dir( "../data/t*" );

  for( Directory::iterator them = dir.begin();
       them != dir.end();
       ++ them )
    {
      cout << "found: " << (*them) << endl;
    }

  return( 1 );
}
#endif
      
int
test( void )
{
  const char * envTz;
  putenv( "TZ=CST6CDT" );

  {
    DateTime dt;
    if( strcmp( dt.getTimeZone(), "CST6CDT" ) )
      cerr << "FAIL." << endl;
    else
      cerr << "ok" << endl;
  }

  cerr << "tz: " << getenv( "TZ" ) << endl;
  {
    DateTime dt( "02/29/92 05:45:50" );
  }

  cerr << "tz: " << getenv( "TZ" ) << endl;
  {
    DateTime dt;
    if( strcmp( dt.getTimeZone(), "CST6CDT" ) )
      cerr << "FAIL." << endl;
    else
      cerr << "ok" << endl;
  }

  cerr << "tz: " << getenv( "TZ" ) << endl;

  return( 1 );
}
  
int
main( int argc, char * argv[] )
{
#if defined( FIXME )
  if( (App = new AppParam( argc, argv, VERID_main ) ) == 0 )
    {
      cerr << "Can't new AppParam." << endl;
      exit( 1 );
    }

  if( ! App->good() || App->help() || ! App->allArgs() )
    App->abort( 1, true, __FILE__, __LINE__ );
#endif


  char	envTz[100];

  strcpy( envTz, "TZ=CST6CDT" );

  putenv( envTz );
  cerr << getenv( "TZ" ) << endl;

  strcpy( envTz, "TZ=xxxxxxxx" );

  cerr << getenv( "TZ" ) << endl;

  exit ( 1 );
  // for( ;; )
    {
      test();
    }

  return( 0 );
}
//
// Revision Log:
//
// $Log$
// Revision 6.2  2011/12/30 23:57:51  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:54  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:33  houghton
// Changed Version Num to 5
//
// Revision 1.2  1998/10/23 13:10:21  houghton
// *** empty log message ***
//
// Revision 1.1  1998/10/13 15:22:53  houghton
// Initial version.
//
//

