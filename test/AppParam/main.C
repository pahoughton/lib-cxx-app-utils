//
// File:        main.C
// Project:	StlUtils
// Desc:        
//
//  Application entry point.
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     03/21/97 07:04
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include "AppParam.hh"

AppParam * App = 0;

STLUTILS_FUNCT_VERSION(
  main,
  "$Id$");

int
main( int argc, char * argv[] )
{

  if( (App = new AppParam( argc, argv, VERID_main ) ) == 0 )
    {
      cerr << "Can't new AppParam." << endl;
      exit( 1 );
    }

  if( ! App->good() || App->help() || ! App->allArgs() )
    {
      AppDebug << App->dump() << endl;
      App->abort( 1, true, __FILE__, __LINE__ );
    }

  AppDebug << App->dump() << endl;
  
  cout << "One:   " << App->tOne() << endl;
  cout << "Two:   " << App->tTwo() << endl;
  cout << "Three: " << App->tThree() << endl;

  return( 0 );
}
//
// Revision Log:
//
// $Log$
// Revision 6.1  2003/08/09 11:22:48  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:24  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:44  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:31  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/03/21 15:58:14  houghton
// Changed base version to 3
//
// Revision 1.1  1997/03/21 15:57:48  houghton
// Initial Version.
//
// Revision 1.2  1997/03/21 15:47:51  houghton
// Initial Version
//
//

