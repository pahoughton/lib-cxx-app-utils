#include <LibTest.hh>
#include <Bitmask.hh>

#include <strstream>

bool
tBitmask02( LibTest & test )
{
  {
    // compare( const Bitmask & ) const
    // compare( unsigned long ) const

    const Bitmask t( 4 );
    const Bitmask te( 4 );
    const Bitmask tl( 3 );
    const Bitmask tm( 5 );

    unsigned long le = 0x10;
    unsigned long ll = 0x04;
    unsigned long lm = 0x20;

    test( t.compare( te ) == 0 );
    test( t.compare( tl ) > 0 );
    test( t.compare( tm ) < 0 );

    test( t.compare( le ) == 0 );
    test( t.compare( ll ) > 0 );
    test( t.compare( lm ) < 0 );

  }

  {
    // operator = ( unsigned long )
    // operator &= ( const Bitmask & )
    // operator |= ( const Bitmask & )
    // operator ^= ( const Bitmask & )

    Bitmask t;
    Bitmask rhs;
    
    t = 0x1080;
    test( (unsigned long) t == 0x1080 );

    rhs.set( 7 );
    t &= rhs;
    
    test( (unsigned long) t == 0x80 );

    rhs.set( 0 );
    t |= rhs;

    test( (unsigned long) t == 0x81 );
    rhs.clear();
    rhs.set( 7 );
    rhs.set( 15 );
    t ^= rhs;
    
    test( (unsigned long) t == 0x8001 );
  }

  {
    // operator ( size_t ) const
    // operator == ( const Bitmask & ) const
    // operator <  ( const Bitmask & ) const
    // operator >  ( const Bitmask & ) const
    // operator == ( unsigned long ) const
    // operator != ( unsigned long ) const
    // operator <  ( unsigned long ) const
    // operator >  ( unsigned long ) const

    const Bitmask t( 4 );
    const Bitmask te( 4 );
    const Bitmask tl( 3 );
    const Bitmask tm( 5 );

    unsigned long le = 0x10;
    unsigned long ll = 0x04;
    unsigned long lm = 0x20;

    test( t( 4 ) );
    test( ! t( 3 ) );
    test( ! t( 5 ) );

    test( t == te );
    test( t != tl );
    test( t < tm );
    test( t > tl );

    test( t == le );
    test( t != lm );
    test( t <  lm );
    test( t >  ll );
  }

  {
    // operator bool ( void ) const
    // operator unsigned long ( void ) const

    const Bitmask t1;
    const Bitmask t2( 3 );

    test( ! t1 );
    test( t2 );

    test( (unsigned long)t1  == 0UL );
    test( (unsigned long)t2 == 0x08 );
  }

  {
    // getClassName( void ) const;
    // toStream( ostream & ) const
    // dumpInfo( ostream & ) const
    // maxPos
    // version
    
    strstream tStream;
    
    const Bitmask t( 2 );

    test( t.getClassName() != 0 );
    t.toStream( tStream );
    t.dumpInfo( tStream );

    test( t.maxPos > 0 );
    test( t.version != 0 );
  }
  
    
  return( true );
}
