#ifndef _StrStreambuf_hh_
#define _StrStreambuf_hh_
//
// File:        StrStreambuf.hh
// Desc:        
//
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/30/95 11:09
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:33  houghton
// Initaial implementation
//
//

#include <ClueConfig.hh>

#include <strstream>

#include <cstddef>

class Str;
class SubStr;

#if !defined( AIX )
#define STREAMBUF_CONST_RDBUF
#endif

#if defined( STREAMBUF_COST_RDBUF )
#define STR_CONST_RDBUF const
#else
#define STR_CONST_RDBUF
#endif

#ifdef  CLUE_DEBUG
#define inline
#endif

class StrStreambuf : public strstreambuf
{

public:

  inline size_t	    	plen(void) STR_CONST_RDBUF;
  inline size_t	    	psize(void) STR_CONST_RDBUF;
  inline const char * 	cstr(void);  

  const char *		getClassName( void ) const;
  
  ostream &		dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true );

  const char *	    getVersion( void ) const;
  static const char version[];
  
private:

#ifdef AIX
  char * pbase( void ) { return( base() ); }
#endif
  
  inline const char * 	strbase( void ) STR_CONST_RDBUF;

  friend class Str;
  friend class SubStr;

};

#ifndef inline
#include <StrStreambuf.ii>
#else
#undef inline
#endif

//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	StrStreambuf	class
//
//  Constructors:
//
//  	StrStreambuf( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. StrStreambuf )
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
//  	operator <<( ostream & dest, const StrStreambuf & obj );
//
#endif // ! def _StrStreambuf_hh_ 
