#include <LibTest.hh>
#include <RegexScan.hh>

bool
tRegexScan( LibTest & test )
{
  {
    // RegexScan( const char * )
    // good( void ) const
    // match( const char * ) const
    // match( const char *, size_t ) const
    // matchStart( void ) const
    // matchLength( void ) const
    // 
    
    
    RegexScan t( "abc" );

    test( t.good() );

    test( t.match( "abc" ) );
    test( t.matchStart() == 0 );
    test( t.matchLength() == 3 );
    test( ! t.match( "xxxabc" ) );
    
    test( t.match( "xxxabc", 3 ) );
    test( t.match( "abcxxx" ) );
    test( t.matchStart() == 0 );
    test( t.matchLength() == 3 );
  }
  
  {
    // search( const char * ) const
    
    RegexScan t( "abc" );

    test( t.search( "abc" ) );
    test( ! t.search( "xbc" ) );
    test( ! t.search( "axc" ) );
    test( ! t.search( "abx" ) );
    test( t.search( "xabcy" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "^abc" );

    test( t.search( "abcdefg" ) );
    test( ! t.search( " abc" ) );
    test( ! t.search( "aabc" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "abc$" );

    test( t.search( "this is a test abc" ) );
    test( t.search( "abc" ) );
    test( t.search( "abc abc" ) );
    test( t.matchStart() == 4 );
    test( ! t.search( "abcc" ) );
  }

  {
    // search( const char * ) const

    RegexScan t( "^abc$" );

    test( ! t.search( "abbc" ) );
    test( ! t.search( "aabc" ) );
    test( t.search( "abc" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "ab+bc" );

    test( ! t.search( "abc" ) );
    test( ! t.search( "abbq" ) );
    test( t.search( "abbbbbc" ) );
  }
  
  {
    // search( const char * ) const
    RegexScan t( "ab?bc" );

    test( t.search( "xabcy" ) );
    test( ! t.search( "abbq" ) );
    test( t.search( "xabbcy" ) );
    test( ! t.search( "xabbbc" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "ab?c" );

    test( t.search( "ac" ) );
    test( t.search( "\nac\n" ) );
    test( t.search( "xxabc" ) );
    test( ! t.search( "abbc" ) );
  }
    
		    
  {
    // search( const char * ) const
    RegexScan t( "ab*c" );
    
    test( t.search( "ac" ) );
    test( t.search( "abc" ) );
    test( t.search( "abbc" ) );      
  }

  {
    // search( const char * ) const
    
    RegexScan t( "ab*bc" );

    test( t.search( "abc" ) );
    test( t.search( "abbc" ) );
    test( t.search( "abbbbbc" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "a.*c" );

    test( t.search( "aabbxyzcdecf" ) );
    test( t.search( "acdefg" ) );
    test( ! t.search( "xxc" ) );
    test( ! t.search( "axx" ) );
  }

  {
    // good( void ) const

    RegexScan t( "a[]b" );

    test( ! t.good() );
  }

  {
    // good( void ) const
    RegexScan t( "a[b" );

    test( ! t.good() );
  }
      
  {
    // good( void ) const
    // search( const char * ) const
    RegexScan t( "a]b" );

    test( t.good() );

    test( t.search( "xa]b[" ) );
  }
      
  {
    // good( void ) const
    // search( const char * ) const
    RegexScan t( "a\\[b" );

    test( t.good() );

    test( t.search( "xa[b]" ) );
  }
      
  {
    // good( void ) const
    // search( const char * ) const
    // \[]
    RegexScan t( "a\\[d-f]b" );

    test( t.good() );

    test( ! t.search( "xaeb" ) );
    test( t.search( "xa[d-f]b" ) );
  }
      
  {
    // search( const char * ) const
    //[ccc]
    RegexScan t( "a[bc]d" );

    test( t.search( "abd" ) );
    test( t.search( "acd" ) );
    test( ! t.search( "abc" ) );
  }

  {
    // search( const char * ) const
    //[n-x]
    RegexScan t( "a[b-d]e" );

    test( t.search( "xacex" ) );
    test( ! t.search( "ab" ) );
    test( ! t.search( "acd" ) );
    test( ! t.search( "abd" ) );

  }

  {
    // search( const char * ) const
    //[n-x]
    RegexScan t( "a[b-d]" );

    test( t.search( "xac" ) );
    test( ! t.search( "bb" ) );
  }

  {
    // search( const char * ) const
    // [xy-]

    RegexScan t( "a[bf-]d" );

    test( t.search( "abde" ) );
    test( t.search( "xafde" ) );
    test( t.search( "a-d" ) );
    test( ! t.search( "aed" ) );
  }

  {
    // search( const char * ) const
    // [xy-]

    RegexScan t( "a[-bf]d" );

    test( t.search( "abde" ) );
    test( t.search( "xafde" ) );
    test( t.search( "a-d" ) );
    test( ! t.search( "aed" ) );
  }

  {
    // search( const char * ) const
    // []]

    RegexScan t( "a[]]b" );

    test( t.search( "a]b" ) );
  }

  {
    // search( const char * ) const
    //[^xx]
    RegexScan t( "a[^bcd]e" );

    test( t.search( "xaee" ) );
    test( ! t.search( "abe" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "a.c" ); 

    test( t.search( "abc" ) );
    test( t.search( "aabcc" ) );
    test( t.search( "xaxcx" ) );
  }

  {
    // search( const char * ) const
    // matchStart( size_t ) const
    // matchLength( size_t ) const
    
    // ()
    RegexScan t( "a(b)cd(ef.+)z" );

    test( t.search( "xabcdefghiz" ) );
    test( t.matchStart( 0 ) == 1 );
    test( t.matchStart( 1 ) == 2 );
    test( t.matchStart( 2 ) == 5 );
    test( t.matchLength( 2 ) == 5 );
  }

  {
    // search( const char * ) const
    // matchStart( size_t ) const
    // matchLength( size_t ) const
    
    // |
    RegexScan t( "a ((dog)|(wolf)) sleeps" );

    test( t.search( "a dog sleeps" ) );
    test( t.matchStart( 1 ) == 2 );
    test( t.matchLength( 1 ) == 3 );
    test( t.search( "a wolf sleeps" ) );
    test( t.matchStart( 1 ) == 2 );
    test( t.matchLength( 1 ) == 4 );
  }

  {
    // search( const char * ) const
    // {}
    RegexScan t("ab{2,4}c" );

    test( t.search( "abbc" ) );
    test( t.search( "abbbc" ) );
    test( t.search( "abbbbc" ) );
    test( ! t.search( "abbbbbc" ) );
    test( ! t.search( "abc" ) );
  }
  return( true );
}

