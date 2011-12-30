//
// File:        LibTest.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for LibTest.
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     05/09/95 09:54 
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "LibTest.hh"
#include <Str.hh>

#include <vector>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <cctype>

STLUTILS_VERSION( LibTest,
	      "$Id$ " );

LibTest::DefaultResults LibTest::defaultResultsObj;


// this should prevent accidental use of cout & cerr

#define cerr
#define cout

bool _LibTest_tf( 0 );


LibTest::LibTest(
  const TestItem *  t,
  bool		    outputLineProgress,
  ostream & 	    dumpStream,
  ostream & 	    outputStream,
  ostream & 	    errorStream
  )
  : lineProgress( outputLineProgress ),
    dump( dumpStream ),
    out( outputStream ),
    err( errorStream ),
    result( defaultResultsObj )
{
  testList = t;
  currentTest = 0;
}

LibTest::LibTest(
  const TestItem *  t,
  bool		    outputLineProgress,
  Results &	    resultsProcObj,
  ostream & 	    dumpStream,
  ostream & 	    outputStream,
  ostream & 	    errorStream
  )
  : lineProgress( outputLineProgress ),
    dump( dumpStream ),
    out( outputStream ),
    err( errorStream ),
    result( resultsProcObj )
{
  testList = t;
  currentTest = 0;
}

LibTest::~LibTest( void )
{
  ;
}

int
LibTest::run( int & argc, char * argv[] )
{
  size_t numTimes = 1;
  int     argsUsed = 1;

  vector< char * >  arglist;
  
  for( int arg = 1; arg < argc; arg++ )
    {      
      if( argv[arg][0] == '-' )
	{
	  argsUsed++;
	  if( isdigit( argv[arg][1]  ) )
	    {
	      numTimes = atoi( argv[arg] + 1 );
	    }
	  else
	    {
	      switch( argv[arg][1] )
		{
		case 'l':
		  lineProgress = true;
		  break;
		default:
		  break;
		}
	    }
	}
      else
	{
	  arglist.push_back( argv[arg] );
	}
    }

  for( size_t passNum = 0; passNum < numTimes; passNum++ )
    {
      if( arglist.empty() )
	{
	  for( size_t tNum = 0; testList[tNum].name; tNum++ )
	    {
	      if( ! testit( tNum, passNum ) )
		return( tNum );
	    }
	}
      else
	{
	  vector< char * >  missingList;

	  bool	tested;
	  
	  for( vector< char * >::iterator them = arglist.begin();
	       them != arglist.end();
	       ++ them )
	    {
	      tested = false;
	      
	      for( size_t tNum = 0; testList[tNum].name; tNum++ )
		{
		  if( ! strcmp( *them, testList[tNum].name ) )
		    {
		      tested = true;
		      if( ! testit( tNum, passNum ) )
			return( tNum );
		    }
		}

	      if( ! tested )
		{
		  err << "WARN: Test: '" << *them << "' Not found."
		      << endl;
		}
	    }
	}
    }
  
  return( 0 );
}

int
LibTest::run( size_type numPasses, const Str & testListString )
{

  Str		tests( testListString );
  size_type	passes( numPasses > 0 ? numPasses : 1 );
  
  vector< Str >	runTestList;

  if( tests.size() )
    {
      Str::size_type    testCount( tests.scan( " \t;,:" ) );

      if( testCount > 1 )
	{
	  for( Str::size_type testIndex( 1 );
	       testIndex < testCount;
	       ++ testIndex )
	    {
	      runTestList.push_back( Str( tests.scanMatch( testIndex ) ) );
	    }
	}
      else
	{
	  runTestList.push_back( tests );
	}
    }
  
  for( size_type passNum = 0; passNum < passes; ++ passNum )
    {
      if( ! runTestList.size() )
	{
	  for( size_t tNum = 0; testList[tNum].name; tNum++ )
	    {
	      if( ! testit( tNum, passNum ) )
		return( tNum );
	    }
	}
      else
	{
	  for( vector< Str >::iterator them = runTestList.begin();
	       them != runTestList.end();
	       ++ them )
	    {
	      bool tested( false );
	      
	      for( size_t tNum = 0; testList[tNum].name; tNum++ )
		{
		  if( (*them) ==  testList[tNum].name )
		    {
		      tested = true;
		      if( ! testit( tNum, passNum ) )
			return( tNum );
		    }
		}

	      if( ! tested )
		{
		  err << "WARN: Test: '" << *them << "' Not found."
		      << endl;
		}
	    }
	}
    }
  
  return( 0 );
}


bool
LibTest::test(
  const char *	srcFn,
  long		srcLine,
  const Str &	reason,
  bool		pass,
  bool		progress
  )
{
  return( test( srcFn, srcLine, reason.c_str(), pass, progress ) );
}
	  
bool
LibTest::test(
  const char *	srcFn,
  long		srcLine,
  const char *	reason,
  bool		pass,
  bool		progress
  )
{
  if( lineProgress )
    err << "Tested: " << srcFn << ':' << srcLine << endl;
  
  if( pass )
    {
      result.passed( *this, testList[currentTest].name,
		     currentTest, currentPass,
		     srcFn, srcLine, progress );
      return( true );
    }
  else
    {
      return( result.failed( *this, testList[currentTest].name,
			     currentTest, currentPass,
			     reason,
			     srcFn, srcLine ) );
    }
}

  
bool
LibTest::test(
  const char *	srcFn,
  long		srcLine,
  bool		pass,
  bool		progress
  )
{
  return( test( srcFn, srcLine, "", pass, progress ) );
}

bool
LibTest::file(
  const char *	srcFn,
  long		srcLine,
  const char *	testFileName,
  const char *	expFileName
  )
{
  Str reason;
  size_t  byte = 0;
  
  ifstream testf( testFileName );
  ifstream expf( expFileName );

  reason.reset();
  reason << "Test File: '" << testFileName << "' open error.";
  test( srcFn, srcLine, reason, testf.good() );

  reason.reset();
  reason << "Expected File: '" << expFileName << "' open error.";
  test( srcFn, srcLine, reason, expf.good() );

  char testBuf[4096];
  char expBuf[4096];

  for(;;) {
    testf.read( testBuf, sizeof( testBuf ) );
    expf.read( expBuf, sizeof( expBuf ) );

    if( testf.gcount() != expf.gcount() ) {
      reason.reset();
      reason << "Read count mismatch: "
	     << testf.gcount()
	     << " expected: "
	     << expf.gcount();
      return( test( srcFn, srcLine, reason, false ) );
    }

    if( ! testf.good() || testf.gcount() < 1 ) {
      if( ! testf.good() ) {
	
	if( ! testf.eof() ) {
	  return( test( srcFn, srcLine,
			"Test input file error", false ) );
	} else {
	  if( ! expf.eof() ) {
	    return( test( srcFn, srcLine,
			  "Unexpected end of test file", false ) );
	  } else {
	    return( test( srcFn, srcLine, true ) );
	  }
	}
      } else {
	return( test( srcFn, srcLine,
		      "Test read no data", false ) );
      }
    }

    if( memcmp( testBuf, expBuf, testf.gcount() ) != 0 ) {
      for( streamsize bufByte = 0; bufByte < testf.gcount(); bufByte++ ) {
	if( testBuf[ bufByte ] != expBuf[ bufByte ] ) {
	  reason.reset();
	  reason << "Data mismatch at byte "
		 << byte + bufByte
		 << ": got: " << testBuf[ bufByte ]
		 << " expected " << expBuf[ bufByte ];			   
			   
	  return( test( srcFn, srcLine, reason, false ) );
	}
      }
      // should never get here
      return( test( srcFn, srcLine, "memcmp LIED!", false ) );
    } else {
      byte += testf.gcount();
    }
  }
}

bool
LibTest::file( const char * srcFn, long srcLine, const char * testFileName )
{
  char * expFileName = new char [ strlen( testFileName ) + 5 ];
  strcpy( expFileName, testFileName );
  strcat( expFileName, ".exp" );

  bool ret = file( srcFn, srcLine, testFileName, expFileName );
  delete expFileName;
  return( ret );
}

  
bool
LibTest::operator () (
  const char *	srcFn,
  long		srcLine,
  const char *	reason,
  bool		pass,
  bool		progress
  )
{
  return( test( srcFn, srcLine, reason, pass, progress ) );
}
  
bool
LibTest::operator () (
  const char *	srcFn,
  long		srcLine,
  bool		pass,
  bool		progress
  )
{
  return( test( srcFn, srcLine, pass, progress ) );
}
  
bool
LibTest::operator () (
  const char *	srcFn,
  long		srcLine,
  const char *	reason,
  bool		pass
  )
{
  return( test( srcFn, srcLine, reason, pass ) );
}
  
bool
LibTest::operator () (
  const char *	srcFn,
  long		srcLine,
  bool		pass
  )
{
  return( test( srcFn, srcLine, pass ) );
}
  
ostream &
LibTest::outputExpect( void )
{
  out << "\n    Expect: ";
  return( out );
}

ostream &
LibTest::outputIs( void )
{
  out <<  "\n    is:     ";
  return( out );
}

const char *
LibTest::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}

ostream &
LibTest::getOutput( void )
{
  return( out );
}

ostream &
LibTest::getError( void )
{
  return( err );
}

ostream &
LibTest::getDump( void )
{
  return( dump );
}

const char *
LibTest::getCurrentTestName( void ) const
{
  return( testList[currentTest].name );
}

bool
LibTest::testit( size_t tNum, size_t passNum )
{
  currentTest = tNum;
  currentPass = passNum;
  result.start( *this, testList[tNum].name, tNum, passNum + 1 );
  return( result.completed( *this, testList[tNum].name, tNum, passNum + 1,
			   testList[tNum].test( *this ) ) );
}

void
LibTest::DefaultResults::start(
 LibTest &	tester,
 const char *	testName,
 size_t		/* testNum */,
 long		passNum
 )
{
  tester.getOutput() << "Testing(" << passNum << "): "<< testName;
  tester.getOutput().flush();
}

bool
LibTest::DefaultResults::completed(
  LibTest &	    tester,
  const char *	    /* testName */,
  size_t	    /* testNum */,
  long		    /* passNum */,
  bool		    passed
  )
{
  if( passed )
    {
      tester.getOutput() << " passed." << endl;
      return( passed );
    }

  return( passed );
}


bool
LibTest::DefaultResults::failed(
  LibTest &	tester,
  const char *	/* testName */,
  size_t	/* testNum */,
  size_t	/* passNum */,
  const char *	reason,
  const char *	srcFile,
  long		srcLine
  )
{
  tester.getOutput() << " FAILED " << reason << endl;
  tester.getOutput() << srcFile << ':' << srcLine
		  << ':' << " FAILED here." << endl;
  exit( 1 );
  return( false );
}

				    
void
LibTest::DefaultResults::passed(
  LibTest &	tester,
  const char *	STLUTILS_UNUSED( testName ),
  size_t	STLUTILS_UNUSED( testNum ),
  size_t	STLUTILS_UNUSED( passNum ),
  const char *	STLUTILS_UNUSED( srcFile ),
  long		STLUTILS_UNUSED( srcLine ),
  bool		progress
  )
{
  if( progress )
    {
      tester.getOutput() << '.';
      tester.getOutput().flush();
    }
}

// Revision History:
//
// 
// %PL%
// 
// $Log$
// Revision 6.2  2011/12/30 23:57:15  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:41  houghton
// Changed to version 6
//
// Revision 5.4  2003/08/09 11:20:58  houghton
// Changed ver strings.
//
// Revision 5.3  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.2  2000/05/29 10:18:46  houghton
// Added run( size_type passes, const Str & testlist).
// Cleanup.
//
// Revision 5.1  2000/05/25 10:33:16  houghton
// Changed Version Num to 5
//
// Revision 4.2  1998/03/08 18:07:18  houghton
// Changed so TESTR call does not access the error until after the test
//     value. This way, if the error is a method, the method being tested
//     will have executed.
//
// Revision 4.1  1997/09/17 15:12:30  houghton
// Changed to Version 4
//
// Revision 3.5  1997/09/17 11:08:25  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.4  1997/08/18 10:21:12  houghton
// Port(Sun5): Renamed 'times' in run to numTimes to prevent a compiler warning.
//
// Revision 3.3  1997/06/09 12:00:55  houghton
// Reworked arg processing so an error will be output if a test is not found.
//
// Revision 3.2  1997/01/18 17:30:13  houghton
// Added new '-l' arg to turn one progress by line number output from
//    command line args.
// Reworked arg processing to support '-l' (and any future) flag.
//
// Revision 3.1  1996/11/14 01:23:44  houghton
// Changed to Release 3
//
// Revision 2.3  1996/10/28 12:08:14  houghton
// Bug-Fix: if passed test should always call result.passed and pass it
// 	 the progress flag. Also now check progress flag in
// 	 DefaultResults::passed
// Cleanup: Removed failed method and the call to it.
//
// Revision 2.2  1996/05/03 16:12:53  houghton
// Added outputLineProgress. Ouptut source line for every test.
//
// Revision 2.1  1995/11/10 12:40:41  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:35  houghton
// Revised
//
//
