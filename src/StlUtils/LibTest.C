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
// Revision 1.1  1995/11/05 13:23:25  houghton
// Initaial implementation
//
//

#include "ClueVersion.h"
#include "LibTest.hh"

#include <cstdlib>
#include <cstring>
#include <fstream>

const char LibTest::version[] =
LIB_CLUE_VERSION
"$Id$";


// this should prevent accidental use of cout & cerr

#define cerr
#define cout

LibTest::LibTest(
  const TestItem *  t,
  ostream & 	    outputStream,
  ostream & 	    errorStream
  )
  : out( outputStream ),
    err( errorStream )
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

  for( size_t pass = 0; pass < times; pass++ )
    {
      if( times > 1 )
	err << "Testing Pass: " << pass + 1 << endl;
	
      if( (argc > 1 && times == 1) || argc > 2  )
	{	  
	  for( int a = 1; a < argc; a++ )
	    {
	      for( size_t tNum = 0; testList[tNum].name; tNum++ )
		{
		  if( ! strcmp( argv[a], testList[tNum].name ) )
		    {
		      currentTest = tNum;
		      err << "Testing: " << testList[tNum].name;
		      if( ! testList[tNum].test( *this ) )
			{
			  return( tNum );
			}
		      else
			{
			  err << " passed!" << endl;
			}
		    }
		}
	    }
	}
      else
	{
	  for( size_t tNum = 0; testList[tNum].name; tNum++ )
	    {
	      currentTest = tNum;
	      err << "Testing: " << testList[tNum].name;
	      if( ! testList[tNum].test( *this ) )
		{
		  return( tNum );
		}
	      else
		{
		  err << " passed!" << endl;
		}
	    }
	}
    }
  return( 0 );
}

void
LibTest::test( bool pass, bool progress )
{
  if( ! pass ) failed();
    
  if( progress ) err << '.';
}
  
void
LibTest::test( const char * name, bool pass )
{
  err << ' ' << name;
  if( ! pass )
    {
      failed();
    }
}

void
LibTest::file( const char * fileName )
{
  char * expFileName = new char [ strlen( fileName ) + 10 ];

  strcpy( expFileName, fileName );
  strcat( expFileName, ".exp" );

  ifstream inf( fileName );
  ifstream expf( expFileName );

  test( inf.good() && expf.good() );

  char inb[4096];
  char expb[4096];

  while( inf.read( inb, sizeof( inb ) ).good() )
    {
      test( expf.read( expb, sizeof( expb ) ).good() );
      test( expf.gcount() == inf.gcount() );
      test( memcmp( inb, expb, inf.gcount() ) == 0 );
    }

  test( ! expf.read( expb, sizeof( expb ) ).good() );
  test( expf.gcount() == inf.gcount() );
  if( expf.gcount() )
    test( memcmp( inb, expb, inf.gcount() ) == 0 );

  test( inf.eof() );
  test( expf.eof() );
  delete expFileName;
  
}
      
  
void
LibTest::operator () ( bool pass, bool progress )
{
  test( pass, progress );
}
  
void
LibTest::operator ()( const char * name, bool pass )
{
  test( name, pass );
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

void
LibTest::failed( void )
{
  err << " FAILED!" << endl;
  exit( 1 );
}


