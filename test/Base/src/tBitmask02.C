//
// File:        tBitmask02.C
// Project:	StlUtils
// Desc:        
//
//  Test the following Bitmask methods.
//
// bit operator [] ( size_t );
// bit operator () ( size_t );
// bool operator [] ( size_t ) const;
// bool operator () ( size_t ) const;
// operator = ( unsigned long )
// operator =  ( const bit & )
// operator &= ( const bit & )
// operator |= ( const bit & )
// operator |= ( const bit & )
// operator ^= ( const bit & )
// operator &= ( const Bitmask & )
// operator |= ( const Bitmask & )
// operator ^= ( const Bitmask & )
// operator == ( const Bitmask & ) const
// operator <  ( const Bitmask & ) const
// operator <= ( const Bitmask & ) const
// operator >  ( const Bitmask & ) const
// operator >= ( const Bitmask & ) const
// operator == ( unsigned long ) const
// operator != ( unsigned long ) const
// operator <  ( unsigned long ) const
// operator <= ( unsigned long ) const
// operator >  ( unsigned long ) const
// operator >= ( unsigned long ) const
// operator bool ( void ) const
// operator unsigned long ( void ) const
// getBinSize( void ) const
// write( ostream & ) const
// read( istream & )
// toStream( ostream & ) const
// fromStream( istream & );
// getClassName( void ) const
// getVersion( void ) const
// getVersion( bool ) const
// dumpInfo( ostream & ) const
// bit::operator bool () const;
// bit::pos( void ) const;
//
// static const bit b00;
// static const bit b01;
// static const bit b02;
// static const bit b03;
// static const bit b04;
// static const bit b05;
// static const bit b06;
// static const bit b07;
// static const bit b08;
// static const bit b09;
// static const bit b10;
// static const bit b11;
// static const bit b12;
// static const bit b13;
// static const bit b14;
// static const bit b15;
// static const bit b16;
// static const bit b17;
// static const bit b18;
// static const bit b19;
// static const bit b20;
// static const bit b21;
// static const bit b22;
// static const bit b23;
// static const bit b24;
// static const bit b25;
// static const bit b26;
// static const bit b27;
// static const bit b28;
// static const bit b29;
// static const bit b30;
// static const bit b31;
// static const Bitmask all;
// static const size_t maxPos;
// static const ClassVersion version
//
//
//  Also uses the following methods.
//
//	bit::pos( void ) const;
//	bit::operator =  ( bool rhs )
//	bit::operator bool () const
//
// Source Header Version: 2.7
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/30/96 08:14
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include "TestConfig.hh"
#include "LibTest.hh"
#include "Bitmask.hh"
#include <Str.hh>
#include <cstring>

#define T_CLASS_NAME	"Bitmask"

bool
tBitmask02( LibTest & tester )
{
  {
    // bit operator [] ( size_t );
    // bit operator () ( size_t );

    //	uses - bit::pos( void ) const;
    //  uses - bit::operator bool () const;

    Bitmask t;

    for( size_t p = 0; p < 16; p++ )
      {
	TEST( t[ p ].pos() == p );
	TEST( t( p ).pos() == p );
	TEST( ! t[ p ] );
	TEST( ! t( p ) );
	
	t.set( p );

	TEST( t[ p ] );
	TEST( t( p ) );

	t[p] = false;
	
	TEST( ! t[ p ] );
	TEST( ! t( p ) );
	TEST( ! t.test( p ) );

	t( p ) = true;
	
	TEST( t[ p ] );
	TEST( t( p ) );
      }
  }

  {
    // bool operator [] ( size_t ) const;
    // bool operator () ( size_t ) const;
    
    const Bitmask t( 0x1824 );

    TEST( ! t[1] );
    TEST( ! t(1) );
    TEST( t[2] );
    TEST( t(2) );
    TEST( t[5] );
    TEST( t(5) );
    TEST( t[11] );
    TEST( t(11) );
    TEST( t[12] );
    TEST( t(12) );
    TEST( ! t[13] );
    TEST( ! t(13) );
  }
      
	
  {
    // operator = ( unsigned long )

    Bitmask t;
    
    t = 0x1080;
    TEST( t.to_ulong() == 0x1080 );
  }

  {
    // operator =  ( const bit & )

    Bitmask t;
    Bitmask s( 0x124f );

    t = s(9);
    TEST( t.to_ulong() == 0x0200 );

    t.set(4);
    TEST( t.to_ulong() == 0x0210 );

    t = s(4);
    TEST( t.to_ulong() == 0x000 );

    t = s(12);
    TEST( t.to_ulong() == 0x1000 );

    // operator &= ( const bit & )
    
    t &= s(12);
    TEST( t.to_ulong() == 0x1000 );

    t &= s(1);
    TEST( t.to_ulong() == 0x1000 );

    t.set( 2 );
    t &= s(2);
    TEST( t.to_ulong() == 0x1004 );
    
    // operator |= ( const bit & )

    t |= s(6);
    TEST( t.to_ulong() == 0x1044 );

    t |= s(16);
    TEST( t.to_ulong() == 0x1044 );

    t.set(16);
    t |= s(16);
    TEST( t.to_ulong() == 0x11044 );

    // operator ^= ( const bit & )

    // 1 1
    t ^= s(2);
    TEST( t.to_ulong() == 0x11040 );

    // 0 1
    t ^= s(1);
    TEST( t.to_ulong() == 0x11042 );

    // 1 0
    t ^= s(16);
    TEST( t.to_ulong() == 0x11042 );

    // 0 0
    t ^= s(4);
    TEST( t.to_ulong() == 0x11042 );
  }
  
  {
    // operator &= ( const Bitmask & )
    // operator |= ( const Bitmask & )
    // operator ^= ( const Bitmask & )

    Bitmask t(0x1f9f);
    Bitmask rhs;
    
    rhs.set( 7 );
    t &= rhs;
    
    TEST( t.to_ulong() == 0x80 );

    rhs.set( 0 );
    t |= rhs;

    TEST( t.to_ulong() == 0x81 );
    
    rhs.reset();
    rhs.set( 7 );
    rhs.set( 15 );
    t ^= rhs;
    
    TEST( t.to_ulong() == 0x8001 );
  }

  {
    // operator == ( const Bitmask & ) const
    // operator <  ( const Bitmask & ) const
    // operator <= ( const Bitmask & ) const
    // operator >  ( const Bitmask & ) const
    // operator >= ( const Bitmask & ) const
    // operator == ( unsigned long ) const
    // operator != ( unsigned long ) const
    // operator <  ( unsigned long ) const
    // operator <= ( unsigned long ) const
    // operator >  ( unsigned long ) const
    // operator >= ( unsigned long ) const

    const Bitmask t( 0x10 );
    const Bitmask te( 0x10 );
    const Bitmask tl( 0x04 );
    const Bitmask tm( 0x20 );

    unsigned int le = 0x10;
    unsigned int ll = 0x04;
    unsigned int lm = 0x20;

    TEST( t == te );
    TEST( t != tl );
    TEST( t <  tm );
    TEST( t <= tm );
    TEST( t <= te );
    TEST( t >  tl );
    TEST( t >= tl );
    TEST( t >= te );

    TEST( t == le );
    TEST( t != lm );
    TEST( t <  lm );
    TEST( t <= lm );
    TEST( t <= le );
    TEST( t >  ll );
    TEST( t >= ll );
    TEST( t >= le );
  }

  {
    // operator bool ( void ) const
    // operator unsigned long ( void ) const

    const Bitmask t1;
    const Bitmask t2( Bitmask::b03 );

    TEST( ! (t1 == true) );
    TEST( t2 );

    TEST( (unsigned)t1  == 0x0U );
    TEST( (unsigned)t2 == 0x08U );
  }

  {
    // getBinSize( void ) const
    // write( ostream & ) const
    // read( istream & )

    const Bitmask   tw(9);
    Bitmask	    tr(5);

    TEST( tw.getBinSize() );

    Str tStrm;

    streampos gpos = tStrm.tellg();
    streampos ppos = tStrm.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    TEST( ppos == 0 );
    TEST( gpos == 0 );
    
    tw.write( tStrm );
    ppos += (streampos)tw.getBinSize();
    TEST( ppos == tStrm.tellp() );
      
    tr.read( tStrm );
    gpos += (streampos)tr.getBinSize();
    TEST( gpos == tStrm.tellg() );
    TEST( tr == tw );
  }

  {
    // toStream( ostream & ) const
    // fromStream( istream & );
    const Bitmask   tw(0xf1248);
    Bitmask	    tr(0xffffffff);

    {
      Str tStrm;

      TEST( tw != tr );
      TEST( tw.toStream( tStrm ).good() );
      TEST( ! tr.fromStream( tStrm ).good() );
      TEST( tStrm.rdstate() == ( ios::eofbit ) );
      TEST( tw == tr );
    }

    {
      Str tStrm;

      TEST( tw.toStream( tStrm ).good() );

      TESTR( tStrm.cstr(),
	     ! strncmp( tw.to_string(), tStrm.cstr(), 32 ) );

    }

    {
      Str tStrm;

      tStrm << "0101    1111";

      TEST( tr.fromStream( tStrm ).good() );
      TEST( tr.to_ulong() == 0x05 );

      
      TEST( ! tr.fromStream( tStrm ).good() );
      cerr << "\nWHAT? : '" << tStrm.rdstate()
	   << "' eof(" << ios::eofbit
	   << ") tr '" << tr 
	   << "'."
	   << endl;
      TEST( tStrm.rdstate() == ( ios::eofbit ) );      
      TEST( tr.to_ulong() == 0x0f );
    }

    {
      Str tStrm;

      tStrm << "2222";
      TEST( ! tr.fromStream( tStrm ).good() );
      TEST( tStrm.fail() );
      TEST( ! tStrm.eof() );
    }
    
  }
    
  {
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    
    const Bitmask t(2);

    TEST( ! strcmp( t.getClassName(), T_CLASS_NAME ) );

    TEST( strstr( t.getVersion(), "@(#) libStlUtils - " ) != 0 );
    TEST( strstr( t.getVersion(), T_CLASS_NAME ) != 0 );
    TEST( strstr( t.getVersion(), "Compiled: " ) != 0 );
    
    TEST( strstr( t.getVersion(true), "@(#) libStlUtils - " )!= 0 );
    TEST( strstr( t.getVersion(true), T_CLASS_NAME ) != 0 );
    TEST( strstr( t.getVersion(true), "Compiled: " ) != 0 );
    
    TEST( strstr( t.getVersion(false), "@(#) libStlUtils - " ) == 0 );
    TEST( strstr( t.getVersion(false), T_CLASS_NAME ) != 0 );
    TEST( strstr( t.getVersion(false), "Compiled: " ) != 0 );

  }

  {
    // dumpInfo( ostream & ) const

    const Bitmask t(0x1248cdef );

    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    
    tester.getDump() << '\n' << tester.getCurrentTestName();    
  }
    
  {
    // bit::operator bool () const;
    // bit::pos( void ) const;
    
    // static const bit b00;
    // static const bit b01;
    // static const bit b02;
    // static const bit b03;
    // static const bit b04;
    // static const bit b05;
    // static const bit b06;
    // static const bit b07;
    // static const bit b08;
    // static const bit b09;
    // static const bit b10;
    // static const bit b11;
    // static const bit b12;
    // static const bit b13;
    // static const bit b14;
    // static const bit b15;
    // static const bit b16;
    // static const bit b17;
    // static const bit b18;
    // static const bit b19;
    // static const bit b20;
    // static const bit b21;
    // static const bit b22;
    // static const bit b23;
    // static const bit b24;
    // static const bit b25;
    // static const bit b26;
    // static const bit b27;
    // static const bit b28;
    // static const bit b29;
    // static const bit b30;
    // static const bit b31;
    
    TEST( Bitmask::b00 == true );
    TEST( Bitmask::b00.pos() == 0 );
    
    TEST( Bitmask::b01 == true );
    TEST( Bitmask::b01.pos() == 1 );
    
    TEST( Bitmask::b02 == true );
    TEST( Bitmask::b02.pos() == 2 );
    
    TEST( Bitmask::b03 == true );
    TEST( Bitmask::b03.pos() == 3 );
    
    TEST( Bitmask::b04 == true );
    TEST( Bitmask::b04.pos() == 4 );
    
    TEST( Bitmask::b05 == true );
    TEST( Bitmask::b05.pos() == 5 );
    
    TEST( Bitmask::b06 == true );
    TEST( Bitmask::b06.pos() == 6 );
    
    TEST( Bitmask::b07 == true );
    TEST( Bitmask::b07.pos() == 7 );
    
    TEST( Bitmask::b08 == true );
    TEST( Bitmask::b08.pos() == 8 );
    
    TEST( Bitmask::b09 == true );
    TEST( Bitmask::b09.pos() == 9 );
    
    TEST( Bitmask::b10 == true );
    TEST( Bitmask::b10.pos() == 10 );
    
    TEST( Bitmask::b11 == true );
    TEST( Bitmask::b11.pos() == 11 );
    
    TEST( Bitmask::b12 == true );
    TEST( Bitmask::b12.pos() == 12 );
    
    TEST( Bitmask::b13 == true );
    TEST( Bitmask::b13.pos() == 13 );
    
    TEST( Bitmask::b14 == true );
    TEST( Bitmask::b14.pos() == 14 );
    
    TEST( Bitmask::b15 == true );
    TEST( Bitmask::b15.pos() == 15 );
    
    TEST( Bitmask::b16 == true );
    TEST( Bitmask::b16.pos() == 16 );
    
    TEST( Bitmask::b17 == true );
    TEST( Bitmask::b17.pos() == 17 );
    
    TEST( Bitmask::b18 == true );
    TEST( Bitmask::b18.pos() == 18 );
    
    TEST( Bitmask::b19 == true );
    TEST( Bitmask::b19.pos() == 19 );
    
    TEST( Bitmask::b20 == true );
    TEST( Bitmask::b20.pos() == 20 );
    
    TEST( Bitmask::b21 == true );
    TEST( Bitmask::b21.pos() == 21 );
    
    TEST( Bitmask::b22 == true );
    TEST( Bitmask::b22.pos() == 22 );
    
    TEST( Bitmask::b23 == true );
    TEST( Bitmask::b23.pos() == 23 );
    
    TEST( Bitmask::b24 == true );
    TEST( Bitmask::b24.pos() == 24 );
    
    TEST( Bitmask::b25 == true );
    TEST( Bitmask::b25.pos() == 25 );
    
    TEST( Bitmask::b26 == true );
    TEST( Bitmask::b26.pos() == 26 );
    
    TEST( Bitmask::b27 == true );
    TEST( Bitmask::b27.pos() == 27 );
    
    TEST( Bitmask::b28 == true );
    TEST( Bitmask::b28.pos() == 28 );
    
    TEST( Bitmask::b29 == true );
    TEST( Bitmask::b29.pos() == 29 );
    
    TEST( Bitmask::b30 == true );
    TEST( Bitmask::b30.pos() == 30 );
    
    TEST( Bitmask::b31 == true );
    TEST( Bitmask::b31.pos() == 31 );

  }

  {
    // static const Bitmask all;

    Bitmask t;

    t.set();

    TEST( t == t.all );
    TEST( t == Bitmask::all );

    for( int i = 0; i < 32; i++ )
      TEST( Bitmask::all.test(i) );
  }

  {
    // static const size_t maxPos;

    TEST( Bitmask::maxPos == 32 );
  }

  {
    // static const ClassVersion version

    TEST( strstr( Bitmask::version.getVer(true), "@(#) libStlUtils - " ) != 0 );
    TEST( strstr( Bitmask::version.getVer(true), T_CLASS_NAME ) != 0 );
    TEST( strstr( Bitmask::version.getVer(true), "Compiled: " ) != 0 );
    
    TEST( strstr( Bitmask::version.getVer(true), "@(#) libStlUtils - " )!= 0 );
    TEST( strstr( Bitmask::version.getVer(true), T_CLASS_NAME ) != 0 );
    TEST( strstr( Bitmask::version.getVer(true), "Compiled: " ) != 0 );
    
    TEST( strstr( Bitmask::version.getVer(false), "@(#) libStlUtils - " ) == 0);
    TEST( strstr( Bitmask::version.getVer(false), T_CLASS_NAME ) != 0 );
    TEST( strstr( Bitmask::version.getVer(false), "Compiled: " ) != 0 );
    
  }
  return( true );
}

//
// $Log$
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.3  2003/07/19 09:17:28  houghton
// Port to 64 bit.
//
// Revision 5.2  2000/05/25 17:11:50  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:27  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:04  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:09:36  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/03/03 19:09:05  houghton
// Changed to use Str (vs strstream).
// Changed for port to AIX.
//
// Revision 3.2  1996/11/19 12:33:58  houghton
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
//
// Revision 3.1  1996/11/14 01:26:23  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 14:46:02  houghton
// Added header comments.
// Changed so that everything in Bitmask.hh is tested.
//
//
