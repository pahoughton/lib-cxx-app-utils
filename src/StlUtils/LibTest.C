//
// File:        LibTest.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/09/95 09:54 
//
// Revision History:
//
// $Log$
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

#if !defined( CLUE_SHORT_FN )
#include "LibTest.hh"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstdio>
#else
#include "LibTest.hh"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstdio>
#endif

CLUE_VERSION( LibTest,
	      "$Id$" );

LibTest::DefaultResults LibTest::defaultResultsObj;


// this should prevent accidental use of cout & cerr

#define cerr
#define cout

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
  size_t times = 1;

  // the count flag must be the first argument

  if( argc > 1 && argv[1][0] == '-' )
    {
      times = atoi( argv[1] + 1 );
    }

  for( size_t passNum = 0; passNum < times; passNum++ )
    {
      if( (argc > 1 && times == 1) || argc > 2  )
	{	  
	  for( int a = 1; a < argc; a++ )
	    {
	      for( size_t tNum = 0; testList[tNum].name; tNum++ )
		{
		  if( ! strcmp( argv[a], testList[tNum].name ) )
		    {
		      if( ! testit( tNum, passNum ) )
			return( tNum );
		    }
		}
	    }
	}
      else
	{
	  for( size_t tNum = 0; testList[tNum].name; tNum++ )
	    {
	      if( ! testit( tNum, passNum ) )
		return( tNum );
	    }
	}
    }

  return( 0 );
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
  char reason[100];
  size_t  byte = 0;
  
  ifstream testf( testFileName );
  ifstream expf( expFileName );

  sprintf( reason, "Test File: '%s' open error", testFileName );
  test( srcFn, srcLine, reason, testf.good() );
  sprintf( reason, "Expected File: '%s' open error", expFileName );
  test( srcFn, srcLine, reason, expf.good() );

  char testBuf[4096];
  char expBuf[4096];

  for(;;)
    {
      testf.read( testBuf, sizeof( testBuf ) );
      expf.read( expBuf, sizeof( expBuf ) );

      if( testf.gcount() != expf.gcount() )
	{
	  sprintf( reason, "Read count mismatch: %d expected: %d",
		   testf.gcount(), expf.gcount() );
	  return( test( srcFn, srcLine, reason, false ) );
	}

      if( ! testf.good() || testf.gcount() < 1 )
	{
	  if( ! testf.good() )
	    {
	      if( ! testf.eof() )
		{
		  return( test( srcFn, srcLine,
				"Test input file error", false ) );
		}
	      else
		{
		  if( ! expf.eof() )
		    {
		      return( test( srcFn, srcLine,
				    "Unexpected end of test file", false ) );
		    }
		  else
		    {
		      return( test( srcFn, srcLine, true ) );
		    }
		}
	    }
	  else
	    {
	      return( test( srcFn, srcLine,
			    "Test read no data", false ) );
	    }
	}

      if( memcmp( testBuf, expBuf, testf.gcount() ) != 0 )
	{
	  for( size_t bufByte = 0; bufByte < testf.gcount(); bufByte++ )
	    {
	      if( testBuf[ bufByte ] != expBuf[ bufByte ] )
		{
		  sprintf( reason,
			   "Data mismatch at byte %d: '0x%x' expected '0x%x'",
			   byte + bufByte,
			   testBuf[ bufByte ],
			   expBuf[ bufByte ] );			   
			   
		  return( test( srcFn, srcLine, reason, false ) );
		}	     
	    }
	  return( test( srcFn, srcLine, "memcmp LIED!", false ) );
	}
      else
	{
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
  const char *	CLUE_UNUSED( testName ),
  size_t	CLUE_UNUSED( testNum ),
  size_t	CLUE_UNUSED( passNum ),
  const char *	CLUE_UNUSED( srcFile ),
  long		CLUE_UNUSED( srcLine ),
  bool		progress
  )
{
  if( progress )
    {
      tester.getOutput() << '.';
      tester.getOutput().flush();
    }
}
