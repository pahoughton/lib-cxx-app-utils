//
// File:        tBitmask01.C
// Project:	StlUtils
// Desc:        
//
//  Test the following Bitmask methods.
//
//	Bitmask( void )
// 	Bitmask( unsigned long val )
// 	Bitmask( const bit & val );
// 	Bitmask( const Bitmask & from )
// 	set( void )
// 	set( size_t )
// 	set( size_t, bool )
// 	reset( void )
// 	reset( size_t )
// 	flip( void )
// 	flip( size_t )
// 	bool test( size_t ) const;
// 	any( void ) const
// 	none( void ) const
// 	count( void ) const;
// 	size( void ) const;
// 	to_ulong( void ) const
// 	to_string( void ) const
// 	compare( const Bitmask & two ) const
// 	compare( unsigned long ) const
//  
// Source Header Version: 2.7
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/30/96 06:05
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include "TestConfig.hh"
#include "LibTest.hh"
#include "Bit.hh"
#include "Bitmask.hh"
#include <strstream.h>
#include <cstring>

bool
tBitmask01( LibTest & tester )
{
  {
    // Bitmask( void )
    
    Bitmask  t;

    TEST( t.to_ulong() == 0 );
  }

  {
    // Bitmask( unsigned long val )

    Bitmask t( 0x24 ); // 0010 0100

    TEST( t.to_ulong() == 0x24UL );
  }

  {
    // Bitmask( const bit & val );
    
    Bitmask s( 0x24 ); // 0010 0100

    for( size_t pos = 0; pos < 8; pos++ )
    {
      Bitmask t( s(pos) );
      TEST( t.to_ulong() == ((unsigned long)( 0x24 & (1 << pos) )) );
    }
  }

  {
    // Bitmask( const Bitmask & from )

    Bitmask s( 0x24 );
    Bitmask t( s );

    TEST( t.to_ulong() == 0x24 );
  }

  {
    // set( void )

    Bitmask t;

    TEST( t.to_ulong() == 0x0 );

    TEST( t.set().to_ulong() == 0xffffffff );
    TEST( t.to_ulong() == 0xffffffff );
  }

  {
    // set( size_t )

    Bitmask t;

    TEST( t.set( 3 ).to_ulong() == 0x08 );
    TEST( t.to_ulong() == 0x08 );

    TEST( t.set( 6 ).to_ulong() == 0x48 );
    TEST( t.to_ulong() == 0x48 );
    
    TEST( t.set( 3 ).to_ulong() == 0x48 );
    TEST( t.to_ulong() == 0x48 );

  }

  {
    // set( size_t, bool )

    Bitmask t;

    TEST( t.set( 3, true ).to_ulong() == 0x08 );
    TEST( t.to_ulong() == 0x08 );

    TEST( t.set( 6, true ).to_ulong() == 0x48 );
    TEST( t.to_ulong() == 0x48 );
    
    TEST( t.set( 3, true ).to_ulong() == 0x48 );
    TEST( t.to_ulong() == 0x48 );

    TEST( t.set( 3, false ).to_ulong() == 0x40 );
    TEST( t.to_ulong() == 0x40 );

    TEST( t.set( 6, false ).to_ulong() == 0x00 );
    TEST( t.to_ulong() == 0x00 );
  }

  {
    // reset( void )

    Bitmask t( 0x24 );

    TEST( t.reset().to_ulong() == 0x00 );
    TEST( t.to_ulong() == 0x00 );
  }


  {
    // reset( size_t )

    Bitmask t( 0x04ff );

    TEST( t.reset(4).to_ulong() == 0x04ef );
    TEST( t.to_ulong() == 0x04ef );
    TEST( t.reset(4).to_ulong() == 0x04ef );
    TEST( t.to_ulong() == 0x04ef );
  }

  {
    // flip( void )

    Bitmask t;

    TEST( t.flip().to_ulong() == LONG_ALL_BITS );
    TEST( t.to_ulong() == LONG_ALL_BITS );

    t.reset();
    t.set( 0 );
    t.set( 4 );
    TEST( t.set( 8 ).to_ulong() == 0x0111 );
    TEST( t.flip().to_ulong() == 0xfffffeee );
    TEST( t.to_ulong() == 0xfffffeee );
  }

  {
    // flip( size_t )

    Bitmask t;

    TEST( t.flip( 2 ).to_ulong() == 0x04 );
    TEST( t.to_ulong() == 0x04 );
    TEST( t.flip( 1 ).to_ulong() == 0x06 );
    TEST( t.flip( 3 ).to_ulong() == 0x0e );
    TEST( t.flip( 1 ).to_ulong() == 0x0c );
    TEST( t.flip( 2 ).to_ulong() == 0x08 );
    TEST( t.flip( 3 ).to_ulong() == 0x00 );
    
  }

  {
    // bool test( size_t ) const;
    {
      const Bitmask t( 0x24 );
      
      for( size_t p = 0; p < 32; p++ )
	{
	  TEST( t.test( p ) == (( 0x24 & (1 << p)) ? true : false ) );
	}
      TEST( t.test( 0 ) == false );
      TEST( t.test( 1 ) == false );
      TEST( t.test( 2 ) == true );
      TEST( t.test( 3 ) == false );
      TEST( t.test( 4 ) == false );
      TEST( t.test( 5 ) == true );
      TEST( t.test( 6 ) == false );
    }

    {
      Bitmask	t;

      TEST( t.test( 2 ) == false );
      t.set(2);
      TEST( t.test( 2 ) == true );
      t.reset(2);
      TEST( t.test( 2 ) == false );
    }
  }

  {
    // any( void ) const
    {
      const Bitmask t;

      TEST( t.any() == false );
    }

    {
      const Bitmask t( 0x24 );

      TEST( t.any() == true );
    }

    {
      const Bitmask t( 0x80000000 );

      TEST( t.any() == true );
    }

    {
      const Bitmask t( 0x01 );

      TEST( t.any() == true );
    }

    {
      const Bitmask t( 0xffffffff );

      TEST( t.any() == true );
    }
    
    {
      Bitmask	t;

      TEST( t.any() == false );
      t.set(8);
      TEST( t.any() == true );
      t.set(2);
      TEST( t.any() == true );
      t.reset(8);
      TEST( t.any() == true );
      t.reset(2);
      TEST( t.any() == false );
    }
  }
      
  {
    // none( void ) const
    {
      const Bitmask t;

      TEST( t.none() == true );
    }

    {
      const Bitmask t( 0x24 );

      TEST( t.none() == false );
    }

    {
      const Bitmask t( 0x80000000 );

      TEST( t.none() == false );
    }

    {
      const Bitmask t( 0x01 );

      TEST( t.none() == false );
    }

    {
      const Bitmask t( 0xffffffff );

      TEST( t.none() == false );
    }
    
    {
      Bitmask	t;

      TEST( t.none() == true );
      t.set(8);
      TEST( t.none() == false );
      t.set(2);
      TEST( t.none() == false );
      t.reset(8);
      TEST( t.none() == false );
      t.reset(2);
      TEST( t.none() == true );
    }
  }

  {
    // count( void ) const;

    {
      const Bitmask t;

      TEST( t.count() == 0 );
    }

    {
      const Bitmask t( 0x242 );

      TEST( t.count() == 3 );
    }

    {
      const Bitmask t( 0x1 );

      TEST( t.count() == 1 );
    }

    {
      const Bitmask t( 0x80000001 );

      TEST( t.count() == 2 );
    }

    {
      const Bitmask t( 0xffffffff );

      TEST( t.count() == 32 );
    }

    {
      Bitmask t;

      TEST( t.count() == 0 );
      t.set( 30 );
      TEST( t.count() == 1 );
      t.set( 24 );
      TEST( t.count() == 2 );
      t.set( 5 );
      TEST( t.count() == 3 );
      t.reset( 24 );
      TEST( t.count() == 2 );
      t.set( 5 );
      TEST( t.count() == 2 );
    }
  }

  {
    // size( void ) const;

    {
      const Bitmask t;

      TEST( t.size() == 32 );
    }

    {
      const Bitmask t( 0xffffffff );

      TEST( t.size() == 32 );
    }
  }

  {
    // to_ulong( void ) const

    {
      const Bitmask t( 0x182 );

      TEST( t.to_ulong() == 0x182 );
    }
    
    {
      
      Bitmask t;
      
      t.set( 1 );
      t.set( 8 );
      t.set( 7 );
      
      TEST( t.to_ulong() == 0x182 );
    }

  }

  {
    // to_string( void ) const

    {
      const Bitmask t;

      TESTR( t.to_string(),
	     ! strcmp( t.to_string(), "00000000000000000000000000000000" ) );
    }

    {
      const Bitmask t( 0x24 );
	
      TESTR( t.to_string(),
	     ! strcmp( t.to_string(), "00000000000000000000000000100100" ) );
    }

    {
      Bitmask t;

      t.set( 31 );
      TESTR( t.to_string(),
	     ! strcmp( t.to_string(), "10000000000000000000000000000000" ) );

      t.set( 0 );
      TESTR( t.to_string(),
	     ! strcmp( t.to_string(), "10000000000000000000000000000001" ) );

      t.reset( 31 );
      TESTR( t.to_string(),
	     ! strcmp( t.to_string(), "00000000000000000000000000000001" ) );

      t.reset( 0 );
      TESTR( t.to_string(),
	     ! strcmp( t.to_string(), "00000000000000000000000000000000" ) );

    }
  }

  {
    // compare( const Bitmask & two ) const
    
    const Bitmask t( 0x24 );
    
    const Bitmask tl( 0x23 );
    const Bitmask te( 0x24 );
    const Bitmask tm( 0x25 );

    TEST( t.compare( tl ) >  0 );
    TEST( t.compare( te ) == 0 );
    TEST( t.compare( tm ) <  0 );
  }

  {
    // compare( unsigned long ) const

    const Bitmask t( 0x24 );

    unsigned long tl = 0x23;
    unsigned long te = 0x24;
    unsigned long tm = 0x25;

    TEST( t.compare( tl ) >  0 );
    TEST( t.compare( te ) == 0 );
    TEST( t.compare( tm ) <  0 );
  }
  
 
  return( true );
}

//
// $Log$
// Revision 4.2  1998/04/02 14:19:22  houghton
// Cleanup and eliminate warnings.
//
// Revision 4.1  1997/09/17 15:14:04  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:09:36  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/07/18 21:33:58  houghton
// Port(Sun5): added include <cstring>
//
// Revision 3.2  1996/11/19 12:33:48  houghton
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
//
// Revision 3.1  1996/11/14 01:26:22  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/04 14:45:59  houghton
// Added header comments.
// Changed so that everything in Bitmask.hh is tested.
//
//
