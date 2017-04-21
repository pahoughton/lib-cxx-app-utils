// 1995-07-21 (cc) <paul4hough@gmai.com>

#include "Bitmask.hpp"
#include "StringUtils.hpp"

namespace clue {
const Bitmask::size_type Bitmask::maxPos = CHAR_BIT * sizeof( Bitmask::value_type );

static Bitmask	allBits( 0, true );

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

#if defined( Linux )
static const Bitmask	    junk( allBits );
#endif

std::ostream &
Bitmask::bit::toStream( std::ostream & dest ) const
{
  dest << (Bitmask.test(bitpos) ? "true" : "false" );
  return( dest );
}

std::ostream &
Bitmask::bit::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  dest << prefix << "pos:     " << bitpos << '\n'
       << prefix << "value:   " << (Bitmask.test( bitpos ) ?
				    "true" : "false" ) << '\n'
    ;

  return( dest  );
}

std::ostream &
Bitmask::toStream( std::ostream & dest ) const
{
  dest << to_string();
  return( dest );
}

std::istream &
Bitmask::fromStream( std::istream & src )
{
  char tmp[64];

  std::istream::sentry   ipfx( src, true );
  if( ! ipfx )
    return( src );

  int c;

  // skip leading white space
  for( c = src.rdbuf()->sbumpc();
       c != EOF && ( c == ' ' || c == '\t' );
       c = src.rdbuf()->sbumpc() );

  char * in = tmp;

  // read input into tmp until EOF or sizeof tmp exceeded

  for( ; // alread have first digit
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
      src.clear( std::ios::failbit );
      return ( src );
    }

  bool wasEof = (c == EOF );

  // null terminate the string
  *in = 0;

  // convert it to an unsigned long
  unsigned int inval;
  if( ! StringTo( inval, tmp, 2 ) )
    src.clear( std::ios::failbit );
  value = inval;
  if( wasEof )
    src.clear( std::ios::eofbit );

  return( src );
}



std::ostream &
Bitmask::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{
  dest << prefix << "bits:  " ;

  for( size_type p = maxPos; p > 0; p-- )
    {
      if( p != maxPos && (p % 4) == 0 )
	dest << ' ';
      dest <<  (test(p-1) ? '1' : '0');
    }

  return( dest  );
}

}
