//
// File:        main.C
// Project:	Clue
// Desc:        
//
//  Application entry point.
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/13/97 12:23
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include "ClueConfig.hh"
#include "AppParam.hh"
#include <Semaphore.hh>
#include <FileStat.hh>
#include <FileLock.hh>

#include <iostream>

AppParam * App = 0;

CLUE_FUNCT_VERSION(
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
      AppError << lockstat.error() << endl;
      return( 1 );
    }

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

  if( ! sem.islocked() )
    {
      if( ! lock.lockread() )
	{
	  AppError << lock.error() << endl;
	  return( 1 );
	}
    }
  
  for( ;; )
    {
      AppDebug << "Sleeping for '" << App->sleepTime() << "' seconds." << endl;
      
      sleep( App->sleepTime() );
      
      if( sem.islocked() )
	{
	  AppDebug << "sem LOCKED." << endl;

	  if( ! lock.unlock() )
	    {
	      AppError << lock.error() << endl;
	      return( 1 );
	    }
	  else
	    {
	      AppDebug << "read UNLOCKED." << endl;
	    }
	  
	  if( ! sem.waitfor() )
	    {
	      AppError << sem.error() << endl;
	    }

	  if( ! lock.lockread() )
	    {
	      AppError << lock.error() << endl;
	      return( 1 );
	    }
	  else
	    {
	      AppDebug << "read LOCKED." << endl;
	    }
	  
	  if( sem.islocked() )
	    {
	      AppError << "still LOCKED!!!" << endl;
	      return( 1 );
	    }
	  
	  AppDebug << "sem UNLOCKED." << endl;
	}
    }
  
  return( 0 );
}
//
// Revision Log:
//
// $Log$
// Revision 1.1  1997/09/16 11:31:27  houghton
// Initial Version.
//
//

