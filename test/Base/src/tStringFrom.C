//
// File:        tStringFrom.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tStringFrom
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     11/15/96 15:15
//
// Revision History: (See end of file for Revision Log)
//

#include "TestConfig.hh"
#include "LibTest.hh"
#include "StringUtils.hh"
#include "Compare.hh"

#ifndef TRUE
#define FALSE 0
#define TRUE 1
#endif

struct IntTestValue
{
  int		value;
  int		useBase;
  short		base;
  int		usePrefix;
  int		prefix;
  const char *	string;
};

static IntTestValue IntTests[] =
{
  {    1234,	FALSE,  0,  FALSE,  FALSE,     "1234" },
  {   -4321,	FALSE,  0,  FALSE,  FALSE,     "-4321" },
  {  0x0abc,	TRUE,  16,  FALSE,  FALSE,     "abc" },
  {  0x0f0f,	TRUE,  16,  TRUE,   FALSE,     "f0f" },
  {  0x0123,	TRUE,  16,  TRUE,   TRUE,	"0x123" },
  {    -045,	TRUE,   8,  TRUE,   TRUE,	"-045" },
  {  0x000f,	TRUE,	2,  FALSE,  FALSE,	"1111" },
  {       0,       0,   0,      0,      0,      0 }
};

struct UIntTestValue
{
  unsigned int	value;
  int		useBase;
  short		base;
  int		usePrefix;
  int		prefix;
  const char *	string;
};

static UIntTestValue UIntTests[] =
{
  {    1234,	FALSE,  0,  FALSE,  FALSE,     "1234" },
  {  0x0abc,	TRUE,  16,  FALSE,  FALSE,     "abc" },
  {  0x0f0f,	TRUE,  16,  TRUE,   FALSE,     "f0f" },
  {  0x0123,	TRUE,  16,  TRUE,   TRUE,	"0x123" },
  {     045,	TRUE,   8,  TRUE,   TRUE,	"045" },
  {  0x000f,	TRUE,	2,  FALSE,  FALSE,	"1111" },
  {       0,       0,   0,      0,      0,      0 }
};

struct ShortTestValue
{
  short		value;
  int		useBase;
  short		base;
  int		usePrefix;
  int		prefix;
  const char *	string;
};

static ShortTestValue ShortTests[] =
{
  {    1234,	FALSE,  0,  FALSE,  FALSE,     "1234" },
  {   -4321,	FALSE,  0,  FALSE,  FALSE,     "-4321" },
  {  0x0abc,	TRUE,  16,  FALSE,  FALSE,     "abc" },
  {  0x0f0f,	TRUE,  16,  TRUE,   FALSE,     "f0f" },
  {  0x0123,	TRUE,  16,  TRUE,   TRUE,	"0x123" },
  {    -045,	TRUE,   8,  TRUE,   TRUE,	"-045" },
  {  0x000f,	TRUE,	2,  FALSE,  FALSE,	"1111" },
  {       0,       0,   0,      0,      0,      0 }
};

struct UShortTestValue
{
  unsigned short    value;
  int		    useBase;
  short		    base;
  int		    usePrefix;
  int		    prefix;
  const char *	    string;
};

static UShortTestValue UShortTests[] =
{
  {    1234,	FALSE,  0,  FALSE,  FALSE,     "1234" },
  {  0x0abc,	TRUE,  16,  FALSE,  FALSE,     "abc" },
  {  0x0f0f,	TRUE,  16,  TRUE,   FALSE,     "f0f" },
  {  0x0123,	TRUE,  16,  TRUE,   TRUE,	"0x123" },
  {     045,	TRUE,   8,  TRUE,   TRUE,	"045" },
  {  0x000f,	TRUE,	2,  FALSE,  FALSE,	"1111" },
  {       0,       0,   0,      0,      0,      0 }
};

struct LongTestValue
{
  long		value;
  int		useBase;
  short		base;
  int		usePrefix;
  int		prefix;
  const char *	string;
};

static LongTestValue LongTests[] =
{
  {    1234,	FALSE,  0,  FALSE,  FALSE,     "1234" },
  {   -4321,	FALSE,  0,  FALSE,  FALSE,     "-4321" },
  {  0x0abc,	TRUE,  16,  FALSE,  FALSE,     "abc" },
  {  0x0f0f,	TRUE,  16,  TRUE,   FALSE,     "f0f" },
  {  0x0123,	TRUE,  16,  TRUE,   TRUE,	"0x123" },
  {    -045,	TRUE,   8,  TRUE,   TRUE,	"-045" },
  {  0x000f,	TRUE,	2,  FALSE,  FALSE,	"1111" },
  {       0,       0,   0,      0,      0,      0 }
};

struct ULongTestValue
{
  unsigned long	value;
  int		useBase;
  short		base;
  int		usePrefix;
  int		prefix;
  const char *	string;
};

static ULongTestValue ULongTests[] =
{
  {    1234,	FALSE,  0,  FALSE,  FALSE,     "1234" },
  {  0x0abc,	TRUE,  16,  FALSE,  FALSE,     "abc" },
  {  0x0f0f,	TRUE,  16,  TRUE,   FALSE,     "f0f" },
  {  0x0123,	TRUE,  16,  TRUE,   TRUE,	"0x123" },
  {     045,	TRUE,   8,  TRUE,   TRUE,	"045" },
  {  0x000f,	TRUE,	2,  FALSE,  FALSE,	"1111" },
  {       0,       0,   0,      0,      0,      0 }
};

struct DoubleTestValue
{
  double	value;
  int		usePrec;
  short		prec;
  const char *	string;
};

static DoubleTestValue DoubleTests[] =
{
  {  123.4567,	FALSE,  0,     "123.46" },
  { -3789.2344,	TRUE,	3,  "-3789.234" },
  { 0, 0, 0, 0 }
};
    
bool
tStringFrom( LibTest & tester )
{
  {
    // StringFrom( int )
    // StirngFrom( int, short )
    // StringFrom( int, short, bool )

    for( int t = 0; IntTests[t].string != 0; ++t )
      {
	if( IntTests[t].useBase )
	  {
	    if( IntTests[t].usePrefix )
	      {
		TEST( compare( StringFrom( IntTests[t].value,
					   IntTests[t].base,
					   IntTests[t].prefix ),
			       IntTests[t].string ) == 0 );
	      }
	    else
	      {
		TEST( compare( StringFrom( IntTests[t].value,
					   IntTests[t].base ),
			       IntTests[t].string ) == 0 );
	      }
	  }
	else
	  {
	    TEST( compare( StringFrom( IntTests[t].value ),
			       IntTests[t].string ) == 0 );
	  }
      }
  }

  {
    // StringFrom( unsigned int )
    // StirngFrom( unsigned int, short )
    // StringFrom( unsigned int, short, bool )

    for( int t = 0; UIntTests[t].string != 0; ++t )
      {
	if( UIntTests[t].useBase )
	  {
	    if( UIntTests[t].usePrefix )
	      {
		TEST( compare( StringFrom( UIntTests[t].value,
					   UIntTests[t].base,
					   UIntTests[t].prefix ),
			       UIntTests[t].string ) == 0 );
	      }
	    else
	      {
		TEST( compare( StringFrom( UIntTests[t].value,
					   UIntTests[t].base ),
			       UIntTests[t].string ) == 0 );
	      }
	  }
	else
	  {
	    TEST( compare( StringFrom( UIntTests[t].value ),
			       UIntTests[t].string ) == 0 );
	  }
      }
  }

  {
    // StringFrom( short )
    // StirngFrom( short, short )
    // StringFrom( short, short, bool )

    for( int t = 0; ShortTests[t].string != 0; ++t )
      {
	if( ShortTests[t].useBase )
	  {
	    if( ShortTests[t].usePrefix )
	      {
		TEST( compare( StringFrom( ShortTests[t].value,
					   ShortTests[t].base,
					   ShortTests[t].prefix ),
			       ShortTests[t].string ) == 0 );
	      }
	    else
	      {
		TEST( compare( StringFrom( ShortTests[t].value,
					   ShortTests[t].base ),
			       ShortTests[t].string ) == 0 );
	      }
	  }
	else
	  {
	    TEST( compare( StringFrom( ShortTests[t].value ),
			       ShortTests[t].string ) == 0 );
	  }
      }
  }

  {
    // StringFrom( unsigned short )
    // StirngFrom( unsigned short, short )
    // StringFrom( unsigned short, short, bool )

    for( int t = 0; UShortTests[t].string != 0; ++t )
      {
	if( UShortTests[t].useBase )
	  {
	    if( UShortTests[t].usePrefix )
	      {
		TEST( compare( StringFrom( UShortTests[t].value,
					   UShortTests[t].base,
					   UShortTests[t].prefix ),
			       UShortTests[t].string ) == 0 );
	      }
	    else
	      {
		TEST( compare( StringFrom( UShortTests[t].value,
					   UShortTests[t].base ),
			       UShortTests[t].string ) == 0 );
	      }
	  }
	else
	  {
	    TEST( compare( StringFrom( UShortTests[t].value ),
			       UShortTests[t].string ) == 0 );
	  }
      }
  }

  {
    // StringFrom( long )
    // StirngFrom( long, short )
    // StringFrom( long, short, bool )

    for( int t = 0; LongTests[t].string != 0; ++t )
      {
	if( LongTests[t].useBase )
	  {
	    if( LongTests[t].usePrefix )
	      {
		TEST( compare( StringFrom( LongTests[t].value,
					   LongTests[t].base,
					   LongTests[t].prefix ),
			       LongTests[t].string ) == 0 );
	      }
	    else
	      {
		TEST( compare( StringFrom( LongTests[t].value,
					   LongTests[t].base ),
			       LongTests[t].string ) == 0 );
	      }
	  }
	else
	  {
	    TEST( compare( StringFrom( LongTests[t].value ),
			       LongTests[t].string ) == 0 );
	  }
      }
  }

  {
    // StringFrom( unsigned long )
    // StirngFrom( unsigned long, short )
    // StringFrom( unsigned long, short, bool )

    for( int t = 0; ULongTests[t].string != 0; ++t )
      {
	if( ULongTests[t].useBase )
	  {
	    if( ULongTests[t].usePrefix )
	      {
		TEST( compare( StringFrom( ULongTests[t].value,
					   ULongTests[t].base,
					   ULongTests[t].prefix ),
			       ULongTests[t].string ) == 0 );
	      }
	    else
	      {
		TEST( compare( StringFrom( ULongTests[t].value,
					   ULongTests[t].base ),
			       ULongTests[t].string ) == 0 );
	      }
	  }
	else
	  {
	    TEST( compare( StringFrom( ULongTests[t].value ),
			       ULongTests[t].string ) == 0 );
	  }
      }
  }

  {
    // StringFrom( double )
    // StirngFrom( double, short )

    for( int t = 0; DoubleTests[t].string != 0; ++t )
      {
	if( DoubleTests[t].usePrec )
	  {
	    TEST( compare( StringFrom( DoubleTests[t].value,
				       DoubleTests[t].prec ),
			   DoubleTests[t].string ) == 0 );
	  }
	else
	  {
	    TESTR( StringFrom( DoubleTests[t].value ),
		   compare( StringFrom( DoubleTests[t].value ),
			    DoubleTests[t].string ) == 0 );
	  }
      }
  }

  {
    // StringFrom( char *   dest,
    //		   size_t   destSize,
    //		   long	    num )

    char	    t[11];
    long	    num = 1234;
    const char *    exp = "*00001234*";

    memset( t, '*', sizeof( t ) - 1);
    t[sizeof(t) - 1] = 0;

    TESTR( t, StringFrom( t + 1, 8, num ) == (t + 1) );
    TESTR( t, strcmp( t, exp ) == 0 );

    memset( t, '*', sizeof( t ) - 1 );
    num = -987;
    exp = "*-0000987*";
    
    TESTR( t, StringFrom( t + 1, 8, num ) == (t + 1) );
    TESTR( t, strcmp( t, exp ) == 0 );

  }
    
    
  {
    // StringFrom( char *   dest,
    //		   size_t   destSize,
    //		   long	    num,
    //		   char     fill );

    char	    t[11];
    long	    num = 1234;
    const char *    exp = "*    1234*";

    memset( t, '*', sizeof( t ) - 1 );
    t[sizeof( t ) - 1] = 0;

    TEST( StringFrom( t + 1, 8, num, ' ' ) == t + 1 );
    TESTR( t, strcmp( t, exp ) == 0 );

    memset( t, '*', sizeof( t ) - 1 );
    num = -987;
    exp = "*    -987*";
    
    TEST( StringFrom( t + 1, 8, num, ' ' ) == t + 1 );
    TESTR( t, strcmp( t, exp ) == 0 );

  }
    
    
  
  {
    // just some output

    int	value = 54321;
    
    tester.getDump() << "\n Example: StringFrom( " << value << " ) == "
		       << StringFrom( value ) << endl;

    tester.getDump() << '\n' << tester.getCurrentTestName();
  }

  return( true );
}

	    
		

//
// $Log$
// Revision 6.1  2003/08/09 11:22:52  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:31  houghton
// Changed Version Num to 5
//
// Revision 4.2  1997/12/23 12:07:19  houghton
// Added tests for StringFrom( char * dest ).
//
// Revision 4.1  1997/09/17 15:14:44  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:08  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/03/21 15:45:35  houghton
// Changed base version to 3
//
// Revision 1.1  1996/11/19 12:36:51  houghton
// Initial Version of test for StringFrom function.
//
//
