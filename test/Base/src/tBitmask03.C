//
// File:        tBitmask03.C
// Project:	Clue
// Desc:        
//
//  Test the following Bitmask methods.
//
// bit::flip( void )
// bit::pos( void );
// bit::operator = ( bool rhs );
// bit::operator = ( const bit & )
// bit::operator ~ ( void ) const
// bit::operator bool ( void ) const
// bit::toStream( ostream & ) const
// bit::dumpinfo( ostream &, const char *, bool )
// ::operator << ( ostream &, const Bitmask & );
// ::operator >> ( istream &, Bitmask & );
// ::operator << ( ostream &, const Bitmask::bit & )
// ::operator & ( const Bitmask &, const Bitmask & )
// ::operator | ( const Bitmask &, const Bitmask & )
// ::operator ^ ( const Bitmask &, const Bitmask & )
// ::operator ~ ( const Bitmask & )
// ::compare( const Bitmask &, const Bitmask & )
// ::compare( const Bitmask &, unsigned long )
// ::compare( unsigned long, const Bitmask & )
// ::operator == ( unsigned long, const Bitmask & )
// ::operator != ( unsigned long, const Bitmask & )
// ::operator <  ( unsigned long, const Bitmask & )
// ::operator <= ( unsigned long, const Bitmask & )
// ::operator >  ( unsigned long, const Bitmask & )
// ::operator >= ( unsigned long, const Bitmask & )
//
//
//  Also uses the following methods.
//
// Source Header Version: 2.7
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/30/96 12:55
//
// Revision History: (See end of file for Revision Log)
//
// $Id$ 


#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Bitmask.hh>
#include <strstream>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Bitmask.hh>
#endif

bool
tBitmask03( LibTest & tester )
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

    for( int p = 0 ; p < 30; p++ )
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

    TEST( t( 3 ) && ! t(2) );
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
    // bit::toStream( ostream & ) const

    Bitmask t(0x8421);
    
    strstream tStrm;

    Bitmask::b00.toStream( tStrm ) << " ";
    t(1).toStream( tStrm ) << " ";
    t(0).toStream( tStrm ) << ends;

    TESTR( tStrm.str(),
	   ! strcmp( tStrm.str(),
		     "true false true" ) );
    tStrm.freeze(0);
  }
    
  {
    // bit::dumpinfo( ostream &, const char *, bool )

    tester.getDump() << '\n' << "Bitmask::bit" << " dumpInfo:\n";
    Bitmask::b16.dumpInfo( tester.getDump(), " -> ", true );
    
    tester.getDump() << '\n' << tester.getCurrentTestName();    
  }

  {
    // ::operator << ( ostream &, const Bitmask & );
    // ::operator >> ( istream &, Bitmask & );

    const Bitmask   tw( 0x8421fedc );
    Bitmask	    tr(0xffffffff);

    {
      strstream tStrm;

      TEST( tw != tr );
      tStrm << tw;
      tStrm >> tr;
      TEST( tw == tr );
    }

    {
      strstream tStrm;
      
      tStrm << tw << ends;
      
      TESTR( tStrm.str(),
	     ! strcmp( tw.to_string(), tStrm.str() ) );
      
      tStrm.freeze(0);
    }
  }

  {
    // ::operator << ( ostream &, const Bitmask::bit & )
    
    Bitmask t(0x8421);
    
    strstream tStrm;

    tStrm << Bitmask::b00 << ' '
	  << t(1) << ' '
	  << t(0) << ends;
    
    TESTR( tStrm.str(),
	   ! strcmp( tStrm.str(),
		     "true false true" ) );
    tStrm.freeze(0);
  }
  
  {
    // ::operator & ( const Bitmask &, const Bitmask & )
    // ::operator | ( const Bitmask &, const Bitmask & )
    // ::operator ^ ( const Bitmask &, const Bitmask & )
    // ::operator ~ ( const Bitmask & )

    const Bitmask   t1( Bitmask::b02 );
    const Bitmask   t2( Bitmask::b04 );
    const Bitmask   t3( Bitmask::b08 );

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
    // ::operator <= ( unsigned long, const Bitmask & )
    // ::operator >  ( unsigned long, const Bitmask & )
    // ::operator >= ( unsigned long, const Bitmask & )

    const Bitmask t( Bitmask::b04 );
    const Bitmask te( Bitmask::b04 );
    const Bitmask tl( Bitmask::b03 );
    const Bitmask tm( Bitmask::b05 );

    unsigned long le = 0x10;
    unsigned long ll = 0x04;
    unsigned long lm = 0x20;

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

  return( true );
  
}

//
// $Log$
// Revision 2.4  1996/11/04 14:46:07  houghton
// Added header comments.
// Changed so that everything in Bitmask.hh is tested.
//
//
