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
tLog05( LibTest & tester )
{
  {
    // tee( ostream & )

    const char *    TestFn = TEST_DATA_DIR "/log.17";
    const char *    TestTeeFn = TEST_DATA_DIR "/log.18";
    
    {
      ofstream teeDest( TestTeeFn );
      
      Log   t( TestFn, LogLevel::Err | LogLevel::Debug,
	       ios::out, 0664,
	       true, false, true );
      
      t( LogLevel::Error, "Test", 1 ) << "Log error output.\n";
      t( LogLevel::Error, "Test", 2 ) << "Log error output.\n";
      t( LogLevel::Error, "Test", 3 ) << "Log error output.\n";

      t.tee( teeDest );
      t( LogLevel::Debug, "Test", 4 ) << "Log debug output.\n";
      t( LogLevel::Debug, "Test", 5 ) << "Log debug output.\n";
      t( LogLevel::Debug, "Test", 6 ) << "Log debug output.\n";
      t( LogLevel::Debug, "Test", 7 ) << "Log debug output.\n";
      
    }

    if( ! tester.file( __FILE__, __LINE__, TestFn ) )
      return( false );
    
    if( ! tester.file( __FILE__, __LINE__, TestTeeFn ) )
      return( false );
  }

  {
    // setMaxSize( void )
    // setTrimSize( void )
    
    const char *    TestFn = TEST_DATA_DIR "/log.19";

    const size_t    MaxSize = 40960;
    const size_t    TrimSize = 1024;
    
    const char *    EntryText =
      "good test checking maxSize.\n";
    const size_t    EntrySize =
      strlen( "mm/dd/yy hh:mm:ss INFO Test.C:n") +
      strlen( EntryText );

    size_t	    EntryNumber = 0;
    {
      
      Log t( TestFn, LogLevel::Info, ios::out );

      for( int l = EntrySize; l < (MaxSize * 2); l += EntrySize )
	t( LogLevel::Info, "Test.C", ++EntryNumber ) << EntryText;

    }

    {
      FileStat t( TestFn );

      TEST( t.good() );
      TEST( t.getSize() > MaxSize );
    }

    {
      Log t( TestFn, LogLevel::Info, (ios::open_mode)(ios::app|ios::out) );

      for( int l = 0; l < 50; ++l )
	t( LogLevel::Info, "Test.C", ++EntryNumber ) << EntryText;

      TEST( t.setMaxSize( MaxSize ) == 0 );

    }

    {
      FileStat t( TestFn );

      TEST( t.getSize() > ((MaxSize / 4 ) * 3) - EntrySize );
      TEST( t.getSize() < MaxSize );
    }

    {
       Log t( TestFn, LogLevel::Info, (ios::open_mode)(ios::app|ios::out) );

      TEST( t.setMaxSize( MaxSize ) == 0 );
     
      for( int l = EntrySize; l < (MaxSize * 3); l += EntrySize )
	t( LogLevel::Info, "Test.C", ++EntryNumber ) << EntryText;

      TEST( t.setMaxSize( 0 ) == MaxSize );
      
      for( int e = EntrySize; e < (MaxSize * 2); e += EntrySize )
	t( LogLevel::Info, "Test.C", ++EntryNumber ) << EntryText;

    }
    
    {
      FileStat t( TestFn );

      TEST( t.good() );
      TEST( t.getSize() > MaxSize );
    }

    {
      
      Log t( TestFn, LogLevel::Info, (ios::open_mode)(ios::app|ios::out) );

      TEST( t.setMaxSize( MaxSize ) == 0 );
      TEST( t.setTrimSize( TrimSize ) == 0 );

      for( int l = EntrySize; l < (MaxSize * 3); l += EntrySize )
	t( LogLevel::Info, "Test.C", ++EntryNumber ) << EntryText;
    }

    {
      FileStat t( TestFn );

      TEST( t.good() );
      TEST( t.getSize() < MaxSize );
      TEST( t.getSize() > (MaxSize - (TrimSize + EntrySize) ) );
    }
  }

  return( true );
}
      
//
// $Log$
// Revision 3.4  1997/09/17 11:09:51  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/07/18 21:44:53  houghton
// Port(Sun5): Changed ios::app to (ios::open_mode)(ios::app|ios::out).
//
// Revision 3.2  1996/11/19 12:35:29  houghton
// Changed include strstream to include strstream.h because strstream
//     is not part of the standard.
//
// Revision 3.1  1996/11/14 01:26:47  houghton
// Changed to Release 3
//
// Revision 2.6  1996/11/13 17:20:02  houghton
// Complete rework of all tests.
// Verified test against Log.hh header comments.
//
//












