#include <TestConfig.hh>
#include <LibTest.hh>
#include <FilePath.hh>
#include <Compare.hh>


#define D   "dir"
#define F   "filename"
#define E   "ext"
#define DD  "/"
#define DE  "."

bool
tFilePath02( LibTest & tester )
{
  {
    // getPath( void ) const
    // getFileName( void ) const
    // getName( void ) const
    // getExt( void ) const

    FilePath	t( D DD F DE E );

    TEST( compare( t.getPath().c_str(), D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE E ) == 0 );
    TEST( compare( t.getName().c_str(), F ) == 0 );
    TEST( compare( t.getExt().c_str(), E ) == 0 );
  }
  
  {
    FilePath	t( D DD D DD D DD F DE E );

    TEST( compare( t.getPath().c_str(), D DD D DD D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE E ) == 0 );
    TEST( compare( t.getName().c_str(), F ) == 0 );
    TEST( compare( t.getExt().c_str(), E ) == 0 );
  }
  
  {
    FilePath	t( D DD D DD D DD F DE "abc" DE E );

    TEST( compare( t.getPath().c_str(), D DD D DD D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE "abc" DE E ) == 0 );
    TEST( compare( t.getName().c_str(), F DE "abc" ) == 0 );
    TEST( compare( t.getExt().c_str(), E ) == 0 );
  }

  {
    // set( const char * )
    
    FilePath	t( D DD F DE E );

    t.set( D DD D DD D DD F DE "abc" DE E );

    TEST( compare( t.getPath().c_str(), D DD D DD D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE "abc" DE E ) == 0 );
    TEST( compare( t.getName().c_str(), F DE "abc" ) == 0 );
    TEST( compare( t.getExt().c_str(), E ) == 0 );
  }

  {
    // expand( void ) 70% tested

    FilePath	t( "~/afile" );

    TEST( t.expand() );

    Str expect( getenv( "HOME" ) );

    TEST( expect.size() > 1 );
    
    expect << "/afile";
		
    TESTR( t.getFullName().c_str(),
	   compare( t.getFullName().c_str(), expect.c_str() ) == 0 );

    TEST( ! putenv( (char *)"FP_EMTPY=" ) );
    TEST( ! putenv( (char *)"FP_1=fp_one" ) );
    TEST( ! putenv( (char *)"FP_2=fp_two" ) );
    TEST( ! putenv( (char *)"FP_3=fp_three" ) );

    t.set( "~" TEST_USER "/afile" );
    TESTR( t.c_str(), t.expand() );
    
    TESTR( t.getFullName().c_str(),
	   compare( t.getFullName().c_str(), expect.c_str() ) == 0 );

    TEST( getenv( "FP_1" ) && strlen( getenv( "FP_1" ) ) );
    
    t.set( "ab/$FP_1/${FP_2}${FP_EMPTY}${FP_3}/$FP_1$F$FP_JUNK/$FP_3$FP_1" );
    expect.assign( "ab/fp_one/fp_twofp_three/fp_one/fp_threefp_one" );
    TESTR( t.c_str(), t.expand() );
    TESTR( t.getFullName().c_str(),
	   compare( t.getFullName().c_str(), expect.c_str() ) == 0 );

    TEST( ! putenv( "FP_USER=" TEST_USER ) );
    t.set( "~$FP_USER/afile" );

    expect.assign( getenv( "HOME" ) );
    expect << "/afile";

    TEST( t.expand() );
    TESTR( t.getFullName().c_str(),
	   compare( t.getFullName().c_str(), expect.c_str() ) == 0 );
  }
		   
  {
    // setPrefix( const char * )

    FilePath	t( D DD F DE E );

    t.setPrefix( D );

    TEST( compare( t.getPath().c_str(), D DD D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE E ) == 0 );

    t.setPrefix( D DE );
    TEST( compare( t.getPath().c_str(), D DE DD D DD D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE E ) == 0 );
  }
  
  {
    // setPath( const char * )
    FilePath t( D DD D DD F );

    t.setPath( D );

    TEST( compare( t.getFullName().c_str(), D DD F ) == 0 );
    TEST( compare( t.getPath().c_str(), D ) == 0 );    
  }

  {
    // setPath( const char * )
    FilePath t( D DD D DD F );

    t.setPath( D DD );

    TEST( compare( t.getFullName().c_str(), D DD F ) == 0 );
    TEST( compare( t.getPath().c_str(), D ) == 0 );    
  }

  {
    // setPath( const char * )
    FilePath t( F );

    t.setPath( D );

    TEST( compare( t.getFullName().c_str(), D DD F ) == 0 );
    TEST( compare( t.getPath().c_str(), D ) == 0 );    
  }

  {
    // changePath( const char *, const char * )

    FilePath t( "d1/d2/d3/d4/filename" );

    TEST( t.changePath( "d2/d3", "other" ) );

    TEST( compare( t.getFullName().c_str(), "d1/other/d4/filename" ) == 0 );

    TEST( t.changePath( "d1/", "/new/base/" ) );
    
    TESTR( t.getFullName().c_str(),
	   compare( t.getFullName().c_str(), "/new/base/other/d4/filename" )
	  == 0 );

    TEST( ! t.changePath( "notfound", "xxxxxxxxxx" ) );
    
    TESTR( t.getFullName().c_str(),
	   compare( t.getFullName().c_str(), "/new/base/other/d4/filename" )
	  == 0 );

  }

  return( true );
}

    
    
    
