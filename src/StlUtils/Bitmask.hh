#ifndef _Bitmask_hh_
#define _Bitmask_hh_
//
// File:        Bitmask.hh
// Desc:        
//
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/18/95 04:35
//
// Revision History:
//
// $Log$
// Revision 2.4  1996/04/27 12:50:50  houghton
// Cleanup.
//
// Revision 2.3  1995/12/04 11:16:41  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
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

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <BinStream.hh>
#include <Str.hh>
#else
#include <ClueCfg.hh>
#include <BinStrm.hh>
#include <Str.hh>
#endif


#if defined( CLUE_DEBUG )
#define inline
#endif

class Bitmask : public BinObject
{

public:

  typedef ULong  ValueType;

  class bit
  {
  public:
    
    inline bit &    flip( void );
    inline size_t   pos( void ) const;
    
    inline bit &    operator =  ( bool rhs );
    inline bit &    operator =  ( const bit & rhs );
    
    inline bool	    operator ~  ( void ) const;
    inline	    operator bool ( void ) const;

  private:
    friend class Bitmask;

    inline bit( Bitmask & owner, size_t pos );

    Bitmask &	bitmask;
    size_t	bitpos;
    
  };
     
  inline Bitmask( void );
  inline Bitmask( const bit & val );
  inline Bitmask( unsigned long val, bool flip = false );

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
  inline Str		to_string( void ) const;
  
  inline int		compare( const Bitmask & two ) const;
  inline int		compare( unsigned long two ) const;
  
  inline Bitmask &	operator =  ( unsigned long rhs );

  inline Bitmask &	operator =  ( const bit & rhs );
  inline Bitmask & 	operator &= ( const bit & rhs );
  inline Bitmask & 	operator |= ( const bit & rhs );
  inline Bitmask & 	operator ^= ( const bit & rhs );

  inline Bitmask & 	operator &= ( const Bitmask & rhs );
  inline Bitmask & 	operator |= ( const Bitmask & rhs );
  inline Bitmask & 	operator ^= ( const Bitmask & rhs );

  inline bit		operator [] ( size_t pos );
  inline bit	    	operator () ( size_t pos );
  
  inline bool		operator [] ( size_t pos ) const;
  inline bool  	    	operator () ( size_t pos ) const;
  
  inline bool		operator == ( const Bitmask & rhs ) const;
  inline bool		operator <  ( const Bitmask & rhs ) const;

  inline bool		operator == ( unsigned long rhs ) const;
  inline bool		operator != ( unsigned long rhs ) const;
  inline bool		operator <  ( unsigned long rhs ) const;
  inline bool		operator >  ( unsigned long rhs ) const;
  
  inline    	    	operator bool ( void ) const;
  inline    	    	operator unsigned long ( void ) const;

  // libClue Common Class Methods
    
  virtual size_t	getBinSize( void ) const;
  virtual BinStream &	write( BinStream & dest ) const;
  virtual BinStream &	read( BinStream & src );
  
  virtual ostream &	write( ostream & dest ) const;
  virtual istream &	read( istream & src );

  virtual ostream &	toStream( ostream & dest = cout ) const;
  
  friend inline ostream & operator << ( ostream & dest, const Bitmask & obj );
  
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
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
  static const bit b32;
  static const Bitmask all;

  static const size_t	maxPos;
  
  static const ClassVersion version;
  
protected:

private:

  ValueType value;
  
};

#if !defined( inline )
#include <Bitmask.ii>
#else
#undef inline

Bitmask
operator & ( const Bitmask & lhs, const Bitmask & rhs );
  
Bitmask
operator | ( const Bitmask & lhs, const Bitmask & rhs );

Bitmask
operator ^ ( const Bitmask & lhs, const Bitmask & rhs );

Bitmask
operator ~ ( const Bitmask & mask );

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
operator >  ( unsigned long lhs, const Bitmask & rhs );

#endif


//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	Bitmask	class
//
//  Constructors:
//
//  	Bitmask( );
//
//  Destructors:
//
//  Public Interface:
//
//  	Bitmask( void );
//
//  	Bitmask( size_t pos );
//
//  	Bitmask( unsigned long set, bool flip );
// 
//  	Bitmask &
//  	set( size_t pos );
//
//  	Bitmask &
//  	clear( size_t pos );
//
//  	Bitmask &
//  	clear( void );
//
//  
//  	bool
//  	isSet( size_t pos ) const;
//
//  	bool
//  	isClear( size_t pos ) const;
//
//  	unsigned long
//  	all( void ) const;
//  
//  	size_t
//  	getStreamSize( void ) const;
//
//  	ostream &
//  	write( ostream & dest ) const;
//
//  	istream &
//  	read( istream & src );
//  
//  	int
//  	compare( const Bitmask & two ) const;
//
//  	int
//  	compare( unsigned long two ) const;
//  
//  	Bitmask &
//  	operator =  ( unsigned long rhs );
//
//  	Bitmask &
//    	operator &= ( const Bitmask & rhs );
//
//  	Bitmask &
//  	operator |= ( const Bitmask & rhs );
//
//  	Bitmask &
//  	operator ^= ( const Bitmask & rhs );
//
//  	bool
//  	operator () ( size_t pos ) const;
//
//  	bool
//  	operator == ( const Bitmask & rhs ) const;
//
//  	bool
//  	operator <  ( const Bitmask & rhs ) const;
//
//  	bool
//  	operator == ( unsigned long rhs ) const;
//
//  	bool
//  	operator != ( unsigned long rhs ) const;
//
//  	bool
//  	operator <  ( unsigned long rhs ) const;
//
//  	bool
//  	operator >  ( unsigned long rhs ) const;
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. Bitmask )
//
//  	virtual Bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const Bitmask & obj );
//

#endif // ! def _Bitmask_hh_ 
