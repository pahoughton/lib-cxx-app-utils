#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <FilePath.hh>
#include <HeapBinStream.hh>
#include <strstream>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <FilePath.hh>
#include <HBinStrm.hh>
#include <strstream>
#endif

bool
tFilePath04( LibTest & tester )
{
  {
    // getBinSize( void ) const
    // write( BinStream & dest ) const
    // read( BinStream & src )
    // BinStream::write( const BinObject & obj )
    // BinStream::read( BinObject & obj )

    HeapBinStream tStrm;

    const FilePath  tw( ":usr:src","libClue.a", '/','.' );
    FilePath	    tr;

    TEST( tw.getBinSize() );

    tw.write( tStrm );
    tr.read( tStrm );

    TEST( tStrm.good() );
    TEST( (size_t)tStrm.tellp() == tw.getBinSize() );
    TEST( tStrm.tellg() == tStrm.tellp() );
    TEST( tr.getBinSize() == tw.getBinSize() );
    TEST( tw == tr );

    tr = "different";
    TEST( tw != tr );
    
    tStrm.write( tw );
    tStrm.read( tr );

    TEST( tr == tw );
  }

  {
    // write( ostream & ) const
    // read( istream & )

    const FilePath  tw( ":usr:src","libClue.a", '/','.' );
    FilePath	    tr;

    strstream tStrm;

    streampos gpos = tStrm.tellg();
    streampos ppos = tStrm.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    TEST( ppos == 0 );
    TEST( gpos == 0 );
    
    tw.write( tStrm );
    ppos += tw.getBinSize();
    TEST( ppos == tStrm.tellp() );
      
    tr.read( tStrm );
    gpos += tr.getBinSize();
    TEST( gpos == tStrm.tellg() );
    TEST( tr == tw );
  }

  {
    // toStream( ostream & ) const
    // operator << ( ostream &, const FilePath & )

    strstream tStrm;
    const FilePath  t( ":usr:src","libClue.a", '/','.' );

    t.toStream( tStrm );
    tStrm << t;
  }
    
  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    const FilePath	t( ":usr:src", "test.c", ':' );

    TESTR( t.error(), t.good() );
    TEST( t.error() != 0 );
    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( false ) != 0 );
    
  }

  {
    // dumpInfo( ostream & ) const
    // version

    const FilePath t( "/usr/local/lib", "libClue.a" );

    tester.getDump() << '\n' << t.getClassName() << " toStream:\n";
    t.toStream( tester.getDump() );
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }
    
  {
    // ::compare( const FilePath &, const FilePath & );
    
    const FilePath l( "dir/test.oper" );
    const FilePath re( "dir/test.oper" );
    const FilePath rl( "c/test.oper" );
    const FilePath rm( "e/test" );

    TEST( compare( l, re ) == 0 );
    TEST( compare( l, rm ) < 0 );
    TEST( compare( l, rl ) > 0 );
  }
  
  return( true );
}
