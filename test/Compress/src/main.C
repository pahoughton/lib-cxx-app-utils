//
// File:        main.C
// Project:	StlUtils
// Desc:        
//
//  Application entry point.
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     10/07/99 06:36
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

#include <Compress.hh>

#include <iostream>

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
    App->abort( 1, true, __FILE__, __LINE__ );

  Compress  comp;

  if( ! (*App).in().size() )
    {
      AppError << "no input file." << endl;
      return( 1 );
    }

  if( (*App).decomp() )
    {
      if( (*App).out().size() )
	{
	  if( ! comp.decompress( (*App).in(), (*App).out() ) )
	    {
	      AppError << comp.error() << endl;
	      return( 1 );
	    }
	  else
	    {
	      AppInfo << "decompressed '" << (*App).in()
		      << "' to '" << (*App).out() << "'." << endl;
	      return( 0 );
	    }
	}
      else
	{
	  FilePath  fn( (*App).in() );
	  if( ! comp.decompress( fn ) )
	    {
	      AppError << comp.error() << endl;
	      return( 1 );
	    }
	  else
	    {
	      AppInfo << "decompressed '" << (*App).in()
		      << "' to '" << (*App).out() << "'." << endl;
	      return( 0 );
	    }
	}
    }
  else
    {
      if( (*App).out().size() )
	{
	  if( ! comp.compress( (*App).in(), (*App).out() ) )
	    {
	      AppError << comp.error() << endl;
	      return( 1 );
	    }
	  else
	    {
	      AppInfo << "compressed '" << (*App).in()
		      << "' to '" << (*App).out() << "'." << endl;
	      return( 0 );
	    }
	}
      else
	{
	  FilePath  fn( (*App).in() );
	  if( ! comp.compress( fn ) )
	    {
	      AppError << comp.error() << endl;
	      return( 1 );
	    }
	  else
	    {
	      AppInfo << "compressed '" << (*App).in()
		      << "' to '" << fn << "'." << endl;
	      return( 0 );
	    }
	}
    }
	  
  return( 0 );
}
//
// Revision Log:
//
// $Log$
// Revision 1.1  1999/10/07 13:11:38  houghton
// Initial Version.
//
//

