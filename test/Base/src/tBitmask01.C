#include <LibTest.hh>
#include <Bitmask.hh>

#include <strstream>

bool
tBitmask01( LibTest & test )
{
  {
    // Bitmask( void )
    
    Bitmask  t;

    test( (unsigned long) t == 0 );
  }

  {
    // Bitmask( size_t pos )
    // operator == ( unsigned long ) const

    Bitmask t( 2 );
    test( (unsigned long) t == 0x04 );
  }

  {
    // set( size_t )
    // clear( size_t )
    // clear( void )
    Bitmask t;

    t.set( 0 );
    test( (unsigned long) t == 0x01 );

    t.set( 7 );
    test( (unsigned long) t == 0x81 );

    t.clear( 5 );
    test( (unsigned long) t == 0x81 );

    t.set( 8 );
    test( (unsigned long) t == 0x181 );

    t.clear( 7 );
    test( (unsigned long) t == 0x101 );

    t.clear();
    test( (unsigned long) t == 0 );
  }

  {
    // isSet( size_t )
    // isClear( size_t )
    // all( void ) const
    
    Bitmask t;

    t.set( 1 );
    t.set( 8 );
    t.set( 7 );

    test( (unsigned long) t == 0x182 );

    test( t.isSet( 1 ) );
    test( t.isSet( 8 ) );
    test( t.isSet( 7 ) );

    test( ! t.isSet( 0 ) );
    test( ! t.isSet( 2 ) );
    test( ! t.isSet( 6 ) );
    test( ! t.isSet( 9 ) );

    test( t.isClear( 0 ) );
    test( t.isClear( 2 ) );
    test( t.isClear( 6 ) );
    test( t.isClear( 9 ) );

    test( ! t.isClear( 1 ) );
    test( ! t.isClear( 7 ) );
    test( ! t.isClear( 8 ) );

    test( t.all() == 0x182 );
  }

  {
    // getStreamSize( void ) const
    // write( ostream & dest ) const
    // read( istream & src )
    
    const Bitmask   tout( 9 );
    Bitmask	    tin;

    strstream  tStream;
    
    streampos gpos = tStream.tellg();
    streampos ppos = tStream.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    test( ppos == 0 );
    test( gpos == 0 );

    tout.write( tStream );
    ppos += tout.getStreamSize();
    test( ppos == tStream.tellp() );

    tin.read( tStream );
    gpos += tin.getStreamSize();
    test( gpos == tStream.tellg() );
    test( tin == tout );
  }
  
  return( true );
}

