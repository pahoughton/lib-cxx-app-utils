//
// File:        main.C
// Project:	StlUtils
// Desc:        
//
//  Application entry point.
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/12/97 16:18
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
#include <FileStat.hh>
#include <Semaphore.hh>
#include <FileLock.hh>

#include <iostream>
#include <fstream>

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

  FileStat  lockstat( App->lockFn() );
    
  if( ! lockstat.good() )
    {
      if( ! lockstat.exist() )
	{
	  // does not exisit, do we want to create it?
	  if( App->createLockFile() )
	    {
	      {
		ofstream f( App->lockFn(), ios::out );
		
		if( ! f.good() )
		  {
		    AppError << "creating '"
			     << App->lockFn() << "' - "
			     << strerror( errno )
			     << endl;
		    return( 1 );
		  }
	      }
	      // it's now closed again.
	      lockstat( App->lockFn() );

	      if( ! lockstat.good() )
		{
		  AppError << "create attempt failed for '"
			   << App->lockFn()
			   << "' - " << lockstat.error()
			   << endl;
		  return( 1 );
		}
	    }
	  else
	    {
	      AppError << "'" << App->lockFn() << "' does not exisit."
		       << endl;
	      return( 1 );
	    }
	}
      else
	{
	  AppError << lockstat.error() << endl;
	  return( 1 );
	}
    }

  // ok, we have a valid lock file;

  Semaphore sem( App->lockFn() );

  if( ! sem.good() )
    {
      AppError << sem.error() << endl;
      return( 1 );
    }

  FileLock  lock( App->lockFn(), (ios::open_mode)(ios::in | ios::out) );

  if( ! lock.good() )
    {
      AppError << lock.error() << endl;
      return( 1 );
    }
  
  for( long i = 0; i < App->swapCount(); ++ i )
    {
      sleep( App->sleepTime() );

      // we want to do a swap
      if( ! sem.lock() )
	{
	  AppError << sem.error() << endl;
	  return( 1 );
	}
      else
	{
	  AppDebug << "sem LOCKED." << endl;
	}

      if( ! lock.lockwrite() )
	{
	  AppError << lock.error() << endl;
	  return( 1 );
	}
      else
	{
	  AppDebug << "write LOCKED" << endl;
	}

      AppDebug << "it's mine, can hot swap." << endl;
      
      sleep( App->sleepTime() );

      if( ! sem.unlock() )
	{
	  AppError << sem.error() << endl;
	  return( 1 );
	}
      else
	{
	  AppDebug << "sem UNLOCK" << endl;
	}

      if( ! lock.unlock() )
	{
	  AppError << lock.error() << endl;
	  return( 1 );
	}
      else
	{
	  AppDebug << "write UNLOCK." << endl;
	}
    }
      
	      
			
	      
  return( 0 );
}
//
// Revision Log:
//
// $Log$
// Revision 6.1  2003/08/09 11:22:53  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:32  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:57  houghton
// Changed to Version 4
//
// Revision 1.2  1997/09/17 11:10:18  houghton
// Changed: renamed library to StlUtils.
//
// Revision 1.1  1997/09/16 11:31:14  houghton
// Initial Version.
//
//

