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
#include <cstdio>

bool
tFileOp01( LibTest & tester )
{
  {
    static const char * TestFn = TEST_DATA_DIR "/FileOp.01.01";

    FileOp    t( TEST_DATA_DIR "/FileOp.01.01.exp" );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.copy( TestFn ) );
       
    if( ! tester.file( __FILE__, __LINE__, TestFn ) )
      return( false );
  }

  {
    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = "/tmp/FileOp.01.01";
    
    FileOp    t( ExpFn  );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.copy( TestFn ) );

    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );

    remove( TestFn );
  }

  {
    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = "/tmp/FileOp.01.01.exp";
    
    FileOp    t( ExpFn  );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.copy( "/tmp" ) );

    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );

    remove( TestFn );
  }

  {
    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_DATA_DIR "/FileOp.01.01";
    
    FileOp t;

    TESTR( t.error(), t.copy( ExpFn, TestFn ) );

    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );
  }

  {
    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = "/FileOp.01.01";
    
    FileOp t( ExpFn );

    TESTR( t.error(), t.good() );

    TEST( ! t.copy( TestFn ) );
  }

  return( true );
}


// Revision Log:
//
// $Log$
// Revision 1.2  1998/11/02 19:36:34  houghton
// Changed: the File class was renamed to FileOp.
//
// Revision 1.1  1998/03/21 13:57:29  houghton
// Initial Version.
//
//
