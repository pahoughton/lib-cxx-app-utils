//
// File:        Bitmask.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     07/21/95 06:41
//
// Revision History:
//
// $Log$
// Revision 2.6  1996/11/11 13:28:16  houghton
// Rework fromStream because of a bug with AIX iostream.
//
// Revision 2.5  1996/11/04 13:20:09  houghton
// Added Bitmask::bit::toStream
// Added Bitmask::bit::dumpInfo
// Removed BinObject/BinStream support.
// Changed BinObject/BinString 'Sizeof' calls to 'sizeof'
// Changed Bitmask::toStream to use to_string().
// Added Bitmask::fromStream().
// Changed Bitmask::dumpInfo to make output more readable.
//
// Revision 2.4  1996/04/27 12:50:22  houghton
// Removed unneeded includes.
//
// Revision 2.3  1995/12/31 11:20:59  houghton
// Bug fix - remove 'inline' statement.
//
// Revision 2.2  1995/12/04 11:16:21  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
// Bug Fix - Now there is a special type for all single 'bit' values.
//
// Revision 2.1  1995/11/10  12:40:16  houghton
// Change to Version 2
//
// Revision 1.5  1995/11/10  00:30:24  houghton
// Fixec Compile error
//
// Revision 1.4  1995/11/09  18:15:18  houghton
// Fixed bug in toStream. was outputing all 0 on AIX
//
// Revision 1.3  1995/11/05  15:28:31  houghton
// Revised
//
//

#include "Bitmask.hh"
#include <StringUtils.hh>

#if defined( CLUE_DEBUG )
#include <Bitmask.ii>
#endif // def( CLUE_DEBUG )

CLUE_VERSION(
  Bitmask,
  "$Id$" );

Bitmask	allBits( 0, true );

const Bitmask	    Bitmask::all( allBits );

const Bitmask::bit  Bitmask::b00( allBits, 0 );
const Bitmask::bit  Bitmask::b01( allBits, 1 );
const Bitmask::bit  Bitmask::b02( allBits, 2 );
const Bitmask::bit  Bitmask::b03( allBits, 3 );
const Bitmask::bit  Bitmask::b04( allBits, 4 );
const Bitmask::bit  Bitmask::b05( allBits, 5 );
const Bitmask::bit  Bitmask::b06( allBits, 6 );
const Bitmask::bit  Bitmask::b07( allBits, 7 );
const Bitmask::bit  Bitmask::b08( allBits, 8 );
const Bitmask::bit  Bitmask::b09( allBits, 9 );
const Bitmask::bit  Bitmask::b10( allBits, 10 );
const Bitmask::bit  Bitmask::b11( allBits, 11 );
const Bitmask::bit  Bitmask::b12( allBits, 12 );
const Bitmask::bit  Bitmask::b13( allBits, 13 );
const Bitmask::bit  Bitmask::b14( allBits, 14 );
const Bitmask::bit  Bitmask::b15( allBits, 15 );
const Bitmask::bit  Bitmask::b16( allBits, 16 );
const Bitmask::bit  Bitmask::b17( allBits, 17 );
const Bitmask::bit  Bitmask::b18( allBits, 18 );
const Bitmask::bit  Bitmask::b19( allBits, 19 );
const Bitmask::bit  Bitmask::b20( allBits, 20 );
const Bitmask::bit  Bitmask::b21( allBits, 21 );
const Bitmask::bit  Bitmask::b22( allBits, 22 );
const Bitmask::bit  Bitmask::b23( allBits, 23 );
const Bitmask::bit  Bitmask::b24( allBits, 24 );
const Bitmask::bit  Bitmask::b25( allBits, 25 );
const Bitmask::bit  Bitmask::b26( allBits, 26 );
const Bitmask::bit  Bitmask::b27( allBits, 27 );
const Bitmask::bit  Bitmask::b28( allBits, 28 );
const Bitmask::bit  Bitmask::b29( allBits, 29 );
const Bitmask::bit  Bitmask::b30( allBits, 30 );
const Bitmask::bit  Bitmask::b31( allBits, 31 );

  
const size_t Bitmask::maxPos = CHAR_BIT * sizeof( Bitmask::ValueType );

ostream &
Bitmask::bit::toStream( ostream & dest ) const
{
  dest << (bitmask.test(bitpos) ? "true" : "false" );
  return( dest );
}

ostream &
Bitmask::bit::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << "Bitmask::bit" << ":\n"
	 << bitmask.getVersion() << '\n';


  dest << prefix << "pos:     " << bitpos << '\n'
       << prefix << "value:   " << (bitmask.test( bitpos ) ?
				    "true" : "false" ) << '\n'
    ;
    
  return( dest  );
}


size_t
Bitmask::getBinSize( void ) const
{
  return( sizeof( value ) );
}

ostream &
Bitmask::write( ostream & dest ) const
{
  dest.write( (const char *)&value, sizeof( value ) );
  return( dest );
}

istream &
Bitmask::read( istream & src )
{
  src.read( (char *)&value, sizeof( value ) );
  return( src );
}

ostream &
Bitmask::toStream( ostream & dest ) const
{
  dest << to_string();
  return( dest );
}

istream &
Bitmask::fromStream( istream & src )
{
  char tmp[64];

  if( ! src.ipfx() )
    return( src );

  char * in = tmp;

  // read input into tmp until EOF or sizeof tmp exceeded

  // AIX BUG cant use char to test for EOF!
  int c;

  for( c = src.rdbuf()->sbumpc();
       c != EOF && ((in - tmp) < (int)sizeof( tmp ));
       ++in, c = src.rdbuf()->sbumpc() )
    {
      *in = (char)c;
      
      // if non-binary digit, put the char it back and break;
      if( *in != '0' && *in != '1' )
	{
	  src.rdbuf()->sputbackc( *in );
	  break;
	}
    }

  if( in == tmp )
    {
      src.clear( ios::failbit );
      return ( src );
    }

  bool wasEof = (c == EOF );
  
  // null terminate the string
  *in = 0;

  // convert it to an unsigned long
  if( ! StringTo( value, tmp, 2 ) )
    src.clear( ios::failbit );

  if( wasEof )
    src.clear( ios::eofbit );

  return( src );
}
  
const char *
Bitmask::getClassName( void ) const
{
  return( "Bitmask" );
}

const char *
Bitmask::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
Bitmask::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Bitmask::getClassName() << ":\n"
	 << Bitmask::getVersion() << '\n';


  dest << prefix << "bits:  " ;
  
  for( size_t p = maxPos; p > 0; p-- )
    {
      if( p != maxPos && (p % 4) == 0 )
	dest << ' ';
      dest <<  (test(p-1) ? '1' : '0');
    }
  
  return( dest  );
}





