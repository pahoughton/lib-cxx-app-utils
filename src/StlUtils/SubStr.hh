#ifndef _SubStr_hh_
#define _SubStr_hh_
//
// File:        SubStr.hh
// Project:	StlUtils
// Desc:        
//
//  	A 'SubStr' is a section of a 'Str'. Any modifications to
//  	the 'SubStr' modify the 'Str' it is a section of.
//
//  	Detail documentation is at the end of this header file.
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     05/30/95 14:59
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include "StlUtilsConfig.hh"
#include <cstddef>
#include <iostream>


#if defined( STLUTILS_DEBUG )
#define inline
#endif

class Str;

class SubStr
{

public:

  typedef STLUTILS_U32_SIZE_T	size_type;
  
  static const size_type npos;
  
  inline SubStr( Str & src, size_type pos = 0, size_type len = NPOS);
  inline SubStr( const Str & src, size_type pos = 0, size_type len = NPOS);

  inline size_type    	size( void ) const; 
  inline size_type    	length( void ) const; 
  inline bool	    	empty( void ) const; 

  inline Str &		of( void );
  inline const Str &	of( void ) const;

  inline size_type    	    copy( char *    dest,
				  size_type destLen,
				  size_type start = 0 ) const;

  inline bool	to( bool &   	     dest ) const;
  inline bool	to( int &   	    	dest,
		    unsigned short	base = 0,
		    bool		stopAtNonDigit = false ) const;
  inline bool	to( short & 	    	dest,
		    unsigned short	base = 0,
		    bool		stopAtNonDigit = false ) const;
  inline bool	to( long &  	    	dest,
		    unsigned short	base = 0,
		    bool		stopAtNonDigit = false ) const;
  inline bool	to( float & 	    	dest,
		    unsigned short	base = 0,
		    bool		stopAtNonDigit = false ) const;
  inline bool	to( double & 	    	dest,
		    unsigned short	base = 0,
		    bool		stopAtNonDigit = false ) const;
  inline bool	to( unsigned int &  	dest,
		    unsigned short	base = 0,
		    bool		stopAtNonDigit = false ) const;
  inline bool	to( unsigned short &  	dest,
		    unsigned short	base = 0,
		    bool		stopAtNonDigit = false ) const;
  inline bool	to( unsigned long  &	dest,
		    unsigned short	base = 0,
		    bool		stopAtNonDigit = false ) const;

#if defined( STLUTILS_HAVE_LONG_LONG )
  inline bool	to( long long  &	dest,
		    unsigned short	base = 0,
		    bool		stopAtNonDigit = false ) const;
  
  inline bool	to( unsigned long long  &   dest,
		    unsigned short	    base = 0,
		    bool		    stopAtNonDigit = false ) const;
#endif
  
  inline bool	    	toBool( void ) const;
  
  inline int	    	toInt( unsigned short base = 0,
			       bool	      stopAtNonDigit = false ) const;
  
  inline long	    	toLong( unsigned short base = 0,
				bool	       stopAtNonDigit = false ) const;
  
  inline double    	toDouble( unsigned short base = 0,
				  bool	         stopAtNonDigit = false ) const;
  
  inline unsigned int	toUInt( unsigned short base = 0,
				bool	       stopAtNonDigit = false ) const;
  
  inline unsigned long	toULong( unsigned short base = 0,
				 bool	        stopAtNonDigit = false ) const;


#if defined( STLUTILS_HAVE_LONG_LONG )
  inline long long	toLongLong( unsigned short base = 0,
				    bool stopAtNonDigit = false ) const;

  inline unsigned long long toULongLong( unsigned short base = 0,
					 bool stopAtNonDigit = false ) const;
#endif

  int 	    compare( const Str &    two,
		     size_type      start = 0,
		     size_type      len = npos ) const; 
  int	    compare( const SubStr & two,
		     size_type      start = 0,
		     size_type      len = npos ) const; 
  int	    compare( const char *   two,
		     size_type      start = 0,
		     size_type      len = npos ) const; 
  
  friend int	compare( const char * 	one,
			 const SubStr & two,
			 size_type      len = npos ); 
  
  int	    fcompare( const Str &    two,
		      size_type      start = 0,
		      size_type      len = npos ) const; 
  int	    fcompare( const SubStr & two,
		      size_type      start = 0,
		      size_type      len = npos ) const; 
  int	    fcompare( const char *   two,
		      size_type      start = 0,
		      size_type      len = npos ) const; 
  
  friend int	fcompare( const char *    one,
			  const SubStr &  two,
			  size_type       len = npos ); 

  inline char &     operator [] ( size_type index ); 
  inline char       operator [] ( size_type index ) const;
  
  inline SubStr &   operator =  ( const SubStr & rhs ); 
  inline SubStr &   operator =  ( const Str & rhs ); 
  inline SubStr &   operator =  ( const char * rhs ); 
  inline SubStr &   operator =  ( char rhs ); 
  
  inline SubStr &   operator += ( const Str & rhs ); 
  inline SubStr &   operator += ( const SubStr & rhs ); 
  inline SubStr &   operator += ( const char * rhs ); 
  inline SubStr &   operator += ( char rhs ); 

  inline bool       operator == ( const SubStr & rhs ) const; 
  inline bool       operator == ( const Str & rhs ) const; 
  inline bool       operator == ( const char * rhs ) const; 
  
  inline bool       operator <  ( const SubStr & rhs ) const; 
  inline bool       operator <  ( const Str & rhs ) const; 
  inline bool       operator <  ( const char * rhs ) const; 

  inline bool       operator != ( const SubStr & rhs ) const; 
  inline bool       operator != ( const Str & rhs ) const; 
  inline bool       operator != ( const char * rhs ) const; 
  
  inline bool       operator >  ( const SubStr & rhs ) const; 
  inline bool       operator >  ( const Str & rhs ) const;
  inline bool       operator >  ( const char * rhs ) const;

  inline bool       operator <= ( const SubStr & rhs ) const; 
  inline bool       operator <= ( const Str & rhs ) const;
  inline bool       operator <= ( const char * rhs ) const;

  inline bool       operator >= ( const SubStr & rhs ) const; 
  inline bool       operator >= ( const Str & rhs ) const;
  inline bool       operator >= ( const char * rhs ) const;
  
  // libStlUtils Common Class Methods

  size_type	    getBinSize( void ) const;

  ostream &	    write( ostream & dest ) const;
  istream &	    read( istream & src );
  
  virtual ostream & toStream( ostream & dest = cout ) const;

  friend inline ostream &  operator << ( ostream & dest, const SubStr & src ); 
  friend inline istream &  operator >> ( istream & src, SubStr & dest ); 
  
  inline bool	    good( void ) const;
  const char *	    error( void ) const;
  const char *	    getClassName( void ) const;
  const char *	    getVersion( bool withPrjVer = true ) const;
  ostream &	    dumpInfo( ostream &	    dest = cerr,
			      const char *  prefix = "    ",
			      bool	    showVer = true ) const;
  
  static const ClassVersion version;

private:
  
  friend class 	Str;
  
  inline const char * 	strbase( void ) const;
  static Str dummyStr;
  
  Str &	    	str;
  const Str &   constStr;
  size_type    	pos;
  size_type    	len;

};

#if !defined( inline )
#include <SubStr.ii>
#else
#undef inline

// These are the global functions that are defined in the .ii
// file. They are declared here so their prototypes will
// be available when STLUTILS_DEBUG is defined.

int
compare( const SubStr &	    one,
	 const char *	    two,
	 SubStr::size_type  len = SubStr::npos ); 
  
int
fcompare( const SubStr &    one,
	  const char *	    two,
	  SubStr::size_type len = SubStr::npos ); 

Str
operator + ( const SubStr & lhs, const Str & rhs );

Str
operator + ( const SubStr & lhs, const SubStr & rhs );

Str
operator + ( const SubStr & lhs, const char * rhs );

Str
operator + ( const char * lhs, const SubStr & rhs );

bool
operator == ( const char * lhs, const SubStr & rhs );

bool
operator <  ( const char * lhs, const SubStr & rhs );

bool
operator != ( const char * lhs, const SubStr & rhs );

bool
operator >  ( const char * lhs, const SubStr & rhs );

bool
operator <= ( const char * lhs, const SubStr & rhs );

bool
operator >= ( const char * lhs, const SubStr & rhs );


bool	    	StringToBool( const SubStr & str );
int 	    	StringToInt( const SubStr & str, unsigned short base = 0 );
long	    	StringToLong( const SubStr & str, unsigned short base = 0 );
double	    	StringToDouble( const SubStr & str, unsigned short base = 0 );
unsigned int 	StringToUInt( const SubStr & str, unsigned short base = 0 );
unsigned long	StringToULong( const SubStr & str, unsigned short base = 0 );

#endif  

//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	SubStr	class
//
//  Constructors:
//
//  	SubStr( );
//
//  Destructors:
//
//  Public Interface:
//
//  	size_type
//  	size( void ) const;
//
//  	size_type
//  	length( void ) const;
//
//  	bool
//  	empty( void ) const;
//
//  	bool
//  	to( int & dest, unsigned short base = 0 ) const;
//
//  	bool
//  	to( short & dest, unsigned short base = 0 ) const;
//
//  	bool
//  	to( long & dest, unsigned short base = 0 ) const;
//
//  	bool
//  	to( double & dest, unsigned short base = 0 ) const;
//
//  	bool
//  	to( unsigned int & dest, unsigned short base = 0 ) const;
//
//  	bool
//  	to( unsigned short & dest, unsigned short base = 0 ) const;
//
//  	bool
//  	to( unsigned long & dest, unsigned short base = 0 ) const;
//
//  	bool
//  	toBool( void ) const;
//
//  	bool
//  	toInt( unsigned short base = 0 )const;
//
//  	bool
//  	tShort( unsigned short base = 0 )const;
//
//  	bool
//  	toLong( unsigned short base = 0 )const;
//
//  	bool
//  	toDouble( unsigned short base = 0 )const;
//
//  	bool
//  	toUInt( unsigned short base = 0 )const;
//
//  	bool
//  	toUShort( unsigned short base = 0 )const;
//
//  	bool
//  	toULong( unsigned short base = 0 )const;
//
//  	int
//  	compare( const Str & two,
//  	    	 size_type start = 0,
//  	    	 size_type len = NPOS ) const;
//
//  	int
//  	compare( const SubStr & two,
//  	    	 size_type start = 0,
//  	    	 size_type len = NPOS ) const;
//
//  	int
//  	compare( const char * two,
//  	    	 size_type start = 0,
//    	    	 size_type len = NPOS ) const;
//
//  	friend int
//  	compare( const char * one,
//  	    	 size_type start = 0,
//  	    	 size_type len = NPOS ) const;
//
//  	int
// 	fcompare( const Str & two,
//  	    	  size_type start = 0,
//  	    	  size_type len = NPOS ) const;
//
//  	int
//  	fcompare( const SubStr & two,
//  	    	  size_type start = 0,
//  	    	  size_type len = NPOS ) const;
//
//  	int
//  	fcompare( const char * two,
//  	    	  size_type start = 0,
//  	    	  size_type len = NPOS ) const;
//
//  	friend int
//  	fcompare( const char * one,
//  	    	  size_type start = 0,
//  	    	  size_type len = NPOS ) const;
//
//  	char &
//  	operator [] ( size_type index );
//
//  	char
//  	operator [] ( size_type index ) const;
//
//  	SubStr &
//  	operator = ( const SubStr & src );
//
//  	SubStr &
//  	operator = ( const Str & src );
//
//  	SubStr &
//  	operator = ( const char * src );
//
//  	SubStr &
//  	operator = ( const char src );
//
//  	bool
//  	operator == ( const SubStr & two ) const;
//
//  	bool
//  	operator == ( const Str & two ) const;
//
//  	bool
//  	operator == ( const char * two ) const;
//
//  	bool
//  	operator < ( const SubStr & two ) const;
//
//  	bool
//  	operator < ( const Str & two ) const;
//
//  	bool
//  	operator < ( const char * two ) const;
//
//  	bool
//  	operator != ( const Str & two ) const;
//
//  	bool
//  	operator != ( const char * two ) const;
//
//  	bool
//  	operator > ( const Str & two ) const;
//
//  	bool
//  	operator > ( const char * two ) const;
//
//  	bool
//  	operator <= ( const Str & two ) const;
//
//  	bool
//  	operator <= ( const char * two ) const;
//
//  	bool
//  	operator >= ( const Str & two ) const;
//
//  	bool
//  	operator >= ( const char * two ) const;
//
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. SubStr )
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
//  	operator <<( ostream & dest, const SubStr & obj );
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.6  1999/05/09 13:07:00  houghton
// Added long long support.
//
// Revision 4.5  1998/10/13 16:26:19  houghton
// Changed to use new standard includes.
// Cleanup #if def Linux.
//
// Revision 4.4  1998/04/02 14:18:39  houghton
// Port(Linux): functional.h implements != operator.
//
// Revision 4.3  1998/02/18 13:22:53  houghton
// Added stopAtNonDigit flag to to() methods.
//
// Revision 4.2  1997/09/19 11:21:16  houghton
// Changed to use new portable types (STLUTILS*_T).
//
// Revision 4.1  1997/09/17 15:13:06  houghton
// Changed to Version 4
//
// Revision 3.6  1997/09/17 11:08:56  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.5  1997/08/28 16:33:07  houghton
// Bug-Fix: changed toStream to virtual (was inline) and added support
//     for setw(n) (the width was being ignored).
//
// Revision 3.4  1997/08/17 22:35:46  houghton
// Added size_type.
// Added copy( const char * ... ).
//
// Revision 3.3  1997/04/03 23:23:22  houghton
// Changed include stddef to stddef.h
//
// Revision 3.2  1996/11/20 12:13:10  houghton
// Removed support for BinStream.
//
// Revision 3.1  1996/11/14 01:24:23  houghton
// Changed to Release 3
//
// Revision 2.6  1996/05/25 12:36:22  houghton
// Added of method. returns owning Str.
//
// Revision 2.5  1996/05/03 16:13:49  houghton
// AIX Port cleanup.
//
// Revision 2.4  1996/02/29 19:07:29  houghton
// Added some ifndefs for GNU
//
// Revision 2.3  1995/11/10 18:47:27  houghton
// Fixed error in comments
//
// Revision 2.2  1995/11/10  14:08:41  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:41:17  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:54  houghton
// Ports and Version ID changes
//

#endif // ! def _SubStr_hh_ 
