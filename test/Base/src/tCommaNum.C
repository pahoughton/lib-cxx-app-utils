/**
  File:		tCommaNum.C
  Project:	StlUtils 
  Desc:

    
  
  Notes:
    
  Author(s):	Paul Houghton 719-527-7834 <paul.houghton@mci.com>
  Created:	04/02/2004 07:30
  
  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Name$
    $Revision$
    $State$


**/

#include "TestConfig.hh"
#include "LibTest.hh"
#include "StlUtilsMisc.hh"
#include "Compare.hh"
#include "Str.hh"

struct TestData
{
  unsigned long	    value;
  size_t	    width;
  char		    fill;
  size_t	    decimalPlaces;
  const char *	    expString;
};

TestData    TestValues[] =
  {
    {     1234,  0,	' ',	0,	"1,234" },
    { 12345678,	12,	' ',    2,	"  123,456.78" },
    { 0, 0, 0, 0, 0 },
  };

      
    
bool
tCommaNum( LibTest & tester )
{
  Str	test;
  
  for( int i = 0; TestValues[i].expString != 0; ++ i ) {
    test.reset();
    CommaNumber( test,
		 TestValues[i].value,
		 TestValues[i].width,
		 TestValues[i].fill,
		 TestValues[i].decimalPlaces );
    TESTR( test.c_str(),
	   test.compare( TestValues[i].expString ) == 0 );
  }

  return( true );
}
