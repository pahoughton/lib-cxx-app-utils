//
// File:        tLog09.C
// Project:	StlUtils
// Desc:        
//
//  Test for LogIf macro.
//
// Note: WARNING!!!
//
//  The expected output of this test is dependant on the
//  line true source line numbers in this file.
//
//  Any change in the positioning of a line will cause this
//  test to fail
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     11/13/96 07:59
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include "TestConfig.hh"
#include "LibTest.hh"
#include "Log.hh"

bool
tLog09( LibTest & tester )
{
  {
    // LogIf( Log, LogLevel::Level )

    const char * TestFn = TEST_DATA_DIR "/log.39";
    
    {
      Log  t( TestFn,
	      LogLevel::Err | LogLevel::Test,
	      ios::out,
	      0664,
	      true, false, true );

      LogIf( t, LogLevel::Error ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Err ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Warning ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Warn ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::App1 ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::App2 ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::App3 ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::App4 ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::App5 ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Lib1 ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Lib2 ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Lib3 ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Lib4 ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Info ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Test ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Debug ) << "LogIf test entry." << endl;
      LogIf( t, LogLevel::Funct ) << "LogIf test entry." << endl;

      LogIf( t, LogLevel::Err ) << "Chunk Test: ";
      
      {
	const char * Entry =
	  " This is a large multi-line entry into the log that\n"
	  "    sould force an overflow becuse there are no sync\n"
	  "    calls.\n\n";

	size_t count = 0;
	for( size_t len = strlen( Entry );
	     len < 4096;
	     len += strlen( Entry ) )
	  {
	    t << "    " << ++count << ')' << Entry;
	  }
      }

      LogIf( t, LogLevel::Debug ) << "BAD" << endl;
      LogIf( t, LogLevel::Test ) << "End of Chnunk good!" << endl;

      LogIf( t, LogLevel::Debug ) << "BAD Chunk Test: ";
      
      {
	const char * Entry =
	  " This is a large multi-line entry into the log that\n"
	  "    sould force an overflow becuse there are no sync\n"
	  "    calls.\n\n";

	size_t count = 0;
	for( size_t len = strlen( Entry );
	     len < 4096;
	     len += strlen( Entry ) )
	  {
	    t << "    " << ++count << ')' << Entry;
	  }
      }

      LogIf( t, LogLevel::Test ) << "End of Test" << endl;
    }

    {
      tester.file( __FILE__, __LINE__, TestFn );
    }
      
  }

  return( true );
}

//
// $Log$
// Revision 6.2  2011/12/30 23:57:45  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:51  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:29  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:26  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:09:53  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/04/26 14:13:00  houghton
// Renamed test file names.
//
// Revision 3.1  1996/11/14 01:26:50  houghton
// Changed to Release 3
//
// Revision 2.1  1996/11/13 17:21:25  houghton
// Initial Version.
//
//
