#include <LibTest.hh>
#include <FilePath.hh>

#include <strstream>

bool
tFilePath04( LibTest & test )
{
  {
    // compare( const FilePath & ) const
    // operator == ( const FilePath & ) const
    // operator <  ( const FilePath & ) const
    // operator >  ( const FilePath & ) const

    const FilePath l( "dir/test.oper" );
    const FilePath re( "dir/test.oper" );
    const FilePath rl( "c/test.oper" );
    const FilePath rm( "e/test" );

    test( l.compare( re ) == 0 );
    test( l == re );
    test( ! ( l == rl ) );

    test( l.compare( rm ) < 0 );
    test( l < rm );
    test( ! ( l < rl ) );

    test( l.compare( rl ) > 0 );
    test( l > rl );
    test( ! ( l > rm ) );
    
  }

  {
    // operator const char * ( void ) const

    FilePath	t( ":usr:src", "test.c", ':' );

    test( strcmp( ":usr:src:test.c", t ) == 0 );
  }

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // toStream( ostream & ) const
    // dumpInfo( ostream & ) const
    // version

    const FilePath	t( ":usr:src", "test.c", ':' );

    test( t.good() );
    test( t.error() != 0 );
    test( t.getClassName() != 0 );

    strstream tStream;

    t.toStream( tStream );
    t.dumpInfo( tStream );

    test( t.version != 0 );
  }

  {
    // ::compare( const FilePath &, const FilePath & );
    
    const FilePath l( "dir/test.oper" );
    const FilePath re( "dir/test.oper" );
    const FilePath rl( "c/test.oper" );
    const FilePath rm( "e/test" );

    test( compare( l, re ) == 0 );
    test( compare( l, rm ) < 0 );
    test( compare( l, rl ) > 0 );
  }
  
  return( true );
}
