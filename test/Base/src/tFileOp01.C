//
// File:        tFileOp01.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tFile01
//  
// Author:      Paul Houghton 719-527-7834 - (paul.houghton@wcom.com)
// Created:     03/08/98 09:03
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <TestConfig.hh>
#include <LibTest.hh>
#include <FileOp.hh>

#include <iomanip>

#include <cstdio>

#if !defined( TEST_TEMP_DIR )
#define TEST_TEMP_DIR	"/tmp"
#endif

bool
tFileOp01( LibTest & tester )
{
  {
    // FileOp( const char * )
    
    static const char * TestFn = TEST_DATA_DIR "/FileOp.01.01.exp";

    FileOp  t( TestFn );

    TESTR( t.error(), t.good() );
  }
  
  {
    // copy( const char * dest )
    //	same dir different name
    static const char * TestFn = TEST_DATA_DIR "/FileOp.01.01";

    FileOp    t( TEST_DATA_DIR "/FileOp.01.01.exp" );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.copy( TestFn ) );
       
    if( ! tester.file( __FILE__, __LINE__, TestFn ) )
      return( false );
  }

  {
    // copy( const char * dest )
    //	different filesystem

    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_TEMP_DIR "/FileOp.01.01";

    FileStat	srcDir( TEST_DATA_DIR );
    FileStat	destDir( TEST_TEMP_DIR );

    TESTR( srcDir.error(), srcDir.good() );
    TESTR( destDir.error(), destDir.good() );

#if !defined( Linux )
    TESTR( "same device", srcDir.getDevice() != destDir.getDevice() );
#endif
    
    FileOp    t( ExpFn  );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.copy( TestFn ) );

    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );

    remove( TestFn );
    
  }

  {
    // copy( const char * dest )
    //	copy to directory
    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_TEMP_DIR "/FileOp.01.01.exp";
    
    FileOp    t( ExpFn  );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.copy( TEST_TEMP_DIR ) );

    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );

    remove( TestFn );
  }

  {
    // copy( const char * src, const char * dest )
    
    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_DATA_DIR "/FileOp.01.01";
    
    FileOp t;

    TESTR( t.error(), t.copy( ExpFn, TestFn ) );

    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );
    
    remove( TestFn );
  }

  {
    // copy()
    //	write only dest dir
#define TEST_RONLY_DIR	TEST_DATA_DIR "/FileOpDir"

    FileStat	destDir( TEST_RONLY_DIR );

    if( destDir.good() )
      {
	TESTR( TEST_RONLY_DIR " permissions wrong",
	       destDir.getMode() == 042555 );
      }
    else
      {
	TESTR( "making dir " TEST_RONLY_DIR,
	       mkdir( TEST_RONLY_DIR, 0555 ) == 0 );
      }
    
    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_RONLY_DIR; 
    
    FileOp t( ExpFn );

    TESTR( t.error(), t.good() );

    TEST( ! t.copy( TestFn ) );
  }

  {
    // copy()
    //	write only dest dir
    
    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_RONLY_DIR "/FileOp.01.01"; 
    
    FileOp t( ExpFn );

    TESTR( t.error(), t.good() );

    TEST( ! t.copy( TestFn ) );
  }

  {
    // copy( const char * dest, overwrite )

    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    
    static const char * Test01Fn = TEST_DATA_DIR "/FileOp.01.01";

    static const char * Test02Dir = TEST_TEMP_DIR;
    static const char * Test02Fn = TEST_TEMP_DIR "/FileOp.01.01";
    
    FileOp t( ExpFn );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.copy( Test01Fn, true ) );

    TESTR( t.error(), t.copy( Test01Fn, true ) );

    TEST( ! t.copy( Test01Fn, false ) );
    
    TESTR( t.error(), t.copy( Test01Fn, Test02Fn, true ) );
    TEST( ! t.copy( Test02Dir, false ) );
          
  }
  
  return( true );
}


// Revision Log:
//
// $Log$
// Revision 1.3  1999/03/02 12:54:44  houghton
// Expanded tests.
//
// Revision 1.2  1998/11/02 19:36:34  houghton
// Changed: the File class was renamed to FileOp.
//
// Revision 1.1  1998/03/21 13:57:29  houghton
// Initial Version.
//
//
