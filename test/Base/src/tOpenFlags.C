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

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StlUtilsMisc.hh>
#include <fcntl.h>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StlUtils.hh>
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
// Revision 4.1  1997/09/17 15:14:28  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 15:11:08  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.2  1997/09/17 11:09:54  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:52  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 18:22:53  houghton
// Chaged include because StlUtils.hh renamed to StlUtilsUtils.hh.
//
// Revision 2.1  1996/11/04 14:50:18  houghton
// Initial Version.
//
//

