/* 1996-10-30 (cc) <paul4hough@gmail.com>

   Test the following Bitmask methods.

    bit::flip( void )
    bit::pos( void );
    bit::operator = ( bool rhs );
    bit::operator = ( const bit & )
    bit::operator ~ ( void ) const
    bit::operator bool ( void ) const
    ::operator & ( const Bitmask &, const Bitmask & )
    ::operator | ( const Bitmask &, const Bitmask & )
    ::operator ^ ( const Bitmask &, const Bitmask & )
    ::operator ~ ( const Bitmask & )
    ::compare( const Bitmask &, const Bitmask & )
    ::compare( const Bitmask &, unsigned long )
    ::compare( unsigned long, const Bitmask & )
    ::operator == ( unsigned long, const Bitmask & )
    ::operator != ( unsigned long, const Bitmask & )
    ::operator <  ( unsigned long, const Bitmask & )
    ::operator <= ( unsigned long, const Bitmask & )
    ::operator >  ( unsigned long, const Bitmask & )
    ::operator >= ( unsigned long, const Bitmask & )
*/

#include <clue/bitmask>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::bitmask03");
using namespace clue;

bool
v_bitmask03( void )
{
  {
    // bit::flip( void )

    Bitmask t( 0x1248 );

    TEST( ! t(3).flip() );
    TEST( t(3).flip() );
    TEST( t(3).flip().pos() == 3 );
  }

  {
    // bit::pos( void );

    Bitmask t( 0x24 );

    for( unsigned int p = 0 ; p < 30; p++ )
      {
	TEST( t[p].pos() == p );
      }

  }

  {
    // bit::operator = ( bool rhs );

    Bitmask t( 0x12481248 );

    TEST( ! t.test(16) );

    t(16) = true;
    TEST( t(16) );
    TEST( t.test( 16 ) );
  }


  {
    // bit::operator = ( const bit & )

    Bitmask t( 0x1234 );
    Bitmask s( 0xff00 );

    TEST( ! t.test(0) );
    t(0) = s(8);
    TEST( t.test(0) );
    t(2) = s(1);
    TEST( t.to_ulong() == 0x1231 );
  }

  {
    // bit::operator ~ ( void ) const

    Bitmask t( 0x1248 );

    TEST( t( 3 ) );
    TEST(! t(2) );
    TEST( ! ~t(3) );
    TEST( ~t(2) );
    TEST( t.to_ulong() == 0x1248 );
  }

  {
    // bit::operator bool ( void ) const

    Bitmask t( 0x1248 );

    TEST( ! t[2] );
    TEST( t[3] );
  }


  {
    // ::operator & ( const Bitmask &, const Bitmask & )
    // ::operator | ( const Bitmask &, const Bitmask & )
    // ::operator ^ ( const Bitmask &, const Bitmask & )
    // ::operator ~ ( const Bitmask & )

    const Bitmask   t1( Bitmask::b02 );
    const Bitmask   t2( Bitmask::b04 );
    const Bitmask   t3( Bitmask::b08 );

    TEST( (unsigned int) (t1 & t2) == 0x00 );
    TEST( (unsigned int) (t1 & t1) == (unsigned int) t1 );
    TEST( (unsigned int) (t1 | t2 ) == 0x14 );
    TEST( (unsigned int) (t1 | t1 ) == 0x04 );
    TEST( (unsigned int) (t1 ^ t3 ) == 0x104 );
    TEST( (unsigned int) (t2 ^ t2 ) == 0x00 );
    TEST( (unsigned int) (~t1) == 0xfffffffb );

  }

  {
    // ::compare( const Bitmask &, const Bitmask & )
    // ::compare( const Bitmask &, unsigned long )
    // ::compare( unsigned long, const Bitmask & )
    // ::operator == ( unsigned long, const Bitmask & )
    // ::operator != ( unsigned long, const Bitmask & )
    // ::operator <  ( unsigned long, const Bitmask & )
    // ::operator <= ( unsigned long, const Bitmask & )
    // ::operator >  ( unsigned long, const Bitmask & )
    // ::operator >= ( unsigned long, const Bitmask & )

    const Bitmask t( Bitmask::b04 );
    const Bitmask te( Bitmask::b04 );
    const Bitmask tl( Bitmask::b03 );
    const Bitmask tm( Bitmask::b05 );

    Bitmask::value_type le = 0x10;
    Bitmask::value_type ll = 0x04;
    Bitmask::value_type lm = 0x20;

    TEST( compare( t, te ) == 0 );
    TEST( compare( t, tl ) >  0 );
    TEST( compare( t, tl ) >= 0 );
    TEST( compare( t, te ) >= 0 );
    TEST( compare( t, tm ) <  0 );
    TEST( compare( t, tm ) <= 0 );
    TEST( compare( t, te ) <= 0 );

    TEST( compare( t, le ) == 0 );
    TEST( compare( t, ll ) >  0 );
    TEST( compare( t, ll ) >= 0 );
    TEST( compare( t, le ) >= 0 );
    TEST( compare( t, lm ) <  0 );
    TEST( compare( t, lm ) <= 0 );
    TEST( compare( t, le ) <= 0 );

    TEST( compare( le, t ) == 0 );
    TEST( compare( ll, t ) <  0 );
    TEST( compare( ll, t ) <= 0 );
    TEST( compare( le, t ) <= 0 );
    TEST( compare( lm, t ) >  0 );
    TEST( compare( lm, t ) >= 0 );
    TEST( compare( le, t ) >= 0 );

    TEST( le == t );
    TEST( le != tl );
    TEST( le < tm );
    TEST( le <= tm );
    TEST( le <= te );
    TEST( le > tl );
    TEST( le >= tl );
    TEST( le >= te );
  }

  return( verify.is_valid() );
}
