#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#include <StringUtils.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#include <StrUtil.hh>
#endif


bool
tIsBaseDigit( LibTest & tester )
{
  {
    // IsBaseDigit( int, unsigned short )
    
    for( unsigned short base = 2; base < 64; base++ )
      {
	for( int num = -2; num < base+2; num++ )
	  {
	    bool result = IsBaseDigit( num,  base );
	    
	    TEST( ( result == true && num >= 0 && num < base )  ||
		  ( result == false && ( num < 0 || num >= base ) ) );
	  }
      }
  }

  {
    // IsBaseDigit( char, unsigned short)

    for( unsigned short base = 2; base < 36; base++ )
      {
	{
	  for( char num = ('0' - 2 ); num <= '9'; num++ )
	    {
	      bool result = IsBaseDigit( num, base );
	      
	      TEST( ( result == true && num >= '0' && (num - '0') < base ) ||
		    ( result == false && ( num < '0' || (num - '0') >= base ) ) );
	    }
	}

	{
	  for( char num = ('a' - 2 ); num <= 'z'; num++ )
	    {
	      bool result = IsBaseDigit( num, base );
	      
	      TEST( ( result == true && ( base > 10 &&
					  (10 + (num - 'a')) >= 10 &&
					  (10 + (num - 'a')) < base ) ) ||
		    ( result == false && ( base < 10 ||
					   (10 + (num - 'a')) < 10 ||
					   (10 + (num - 'a')) >= base ) ) );
	    }
	}

	{
	  for( char num = ('A' - 2 ); num <= 'Z'; num++ )
	    {
	      bool result = IsBaseDigit( num, base );
	      
	      TEST( ( result == true && ( base > 10 &&
					  (10 + (num - 'A')) >= 10 &&
					  (10 + (num - 'A')) < base ) ) ||
		    ( result == false && ( base < 10 ||
					   (10 + (num - 'A')) < 10 ||
					   (10 + (num - 'A')) >= base ) ) );
	    }
	}
		    
      }
  }

    
  return( true );
}
	  
