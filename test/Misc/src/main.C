//
// File:        main.C
// Project:	StlUtils
// Desc:        
//
//  Application entry point.
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
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

#include <Directory.hh>

#include <iostream>

// AppParam * App = 0;

STLUTILS_FUNCT_VERSION(
  main,
  "$Id$");

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


  for( ;; )
    {
      test();
    }

  return( 0 );
}
//
// Revision Log:
//
// $Log$
// Revision 1.1  1998/10/13 15:22:53  houghton
// Initial version.
//
//

