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
// Revision 5.1  2000/05/25 10:33:17  houghton
// Changed Version Num to 5
//
// Revision 4.3  1998/10/13 16:25:10  houghton
// Changed to use new standard includes.
//
// Revision 4.2  1998/07/20 11:27:16  houghton
// Bug-Fix: no need for default constructor declaration.
//
// Revision 4.1  1997/09/17 15:12:59  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:08:50  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/04/03 23:23:22  houghton
// Changed include stddef to stddef.h
//
// Revision 3.2  1996/11/20 12:12:50  houghton
// Changed strstream to strstream.h because it is not part of the standard.
//
// Revision 3.1  1996/11/14 01:24:14  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 14:28:24  houghton
// Added include stddef.
//
// Revision 2.3  1996/04/27 13:09:15  houghton
// Cleanup includes.
//
// Revision 2.2  1995/11/10 14:08:41  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:41:07  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:46  houghton
// Ports and Version ID changes
//
//

#include "StlUtilsConfig.hh"
#include <cstddef>
#include <strstream.h>


#if defined( STLUTILS_DEBUG )
#define inline
#endif

class STLUTILS_CLASS_T Str;
class STLUTILS_CLASS_T SubStr;

class STLUTILS_CLASS_T StrStreambuf : public strstreambuf
{

public:
  
  inline size_t	    	plen(void) STLUTILS_STRBUF_CONST_RDBUF;
  inline size_t	    	psize(void) STLUTILS_STRBUF_CONST_RDBUF;
  inline const char * 	cstr(void);  

  const char *		getClassName( void ) const;
  const char *		getVersion( bool withPrjVer = true ) const;
  
  ostream &		dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true );


  static const ClassVersion version;
  
private:

#if defined( STLUTILS_STRBUF_PBASE )
  char * pbase( void ) { return( base() ); }
#endif
  
  inline const char * 	strbase( void ) STLUTILS_STRBUF_CONST_RDBUF;
  
  friend class Str;
  friend class SubStr;

};

#if !defined( inline )
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
//  	size_t
//  	plen(void) STR_CONST_RDBUF;
//
//  	size_t
//  	psize(void) STR_CONST_RDBUF;
//
//  	const char *
//  	cstr(void);  
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
