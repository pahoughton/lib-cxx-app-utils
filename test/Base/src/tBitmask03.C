#include <LibTest.hh>
#include <Bitmask.hh>

#include <strstream>

bool
tBitmask03( LibTest & test )
{
  {
    // ::operator & ( const Bitmask &, const Bitmask & )
    // ::operator | ( const Bitmask &, const Bitmask & )
    // ::operator ^ ( const Bitmask &, const Bitmask & )
    // ::operator ~ ( const Bitmask & )

    const Bitmask   t1( 2 );
    const Bitmask   t2( 4 );
    const Bitmask   t3( 8 );

    test( (unsigned long) (t1 & t2) == 0x00 );
    test( (unsigned long) (t1 & t1) == (unsigned long) t1 );
    test( (unsigned long) (t1 | t2 ) == 0x14 );
    test( (unsigned long) (t1 | t1 ) == 0x04 );
    test( (unsigned long) (t1 ^ t3 ) == 0x104 );
    test( (unsigned long) (t2 ^ t2 ) == 0x00 );
    test( (unsigned long) (~t1) == 0xfffffffb );
    
  }

  {
    // ::compare( const Bitmask &, const Bitmask & )
    // ::compare( const Bitmask &, unsigned long )
    // ::compare( unsigned long, const Bitmask & )
    // ::operator == ( unsigned long, const Bitmask & )
    // ::operator != ( unsigned long, const Bitmask & )
    // ::operator <  ( unsigned long, const Bitmask & )
    // ::operator >  ( unsigned long, const Bitmask & )

    const Bitmask t( 4 );
    const Bitmask te( 4 );
    const Bitmask tl( 3 );
    const Bitmask tm( 5 );

    unsigned long le = 0x10;
    unsigned long ll = 0x04;
    unsigned long lm = 0x20;

    test( compare( t, te ) == 0 );
    test( compare( t, tl ) > 0 );
    test( compare( t, tm ) < 0 );

    test( compare( t, le ) == 0 );
    test( compare( t, ll ) > 0 );
    test( compare( t, lm ) < 0 );
    
    test( compare( le, t ) == 0 );
    test( compare( ll, t ) < 0 );
    test( compare( lm, t ) > 0 );

    test( le == t );
    test( le != tl );
    test( le < tm );
    test( le > tl );
  }

  {
    // ::operator << ( ostream &, const Bitmask & )

    const Bitmask t(5);

    strstream tStream;

    tStream << t;
  }
  
  return( true );
  
}
