//
// File:        tBitmask03.C
// Project:	StlUtils
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


#include "TestConfig.hh"
#include "LibTest.hh"
#include "Bitmask.hh"
#include <Str.hh>
#include <strstream.h>
#include <cstring>

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
    // bit::toStream( ostream & ) const

    Bitmask t(0x8421);
    
    Str tStrm;

    Bitmask::b00.toStream( tStrm ) << " ";
    t(1).toStream( tStrm ) << " ";
    t(0).toStream( tStrm ) << ends;

    TESTR( tStrm.cstr(),
	   ! strcmp( tStrm.cstr(),
		     "true false true" ) );
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
      
      tStrm.rdbuf()->freeze(0);
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
    tStrm.rdbuf()->freeze(0);
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
// Revision 5.2  2003/07/19 09:17:28  houghton
// Port to 64 bit.
//
// Revision 5.1  2000/05/25 10:33:27  houghton
// Changed Version Num to 5
//
// Revision 4.2  1998/04/02 14:19:23  houghton
// Cleanup and eliminate warnings.
//
// Revision 4.1  1997/09/17 15:14:05  houghton
// Changed to Version 4
//
// Revision 3.5  1997/09/17 11:09:37  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.4  1997/07/18 21:34:12  houghton
// Port(Sun5): added include <cstring>
//
// Revision 3.3  1997/03/03 19:09:24  houghton
// Changed to use Str (vs strstream).
// Changed for port to AIX.
//
// Revision 3.2  1996/11/19 12:34:04  houghton
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
//
// Revision 3.1  1996/11/14 01:26:23  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 14:46:07  houghton
// Added header comments.
// Changed so that everything in Bitmask.hh is tested.
//
//
