#ifndef _clue_bitmask_hpp_
#define _clue_bitmask_hpp_
// 1995-05-18 (cc) paul4hough@gmail.com

#include <clue/compare>
#include <clue/bit>
#include <iostream>
#include <cstdint>
// #include <functional>

namespace clue {
class Bitmask
{

public:

  typedef uint32_t  value_type;
  typedef uint32_t  size_type;

  class bit
  {
  public:

    inline bit &     flip( void );
    inline size_type pos( void ) const;

    inline bit &     operator =  ( bool rhs );
    inline bit &     operator =  ( const bit & rhs );

    inline bool	     operator ~  ( void ) const;
    inline bool	     operator !  ( void ) const;

    inline	     operator bool ( void ) const;

    inline bool	     operator == ( bool rhs ) const;
    inline bool	     operator != ( bool rhs ) const;

    std::ostream &   toStream( std::ostream & dest = std::cout ) const;

    std::ostream &   dumpInfo( std::ostream & dest = std::cerr,
			       const char *   prefix = "    " ) const;

  private:
    friend class ::clue::Bitmask;

    inline bit( ::clue::Bitmask & owner, size_type pos );

    ::clue::Bitmask &	Bitmask;
    size_type	bitpos;

  };

  inline Bitmask( void );
  inline Bitmask( value_type val, bool flip = false );
  inline Bitmask( const bit & val );
  inline Bitmask( const Bitmask & from );

  inline Bitmask &  set( void );
  inline Bitmask &  set( size_type pos, bool val = true );

  inline Bitmask &  reset( void );
  inline Bitmask &  reset( size_type pos );

  inline Bitmask &  flip( void );
  inline Bitmask &  flip( size_type pos );

  inline bool	    test( size_type pos ) const;
  inline bool	    any( void ) const;
  inline bool	    none( void ) const;

  inline size_type	count( void ) const;
  inline size_type	size( void ) const;

  inline unsigned long	to_ulong( void ) const;
  inline const char *	to_string( void ) const;
  inline value_type	to_value_type( void ) const;

  inline int		compare( const Bitmask & two ) const;
  inline int		compare( value_type two ) const;

  inline bit		operator [] ( size_type pos );
  inline bit	    	operator () ( size_type pos );

  inline bool		operator [] ( size_type pos ) const;
  inline bool  	    	operator () ( size_type pos ) const;

  inline Bitmask &	operator =  ( value_type rhs );

  inline Bitmask &	operator =  ( const bit & rhs );
  inline Bitmask & 	operator &= ( const bit & rhs );
  inline Bitmask & 	operator |= ( const bit & rhs );
  inline Bitmask & 	operator ^= ( const bit & rhs );

  inline Bitmask &	operator =  ( const Bitmask & rhs );
  inline Bitmask & 	operator &= ( const Bitmask & rhs );
  inline Bitmask & 	operator |= ( const Bitmask & rhs );
  inline Bitmask & 	operator ^= ( const Bitmask & rhs );

  inline bool		operator == ( const Bitmask & rhs ) const;
  inline bool		operator != ( const Bitmask & rhs ) const;
  inline bool		operator <  ( const Bitmask & rhs ) const;
  inline bool		operator >  ( const Bitmask & rhs ) const;
  inline bool		operator <= ( const Bitmask & rhs ) const;
  inline bool		operator >= ( const Bitmask & rhs ) const;

  inline bool		operator == ( bool rhs ) const;
  inline bool		operator != ( bool rhs ) const;

  inline bool		operator == ( value_type rhs ) const;
  inline bool		operator != ( value_type rhs ) const;
  inline bool		operator <  ( value_type rhs ) const;
  inline bool		operator <= ( value_type rhs ) const;
  inline bool		operator >  ( value_type rhs ) const;
  inline bool		operator >= ( value_type rhs ) const;

  inline    	    	operator bool ( void ) const;
  inline    	    	operator value_type ( void ) const;

  // use by iostream << and >> operators
  virtual std::ostream & toStream( std::ostream & dest = std::cout ) const;
  virtual std::istream & fromStream( std::istream & src );

  std::ostream &   dumpInfo( std::ostream & dest = std::cerr,
			     const char *   prefix = "    " ) const;
  static const Bitmask all;

  static const bit b00;
  static const bit b01;
  static const bit b02;
  static const bit b03;
  static const bit b04;
  static const bit b05;
  static const bit b06;
  static const bit b07;
  static const bit b08;
  static const bit b09;
  static const bit b10;
  static const bit b11;
  static const bit b12;
  static const bit b13;
  static const bit b14;
  static const bit b15;
  static const bit b16;
  static const bit b17;
  static const bit b18;
  static const bit b19;
  static const bit b20;
  static const bit b21;
  static const bit b22;
  static const bit b23;
  static const bit b24;
  static const bit b25;
  static const bit b26;
  static const bit b27;
  static const bit b28;
  static const bit b29;
  static const bit b30;
  static const bit b31;

  static const size_type    maxPos;

protected:

private:

  value_type value;

};


std::ostream &
operator << ( std::ostream & dest, const Bitmask & obj );

std::istream &
operator >> ( std::istream & src, Bitmask & obj );

std::ostream &
operator << ( std::ostream & dest, const Bitmask::bit & obj );

Bitmask
operator & ( const Bitmask & lhs, const Bitmask & rhs );

Bitmask
operator | ( const Bitmask & lhs, const Bitmask & rhs );

Bitmask
operator ^ ( const Bitmask & lhs, const Bitmask & rhs );

Bitmask
operator ~ ( const Bitmask & mask );

bool
operator == ( bool lhs, const Bitmask::bit & rhs );

bool
operator != ( bool lhs, const Bitmask::bit & rhs );

int
compare( const Bitmask & one, const Bitmask & two );

int
compare( const Bitmask & one, Bitmask::value_type two );

int
compare( Bitmask::value_type one, const Bitmask & two );

bool
operator == ( Bitmask::value_type lhs, const Bitmask & rhs );

bool
operator != ( Bitmask::value_type lhs, const Bitmask & rhs );

bool
operator <  ( Bitmask::value_type lhs, const Bitmask & rhs );

bool
operator <= ( Bitmask::value_type lhs, const Bitmask & rhs );

bool
operator >  ( Bitmask::value_type lhs, const Bitmask & rhs );

bool
operator >= ( Bitmask::value_type lhs, const Bitmask & rhs );


inline
Bitmask::bit &
Bitmask::bit::flip( void )
{
  Bitmask.flip( bitpos );
  return( *this );
}

inline
Bitmask::size_type
Bitmask::bit::pos( void ) const
{
  return( bitpos );
}

inline
Bitmask::bit &
Bitmask::bit::operator = ( bool rhs )
{
  Bitmask.set( bitpos, (rhs) ? 1 : 0 );
  return( *this );
}

inline
Bitmask::bit &
Bitmask::bit::operator = ( const bit & rhs )
{
  Bitmask.set( bitpos, rhs.Bitmask.test( rhs.bitpos ) );
  return( *this );
}

inline
bool
Bitmask::bit::operator ~ ( void ) const
{
  return( ! Bitmask.test( bitpos ) );
}

inline
bool
Bitmask::bit::operator ! ( void ) const
{
  return( ! Bitmask.test( bitpos ) );
}

inline
Bitmask::bit::operator bool ( void ) const
{
  return( Bitmask.test( bitpos ) );
}

inline
Bitmask::bit::bit( clue::Bitmask & owner, size_type position )
  : Bitmask( owner ),
    bitpos( position )
{
}

inline
bool
Bitmask::bit::operator == ( bool rhs ) const
{
  return( Bitmask.test( bitpos ) ? rhs : ! rhs );
}

inline
bool
Bitmask::bit::operator != ( bool rhs ) const
{
  return( ! ( *this == rhs ) );
}

inline
Bitmask::Bitmask( void )
  : value( 0 )
{
}

inline
Bitmask::Bitmask( value_type val, bool flip )
  : value( val )
{
  if( flip )
    value = ~val;
}

inline
Bitmask::Bitmask( const Bitmask::bit & val )
  : value( 0 )
{
  set( val.pos(), val );
}

inline
Bitmask::Bitmask( const Bitmask & from )
  : value( from.value )
{
}


inline
Bitmask &
Bitmask::set( void )
{
  value = ~0U;
  return( *this );
}

inline
Bitmask &
Bitmask::set( size_type pos, bool val )
{
  if( val )
    value |= 1U << pos;
  else
    value &= ~(1U << pos );

  return( *this );
}

inline
Bitmask &
Bitmask::reset( void )
{
  value = 0;
  return( *this );
}

inline
Bitmask &
Bitmask::reset( size_type pos )
{
  return( set( pos, false ) );
}

inline
Bitmask &
Bitmask::flip( void )
{
  value = ~value;
  return( *this );
}

inline
Bitmask &
Bitmask::flip( size_type pos )
{
  return( set( pos, ! test( pos ) ) );
}

inline
bool
Bitmask::test( size_type pos ) const
{
  return( value & (1U << pos) );
}

inline
bool
Bitmask::any( void ) const
{
  return( value != 0 );
}

inline
bool
Bitmask::none( void ) const
{
  return( value == 0 );
}

inline
Bitmask::size_type
Bitmask::count( void ) const
{
  size_type cnt = 0;
  for( size_type p = 0; p < maxPos; p++ )
    if( test( p ) ) cnt++;

  return( cnt );
}

inline
Bitmask::size_type
Bitmask::size( void ) const
{
  return( maxPos );
}


inline
unsigned long
Bitmask::to_ulong( void ) const
{
  return( value );
}

inline
const char *
Bitmask::to_string( void ) const
{
  static char	tmp[ CHAR_BITS * sizeof( Bitmask::value_type ) ];

  int p = maxPos;
  for( ; p > 0; p-- )
    tmp[ maxPos - p ] = (test(p - 1) ? '1' : '0');
  tmp[ maxPos ] = 0;

  return( tmp );
}

inline
Bitmask::value_type
Bitmask::to_value_type( void ) const
{
  return( value );
}

inline
int
Bitmask::compare( const Bitmask & two ) const
{
  return( clue::compare( value, two.value ) );
}

inline
int
Bitmask::compare( value_type two ) const
{
  return( clue::compare( value, two ) );
}

inline
Bitmask::bit
Bitmask::operator () ( size_type pos )
{
  return( bit( *this, pos ) );
}

inline
Bitmask::bit
Bitmask::operator [] ( size_type pos )
{
  return( bit( *this, pos ) );
}

inline
bool
Bitmask::operator () ( size_type pos ) const
{
  return( test( pos ) );
}

inline
bool
Bitmask::operator [] ( size_type pos ) const
{
  return( test( pos ) );
}

inline
Bitmask &
Bitmask::operator = ( value_type rhs )
{
  value = rhs;
  return( *this );
}

inline
Bitmask &
Bitmask::operator = ( const Bitmask::bit & rhs )
{
  reset();
  set( rhs.pos(), rhs );
  return( *this );
}

inline
Bitmask &
Bitmask::operator &= ( const Bitmask::bit & rhs )
{
  set( rhs.pos(), test( rhs.pos() ) && (bool)rhs );
  return( *this );
}

inline
Bitmask &
Bitmask::operator |= ( const Bitmask::bit & rhs )
{
  set( rhs.pos(), test( rhs.pos() ) || (bool)rhs );
  return( *this );
}

inline
Bitmask &
Bitmask::operator ^= ( const Bitmask::bit & rhs )
{
  set( rhs.pos(), test( rhs.pos() ) != (bool)rhs );
  return( *this );
}

inline
Bitmask &
Bitmask::operator =  ( const Bitmask & rhs )
{
  value = rhs.value;
  return( *this );
}

inline
Bitmask &
Bitmask::operator &= ( const Bitmask & rhs )
{
  value &= rhs.value;
  return( *this );
}

inline
Bitmask &
Bitmask::operator |= ( const Bitmask & rhs )
{
  value |= rhs.value;
  return( *this );
}

inline
Bitmask &
Bitmask::operator ^= ( const Bitmask & rhs )
{
  value ^= rhs.value;
  return( *this );
}

CLUE_SELF_COMPARE_IMPL( Bitmask, == )
CLUE_SELF_COMPARE_IMPL( Bitmask, != )
CLUE_SELF_COMPARE_IMPL( Bitmask, <  )
CLUE_SELF_COMPARE_IMPL( Bitmask, >  )
CLUE_SELF_COMPARE_IMPL( Bitmask, <= )
CLUE_SELF_COMPARE_IMPL( Bitmask, >= )


inline
bool
Bitmask::operator == ( bool rhs ) const
{
  return( any() == rhs );
}

inline
bool
Bitmask::operator != ( bool rhs ) const
{
  return( !(*this == rhs) );
}


inline
bool
Bitmask::operator == ( value_type rhs ) const
{
  return( compare( rhs ) == 0 );
}

inline
bool
Bitmask::operator != ( value_type rhs ) const
{
  return( compare( rhs ) != 0 );
}

inline
bool
Bitmask::operator <  ( value_type rhs ) const
{
  return( compare( rhs ) <  0 );
}

inline
bool
Bitmask::operator <= ( value_type rhs ) const
{
  return( compare( rhs ) <=  0 );
}

inline
bool
Bitmask::operator >  ( value_type rhs ) const
{
  return( compare( rhs ) >  0 );
}

inline
bool
Bitmask::operator >= ( value_type rhs ) const
{
  return( compare( rhs ) >= 0 );
}

inline
Bitmask::operator bool ( void ) const
{
  return( value != 0 );
}

inline
Bitmask::operator value_type ( void ) const
{
  return( value );
}


inline
Bitmask
operator & ( const Bitmask & lhs, const Bitmask & rhs )
{
  Bitmask ret( lhs );
  ret &= rhs;
  return( ret );
}

inline
Bitmask
operator | ( const Bitmask & lhs, const Bitmask & rhs )
{
  Bitmask ret( lhs );
  ret |= rhs;
  return( ret );
}

inline
Bitmask
operator ^ ( const Bitmask & lhs, const Bitmask & rhs )
{
  Bitmask ret( lhs );
  ret ^= rhs;
  return( ret );
}

inline
Bitmask
operator ~ ( const Bitmask & mask )
{
  Bitmask::value_type nValue = mask;
  Bitmask ret;

  ret = ~nValue;
  return( ret );
}

inline
bool
operator == ( bool lhs, const Bitmask & rhs )
{
  return( rhs == lhs );
}

inline
bool
operator != ( bool lhs, const Bitmask & rhs )
{
  return( rhs != lhs );
}

inline
int
compare( const Bitmask & one, const Bitmask & two )
{
  return( one.compare( two ) );
}

inline
int
compare( Bitmask::value_type one, const Bitmask & two )
{
  return( compare( one, two.to_value_type() ) );
}

inline
int
compare( const Bitmask & one, Bitmask::value_type two )
{
  return( one.compare( two ) );
}

inline
bool
operator == ( Bitmask::value_type lhs, const Bitmask & rhs )
{
  return( clue::compare( lhs, rhs ) == 0 );
}

inline
bool
operator != ( Bitmask::value_type lhs, const Bitmask & rhs )
{
  return( clue::compare( lhs, rhs ) != 0 );
}

inline
bool
operator <  ( Bitmask::value_type lhs, const Bitmask & rhs )
{
  return( clue::compare( lhs, rhs ) <  0 );
}

inline
bool
operator <= ( Bitmask::value_type lhs, const Bitmask & rhs )
{
  return( clue::compare( lhs, rhs ) <= 0 );
}

inline
bool
operator >  ( Bitmask::value_type lhs, const Bitmask & rhs )
{
  return( clue::compare( lhs, rhs ) >  0 );
}

inline
bool
operator >= ( Bitmask::value_type lhs, const Bitmask & rhs )
{
  return( clue::compare( lhs, rhs ) >=  0 );
}


inline
std::ostream &
operator << ( std::ostream & dest, const Bitmask & obj )
{
  return( obj.toStream( dest ) );
}

inline
std::istream &
operator >> ( std::istream & src, Bitmask & obj )
{
  return( obj.fromStream( src ) );
}

inline
std::ostream &
operator << ( std::ostream & dest, const Bitmask::bit & obj )
{
  return( obj.toStream( dest ) );
}

}

/**
    This class provides for easy to use high perfomance
    bit manipulations. It can be used to manipulate up to
    32 bits (i.e. a long on most architectures). To work with
    more than 32 bits, see bit_vector in the STL.

    All position parameters are right to left staring with 0.
    So, for 00010000, pos 4 is a 1.



    Types:

    	class Bitmask

  	scalar Bitmask::value_type
  	    An unsigned 32 bit type used to contain the bit data.

  	class Bitmask::bit
  	    A bit is a single bit of a Bitmask. It knows both the
  	    position and value from the original Binmask. It
  	    contains a reference to the original Bitmask, so if
  	    the value of that bit changes in the original Bitmask,
  	    the bit's value will also change.

    Public Fields:

  	static const bit b00;
  	    This is a static variable that represents bit 0 set to true.
  	    b01 through b31 are also available for the rest of the bits.

  	static const Bitmask all
  	    This is a static Bitmask with all bits set to 1;

  	static const size_type maxPos;
  	    This static variable contains the maximum number of positions
  	    available in the bit mask (i.e. 32).

  	static const ClassVersion version;
  	    This contains the version information for the Bitmask class.

    Constructors:

  	inline
    	Bitmask( void );
  	    Construct a default Bitmask with its value set to all 0's.

  	inline
  	Bitmask( value_type val, bool flip = false )
  	    Construct a Bitmask, setting its value to 'val'. If
  	    flip is true, all 0's in val will be 1's, and all 1's
            will be 0's, in the new Bitmask object.

  	inline
  	Bitmask( const bit & val )
  	    Construct a Bitmask with its value set to 'val'. The bit's
            pos and value are both used. So, if a bit has a pos of 3
            and it's value is 1, then the value of the Bitmask would be
            binary '1000'.

  	inline
  	Bitmask( const Bitmask & from )
  	    Copy constructor used to create a new Bitmask from an old one.

    Public Interface:

  	inline
  	Bitmask &
  	set( void );
  	    Set all bits to '1'.

  	inline
    	Bitmask &
    	set( size_type pos, bool val = true );
  	    Set the bit at 'pos' to 'val'.

  	inline
  	Bitmask &
  	reset( void );
  	    Set all bits to '0'.

  	inline
  	Bitmask &
  	reset( size_type pos );
  	    Set the bit a pos to '0';

  	inline
  	Bitmask &
  	flip( void );
  	    Flip all the bits in the Bitmask. For each bit that is
  	    a '1', it is set to '0'. For each bit that is a '0',
  	    it is set to '1'.

  	inline
  	Bitmask &
  	flip( size_type pos );
  	    Flip the bit at pos. If it was a '0', set it to a '1'.
  	    If it was a '1', set it to '0'.

  	inline
  	bool
  	test( size_type pos ) const;
  	    Return true if the bit at 'pos' is a '1' or false if
  	    it a '0';

  	inline
  	bool
  	any( void ) const
  	    Return true if any bit in the Bitmask is set to a '1',
  	    else return false.

  	inline
  	bool
  	none( void ) const;
  	    Return true if all bits in the Bitmask are set to '0',
  	    else return false.

  	inline
  	size_type
  	count( void ) const;
  	    Return the number of bits in the Bitmask that are
  	    set to '1'. (i.e. '0101000' will return 2).

  	inline
  	size_type
  	size( void ) const;
  	    Return the maximum number of bits (i.e. 32).

  	inline
  	Bitmask::value_type
  	to_ulong( void ) const
  	    Return the Bitmask as a value_type.

  	inline
  	const char *
  	to_string( void ) const
  	    Return the Bitmask as a null terminated string.
  	    (i.e. "00000000000000000000000000111100" )

  	inline
  	int
  	compare( const Bitmask & two ) const
  	    Compare the Bitmask value with the value of two.
  	    return 0 if Bitmask == two, return < 0 if Bitmask < two
            or return > 0 if Bitmask > two.

  	inline
  	int
  	compare( value_type two ) const
  	    Compare the Bitmask value with the value of two.
  	    return 0 if Bitmask == two, return < 0 if Bitmask < two
            or return > 0 if Bitmask > two.

  	inline
  	bit
  	operator [] ( size_type pos )
  	    Return a bit for the value at pos.

  	inline
  	bit
  	operator () ( size_type pos )
  	    Return a bit for the value at pos.

  	inline
  	bool
  	operator [] ( size_type pos ) const
  	    Return a bool value for the value at pos.

  	inline
  	bool
  	operator () ( size_type pos ) const
  	    Return a bool value for the value at pos.

  	inline
  	Bitmask &
  	operator =  ( value_type rhs );
  	    Assign the Bitmask to the value of rhs.

  	inline
  	Bitmask &
  	operator =  ( const bit & rhs );
  	    Reset the Bitmask and then assign the bit
  	    at 'rhs.pos' to 'rhs' value.

  	inline
  	Bitmask &
  	operator &= ( const bit & rhs );
  	    Assign the bit at 'rhs.pos' to 1, only if it is already 1
  	    and rhs's value is 1.

  	inline
  	Bitmask &
  	operator |= ( const bit & rhs );
  	    Assign the bit at 'rhs.pos' to 1, if it is already 1
  	    or rhs's value is 1.

  	inline
  	Bitmask &
  	operator ^= ( const bit & rhs );
  	    Assign the bit at 'rhs.pos' to 1, if its value and
  	    rhs's value are different.

  	inline
  	Bitmask &
  	operator =  ( const Bitmask & rhs )
  	    Assign the Bitmask value to the value of rhs.


  	inline
  	Bitmask &
  	operator &= ( const Bitmask & rhs )
  	    Set the bits in the Bitmask to 1, only if they are 1
  	    in both the Bitmask and rhs. All other bits are set to 0.

  	inline
  	Bitmask &
  	operator |= ( const Bitmask & rhs )
  	    Set the bits in the Bitmask to 1, if they are 1
  	    in either the Bitmask or rhs. All other bits are set to 0.

  	inline
  	Bitmask &
  	operator ^= ( const Bitmask & rhs )
  	    Set the bits in the Bitmask to 1, if they are not
  	    the same in both Bitmask and rhs. All other bits are set to 0.

  	inline
  	bool
  	operator == ( const Bitmask & rhs ) const
  	    Return true if the Bitmask is == rhs. Else return false.

  	inline
  	bool
  	operator <  ( const Bitmask & rhs ) const
  	    Return true if the Bitmask is <  rhs. Else return false.

  	inline
  	bool
  	operator == ( value_type rhs ) const
  	    Return true if the value of the Bitmask is == rhs. Else return
            false.

  	inline
  	bool
  	operator != ( value_type rhs ) const
  	    Return true if the value of the Bitmask is != rhs. Else return
            false.

  	inline
  	bool
  	operator <  ( value_type rhs ) const
  	    Return true if the value of the Bitmask is < rhs. Else return
            false.

  	inline
  	bool
  	operator <= ( value_type rhs ) const
  	    Return true if the value of the Bitmask is <= rhs. Else return
            false.

  	inline
  	bool
  	operator <  ( value_type rhs ) const
  	    Return true if the value of the Bitmask is < rhs. Else return
            false.

  	inline
  	bool
  	operator >= ( value_type rhs ) const
  	    Return true if the value of the Bitmask is >= rhs. Else return
            false.

  	inline
  	operator bool ( void ) const
  	    Convert the Bitmask to a bool. It will b true if any bit
  	    is a '1'.

  	inline
  	operator value_type ( void ) const
  	    Convert the Bitmask to an value_type.

  	virtual
  	size_type
  	getBinSize( void ) const;
  	    Return the number of bytes that would be written to
  	    a std::ostream to store the data for this
  	    instance.

  	virtual
  	std::ostream &
  	write( std::ostream & dest ) const
  	    Write the Bimask in binary to an std::ostream.
  	    Format: value_type

  	virtual
  	std::istream &
  	read( std::istream & src )
  	    Set the Bitmask by reading the binary form from an std::istream.

  	virtual
  	std::ostream &
  	toStream( std::ostream & dest = std::cout ) const
  	    Convert the Bitmask to a string and write it to an std::ostream.

  	virtual
  	std::istream &
  	fromStream( std::istream & src )
  	    Set the Bitmask by reading an std::istream. The format
  	    expected is a sequence of '0' or '1' chars.

    	virtual const char *
    	getClassName( void ) const;
    	    Return the name of this class (i.e. Bitmask )

  	virtual
  	const char *
  	getVersion( bool withPrjVer = true ) const
  	    Return the version string for the Bitmask. If
  	    withPrjVer == true, the project version info will also
  	    be returned.

  	virtual
  	std::ostream &
  	dumpInfo( std::ostream &	dest = std::cerr,
  		  const char *	prefix = "    ",
  		  bool		showVer = true ) const;
  	    Output detailed information about the current
  	    state of the Bitmask.

  	inline
  	bit &
  	bit::flip( void );
  	    Flip the bit. If it was '0' change it to a '1'. If
  	    it was '1' change it to '0'.

  	inline
  	size_type
  	bit::pos( void ) const
  	    Return the position in the Bitmask of this bit.

  	inline
  	bit &
  	bit::operator =  ( bool rhs );
  	    Assign the bit to the value of rhs.

  	inline
  	bit &
  	bit::operator =  ( const bit & rhs )
  	    Assign the bit to the value of rhs. Does not change the pos.

  	inline
  	bool
  	bit::operator ~  ( void ) const;
  	    Return the one's complement of the bit.

  	inline
  	bit::operator bool ( void ) const;
  	    Return the bit's value converted to a bool.

  	std::ostream &
  	bit::dumpInfo( std::ostream &	dest = std::cerr,
  		       const char *	prefix = "    ",
  		       bool		showVer = true ) const;
  	    Output detailed information about the current
  	    state of the bit.

    Protected Interface:

    Private Methods:

    Associated Functions:

  	inline
    	std::ostream &
    	operator <<( std::ostream & dest, const Bitmask & obj );
  	    Uses Bitmask::toStream to write the Bitmask as a string
  	    to the std::ostream.

  	inline
  	std::istream &
  	operator >> ( std::istream & src, Bitmask & obj );
  	    Uses Bitmask::fromStream to set the Bitmask by reading
  	    the std::istream.

  	inline
  	Bitmask
  	operator &  ( const Bitmask & lhs, const Bitmask & rhs )
  	    Return a Bitmask that is the result of an 'AND" operation using
            lhs with rhs.

  	inline
  	Bitmask
  	operator |  ( const Bitmask & lhs, const Bitmask & rhs )
  	    Return a Bitmask that is the result of a 'OR' operation using
            lhs with rhs.

  	inline
  	Bitmask
  	operator ^  ( const Bitmask & lhs, const Bitmask & rhs )
  	    Return a Bitmask that is the result of a 'XOR' operation using
            lhs with rhs.

  	inline
  	Bitmask
  	operator ~  ( const Bitmask & mask)
  	    Return a Bitmask that is the one's complement of mask
  	    (i.e. mask with all its bits flipped).

  	inline
  	int
  	compare( const Bitmask & one, const Bitmask & two )
  	    Return the difference of one and two by comparing there
  	    values.

  	inline
  	int
  	compare( const Bitmask & one, Bitmask::value_type two )
  	    Return the difference of one and two by comparing there
  	    values.

  	inline
  	int
  	compare( Bitmask::value_type one, const Bitmask & two )
  	    Return the difference of one and two by comparing there
  	    values.

  	inline
  	bool
  	operator == ( Bitmask::value_type lhs, const Bitmask & rhs )
  	    Return true if lhs == rhs. Else return false.

  	inline
  	bool
  	operator != ( Bitmask::value_type lhs, const Bitmask & rhs )
  	    Return true if lhs != rhs. Else return false.

  	inline
  	bool
  	operator <  ( Bitmask::value_type lhs, const Bitmask & rhs )
  	    Return true if lhs < rhs. Else return false.

  	inline
  	bool
  	operator <= ( Bitmask::value_type lhs, const Bitmask & rhs )
  	    Return true if lhs <= rhs. Else return false.

  	inline
  	bool
  	operator >  ( Bitmask::value_type lhs, const Bitmask & rhs )
  	    Return true if lhs > rhs. Else return false.

  	inline
  	bool
  	operator >= ( Bitmask::value_type lhs, const Bitmask & rhs )
  	    Return true if lhs >= rhs. Else return false.


**/

#endif // ! def _clue_Bitmask_hpp_
