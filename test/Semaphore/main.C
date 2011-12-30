//
// File:        main.C
// Project:	StlUtils
// Desc:        
//
//  Application entry point.
//
// Author:      Paul A. Houghton - (paul4hough@gmail.com)
// Created:     06/10/97 06:25
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
#include <Semaphore.hh>
#include <iostream>
#include <cstdlib>


int
main( int argc, char * argv[] )
{

  Semaphore sem( argv[0] );

  if( ! sem.good() )
    {
      cerr << sem.error() << endl;
      exit( 1 );
    }

  for( ;; )
    {
      cout << "Comand (l,L,u,w,r,d)? ";
      
      char cmd;
      cin >> cmd;

      switch( cmd )
	{
	case 'l':
	  if( ! sem.lock( false ) )
	    cerr << sem.error() << endl;

	  break;

	case 'L':
	  if( ! sem.lock( true ) )
	    cerr << sem.error() << endl;
	  break;

	case 'u':
	  if( ! sem.unlock() )
	    cerr << sem.error() << endl;
	  break;

	case 'w':
	  if( ! sem.waitfor() )
	    cerr << sem.error() << endl;
	  break;

	case 'r':
	  if( ! sem.remove() )
	    cerr << sem.error() << endl;
	  break;
	  
	case 'd':
	  sem.dumpInfo( cout ) << endl;
	  break;
	  
	default:
	  cout << "WHAT?\n";
	  break;
	}
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
// Revision 4.1  1997/09/17 15:15:02  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:22  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/07/25 12:27:36  houghton
// Changed version number to 3.
//
// Revision 1.2  1997/07/20 18:53:01  houghton
// Added include cstdlib.
//
// Revision 1.1  1997/07/11 15:57:25  houghton
// Initial Version.
//
//

