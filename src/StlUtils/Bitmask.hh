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
// Revision 1.2  1995/11/05 14:44:23  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <iostream>
#include <algorithm>
#include <cstddef>
#else
#include <ClueCfg.hh>
#include <iostream>
#include <algorithm>
#include <cstddef>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class Bitmask
{

public:

  typedef unsigned long  ValueType;

  inline Bitmask( void );
  inline Bitmask( size_t pos );
  inline Bitmask( unsigned long set, bool flip );
  
  inline Bitmask &  set( size_t pos );
  inline Bitmask &  clear( size_t pos );
  inline Bitmask &  clear( void );
  
  inline bool		isSet( size_t pos ) const;
  inline bool		isClear( size_t pos ) const;

  inline unsigned long	all( void ) const;
  
  inline size_t	    getStreamSize( void ) const;
  inline ostream &  write( ostream & dest ) const;
  inline istream &  read( istream & src );
  
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

  inline const char *	getClassName( void ) const;
  inline ostream &	toStream( ostream & dest = cout ) const;
  ostream &		dumpInfo( ostream & dest = cerr ) const;
  
  static const size_t	maxPos;
  static const char	version[];
  
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

ostream &
operator << ( ostream & dest, const Bitmask & obj );
  
#endif


#endif // ! def _Bitmask_hh_ 
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
