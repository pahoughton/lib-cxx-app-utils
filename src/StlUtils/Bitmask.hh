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
// Revision 2.2  1995/11/10 14:08:33  houghton
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
#include <iostream>
#include <algorithm>
#include <cstddef>
#else
#include <ClueCfg.hh>
#include <BinStrm.hh>
#include <iostream>
#include <algorithm>
#include <cstddef>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class Bitmask : public BinObject
{

public:

  typedef ULong  ValueType;

  inline Bitmask( void );
  inline Bitmask( size_t pos );
  inline Bitmask( unsigned long set, bool flip );
  
  inline Bitmask &  set( size_t pos );
  inline Bitmask &  clear( size_t pos );
  inline Bitmask &  clear( void );
  
  inline bool		isSet( size_t pos ) const;
  inline bool		isClear( size_t pos ) const;

  inline unsigned long	all( void ) const;
  
  inline int	    compare( const Bitmask & two ) const;
  inline int	    compare( unsigned long two ) const;
  
  inline Bitmask &	operator =  ( unsigned long rhs );
  inline Bitmask & 	operator &= ( const Bitmask & rhs );
  inline Bitmask & 	operator |= ( const Bitmask & rhs );
  inline Bitmask & 	operator ^= ( const Bitmask & rhs );

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
  
  static const ClassVersion version;
  
  static const size_t	maxPos;
  
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
