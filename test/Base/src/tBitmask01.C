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
    // Bitmask( size_t pos )
    // operator == ( unsigned long ) const

    Bitmask t( 2 );
    TEST( (unsigned long) t == 0x04 );
  }

  {
    // set( size_t )
    // clear( size_t )
    // clear( void )
    Bitmask t;

    t.set( 0 );
    TEST( (unsigned long) t == 0x01 );

    t.set( 7 );
    TEST( (unsigned long) t == 0x81 );

    t.clear( 5 );
    TEST( (unsigned long) t == 0x81 );

    t.set( 8 );
    TEST( (unsigned long) t == 0x181 );

    t.clear( 7 );
    TEST( (unsigned long) t == 0x101 );

    t.clear();
    TEST( (unsigned long) t == 0 );
  }

  {
    // isSet( size_t )
    // isClear( size_t )
    // all( void ) const
    
    Bitmask t;

    t.set( 1 );
    t.set( 8 );
    t.set( 7 );

    TEST( (unsigned long) t == 0x182 );

    TEST( t.isSet( 1 ) );
    TEST( t.isSet( 8 ) );
    TEST( t.isSet( 7 ) );

    TEST( ! t.isSet( 0 ) );
    TEST( ! t.isSet( 2 ) );
    TEST( ! t.isSet( 6 ) );
    TEST( ! t.isSet( 9 ) );

    TEST( t.isClear( 0 ) );
    TEST( t.isClear( 2 ) );
    TEST( t.isClear( 6 ) );
    TEST( t.isClear( 9 ) );

    TEST( ! t.isClear( 1 ) );
    TEST( ! t.isClear( 7 ) );
    TEST( ! t.isClear( 8 ) );

    TEST( t.all() == 0x182 );
  }
 
  return( true );
}

