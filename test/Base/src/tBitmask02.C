#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Bitmask.hh>
#include <HeapBinStream.hh>
#include <strstream>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Bitmask.hh>
#include <HBinStrm.hh>
#include <strstream>
#endif

bool
tBitmask02( LibTest & tester )
{
  {
    // compare( const Bitmask & ) const
    // compare( unsigned long ) const

    const Bitmask t( Bitmask::b04 );
    const Bitmask te( Bitmask::b04 );
    const Bitmask tl( Bitmask::b03 );
    const Bitmask tm( Bitmask::b05 );

    unsigned long le = 0x10;
    unsigned long ll = 0x04;
    unsigned long lm = 0x20;

    TEST( t.compare( te ) == 0 );
    TEST( t.compare( tl ) >  0 );
    TEST( t.compare( tl ) >= 0 );
    TEST( t.compare( te ) >= 0 );
    TEST( t.compare( tm ) <  0 );
    TEST( t.compare( tm ) <= 0 );
    TEST( t.compare( te ) <= 0 );

    TEST( t.compare( le ) == 0 );
    TEST( t.compare( ll ) >  0 );
    TEST( t.compare( ll ) >= 0 );
    TEST( t.compare( le ) <= 0 );
    TEST( t.compare( lm ) <  0 );
    TEST( t.compare( lm ) <= 0 );
    TEST( t.compare( le ) <= 0 );

  }

  {
    // operator = ( unsigned long )
    // operator &= ( const Bitmask & )
    // operator |= ( const Bitmask & )
    // operator ^= ( const Bitmask & )

    Bitmask t;
    Bitmask rhs;
    
    t = 0x1080;
    TEST( (unsigned long) t == 0x1080 );

    rhs.set( 7 );
    t &= rhs;
    
    TEST( (unsigned long) t == 0x80 );

    rhs.set( 0 );
    t |= rhs;

    TEST( (unsigned long) t == 0x81 );
    rhs.reset();
    rhs.set( 7 );
    rhs.set( 15 );
    t ^= rhs;
    
    TEST( (unsigned long) t == 0x8001 );
  }

  {
    // operator ( size_t ) const
    // operator == ( const Bitmask & ) const
    // operator <  ( const Bitmask & ) const
    // operator <= ( const Bitmask & ) const
    // operator >  ( const Bitmask & ) const
    // operator >= ( const Bitmask & ) const
    // operator == ( unsigned long ) const
    // operator != ( unsigned long ) const
    // operator <  ( unsigned long ) const
    // operator <= ( unsigned long ) const
    // operator >  ( unsigned long ) const
    // operator >= ( unsigned long ) const

    const Bitmask t( Bitmask::b04 );
    const Bitmask te( Bitmask::b04 );
    const Bitmask tl( Bitmask::b03 );
    const Bitmask tm( Bitmask::b05 );

    unsigned long le = 0x10;
    unsigned long ll = 0x04;
    unsigned long lm = 0x20;

    TEST( t( 4 ) );
    TEST( ! t( 3 ) );
    TEST( ! t( 5 ) );

    TEST( t == te );
    TEST( t != tl );
    TEST( t <  tm );
    TEST( t <= tm );
    TEST( t <= te );
    TEST( t >  tl );
    TEST( t >= tl );
    TEST( t >= te );

    TEST( t == le );
    TEST( t != lm );
    TEST( t <  lm );
    TEST( t <= lm );
    TEST( t <= le );
    TEST( t >  ll );
    TEST( t >= ll );
    TEST( t >= le );
  }

  {
    // operator bool ( void ) const
    // operator unsigned long ( void ) const

    const Bitmask t1;
    const Bitmask t2( Bitmask::b03 );

    TEST( ! t1 );
    TEST( t2 );

    TEST( (unsigned long)t1  == 0UL );
    TEST( (unsigned long)t2 == 0x08 );
  }

  {
    // getBinSize( void ) const
    // write( BinStream & dest ) const
    // read( BinStream & src )
    // BinStream::write( const BinObject & obj )
    // BinStream::read( BinObject & obj )

    HeapBinStream tStrm;

    const Bitmask   tw( 9 );
    Bitmask	    tr(5);

    TEST( tw.getBinSize() );

    tw.write( tStrm );
    tr.read( tStrm );

    TEST( tStrm.good() );
    TEST( (size_t)tStrm.tellp() == tw.getBinSize() );
    TEST( tStrm.tellg() == tStrm.tellp() );
    TEST( tr.getBinSize() == tw.getBinSize() );
    TEST( tw == tr );

    tr = 0xff;
    TEST( tw != tr );
    
    tStrm.write( tw );
    tStrm.read( tr );

    TEST( tr == tw );
  }

  {
    // write( ostream & ) const
    // read( istream & )

    const Bitmask   tw(9);
    Bitmask	    tr(5);

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

    const Bitmask   t(9);
    strstream tStrm;

    t.toStream( tStrm );
    tStrm << t;
  }
    
  {
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    const Bitmask t(2);

    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( false ) != 0 );
    
  }

  {
    // dumpInfo( ostream & ) const
    // version

    const Bitmask t(4);

    tester.getDump() << '\n' << t.getClassName() << " toStream:\n";
    t.toStream( tester.getDump() );
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }
    
    
  return( true );
}
