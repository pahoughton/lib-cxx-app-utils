//
// File:        tLog08.C
// Project:	Clue
// Desc:        
//
//  Test the following Log methods
//  
//  
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     11/13/96 06:47
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include "TestConfig.hh"
#include "LibTest.hh"
#include "Log.hh"
#include "Compare.hh"
#include <cstdio>

#define T_CLASS_NAME	"Log"

bool
tLog08( LibTest & tester )
{
  {
    // rdbuf( void )

    Log	t;

    
    TESTR( t.rdbuf()->getClassName(),
	   compare( t.rdbuf()->getClassName(), "LogBuf" ) == 0 );
  }

  {
    // rdbuf( void ) const
    
    const Log t;

    TEST( compare( t.rdbuf()->getClassName(), "LogBuf" ) == 0 );
  }

  {
    // lock( void );
    // unlock( void );

    // just making sure the calls link ok, cant really test it.
    Log t;

    t.lock();
    t.unlock();
  }

  {
    // good( void ) const;
    // error( void ) const;
    const char * TestFn = TEST_DATA_DIR "/log.36";
    const char * TestBadFn = "BAD_DIR_NAME/BAD_FILENAME";

    {
      Log t( TestFn );

      TEST( t.good() );
    }
    {
      const Log t( TestBadFn );

      TEST( ! t.good() );
      TESTR( t.error(), strstr( t.error(), "BAD" ) != 0 );
    }
  }

  {
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    
    const Log t;

    TEST( ! strcmp( t.getClassName(), T_CLASS_NAME ) );

    TEST( strstr( t.getVersion(), "@(#) libClue - " ));
    TEST( strstr( t.getVersion(), T_CLASS_NAME ) );
    TEST( strstr( t.getVersion(), "Compiled: " ) );
    
    TEST( strstr( t.getVersion(true), "@(#) libClue - " ));
    TEST( strstr( t.getVersion(true), T_CLASS_NAME ) );
    TEST( strstr( t.getVersion(true), "Compiled: " ) );
    
    TEST( ! strstr( t.getVersion(false), "@(#) libClue - " ) );
    TEST( strstr( t.getVersion(false), T_CLASS_NAME ) );
    TEST( strstr( t.getVersion(false), "Compiled: " ) );

  }
  
  {
    // dumpInfo( ostream & ) const
    const char * TestFn = TEST_DATA_DIR "/log.37";

    const Log  t( TestFn,
		  LogLevel::Debug | LogLevel::Warn | LogLevel::Test );
    
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    
    tester.getDump() << '\n' << tester.getCurrentTestName();    
  }
    
  {
    // static const ClassVersion version

    TEST( strstr( Log::version.getVer(true), "@(#) libClue - " ));
    TEST( strstr( Log::version.getVer(true), T_CLASS_NAME ) );
    TEST( strstr( Log::version.getVer(true), "Compiled: " ) );
    
    TEST( strstr( Log::version.getVer(true), "@(#) libClue - " ));
    TEST( strstr( Log::version.getVer(true), T_CLASS_NAME ) );
    TEST( strstr( Log::version.getVer(true), "Compiled: " ) );
    
    TEST( ! strstr( Log::version.getVer(false), "@(#) libClue - " ) );
    TEST( strstr( Log::version.getVer(false), T_CLASS_NAME ) );
    TEST( strstr( Log::version.getVer(false), "Compiled: " ) );
    
  }

  return( true );
}

//
// $Log$
// Revision 2.1  1996/11/13 17:21:24  houghton
// Initial Version.
//
//
