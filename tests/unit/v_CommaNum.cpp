// 2004-04-02 (cc) <paul4hough@gmail.com>

#include <clue/CommaNum.hpp>
#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::CommaNum");
using namespace clue;

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
v_CommaNum( void )
{
  Str	test;

  for( int i = 0; TestValues[i].expString != 0; ++ i ) {
    test.reset();
    CommaNumber( test,
		 TestValues[i].value,
		 TestValues[i].width,
		 TestValues[i].fill,
		 TestValues[i].decimalPlaces );
    TEST( test.compare( TestValues[i].expString ) == 0 );
  }
  return( verify.is_valid() );
}
