#ifndef _Bitmask_hh_
#define _Bitmask_hh_
//
// File:        Bitmask.hh
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  This class provides for easy to use high perfomance
//  bit manipulations. It can be used to manipulate up to
//  32 bits (i.e. a long on most architectures). To work with
//  more than 32 bits, see bit_vector in the STL.
//
//  All position parameters are right to left staring with 0.
//  So, for 00010000, pos 4 is a 1.
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/18/95 04:35
//
// Revision History: (See end of file for Revision Log)
//
// %PID%
//


#include "StlUtilsConfig.hh"
#include <functional>


#if defined( STLUTILS_DEBUG )
#define inline
#endif

class Bitmask
{

public:

  typedef STLUTILS_LONG_U32_T  value_type;

  class bit
  {
  public:
    
    inline bit &    flip( void );
    inline size_t   pos( void ) const;
    
    inline bit &    operator =  ( bool rhs );
    inline bit &    operator =  ( const bit & rhs );
    
    inline bool	    operator ~  ( void ) const;
    inline bool	    operator !  ( void ) const;
    
    inline	    operator bool ( void ) const;

    inline bool	    operator == ( bool rhs ) const;
    inline bool	    operator != ( bool rhs ) const;
    
    ostream &	    toStream( ostream & dest = cout ) const;
    
    ostream &	    dumpInfo( ostream &	    dest = cerr,
			      const char *  prefix = "    ",
			      bool	    showVer = true ) const;

  private:
    friend class Bitmask;

    inline bit( Bitmask & owner, size_t pos );

    Bitmask &	bitmask;
    size_t	bitpos;
    
  };
     
  inline Bitmask( void );
  inline Bitmask( unsigned long val, bool flip = false );
  inline Bitmask( const bit & val );
  inline Bitmask( const Bitmask & from );

  inline Bitmask &  set( void );
  inline Bitmask &  set( size_t pos, bool val = true );
  
  inline Bitmask &  reset( void );
  inline Bitmask &  reset( size_t pos );

  inline Bitmask &  flip( void );
  inline Bitmask &  flip( size_t pos );

  inline bool	    test( size_t pos ) const;
  inline bool	    any( void ) const;
  inline bool	    none( void ) const;

  inline size_t	    count( void ) const;
  inline size_t	    size( void ) const;
  
  inline unsigned long	to_ulong( void ) const;
  inline const char *	to_string( void ) const;
  
  inline int		compare( const Bitmask & two ) const;
  inline int		compare( unsigned long two ) const;
  
  inline bit		operator [] ( size_t pos );
  inline bit	    	operator () ( size_t pos );
  
  inline bool		operator [] ( size_t pos ) const;
  inline bool  	    	operator () ( size_t pos ) const;
  
  inline Bitmask &	operator =  ( unsigned long rhs );

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
  
  inline bool		operator == ( unsigned long rhs ) const;
  inline bool		operator != ( unsigned long rhs ) const;
  inline bool		operator <  ( unsigned long rhs ) const;
  inline bool		operator <= ( unsigned long rhs ) const;
  inline bool		operator >  ( unsigned long rhs ) const;
  inline bool		operator >= ( unsigned long rhs ) const;
  
  inline    	    	operator bool ( void ) const;
  inline    	    	operator unsigned long ( void ) const;

  // libStlUtils Common Class Methods
    
  virtual size_t	getBinSize( void ) const;
  
  virtual ostream &	write( ostream & dest ) const;
  virtual istream &	read( istream & src );

  // use by iostream << and >> operators
  virtual ostream &	toStream( ostream & dest = cout ) const;
  virtual istream &	fromStream( istream & src );
  
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
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

  static const size_t	maxPos;
  
  static const ClassVersion version;
  
protected:

private:

  value_type value;
  
};

#if !defined( inline )
#include <Bitmask.ii>
#else
#undef inline

ostream &
operator << ( ostream & dest, const Bitmask & obj );

istream &
operator >> ( istream & src, Bitmask & obj );
  
ostream &
operator << ( ostream & dest, const Bitmask::bit & obj );

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
compare( const Bitmask & one, unsigned long two );

int
compare( unsigned long one, const Bitmask & two );

bool
operator == ( unsigned long lhs, const Bitmask & rhs );

bool
operator != ( unsigned long lhs, const Bitmask & rhs );

bool
operator <  ( unsigned long lhs, const Bitmask & rhs );

bool
operator <= ( unsigned long lhs, const Bitmask & rhs );

bool
operator >  ( unsigned long lhs, const Bitmask & rhs );

bool
operator >= ( unsigned long lhs, const Bitmask & rhs );

#endif


//
//  Types:
//
//  	class Bitmask
//
//	scalar Bitmask::value_type
//	    An unsigned 32 bit type used to contain the bit data.
//
//	class Bitmask::bit
//	    A bit is a single bit of a Bitmask. It knows both the
//	    position and value from the original Binmask. It
//	    contains a reference to the original Bitmask, so if
//	    the value of that bit changes in the original bitmask,
//	    the bit's value will also change.
//
//  Public Fields:
//
//	static const bit b00;
//	    This is a static variable that represents bit 0 set to true.
//	    b01 through b31 are also available for the rest of the bits.
//
//	static const Bitmask all
//	    This is a static Bitmask with all bits set to 1;
//
//	static const size_t maxPos;
//	    This static variable contains the maximum number of positions
//	    available in the bit mask (i.e. 32).
//
//	static const ClassVersion version;
//	    This contains the version information for the Bitmask class.
//
//  Constructors:
//
//	inline
//  	Bitmask( void );
//	    Construct a default Bitmask with its value set to all 0's.
//
//	inline
//	Bitmask( unsigned long val, bool flip = false )
//	    Construct a bitmask, setting its value to 'val'. If
//	    flip is true, all 0's in val will be 1's, and all 1's
//          will be 0's, in the new bitmask object.
//
//	inline
//	Bitmask( const bit & val )
//	    Construct a Bitmask with its value set to 'val'. The bit's
//          pos and value are both used. So, if a bit has a pos of 3
//          and it's value is 1, then the value of the Bitmask would be
//          binary '1000'.
//
//	inline
//	Bitmask( const Bitmask & from )
//	    Copy constructor used to create a new Bitmask from an old one.
//
//  Public Interface:
//
//	inline
//	Bitmask &
//	set( void );
//	    Set all bits to '1'.
//
//	inline
//  	Bitmask &
//  	set( size_t pos, bool val = true );
//	    Set the bit at 'pos' to 'val'. 
//
//	inline
//	Bitmask &
//	reset( void );
//	    Set all bits to '0'.
//
//	inline
//	Bitmask &
//	reset( size_t pos );
//	    Set the bit a pos to '0';
//
//	inline
//	Bitmask &
//	flip( void );
//	    Flip all the bits in the Bitmask. For each bit that is
//	    a '1', it is set to '0'. For each bit that is a '0',
//	    it is set to '1'.
//
//	inline
//	Bitmask &
//	flip( size_t pos );
//	    Flip the bit at pos. If it was a '0', set it to a '1'.
//	    If it was a '1', set it to '0'.
//
//	inline
//	bool
//	test( size_t pos ) const;
//	    Return true if the bit at 'pos' is a '1' or false if
//	    it a '0';
//
//	inline
//	bool
//	any( void ) const
//	    Return true if any bit in the Bitmask is set to a '1',
//	    else return false.
//
//	inline
//	bool
//	none( void ) const;
//	    Return true if all bits in the Bitmask are set to '0',
//	    else return false.
//
//	inline
//	size_t
//	count( void ) const;
//	    Return the number of bits in the Bitmask that are
//	    set to '1'. (i.e. '0101000' will return 2).
//
//	inline
//	size_t
//	size( void ) const;
//	    Return the maximum number of bits (i.e. 32).
//
//	inline
//	unsigned long
//	to_ulong( void ) const
//	    Return the Bitmask as a unsigned long.
//
//	inline
//	const char *
//	to_string( void ) const
//	    Return the Bitmask as a null terminated string.
//	    (i.e. "00000000000000000000000000111100" )
//
//	inline
//	int
//	compare( const Bitmask & two ) const
//	    Compare the Bitmask value with the value of two.
//	    return 0 if Bitmask == two, return < 0 if Bitmask < two
//          or return > 0 if Bitmask > two.
//
//	inline
//	int
//	compare( unsigned long two ) const
//	    Compare the Bitmask value with the value of two.
//	    return 0 if Bitmask == two, return < 0 if Bitmask < two
//          or return > 0 if Bitmask > two.
//
//	inline
//	bit
//	operator [] ( size_t pos )
//	    Return a bit for the value at pos.
//
//	inline
//	bit
//	operator () ( size_t pos )
//	    Return a bit for the value at pos.
//
//	inline
//	bool
//	operator [] ( size_t pos ) const
//	    Return a bool value for the value at pos.
//
//	inline
//	bool
//	operator () ( size_t pos ) const
//	    Return a bool value for the value at pos.
//
//	inline
//	Bitmask &
//	operator =  ( unsigned long rhs );
//	    Assign the Bitmask to the value of rhs.
//
//	inline
//	Bitmask &
//	operator =  ( const bit & rhs );
//	    Reset the Bitmask and then assign the bit
//	    at 'rhs.pos' to 'rhs' value.
//
//	inline
//	Bitmask &
//	operator &= ( const bit & rhs );
//	    Assign the bit at 'rhs.pos' to 1, only if it is already 1
//	    and rhs's value is 1.
//
//	inline
//	Bitmask &
//	operator |= ( const bit & rhs );
//	    Assign the bit at 'rhs.pos' to 1, if it is already 1
//	    or rhs's value is 1.
//
//	inline
//	Bitmask &
//	operator ^= ( const bit & rhs );
//	    Assign the bit at 'rhs.pos' to 1, if its value and
//	    rhs's value are different.
//
//	inline
//	Bitmask &
//	operator =  ( const Bitmask & rhs )
//	    Assign the Bitmask value to the value of rhs.
//
//
//	inline
//	Bitmask &
//	operator &= ( const Bitmask & rhs )
//	    Set the bits in the Bitmask to 1, only if they are 1
//	    in both the Bitmask and rhs. All other bits are set to 0.
//
//	inline
//	Bitmask &
//	operator |= ( const Bitmask & rhs )
//	    Set the bits in the Bitmask to 1, if they are 1
//	    in either the Bitmask or rhs. All other bits are set to 0.
//
//	inline
//	Bitmask &
//	operator ^= ( const Bitmask & rhs )
//	    Set the bits in the Bitmask to 1, if they are not
//	    the same in both Bitmask and rhs. All other bits are set to 0.
//
//	inline
//	bool
//	operator == ( const Bitmask & rhs ) const
//	    Return true if the Bitmask is == rhs. Else return false.
//
//	inline
//	bool
//	operator <  ( const Bitmask & rhs ) const
//	    Return true if the Bitmask is <  rhs. Else return false.
//
//	inline
//	bool
//	operator == ( unsigned long rhs ) const
//	    Return true if the value of the Bitmask is == rhs. Else return
//          false.
//
//	inline
//	bool
//	operator != ( unsigned long rhs ) const
//	    Return true if the value of the Bitmask is != rhs. Else return
//          false.
//
//	inline
//	bool
//	operator <  ( unsigned long rhs ) const
//	    Return true if the value of the Bitmask is < rhs. Else return
//          false.
//
//	inline
//	bool
//	operator <= ( unsigned long rhs ) const
//	    Return true if the value of the Bitmask is <= rhs. Else return
//          false.
//
//	inline
//	bool
//	operator <  ( unsigned long rhs ) const
//	    Return true if the value of the Bitmask is < rhs. Else return
//          false.
//
//	inline
//	bool
//	operator >= ( unsigned long rhs ) const
//	    Return true if the value of the Bitmask is >= rhs. Else return
//          false.
//
//	inline
//	operator bool ( void ) const
//	    Convert the Bitmask to a bool. It will b true if any bit
//	    is a '1'.
//
//	inline
//	operator unsigned long ( void ) const
//	    Convert the Bitmask to an unsigned long.
//
//	virtual
//	size_t
//	getBinSize( void ) const;
//	    Return the number of bytes that would be written to
//	    a ostream to store the data for this
//	    instance.
//
//	virtual
//	ostream &
//	write( ostream & dest ) const
//	    Write the Bimask in binary to an ostream.
//	    Format: unsigned long
//
//	virtual
//	istream &
//	read( istream & src )
//	    Set the Bitmask by reading the binary form from an istream.
//
//	virtual
//	ostream &
//	toStream( ostream & dest = cout ) const
//	    Convert the Bitmask to a string and write it to an ostream.
//
//	virtual
//	istream &
//	fromStream( istream & src )
//	    Set the Bitmask by reading an istream. The format
//	    expected is a sequence of '0' or '1' chars.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. Bitmask )
//
//	virtual
//	const char *
//	getVersion( bool withPrjVer = true ) const
//	    Return the version string for the Bitmask. If
//	    withPrjVer == true, the project version info will also
//	    be returned.
//
//	virtual
//	ostream &
//	dumpInfo( ostream &	dest = cerr,
//		  const char *	prefix = "    ",
//		  bool		showVer = true ) const;
//	    Output detailed information about the current
//	    state of the Bitmask. 
//
//	inline
//	bit &
//	bit::flip( void );
//	    Flip the bit. If it was '0' change it to a '1'. If
//	    it was '1' change it to '0'.
//
//	inline
//	size_t
//	bit::pos( void ) const
//	    Return the position in the bitmask of this bit.
//
//	inline
//	bit &
//	bit::operator =  ( bool rhs );
//	    Assign the bit to the value of rhs.
//
//	inline
//	bit &
//	bit::operator =  ( const bit & rhs )
//	    Assign the bit to the value of rhs. Does not change the pos.
//
//	inline
//	bool
//	bit::operator ~  ( void ) const;
//	    Return the one's complement of the bit.
//
//	inline
//	bit::operator bool ( void ) const;
//	    Return the bit's value converted to a bool.
//
//	ostream &
//	bit::dumpInfo( ostream &	dest = cerr,
//		       const char *	prefix = "    ",
//		       bool		showVer = true ) const;
//	    Output detailed information about the current
//	    state of the bit. 
//	
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
//
//	inline
//  	ostream &
//  	operator <<( ostream & dest, const Bitmask & obj );
//	    Uses Bitmask::toStream to write the Bitmask as a string
//	    to the ostream.
//
//	inline
//	istream &
//	operator >> ( istream & src, Bitmask & obj );
//	    Uses Bitmask::fromStream to set the Bitmask by reading
//	    the istream.
//
//	inline
//	Bitmask
//	operator &  ( const Bitmask & lhs, const Bitmask & rhs )
//	    Return a Bitmask that is the result of an 'AND" operation using
//          lhs with rhs.
//
//	inline
//	Bitmask
//	operator |  ( const Bitmask & lhs, const Bitmask & rhs )
//	    Return a Bitmask that is the result of a 'OR' operation using
//          lhs with rhs.
//
//	inline
//	Bitmask
//	operator ^  ( const Bitmask & lhs, const Bitmask & rhs )
//	    Return a Bitmask that is the result of a 'XOR' operation using
//          lhs with rhs.
//
//	inline
//	Bitmask
//	operator ~  ( const Bitmask & mask)
//	    Return a Bitmask that is the one's complement of mask
//	    (i.e. mask with all its bits flipped).
//
//	inline
//	int
//	compare( const Bitmask & one, const Bitmask & two )
//	    Return the difference of one and two by comparing there
//	    values.
//
//	inline
//	int
//	compare( const Bitmask & one, unsigned long two )
//	    Return the difference of one and two by comparing there
//	    values.
//
//	inline
//	int
//	compare( unsigned long one, const Bitmask & two )
//	    Return the difference of one and two by comparing there
//	    values.
//
//	inline
//	bool
//	operator == ( unsigned long lhs, const Bitmask & rhs )
//	    Return true if lhs == rhs. Else return false.
//
//	inline
//	bool
//	operator != ( unsigned long lhs, const Bitmask & rhs )
//	    Return true if lhs != rhs. Else return false.
//
//	inline
//	bool
//	operator <  ( unsigned long lhs, const Bitmask & rhs )
//	    Return true if lhs < rhs. Else return false.
//
//	inline
//	bool
//	operator <= ( unsigned long lhs, const Bitmask & rhs )
//	    Return true if lhs <= rhs. Else return false.
//
//	inline
//	bool
//	operator >  ( unsigned long lhs, const Bitmask & rhs )
//	    Return true if lhs > rhs. Else return false.
//
//	inline
//	bool
//	operator >= ( unsigned long lhs, const Bitmask & rhs )
//	    Return true if lhs >= rhs. Else return false.
//
//	
//  See Also:
//
//	Bit(3)
//
//  Files:
//
//	Bitmask.hh, Bitmask.ii, libStlUtils.a
//
//  Documented Ver: 2.7
//  Tested Ver: 2.7
//	
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.4  2001/07/28 01:15:00  houghton
// *** empty log message ***
//
// Revision 5.3  2001/07/26 19:29:01  houghton
// *** empty log message ***
//
// Revision 5.2  2000/06/04 17:58:04  houghton
// Updated documentation.
//
// Revision 5.1  2000/05/25 10:33:14  houghton
// Changed Version Num to 5
//
// Revision 4.4  1998/10/13 16:13:46  houghton
// Changed ValueType to value_type for consistency.
//
// Revision 4.3  1998/07/20 11:19:39  houghton
// Port(Hpux): Added operatoer == (bool) && operator != (bool).
//
// Revision 4.2  1997/09/19 11:20:30  houghton
// Changed to use new portable types (STLUTILS*_T).
//
// Revision 4.1  1997/09/17 15:12:10  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:09  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1996/11/19 12:19:40  houghton
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
//
// Revision 3.1  1996/11/14 01:23:26  houghton
// Changed to Release 3
//
// Revision 2.8  1996/11/11 13:30:11  houghton
// Added Bitmask::bit::operator ! ( void )
// Added Bitmask::bit::operator == ( bool )
// Added Bitmask::bit::operator != ( bool )
// Added ::operator == ( bool lhs, const Bitmask::bit & rhs );
// Added ::operator != ( bool lhs, const Bitmask::bit & rhs );
//
// Revision 2.7  1996/11/04 13:24:14  houghton
// Restructure header comments layout.
// Updated and verified header comment documentation.
// Removed BinObject/BinStream support.
// Added Bitmask::bit::toStream
// Added Bitmask::bit::dumpInfo
// Added Copy Constructor.
// Changed to_string to return a const char *.
// Added Bitmask::operator = ( const Bitmask & rhs )
// Added Bitmask::fromStream().
// Removed static const bit b32 (no such thing).
// Added ::operator >> ( istream, Bitmask )
//
// Revision 2.6  1996/05/11 11:01:06  houghton
// Added operators <= and >=.
//
// Revision 2.5  1996/05/02 01:27:22  houghton
// Add missing operators for <= & >= long rhs.
//
// Revision 2.4  1996/04/27 12:50:50  houghton
// Cleanup.
//
// Revision 2.3  1995/12/04 11:16:41  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
// Bug Fix - Now there is a special type for all single 'bit' values.
//
// Revision 2.2  1995/11/10  14:08:33  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:17  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:31  houghton
// Revised
//
//

#endif // ! def _Bitmask_hh_ 
