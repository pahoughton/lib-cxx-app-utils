#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <RegexScan.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <RxScan.hh>
#endif

bool
tRegexScan( LibTest & tester )
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

    TEST( t.good() );

    TEST( t.match( "abc" ) );
    TEST( t.matchStart() == 0 );
    TEST( t.matchLength() == 3 );
    TEST( ! t.match( "xxxabc" ) );
    
    TEST( t.match( "xxxabc", 3 ) );
    TEST( t.match( "abcxxx" ) );
    TEST( t.matchStart() == 0 );
    TEST( t.matchLength() == 3 );
  }
  
  {
    // search( const char * ) const
    
    RegexScan t( "abc" );

    TEST( t.search( "abc" ) );
    TEST( ! t.search( "xbc" ) );
    TEST( ! t.search( "axc" ) );
    TEST( ! t.search( "abx" ) );
    TEST( t.search( "xabcy" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "^abc" );

    TEST( t.search( "abcdefg" ) );
    TEST( ! t.search( " abc" ) );
    TEST( ! t.search( "aabc" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "abc$" );

    TEST( t.search( "this is a test abc" ) );
    TEST( t.search( "abc" ) );
    TEST( t.search( "abc abc" ) );
    TEST( t.matchStart() == 4 );
    TEST( ! t.search( "abcc" ) );
  }

  {
    // search( const char * ) const

    RegexScan t( "^abc$" );

    TEST( ! t.search( "abbc" ) );
    TEST( ! t.search( "aabc" ) );
    TEST( t.search( "abc" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "ab+bc" );

    TEST( ! t.search( "abc" ) );
    TEST( ! t.search( "abbq" ) );
    TEST( t.search( "abbbbbc" ) );
  }
  
  {
    // search( const char * ) const
    RegexScan t( "ab?bc" );

    TEST( t.search( "xabcy" ) );
    TEST( ! t.search( "abbq" ) );
    TEST( t.search( "xabbcy" ) );
    TEST( ! t.search( "xabbbc" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "ab?c" );

    TEST( t.search( "ac" ) );
    TEST( t.search( "\nac\n" ) );
    TEST( t.search( "xxabc" ) );
    TEST( ! t.search( "abbc" ) );
  }
    
		    
  {
    // search( const char * ) const
    RegexScan t( "ab*c" );
    
    TEST( t.search( "ac" ) );
    TEST( t.search( "abc" ) );
    TEST( t.search( "abbc" ) );      
  }

  {
    // search( const char * ) const
    
    RegexScan t( "ab*bc" );

    TEST( t.search( "abc" ) );
    TEST( t.search( "abbc" ) );
    TEST( t.search( "abbbbbc" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "a.*c" );

    TEST( t.search( "aabbxyzcdecf" ) );
    TEST( t.search( "acdefg" ) );
    TEST( ! t.search( "xxc" ) );
    TEST( ! t.search( "axx" ) );
  }

  {
    // good( void ) const

    RegexScan t( "a[]b" );

    TEST( ! t.good() );
  }

  {
    // good( void ) const
    RegexScan t( "a[b" );

    TEST( ! t.good() );
  }
      
  {
    // good( void ) const
    // search( const char * ) const
    RegexScan t( "a]b" );

    TEST( t.good() );

    TEST( t.search( "xa]b[" ) );
  }
      
  {
    // good( void ) const
    // search( const char * ) const
    RegexScan t( "a\\[b" );

    TEST( t.good() );

    TEST( t.search( "xa[b]" ) );
  }
      
  {
    // good( void ) const
    // search( const char * ) const
    // \[]
    RegexScan t( "a\\[d-f]b" );

    TEST( t.good() );

    TEST( ! t.search( "xaeb" ) );
    TEST( t.search( "xa[d-f]b" ) );
  }
      
  {
    // search( const char * ) const
    //[ccc]
    RegexScan t( "a[bc]d" );

    TEST( t.search( "abd" ) );
    TEST( t.search( "acd" ) );
    TEST( ! t.search( "abc" ) );
  }

  {
    // search( const char * ) const
    //[n-x]
    RegexScan t( "a[b-d]e" );

    TEST( t.search( "xacex" ) );
    TEST( ! t.search( "ab" ) );
    TEST( ! t.search( "acd" ) );
    TEST( ! t.search( "abd" ) );

  }

  {
    // search( const char * ) const
    //[n-x]
    RegexScan t( "a[b-d]" );

    TEST( t.search( "xac" ) );
    TEST( ! t.search( "bb" ) );
  }

  {
    // search( const char * ) const
    // [xy-]

    RegexScan t( "a[bf-]d" );

    TEST( t.search( "abde" ) );
    TEST( t.search( "xafde" ) );
    TEST( t.search( "a-d" ) );
    TEST( ! t.search( "aed" ) );
  }

  {
    // search( const char * ) const
    // [xy-]

    RegexScan t( "a[-bf]d" );

    TEST( t.search( "abde" ) );
    TEST( t.search( "xafde" ) );
    TEST( t.search( "a-d" ) );
    TEST( ! t.search( "aed" ) );
  }

  {
    // search( const char * ) const
    // []]

    RegexScan t( "a[]]b" );

    TEST( t.search( "a]b" ) );
  }

  {
    // search( const char * ) const
    //[^xx]
    RegexScan t( "a[^bcd]e" );

    TEST( t.search( "xaee" ) );
    TEST( ! t.search( "abe" ) );
  }

  {
    // search( const char * ) const
    RegexScan t( "a.c" ); 

    TEST( t.search( "abc" ) );
    TEST( t.search( "aabcc" ) );
    TEST( t.search( "xaxcx" ) );
  }

  {
    // search( const char * ) const
    // matchStart( size_t ) const
    // matchLength( size_t ) const
    
    // ()
    RegexScan t( "a(b)cd(ef.+)z" );

    TEST( t.search( "xabcdefghiz" ) );
    TEST( t.matchStart( 0 ) == 1 );
    TEST( t.matchStart( 1 ) == 2 );
    TEST( t.matchStart( 2 ) == 5 );
    TEST( t.matchLength( 2 ) == 5 );
  }

  {
    // search( const char * ) const
    // matchStart( size_t ) const
    // matchLength( size_t ) const
    
    // |
    RegexScan t( "a ((dog)|(wolf)) sleeps" );

    TEST( t.search( "a dog sleeps" ) );
    TEST( t.matchStart( 1 ) == 2 );
    TEST( t.matchLength( 1 ) == 3 );
    TEST( t.search( "a wolf sleeps" ) );
    TEST( t.matchStart( 1 ) == 2 );
    TEST( t.matchLength( 1 ) == 4 );
  }

  {
    // search( const char * ) const
    // {}
    RegexScan t("ab{2,4}c" );

    TEST( t.search( "abbc" ) );
    TEST( t.search( "abbbc" ) );
    TEST( t.search( "abbbbc" ) );
    TEST( ! t.search( "abbbbbc" ) );
    TEST( ! t.search( "abc" ) );
  }

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // getVersion( bool )

    RegexScan t("ab{2,4}c" );
    
    TEST( t.good() );
    TEST( t.error() != 0 );
    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
  }

  {
    // dumpInfo( ostream &, const char *, bool ) const
    // version
    
    RegexScan t("ab{2,4}c" );
        
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), "    ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }
    
  return( true );
}

