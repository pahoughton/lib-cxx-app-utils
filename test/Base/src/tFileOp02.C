//
// File:        tFileOp02.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tFileOp02
//  
// Author:      Paul Houghton 719-527-7834 - (paul.houghton@wcom.com)
// Created:     03/08/98 11:24
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
tFileOp02( LibTest & tester )
{
  static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
  
  {
    static const char * TestFn = TEST_DATA_DIR "/FileOp.02.01";

    FileOp    t( ExpFn );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.copy( TestFn ) );
       
    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );
  }

  {
    static const char * SrcFn  = TEST_DATA_DIR "/FileOp.02.01";
    static const char * TestFn = TEST_DATA_DIR "/FileOp.02.01.01";

    FileOp t( SrcFn );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.move( TestFn ) );

    FileStat destStat( TestFn );

    TEST( destStat.good() && destStat.isReg() );
    
    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );

    FileStat srcStat( SrcFn );
    
    TESTR( "should not exist", ! srcStat.good() );
  }

  {
    static const char * SrcFn = TEST_DATA_DIR "/FileOp.02.01.01";
    static const char * TestFn = "/tmp/FileOp.02.01.01";
    static const char * TestDir = "/tmp";
      
    FileOp t( SrcFn );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.move( TestDir ) );

    FileStat destStat( TestFn );

    TEST( destStat.good() && destStat.isReg() );
    
    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );

    FileStat srcStat( SrcFn );
    
    TESTR( "should not exist", ! srcStat.good() );
  }

  {
    static const char * SrcFn = "/tmp/FileOp.02.01.01";
    static const char * TestFn = TEST_DATA_DIR "/FileOp.02.01.01";
      
    FileOp t( SrcFn );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.move( TestFn ) );

    FileStat destStat( TestFn );

    TEST( destStat.good() && destStat.isReg() );
    
    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );

    FileStat srcStat( SrcFn );
    
    TESTR( "should not exist", ! srcStat.good() );
  }

  return( true );
}
    


// Revision Log:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:28  houghton
// Changed Version Num to 5
//
// Revision 1.2  1998/11/02 19:36:39  houghton
// Changed: the File class was renamed to FileOp.
//
// Revision 1.1  1998/03/21 13:57:29  houghton
// Initial Version.
//
//
