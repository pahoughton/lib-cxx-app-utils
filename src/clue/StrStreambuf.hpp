#ifndef _clue_StrStreambuf_hpp_
#define _clue_StrStreambuf_hpp_
// 1995-05-30 (cc) Paul Houghton - (paul4hough@gmail.com)

#include <iostream>
#include <sstream>
#include <cstddef>

namespace clue {

class Str;
class SubStr;

class StrStreambuf : public std::stringbuf
{

public:

  inline size_t	    	plen(void) {
    return( pptr() - pbase() );
  }

  inline size_t	    	psize(void) {
    return( epptr() - pbase() );
  }

  inline const char * 	cstr(void) {
    sputc(0);
    seekoff( -1, std::ios::cur, std::ios::out );

    return( pbase() );
  }

  void			readPrep( void );

  std::ostream &	dumpInfo( std::ostream & dest = std::cerr,
				  const char *	 prefix = "    " );

private:

  //char * pbase( void ) { return( base() ); }

  inline const char * 	strbase( void ) const {
    return( pbase() );
  };

  friend class Str;
  friend class SubStr;

};

}; // namespace clue
/*
  	size_t
  	plen(void) STR_CONST_RDBUF;

  	size_t
  	psize(void) STR_CONST_RDBUF;

  	const char *
  	cstr(void);

  	virtual const char *
  	getClassName( void ) const;
  	    Return the name of this class (i.e. StrStreambuf )

  	virtual Bool
  	good( void ) const;
  	    Returns true if there are no detected errors associated
  	    with this class, otherwise FALSE.

  	virtual const char *
  	error( void ) const
  	    Returns as string description of the state of the class.

  	std::ostream &
  	operator <<( std::ostream & dest, const StrStreambuf & obj );
*/
#endif // ! def _clue_StrStreambuf_hpp_
