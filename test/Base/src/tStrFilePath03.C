#include <LibTest.hh>
#include <FilePath.hh>

#define P   "dir"
#define F   "filename"
#define E   "ext"
#define DD  "/"
#define DE  "."

bool
tFilePath03( LibTest & test )
{
  {
    // setFileName( const char * )
    // setName( const char * )
    // setPath( const char * )
    // setName( const char *, char )
    // setName( const char *, const char * )
    // setExt( const char * )
    // setExt( const char *, char )
    // setExt( const char *, const char * )
    
    
    FilePath t('/','-');

    t.setFileName( F "-" E );
    test( compare( t.getFullName(), F "-" E ) == 0 );

    t.setName( "fn" );
    test( compare( t.getFullName(), "fn" "-" E ) == 0 );

    t.setPath( "dir" );
    test( compare( t.getFullName(), "dir" "/" "fn" "-" E ) == 0 );

    t.setFileName( F "." "a" "-" "b" );
    test( compare( t.getFullName(), "dir" "/" F "." "a" "-" "b" ) == 0 );

    t.setName( "FN", '.' );
    test( compare( t.getFullName(), "dir" "/" "FN" "." "a" "-" "b" ) == 0 );
	  
    t.setName( "file", ".a-b" );
    test( compare( t.getFullName(), "dir" "/" "file" "." "a" "-" "b" ) == 0 );

    t.setExt( "bak" );
    test( compare( t.getFullName(), "dir" "/" "file" "." "a" "-" "bak" ) == 0 );

    t.setFileName( "file" "-" "bak" "." "exe" );
    test( compare( t.getFullName(), "dir" "/" "file" "-" "bak" "." "exe" ) == 0 );

    t.setExt( "o", '.' );
    test( compare( t.getFullName(), "dir" "/" "file" "-" "bak" "." "o" ) == 0 );

    t.setExt( "ak.o", "rown" );
    test( compare( t.getFullName(), "dir" "/" "file" "-" "brown" ) == 0 );
  }
  
  {
    // getStreamSize( void ) const
    // write( void ) const
    // read( void ) const

    const FilePath  tout( ":usr:src","libClue.a", '/','.' );
    FilePath	    tin;

    strstream testStream;

    streampos gpos = testStream.tellg();
    streampos ppos = testStream.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    test( ppos == 0 );
    test( gpos == 0 );
    
    tout.write( testStream );
    ppos += tout.getStreamSize();
    test( ppos == testStream.tellp() );
      
    tin.read( testStream );
    gpos += tin.getStreamSize();
    test( gpos == testStream.tellg() );
    test( tin == tout );
  }
    
  return( true );
}

    
