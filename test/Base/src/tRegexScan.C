//
// File:        tRegexScan.C
// Project:	StlUtils
// Desc:        
//
//  Test for RegexScan class.
//
// Source Header Version: 2.5
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     11/03/96 07:01
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <RegexScan.hh>
#include <cstring>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <RxScan.hh>
#endif

#define T_CLASS_NAME	"RegexScan"

bool
tRegexScan( LibTest & tester )
{
  {
    // RegexScan( const char * )
    // good( void ) const
    // match( const char * ) const
    // match( const char *, size_t ) const
    // matchCount( void ) const
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
    TEST( t.matchCount() == 0 );
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
    // .
    RegexScan t( "a.c" ); 

    TEST( t.search( "abc" ) );
    TEST( t.search( "aabcc" ) );
    TEST( t.search( "xaxcx" ) );
  }

  {
    // search( const char * ) const
    // *
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
    // search( const char * ) const
    // +
    RegexScan t( "ab+bc" );

    TEST( ! t.search( "abc" ) );
    TEST( ! t.search( "abbq" ) );
    TEST( t.search( "abbbbbc" ) );
  }
  
  {
    // search( const char * ) const
    // ?
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
    //[:alpha:]
    RegexScan	t( "1[[:alpha:]]3" );

    TEST( t.search( "1z3" ) );
    TEST( t.search( "1G3" ) );
    TEST( ! t.search( "1 3" ) );
  }

  {
    // search( const char * ) const
    //[:upper:]

    RegexScan t( "a[[:upper:]]c" );

    TEST( t.search( "aBc" ) );
    TEST( ! t.search( "abc" ) );
    TEST( ! t.search( "a1c" ) );
    TEST( ! t.search( "a c" ) );
  }

  {
    // search( const char * ) const
    //[:lower:]

    RegexScan t( "a[[:lower:]]c" );

    TEST( t.search( "abc" ) );
    TEST( ! t.search( "aBc" ) );
    TEST( ! t.search( "a1c" ) );
    TEST( ! t.search( "a c" ) );
  }

  {
    // search( const char * ) const
    //[:digit:]

    RegexScan t( "a[[:digit:]]c" );

    TEST( t.search( "a2c" ) );
    TEST( ! t.search( "abc" ) );
    TEST( ! t.search( "aBc" ) );
    TEST( ! t.search( "a c" ) );
  }

  {
    // search( const char * ) const
    //[:alnum:]

    RegexScan t( "a[[:alnum:]]c" );

    TEST( t.search( "a2c" ) );
    TEST( t.search( "abc" ) );
    TEST( t.search( "aBc" ) );
    TEST( ! t.search( "a c" ) );
  }

  {
    // search( const char * ) const
    //[:xdigit:]

    RegexScan t( "a[[:xdigit:]]c" );

    TEST( t.search( "a2c" ) );
    TEST( t.search( "abc" ) );
    TEST( t.search( "aBc" ) );
    TEST( ! t.search( "aGc" ) );
    TEST( ! t.search( "a c" ) );
  }

  {
    // search( const char * ) const
    //[:space:]

    RegexScan t( "a[[:space:]]c" );

    TEST( t.search( "a c" ) );
    TEST( t.search( "a\tc" ) );
    TEST( ! t.search( "a2c" ) );
    TEST( ! t.search( "abc" ) );
    TEST( ! t.search( "aBc" ) );
    TEST( ! t.search( "aGc" ) );
  }

  {
    // search( const char * ) const
    //[:blank:]

    RegexScan t( "a[[:blank:]]c" );

    TEST( t.search( "a c" ) );
    TEST( t.search( "a\tc" ) );
    TEST( ! t.search( "a2c" ) );
    TEST( ! t.search( "abc" ) );
    TEST( ! t.search( "aBc" ) );
    TEST( ! t.search( "aGc" ) );
  }

  {
    // search( const char * ) const
    //[:print:]

    RegexScan t( "a[[:print:]]c" );

    TEST( t.search( "a c" ) );
    TEST( t.search( "a2c" ) );
    TEST( t.search( "abc" ) );
    TEST( t.search( "aBc" ) );
    TEST( ! t.search( "a\tc" ) );
    TEST( ! t.search( "a\177c" ) );
  }

  {
    // search( const char * ) const
    //[:punct:]

    RegexScan t( "a[[:punct:]]c" );

    TEST( t.search( "a.c" ) );
    TEST( t.search( "a,c" ) );
    TEST( ! t.search( "a c" ) );
    TEST( ! t.search( "a\tc" ) );
    TEST( ! t.search( "a2c" ) );
    TEST( ! t.search( "abc" ) );
    TEST( ! t.search( "aBc" ) );
  }

  {
    // search( const char * ) const
    //[:graph:]

    RegexScan t( "a[[:graph:]]c" );

    TEST( t.search( "adc" ) );
    TEST( t.search( "a2c" ) );
    TEST( t.search( "abc" ) );
    TEST( t.search( "aBc" ) );
    TEST( ! t.search( "a c" ) );
    TEST( ! t.search( "a\tc" ) );
  }

  {
    // search( const char * ) const
    //[:cntrl:]

    RegexScan t( "a[[:cntrl:]]c" );

    TEST( t.search( "a\005c" ) );
    TEST( t.search( "a\tc" ) );
    TEST( ! t.search( "a c" ) );
    TEST( ! t.search( "a2c" ) );
    TEST( ! t.search( "abc" ) );
    TEST( ! t.search( "aBc" ) );
  }
	  
  {
    // search( const char * ) const
    //[::]
    RegexScan	t( " [[:lower:][:digit:]]" );

    TEST( t.search( " p " ) );
    TEST( t.search( " 5 " ) );
    TEST( ! t.search( " H " ) );
    TEST( ! t.search( "   " ) );
    TEST( ! t.search( " . " ) );
  }

  {
    // search( const char * ) const
    // ^
    RegexScan t( "^abc" );

    TEST( t.search( "abcdefg" ) );
    TEST( ! t.search( " abc" ) );
    TEST( ! t.search( "aabc" ) );
  }

  {
    // search( const char * ) const
    // $
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
    // \ char
    
    RegexScan t( "a\\.c" );

    TEST( t.search( "a.c" ) );
    TEST( ! t.search( "abc" ) );
  }

  {
    // search( const char * ) const
    // |
    RegexScan t( "abc|de*f" );

    TEST( t.search( "abc" ) );
    TEST( t.search( "df" ) );
    TEST( t.search( "deeef" ) );
    TEST( t.search( "dffff" ) );
    TEST( t.search( "abcxyx" ) );
    TEST( ! t.search( "dxf" ) );
  }
  
  {
    // search( const char * ) const
    // matchStart( size_t ) const
    // matchLength( size_t ) const
    
    // ()
    RegexScan t( "a(b)cd(ef.+)z" );

    TEST( t.search( "xabcdefghiz" ) );
    TEST( t.matchCount() == 2 );
    TEST( t.matchStart( 0 ) == 1 );
    TEST( t.matchStart( 1 ) == 2 );
    TEST( t.matchStart( 2 ) == 5 );
    TEST( t.matchLength( 2 ) == 5 );
  }

  {
    // search( const char * ) const
    // matchStart( size_t ) const
    // matchLength( size_t ) const
    
    RegexScan t( "a ((dog)|(wolf)) sleeps" );

    TEST( t.search( "a dog sleeps" ) );
    TEST( t.matchCount() == 3 );
    TEST( t.matchStart( 1 ) == 2 );
    TEST( t.matchLength( 1 ) == 3 );
    TEST( t.search( "a wolf sleeps" ) );
    TEST( t.matchStart( 1 ) == 2 );
    TEST( t.matchLength( 1 ) == 4 );
  }

  {
    // search( const char * ) const
    // \DIGIT

    RegexScan t( "(de.) \\1" );

    TEST( t.search( "def def" ) );
    TEST( ! t.search( "def dee" ) );
  }

  {
    // search( const char * ) const
    // {n}
    RegexScan t("ab{2}c" );

    TEST( t.search( "abbc" ) );
    TEST( ! t.search( "abbbc" ) );
    TEST( ! t.search( "abbbbc" ) );
    TEST( ! t.search( "abbbbbc" ) );
    TEST( ! t.search( "abc" ) );
  }

  {
    // search( const char * ) const
    // {n,}
    RegexScan t("ab{2,}c" );

    TEST( t.search( "abbc" ) );
    TEST( t.search( "abbbc" ) );
    TEST( t.search( "abbbbc" ) );
    TEST( t.search( "abbbbbc" ) );
    TEST( ! t.search( "abc" ) );
  }

  {
    // search( const char * ) const
    // {,m}
    RegexScan t("ab{,4}c" );

    TEST( t.search( "ac" ) );
    TEST( t.search( "abc" ) );
    TEST( t.search( "abbc" ) );
    TEST( t.search( "abbbc" ) );
    TEST( t.search( "abbbbc" ) );
    TEST( ! t.search( "abbbbbc" ) );
  }

  {
    // search( const char * ) const
    // {n,m}
    RegexScan t("ab{2,4}c" );

    TEST( t.search( "abbc" ) );
    TEST( t.search( "abbbc" ) );
    TEST( t.search( "abbbbc" ) );
    TEST( ! t.search( "abbbbbc" ) );
    TEST( ! t.search( "abc" ) );
  }

  {
    // search( const char * ) const
    // \b

    RegexScan t( "\\babc" );

    TEST( t.search( "abc" ) );
    TEST( t.search( "xxx abc" ) );
    TEST( ! t.search( "dabc" ) );
  }

  {
    // search( const char * ) const
    // \B

    RegexScan t( "abc\\B" );

    TEST( t.search( " abcx" ) );
    TEST( ! t.search( "abc" ) );
    TEST( ! t.search( "abc xxx" ) );
    TEST( ! t.search( "xxx abc" ) );
  }
  
  {
    // search( const char * ) const
    // \<

    RegexScan t( "\\<abc" );
    
    TEST( t.search( "abc" ) );
    TEST( t.search( "xxx abc" ) );
    TEST( ! t.search( "dabc" ) );
  }

  {
    // search( const char * ) const
    // \>

    RegexScan t( "abc\\>" );
    
    TEST( t.search( "abc" ) );
    TEST( t.search( "abc xxx" ) );
    TEST( t.search( "xxx abc" ) );
    TEST( ! t.search( " abcx" ) );
  }

  {
    // search( const char * ) const
    // \w

    RegexScan t( " \\w\\w\\w " );

    TEST( t.search( " def " ) );
    TEST( t.search( " d1f " ) );
    TEST( ! t.search( " d.f " ) );
    TEST( ! t.search( " d f " ) );
  }

  {
    // search( const char * ) const
    // \W

    RegexScan t( ".\\W." );

    TEST( t.search( "   " ) );
    TEST( t.search( " . " ) );
    TEST( t.search( " ; " ) );
    TEST( ! t.search( " 1 " ) );
    TEST( ! t.search( " a " ) );
    TEST( ! t.search( " D " ) );
    TEST( ! t.search( " Z " ) );
  }
    
  {
    // good( void ) const

    RegexScan t( "a[]b" );

    TEST( ! t.good() );
  }

  {
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
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    
    const RegexScan t(".*");

    TEST( ! strcmp( t.getClassName(), T_CLASS_NAME ) );

    TEST( strstr( t.getVersion(), "@(#) libStlUtils - " ) != 0 );
    TEST( strstr( t.getVersion(), T_CLASS_NAME ) != 0 );
    TEST( strstr( t.getVersion(), "Compiled: " ) != 0 );
    
    TEST( strstr( t.getVersion(true), "@(#) libStlUtils - " ) != 0 );
    TEST( strstr( t.getVersion(true), T_CLASS_NAME ) != 0 );
    TEST( strstr( t.getVersion(true), "Compiled: " ) != 0 );
    
    TEST( strstr( t.getVersion(false), "@(#) libStlUtils - " ) == 0 );
    TEST( strstr( t.getVersion(false), T_CLASS_NAME ) != 0 );
    TEST( strstr( t.getVersion(false), "Compiled: " ) != 0 );

  }
  
  {
    // dumpInfo( ostream & ) const

    const RegexScan t("ab{2,4}c" );
        
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    
    tester.getDump() << '\n' << tester.getCurrentTestName();    
  }
    
  {
    // static const ClassVersion version

    TEST( strstr( RegexScan::version.getVer(true), "@(#) libStlUtils - " ) != 0 );
    TEST( strstr( RegexScan::version.getVer(true), T_CLASS_NAME ) != 0 );
    TEST( strstr( RegexScan::version.getVer(true), "Compiled: " ) != 0 );
    
    TEST( strstr( RegexScan::version.getVer(true), "@(#) libStlUtils - " ) != 0 );
    TEST( strstr( RegexScan::version.getVer(true), T_CLASS_NAME ) != 0 );
    TEST( strstr( RegexScan::version.getVer(true), "Compiled: " ) != 0 );
    
    TEST( strstr( RegexScan::version.getVer(false), "@(#) libStlUtils - " ) == 0 );
    TEST( strstr( RegexScan::version.getVer(false), T_CLASS_NAME ) != 0 );
    TEST( strstr( RegexScan::version.getVer(false), "Compiled: " ) != 0 );
    
  }

  return( true );
}


//
// $Log$
// Revision 6.1  2003/08/09 11:22:51  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:29  houghton
// Changed Version Num to 5
//
// Revision 4.2  1998/10/13 16:40:50  houghton
// Cleanup.
//
// Revision 4.1  1997/09/17 15:14:29  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:09:56  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/03/03 19:11:01  houghton
// Changed for port to AIX41.
//
// Revision 3.1  1996/11/14 01:26:53  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:50:42  houghton
// Added header comments.
// Chagned to test everything in RegexScan.hh.
//
//
