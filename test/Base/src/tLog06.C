
//
// File:        tLog05.C
// Project:	StlUtils
// Desc:        
//
//  Test the following Log methods
//
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     11/12/96 09:32
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include "TestConfig.hh"
#include "LibTest.hh"
#include "Log.hh"
#include "FileStat.hh"
#include <cstdio>
#include <strstream.h>

bool
tLog06( LibTest & tester )
{
  {
    // trim( void );
    // trim( size_t );

    const char *    TestFn = TEST_DATA_DIR "/log.20";

    const FileStat::size_type    MaxSize = 40960;
    const FileStat::size_type    TrimSize = 1024;
    
    const char *    EntryText =
      "good test checking trim( void ).\n";
    const FileStat::size_type    EntrySize =
      strlen( "mm/dd/yy hh:mm:ss INFO ") +
      strlen( EntryText );

    {
      Log t( TestFn,
	     LogLevel::Info,
	     ios::out );

      for( FileStat::size_type e = EntrySize;
	   e < (MaxSize - (EntrySize * 2));
	   e += EntrySize )
	t( LogLevel::Info ) << EntryText;

    }
    {
      // make sure we are between (MaxSize - TrimSize) and MaxSize
      FileStat t( TestFn );

      TEST( t.getSize() < MaxSize );
      TEST( t.getSize() > (MaxSize - TrimSize) );
    }
    {
      Log t( TestFn,
	     LogLevel::Info,
	     (ios::open_mode)(ios::app|ios::out),
	     0664,
	     true,
	     true,
	     true,
	     MaxSize,
	     TrimSize );

      size_t trimmed = t.trim();

      TEST( trimmed > 0 );
      TEST( trimmed < TrimSize );
    }

    {
      FileStat t( TestFn );

      TEST( t.getSize() < MaxSize );
      TEST( t.getSize() > (MaxSize - (TrimSize + EntrySize)) );
    }

    {
      Log t( TestFn,
	     LogLevel::Info,
	     (ios::open_mode)(ios::app|ios::out),
	     0664,
	     true,
	     true,
	     true,
	     MaxSize );

      size_t trimmed = t.trim( 10240 );

      TEST( trimmed < MaxSize );
      TEST( trimmed > 0 );
    }

    {
      FileStat t( TestFn );

      TEST( t.getSize() < 10240 );
      TEST( t.getSize() > (10240 - ((10240/4) + EntrySize)) );
    }
  }      
      
  {
    // open( const char * )
    
    const char *    TestFn = TEST_DATA_DIR "/log.21";
    remove( TestFn );
    {
      
      strstream tStream;
    
      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.open( TestFn );

      t() << "error good\n";
      t( LogLevel::Info ) << "info good\n";

    }

    {
      strstream tStream;
    
      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.open( TestFn );

      t() << "error good\n";
      t( LogLevel::Info ) << "info good\n";
    }
      
    tester.file( __FILE__, __LINE__, TestFn );
  }

  {
    // open( const char *, ios::open_mode )

    const char * TestFn = TEST_DATA_DIR "/log.22";

    {
      // put some stuff in the file first
      ofstream t( TestFn );

      t << "Junk text BAD." << endl;
    }
    
    {
      
      strstream tStream;
    
      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.open( TestFn, ios::out );

      t() << "error Good\n";
      t( "info" ) << "Info good" << endl;
    }

    {
      strstream tStream;
    
      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.open( TestFn, (ios::open_mode)(ios::app|ios::out) );

      t() << "error Good\n";
      t( "info" ) << "Info good" << endl;
    }

    tester.file( __FILE__, __LINE__, TestFn );
  }
  
  {
    // setFileName( const char * )
    
    const char *    TestFn = TEST_DATA_DIR "/log.23";
    remove( TestFn );
    {
      
      strstream tStream;
    
      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.setFileName( TestFn );

      t() << "error good\n";
      t( LogLevel::Info ) << "info good\n";

    }

    {
      strstream tStream;
    
      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.setFileName( TestFn );

      t() << "error good\n";
      t( LogLevel::Info ) << "info good\n";
    }
      
    tester.file( __FILE__, __LINE__, TestFn );
  }

  {
    // setFileName( const char *, ios::open_mode )

    const char * TestFn = TEST_DATA_DIR "/log.24";

    {
      // put some stuff in the file first
      ofstream t( TestFn );

      t << "Junk text BAD." << endl;
    }
    
    {
      
      strstream tStream;
    
      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.setFileName( TestFn, ios::out );

      t() << "error Good\n";
      t( "info" ) << "Info good" << endl;
    }

    {
      strstream tStream;
    
      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.setFileName( TestFn, (ios::open_mode)(ios::app|ios::out) );

      t() << "error Good\n";
      t( "info" ) << "Info good" << endl;
    }

    tester.file( __FILE__, __LINE__, TestFn );
  }

  {
    // close( void )
    
    const char * TestFn = TEST_DATA_DIR "/log.25";
    const char * TestOpenFn = TEST_DATA_DIR "/log.26";

    {
      Log t( TestFn, LogLevel::Error | LogLevel::Debug,
	     ios::out, 0664,
	     true, false );

      t() << "error good\n";
      t( "DEBUG" ) << "debug good" << endl;

      {
	t.close();

	t() << "BAD" << endl;

	TEST( ! t.good() );
    
	for( size_t l = 0; l < 50; l++ )
	  t() << "BAD " << l << "\n";
      
	tester.file( __FILE__, __LINE__, TestFn );
      }

      {
	t.open( TestOpenFn, ios::out );

	TESTR( t.error(), t.good() );

	t() << "error good\n";
	t( "DEBUG" ) << "debug good" << endl;

	TEST( t.good() );
      }

    }

    tester.file( __FILE__, __LINE__, TestOpenFn );
  }

  return( true );
}

//
// $Log$
// Revision 4.2  1998/04/02 14:19:25  houghton
// Cleanup and eliminate warnings.
//
// Revision 4.1  1997/09/17 15:14:25  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:09:52  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/07/18 21:46:09  houghton
// Port(Sun5): Changed ios::app to (ios::open_mode)(ios::app|ios::out).
//
// Revision 3.2  1996/11/19 12:35:39  houghton
// Changed include strstream to include strstream.h because strstream
//     is not part of the standard.
//
// Revision 3.1  1996/11/14 01:26:48  houghton
// Changed to Release 3
//
// Revision 2.1  1996/11/13 17:21:23  houghton
// Initial Version.
//
//

