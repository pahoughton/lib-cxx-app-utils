//
// File:        main.C
// Project:	StlUtils
// Desc:        
//
//  Application entry point.
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     07/20/97 07:07
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
#include "AppParam.hh"
#include <InboundProcessor.hh>
#include <FileStat.hh>

#include <cstdio>

#include <iostream>

AppParam * App = 0;

STLUTILS_FUNCT_VERSION(
  main,
  "$Id$");

class FileProc
{
public:

  FileProc( void ) : counter( 0 ) {};
  
  bool	operator () ( const FilePath & fn );

private:

  int counter;
};

bool
FileProc::operator () ( const FilePath & fn )
{
  FileStat  fs( fn );
  
  AppInfo << App->appName()
	  << " processing: '" << fs.getName() << '\'' << endl;

  remove( fn );

  // sleep( (rand() % 5) + 1 );
  
  if( ++ counter < 100 )
    return( true );
  else
    return( false );
      
}

int
main( int argc, char * argv[] )
{

  if( (App = new AppParam( argc, argv, VERID_main ) ) == 0 )
    {
      cerr << "Can't new AppParam." << endl;
      exit( 1 );
    }

  if( ! App->good() || App->help() || ! App->allArgs() )
    App->abort( 1, true, __FILE__, __LINE__ );

  FileProc  fileProc;
  
  InboundProcessor< FileProc >	inProc( App->fnPattern(),
					App->inDir(),
					App->procDir(),
					App->waitSecs(),
					fileProc );

  inProc.run();
  
  if( ! inProc.good() )
    AppError << inProc.error() << endl;
  
  return( 0 );
}

//
// Revision Log:
//
// $Log$
// Revision 3.2  1997/09/17 11:10:21  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/07/25 12:27:33  houghton
// Changed version number to 3.
//
// Revision 1.1  1997/07/20 18:55:53  houghton
// Initial Version.
//
//

