//
// File:        tOpenFlags.C
// Desc:        
//
//  Test for OpenFlags function.
//  
// Source Header Version: 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/31/96 06:44
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#include <fcntl.h>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#include <fcntl.h>
#endif

bool
tOpenFlags( LibTest & tester )
{
  // int OpenFlags( ios::open_mode openMode )

  TEST( OpenFlags( ios::in ) == O_RDONLY );
  TEST( OpenFlags( ios::out ) == O_WRONLY | O_CREAT );
  TEST( OpenFlags( ios::app ) == O_WRONLY | O_CREAT | O_APPEND );
  TEST( OpenFlags( (ios::open_mode)(ios::in | ios::out) ) == O_RDWR | O_CREAT);
  TEST( OpenFlags( (ios::open_mode)(ios::app|ios::nocreate) )
	== O_WRONLY | O_APPEND );
  TEST( OpenFlags( (ios::open_mode)(ios::out|ios::noreplace) )
	== O_WRONLY | O_EXCL );
  TEST( OpenFlags( (ios::open_mode)(ios::out|ios::trunc ) )
	== O_WRONLY | O_TRUNC );

  return( true );
}
		   
		   

//
// $Log$
// Revision 2.1  1996/11/04 14:50:18  houghton
// Initial Version.
//
//

