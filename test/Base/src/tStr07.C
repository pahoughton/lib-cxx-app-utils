#include <LibTest.hh>
#include <Str.hh>

// Str::iterators

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
tStr07( LibTest & test )
{
  {
    // begin( void )
    // end( void )
    
    const char str[] = "123456";
    
    Str s( str );

    int i = 0;
    {
      for( Str::iterator t = s.begin();
	  t != s.end();
	  t++ )
	{
	  test( *t == str[i] );
	  i++;
	}
    }
    test( i == 6 );

    Str::iterator t = s.begin();

    t++; t++;
    *t = 'a';

    test( s == "12a456" );
    
  }

  {
    // begin( void ) const
    // end( void ) const
    
    const char str[] = "123456";
    
    Str s( str );

    int i = 0;
    for( Str::const_iterator t = s.begin();
	t != s.end();
	t++ )
      {
	test( *t == str[i] );
	i++;
      }
    test( i == 6 );
  }

  {
    // rbegin( void )
    // rend( void )
    
    const char str[] = "123456";
    
    Str s( str );

    int i = 5;
    {
      for( Str::reverse_iterator t = s.rbegin();
	  t != s.rend();
	  t++ )
	{
	  test( *t == str[i] );
	  i--;
	}
    }
    
    test( i == -1 );

    Str::reverse_iterator t = s.rbegin();

    t++; t++;
    *t = 'a';

    test( s == "123a56" );
  }
    
  {
    // rbegin( void ) const
    // rend( void ) const
    
    const char str[] = "123456";
    
    const Str s( str );

    int i = 5;
    for( Str::const_reverse_iterator t = s.rbegin();
	t != s.rend();
	t++ )
      {
	test( *t == str[i] );
	i--;
      }
    
    test( i == -1 );
  }
  
  return( true );
}

    
	
      
