//
// File:        tFile02.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tFile02
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
#include <File.hh>
#include <cstdio>

bool
tFile02( LibTest & tester )
{
  static const char * ExpFn = TEST_DATA_DIR "/File.01.01.exp";
  
  {
    static const char * TestFn = TEST_DATA_DIR "/File.02.01";

    File    t( ExpFn );

    TESTR( t.error(), t.good() );

    TESTR( t.error(), t.copy( TestFn ) );
       
    if( ! tester.file( __FILE__, __LINE__, TestFn, ExpFn ) )
      return( false );
  }

  {
    static const char * SrcFn  = TEST_DATA_DIR "/File.02.01";
    static const char * TestFn = TEST_DATA_DIR "/File.02.01.01";

    File t( SrcFn );

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
    static const char * SrcFn = TEST_DATA_DIR "/File.02.01.01";
    static const char * TestFn = "/tmp/File.02.01.01";
    static const char * TestDir = "/tmp";
      
    File t( SrcFn );

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
    static const char * SrcFn = "/tmp/File.02.01.01";
    static const char * TestFn = TEST_DATA_DIR "/File.02.01.01";
      
    File t( SrcFn );

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
// Revision 1.1  1998/03/21 13:57:29  houghton
// Initial Version.
//
//
