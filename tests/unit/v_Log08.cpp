//
// File:        tLog08.C
// Project:	StlUtils
// Desc:        
//
//  Test the following Log methods
//  
//  
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
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
    const char * TestFn = TEST_DATA_DIR "/log.36";
    {
    
      Log	    t( TestFn, LogLevel::All, ios::out, 0644,
		       true, false, false  );

      t.tieCommonLogger();

      t( LogLevel::Error ) << "test Log Error" << '\n';
      LOGIT( LOG_ERROR, ( "test Common ERROR(%d)\n", LOG_ERROR ) );

      t( LogLevel::Warn ) << "test Log Warn" << '\n';
      LOGIT( LOG_WARN, ( "test Common WARN(%d)\n", LOG_WARN ) );

      t( LogLevel::App1 ) << "test Log App1" << '\n';
      LOGIT( LOG_APP1, ( "test Common APP1(%d)\n", LOG_APP1 ) );

      t( LogLevel::App2 ) << "test Log App2" << '\n';
      LOGIT( LOG_APP2, ( "test Common APP2(%d)\n", LOG_APP2 ) );

      t( LogLevel::App3 ) << "test Log App3" << '\n';
      LOGIT( LOG_APP3, ( "test Common APP3(%d)\n", LOG_APP3 ) );

      t( LogLevel::App4 ) << "test Log App4" << '\n';
      LOGIT( LOG_APP4, ( "test Common APP4(%d)\n", LOG_APP4 ) );

      t( LogLevel::App5 ) << "test Log App5" << '\n';
      LOGIT( LOG_APP5, ( "test Common APP5(%d)\n", LOG_APP5 ) );

      t( LogLevel::App6 ) << "test Log App6" << '\n';
      LOGIT( LOG_APP6, ( "test Common APP6(%d)\n", LOG_APP6 ) );

      t( LogLevel::Lib1 ) << "test Log Lib1" << '\n';
      LOGIT( LOG_LIB1, ( "test Common LIB1(%d)\n", LOG_LIB1 ) );

      t( LogLevel::Lib2 ) << "test Log Lib2" << '\n';
      LOGIT( LOG_LIB2, ( "test Common LIB2(%d)\n", LOG_LIB2 ) );

      t( LogLevel::Lib3 ) << "test Log Lib3" << '\n';
      LOGIT( LOG_LIB3, ( "test Common LIB3(%d)\n", LOG_LIB3 ) );

      t( LogLevel::Lib4 ) << "test Log Lib4" << '\n';
      LOGIT( LOG_LIB4, ( "test Common LIB4(%d)\n", LOG_LIB4 ) );

      t( LogLevel::Info ) << "test Log Info" << '\n';
      LOGIT( LOG_INFO, ( "test Common INFO(%d)\n", LOG_INFO ) );

      t( LogLevel::Test ) << "test Log Test" << '\n';
      LOGIT( LOG_TEST, ( "test Common TEST(%d)\n", LOG_TEST ) );

      t( LogLevel::Debug ) << "test Log Debug" << '\n';
      LOGIT( LOG_DEBUG, ( "test Common DEBUG(%d)\n", LOG_DEBUG ) );

      t( LogLevel::Funct ) << "test Log Funct" << '\n';
      LOGIT( LOG_FUNCT, ( "test Common FUNCT(%d)\n", LOG_FUNCT ) );
    }
    
    tester.file( __FILE__, __LINE__, TestFn );
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
    const char * TestFn = TEST_DATA_DIR "/log.37";
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

    TEST( strstr( t.getVersion(), "@(#) libStlUtils - " ) != 0 );
    TEST( strstr( t.getVersion(), T_CLASS_NAME ) != 0 );
    TEST( strstr( t.getVersion(), "Compiled: " ) != 0 );
    
    TEST( strstr( t.getVersion(true), "@(#) libStlUtils - " ) != 0 );
    TEST( strstr( t.getVersion(true), T_CLASS_NAME ) != 0 );
    TEST( strstr( t.getVersion(true), "Compiled: " ) != 0 );
    
    TEST( strstr( t.getVersion(false), "@(#) libStlUtils - " ) == 0 );
    TEST( strstr( t.getVersion(false), T_CLASS_NAME ) != 0 );
    TEST( strstr( t.getVersion(false), "Compiled: " ) != 0 );

  }
  
  {
    // dumpInfo( ostream & ) const
    const char * TestFn = TEST_DATA_DIR "/log.38";

    const Log  t( TestFn,
		  LogLevel::Debug | LogLevel::Warn | LogLevel::Test );
    
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    
    tester.getDump() << '\n' << tester.getCurrentTestName();    
  }
    
  {
    // static const ClassVersion version

    TEST( strstr( Log::version.getVer(true), "@(#) libStlUtils - " ) != 0 );
    TEST( strstr( Log::version.getVer(true), T_CLASS_NAME ) != 0 );
    TEST( strstr( Log::version.getVer(true), "Compiled: " ) != 0 );
    
    TEST( strstr( Log::version.getVer(true), "@(#) libStlUtils - " ) != 0 );
    TEST( strstr( Log::version.getVer(true), T_CLASS_NAME ) != 0 );
    TEST( strstr( Log::version.getVer(true), "Compiled: " ) != 0 );
    
    TEST( strstr( Log::version.getVer(false), "@(#) libStlUtils - " ) == 0 );
    TEST( strstr( Log::version.getVer(false), T_CLASS_NAME ) != 0 );
    TEST( strstr( Log::version.getVer(false), "Compiled: " ) != 0 );
    
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
// Revision 3.4  1997/09/17 11:09:53  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/04/26 14:12:55  houghton
// Renamed test file names.
// Added test for tieCommonLogger().
//
// Revision 3.2  1997/03/03 19:10:26  houghton
// Changed for port to AIX41.
//
// Revision 3.1  1996/11/14 01:26:50  houghton
// Changed to Release 3
//
// Revision 2.1  1996/11/13 17:21:24  houghton
// Initial Version.
//
//
