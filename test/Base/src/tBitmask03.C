#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Bitmask.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Bitmask.hh>
#endif

bool
tBitmask03( LibTest & tester )
{
  {
    // ::operator & ( const Bitmask &, const Bitmask & )
    // ::operator | ( const Bitmask &, const Bitmask & )
    // ::operator ^ ( const Bitmask &, const Bitmask & )
    // ::operator ~ ( const Bitmask & )

    const Bitmask   t1( 2 );
    const Bitmask   t2( 4 );
    const Bitmask   t3( 8 );

    TEST( (unsigned long) (t1 & t2) == 0x00 );
    TEST( (unsigned long) (t1 & t1) == (unsigned long) t1 );
    TEST( (unsigned long) (t1 | t2 ) == 0x14 );
    TEST( (unsigned long) (t1 | t1 ) == 0x04 );
    TEST( (unsigned long) (t1 ^ t3 ) == 0x104 );
    TEST( (unsigned long) (t2 ^ t2 ) == 0x00 );
    TEST( (unsigned long) (~t1) == 0xfffffffb );
    
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

    TEST( compare( t, te ) == 0 );
    TEST( compare( t, tl ) > 0 );
    TEST( compare( t, tm ) < 0 );

    TEST( compare( t, le ) == 0 );
    TEST( compare( t, ll ) > 0 );
    TEST( compare( t, lm ) < 0 );
    
    TEST( compare( le, t ) == 0 );
    TEST( compare( ll, t ) < 0 );
    TEST( compare( lm, t ) > 0 );

    TEST( le == t );
    TEST( le != tl );
    TEST( le < tm );
    TEST( le > tl );
  }

  return( true );
  
}
