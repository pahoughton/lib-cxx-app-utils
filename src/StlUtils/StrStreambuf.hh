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
// Revision 1.2  1995/11/05 14:44:46  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <strstream>
#include <cstddef>
#else
#include <ClueCfg.hh>
#include <strstream>
#include <cstddef>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class CLUE_CLASS_T Str;
class CLUE_CLASS_T SubStr;

class CLUE_CLASS_T StrStreambuf : public strstreambuf
{

public:
  StrStreamBuf( void );
  
  inline size_t	    	plen(void) CLUE_STRBUF_CONST_RDBUF;
  inline size_t	    	psize(void) CLUE_STRBUF_CONST_RDBUF;
  inline const char * 	cstr(void);  

  const char *		getClassName( void ) const;
  const char *		getVersion( bool withPrjVer = true ) const;
  
  ostream &		dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true );


  static const ClassVersion version;
  
private:

#if defined( CLUE_STRBUF_PBASE )
  char * pbase( void ) { return( base() ); }
#endif
  
  inline const char * 	strbase( void ) CLUE_STRBUF_CONST_RDBUF;
  
  friend class Str;
  friend class SubStr;

};

#if !defined( inline )
#if !defined( CLUE_SHORT_FN )
#include <StrStreambuf.ii>
#else
#include <StrSbuf.ii>
#endif
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
