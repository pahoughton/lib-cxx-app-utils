#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Bitmask.hh>
#include <strstream>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Bitmask.hh>
#include <strstream>
#endif


bool
tBitmask01( LibTest & tester )
{
  {
    // Bitmask( void )
    
    Bitmask  t;

    TEST( (unsigned long) t == 0 );
  }

  {
    // Bitmask( const bit & )
    // operator == ( unsigned long ) const

    Bitmask t( Bitmask::b02 );
    TEST( (unsigned long) t == 0x04 );
  }

  {
    // set( size_t )
    // reset( size_t )
    // reset( void )
    
    Bitmask t;

    t.set( 0 );
    TEST( (unsigned long) t == 0x01 );

    t.set( 7 );
    TEST( (unsigned long) t == 0x81 );

    t.reset( 5 );
    TEST( (unsigned long) t == 0x81 );

    t.set( 8 );
    TEST( (unsigned long) t == 0x181 );

    t.reset( 7 );
    TEST( (unsigned long) t == 0x101 );

    t.reset();
    TEST( (unsigned long) t == 0 );
  }

  {
    // test( size_t ) const
    // any( void ) const
    // none( void ) const
    // to_ulong( void ) const
    
    Bitmask t;

    t.set( 1 );
    t.set( 8 );
    t.set( 7 );

    TEST( (unsigned long) t == 0x182 );

    TEST( t.test( 1 ) );
    TEST( t.test( 8 ) );
    TEST( t.test( 7 ) );

    TEST( ! t.test( 0 ) );
    TEST( ! t.test( 2 ) );
    TEST( ! t.test( 6 ) );
    TEST( ! t.test( 9 ) );

    TEST( t.any() );
    TEST( ! t.none() );
    
    TEST( t.to_ulong() == 0x182 );

    t.reset();
    TEST( t.none() );
    
  }

 
  return( true );
}

