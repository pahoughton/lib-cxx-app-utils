#ifndef _clue_Str_hh_
#define _clue_Str_hh_
/* 1995-05-30 (cc) Paul Houghton - (paul4hough@gmail.com)

   A 'Str' provides many methods to manipulate sequences
   of characters (i.e. strings). It is a 'iostream' so you
   can use the '<<' and '>>' operators.

**/

#include <clue/StrStreambuf.hpp>
#include <clue/StringUtils.hpp>

#include <iostream>
#include <iterator>
#include <functional>
#include <utility>
#include <vector>
#include <cstddef>
#include <cstring>

#if !defined(NPOS)
#define NPOS static_cast<size_t>(-1)
#endif

namespace clue {

class SubStr;
class Str : public std::iostream
{

public:

  typedef size_t		size_type;
  typedef ptrdiff_t		difference_type;
  typedef char &		reference;
  typedef const char &		const_reference;
  typedef char *		pointer;
  typedef const char *		const_pointer;
  typedef pointer		iterator;
  typedef const_pointer		const_iterator;


  typedef std::reverse_iterator< iterator >	reverse_iterator;
  typedef std::reverse_iterator< const_iterator >	const_reverse_iterator;


  typedef std::pair< long long, long long >	Range;

  typedef std::vector< Range >   RangeList;

  typedef const_iterator    InputIterator; // work around no compiler support

  static const size_type npos;

  // constructors

  Str( void );

  inline Str( const Str &    src,
	      size_type      srcStart = 0,
	      size_type      srcLen = npos );

  inline Str( const SubStr &	src,
	      size_type 	srcStart = 0,
	      size_type 	srcLen = npos );

  inline Str( const std::string &   src,
	      size_type		    srcStart = 0,
	      size_type		    srcLen = npos );

  inline Str( const char * src, size_type srcLen = npos );
  inline Str( size_type count, char src );

  inline Str( InputIterator first, InputIterator last );

  inline Str( std::istream & src, bool text = false, bool line = false );

  virtual ~Str( void );


  // misc support

  inline void 	    	    reset( void );

  inline size_type    	    size( void ) const;
  inline size_type    	    length( void ) const;
  inline bool	    	    empty( void ) const;
  inline size_type    	    max_size( void ) const;

  inline const char *	    cstr( void ) const;
  inline const char *	    c_str( void ) const;

  inline size_type    	    copy( char * dest,
				  size_type destLen,
				  size_type start = 0 ) const;

  inline StrStreambuf *     rdbuf( void ) const;
  inline StrStreambuf *     rdbuf( void );


  // append

  Str &	        append( const char * src, size_type srcLen = npos );

  inline Str &	append( const Str & 	src,
			size_type 	srcStart = 0,
			size_type 	srcLen = npos );

  inline Str &	append( const SubStr & 	src,
			size_type 	srcStart = 0,
			size_type 	srcLen = npos );

  inline Str &	append( const std::string & 	src,
			size_type 	    	srcStart = 0,
			size_type 	    	srcLen = npos );

  inline Str &  append( size_type count, char src );
  inline Str &  append( char src );
  inline Str &  append( InputIterator first, InputIterator last );


  // assignment

  inline Str &	assign( const Str & 	src,
		    	size_type 	srcStart = 0,
			size_type 	srcLen = npos );

  inline Str &	assign( const SubStr & 	src,
		        size_type 	srcStart = 0,
			size_type	srcLen = npos );

  inline Str &	assign( const std::string & src,
		        size_type 	    srcStart = 0,
			size_type	    srcLen = npos );

  inline Str &	assign( const char * src, size_type srcLen = npos );
  inline Str &  assign( size_type count, char src );
  inline Str &  assign( char src );
  inline Str &  assign( InputIterator first, InputIterator last );


  // insert

  inline Str &	insert( size_type 	before,
			const Str & 	src,
			size_type 	srcStart = 0,
			size_type 	srcLen = npos );

  inline Str &	insert( size_type 	before,
			const SubStr &	src,
			size_type 	srcStart = 0,
			size_type 	srcLen = npos );

  inline Str &	insert( size_type	    before,
			const std::string & src,
			size_type	    srcStart = 0,
			size_type	    srcLen = npos );

  inline Str &	insert( size_type 	before,
			const char * 	src,
			size_type      	srcLen = npos );

  inline Str &	insert( size_type before, size_type count, char src );
  inline Str &	insert( size_type before, char src );

  inline Str &  insert( iterator    	before,
 			InputIterator   first,
			InputIterator   last );


  // remove

  inline Str &	remove( size_type start, size_type len = npos );
  inline Str &	remove( iterator which );
  inline Str &	remove( iterator first, iterator last );


  // replacement

  Str &	    	replace( size_type     	start,
			 size_type     	len,
			 const char * 	src,
			 size_type     	srcLen = npos );

  Str &	    	replace( size_type start, size_type len, size_type count, char src );

  inline Str &	replace( size_type     	start,
			 size_type     	len,
			 const Str & 	src,
			 size_type     	srcStart = 0,
			 size_type     	srcLen = npos );

  inline Str &	replace( size_type     	start,
			 size_type     	len,
			 const SubStr & src,
			 size_type     	srcStart = 0,
			 size_type     	srcLen = npos );

  inline Str &	replace( size_type	     start,
			 size_type	     len,
			 const std::string & src,
			 size_type	     srcStart = 0,
			 size_type	     srcLen = npos );

  inline Str &	replace( size_type start, size_type len, char src );

  inline Str &	replace( iterator   	first,
			 iterator   	last,
			 const Str & 	src,
			 size_type     	srcStart = 0,
			 size_type     	srcLen = npos );

  inline Str &	replace( iterator   	first,
			 iterator   	last,
			 const SubStr & src,
			 size_type	srcStart = 0,
			 size_type	srcLen = npos );

  inline Str &	replace( iterator		first,
			 iterator		last,
			 const std::string &	src,
			 size_type		srcStart = 0,
			 size_type		srcLen = npos );

  inline Str &	replace( iterator   	first,
			 iterator	last,
			 const char *	src,
			 size_type		srcLen = npos );

  Str &	    	replace( iterator   	first,
			 iterator	last,
			 InputIterator	srcFirst,
			 InputIterator	srcLast );

  Str &         replaceAny( const char * chars,
                            char         val );


  // iterators

  inline iterator  	    	begin( void );
  inline iterator  	    	end( void );

  inline const_iterator    	begin( void ) const;
  inline const_iterator    	end( void ) const;

  inline reverse_iterator    	rbegin( void );
  inline reverse_iterator    	rend( void );

  inline const_reverse_iterator rbegin( void ) const;
  inline const_reverse_iterator	rend( void ) const;


  // compare

  int 	    compare( const Str &    two,
		     size_type	    start = 0,
		     size_type	    len = npos ) const;

  int 	    compare( const SubStr & two,
		     size_type	    start = 0,
		     size_type	    len = Str::npos ) const;

  int 	    compare( const std::string &    two,
		     size_type		    start = 0,
		     size_type		    len = Str::npos ) const;

  int 	    compare( const char *   two,
		     size_type	    start = 0,
		     size_type	    len = npos ) const;

  friend int	compare( const SubStr & one,
			 const Str &    two,
			 size_type      len = Str::npos );

  friend int	compare( const char *   one,
			 const Str &    two,
			 size_type      len = Str::npos );

  int 	    fcompare( const Str &    two,
		      size_type	     start = 0,
		      size_type	     len = npos ) const;

  int 	    fcompare( const SubStr & two,
		      size_type	     start = 0,
		      size_type	     len = npos ) const;

  int 	    fcompare( const std::string &   two,
		      size_type		    start = 0,
		      size_type		    len = npos ) const;

  int 	    fcompare( const char *   two,
		      size_type	     start = 0,
		      size_type	     len = npos ) const;

  friend int	fcompare( const SubStr & one,
			  const Str &    two,
			  size_type         len = Str::npos );

  friend int	fcompare( const char *   one,
			  const Str &    two,
			  size_type         len = Str::npos );


  // substring

  inline char &     at( size_type index );
  inline char 	    at( size_type index ) const;

  inline SubStr     	substr( size_type start = 0, size_type len = npos );
  inline const SubStr   substr( size_type start = 0, size_type len = npos ) const;
  inline SubStr     	at( size_type start, size_type len );
  inline const SubStr   at( size_type start, size_type len ) const;

  inline SubStr	    	at( const char *    pat,
			    size_type  	    start = 0,
			    size_type  	    patLen = npos );
  inline const SubStr	at( const char *    pat,
			    size_type  	    start = 0,
			    size_type  	    patLen = npos ) const;

  inline SubStr	    	at( const Str & pat, size_type start = 0 );
  inline const SubStr	at( const Str & pat, size_type start = 0 ) const;
  inline SubStr	    	at( const SubStr & pat, size_type start = 0 );
  inline const SubStr	at( const SubStr & pat, size_type start = 0 ) const;

  inline SubStr     	before( size_type end );
  inline const SubStr   before( size_type end ) const;
  inline SubStr	    	after( size_type start );
  inline const SubStr	after( size_type start ) const;

  // searching

  inline size_type	find( const Str & pat, size_type start = 0) const;
  inline size_type	find( const SubStr & pat, size_type start = 0) const;
  inline size_type	find( const char *  pat,
			      size_type     start = 0,
			      size_type     patLen = npos) const;
  inline size_type	find( char c, size_type start = 0 ) const;

  inline size_type	rfind( const Str & s, size_type end = npos) const;
  inline size_type	rfind( const SubStr & s, size_type end = npos) const;
  inline size_type	rfind( const char * s,
			       size_type    end = npos,
			       size_type    sLen = npos) const;
  inline size_type	rfind( char c, size_type end = npos ) const;

  // fold (ignore case)

  inline size_type	ffind( const Str & s, size_type start = 0) const;
  inline size_type	ffind( const SubStr & s, size_type start = 0) const;
  inline size_type	ffind( const char * s,
			       size_type    start = 0,
			       size_type    sLen = npos) const;
  inline size_type	ffind( char c, size_type start = 0 ) const;

  inline size_type	rffind( const Str & s, size_type end = npos) const;
  inline size_type	rffind( const SubStr & s, size_type end = npos) const;
  inline size_type	rffind( const char * s,
				size_type     end = npos,
				size_type     sLen = npos) const;
  inline size_type	rffind( char c, size_type end = npos ) const;


  inline size_type find_first_of( const Str & s, size_type start = 0 ) const;
  inline size_type find_first_of( const SubStr & s, size_type start = 0 ) const;
  inline size_type find_first_of( const char *	s,
				  size_type	start = 0,
				  size_type	sLen = npos ) const;

  inline size_type find_last_of( const Str & s, size_type end = npos ) const;
  inline size_type find_last_of( const SubStr & s, size_type end = npos ) const;
  inline size_type find_last_of( const char *	s,
				 size_type	end = npos,
				 size_type	sLen = npos ) const;

  inline size_type find_first_not_of( const Str & s, size_type start = 0 ) const;
  inline size_type find_first_not_of( const SubStr & s, size_type start = 0 ) const;
  inline size_type find_first_not_of( const char *  s,
				      size_type	    start = 0,
				      size_type	    sLen = npos ) const;

  inline size_type find_last_not_of( const Str & s, size_type end = npos ) const;
  inline size_type find_last_not_of( const SubStr & s, size_type end = npos ) const;
  inline size_type find_last_not_of( const char * s,
				  size_type end = npos,
				  size_type sLen = npos ) const;

  // converters

  // NOTE: from appends

  inline Str &	from( int   	    	src, unsigned short base = 0);
  inline Str &	from( short 	    	src, unsigned short base = 0);
  inline Str &	from( long  	    	src, unsigned short base = 0);
  inline Str &	from( unsigned int  	src, unsigned short base = 0);
  inline Str &	from( unsigned short 	src, unsigned short base = 0);
  inline Str &	from( unsigned long 	src, unsigned short base = 0);
  inline Str &	from( long long		src, unsigned short base = 0);
  inline Str &	from( unsigned long long src, unsigned short base = 0);

  inline bool	to( bool &		dest ) const;
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

  inline bool	to( long long &	    	dest,
		    unsigned short	base = 0,
		    bool		stopAtNonDigit = false ) const;

  inline bool	to( unsigned long long  &   dest,
		    unsigned short	    base = 0,
		    bool		    stopAtNonDigit = false ) const;
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

  inline long long    	toLongLong( unsigned short base = 0,
				    bool       stopAtNonDigit = false ) const;

  inline unsigned long long toULongLong( unsigned short base = 0,
					 bool	stopAtNonDigit = false ) const;

  bool			to( Range & r, unsigned short base = 0 ) const;
  RangeList::size_type	to( RangeList & range, unsigned short base = 0 ) const;

  // modifications

  inline void	    	upcase( void );
  inline void	    	downcase( void );
  inline void 	    	capitalize( void );

  size_type        	strip( const char * stripChars );
  inline size_type    	stripLeading( const char * stripChars );
  inline size_type    	stripTrailing( const char * strinpChars );
  inline size_type    	stripEnds( const char * stripChars = " \t\n\r\f\v" );

  Str &     substitute( char 	from,
			char 	to,
			size_type 	start = 0,
			bool 	global = true );

  Str &     substitute( const char * 	from,
			const char * 	to,
			size_type 	    	start = 0,
			bool 	    	global = true );

  size_type    wrap( size_type width = 72, long pad = -1, long firstPad = -1 );

  // scan - scan for substrings

  inline size_type  scan( const Str &	delimChars,
			  bool		multiDelim = true,
			  size_type	start = 0 );

  inline size_type  scan( const SubStr &    delimChars,
			  bool		    multiDelim = true,
			  size_type	    start = 0 );

  size_type	    scan( const char *	delimChars,
			  bool		multiDelim = true,
			  size_type	start = 0,
			  size_type	dLen = npos );

  size_type	    scan( const char *	quoteChars,
			  char		escChar,
			  const char *	delimChars,
			  bool		multiDelim = true,
			  size_type	start = 0 );

  size_type    scan( char delim, bool multiDelim = true, size_type start = 0 );

  size_type    scanString( const Str & delimStr, size_type start = 0 );
  size_type    scanString( const SubStr & delimStr, size_type start = 0 );
  size_type    scanString( const char * dStr, size_type start = 0, size_type dLen = npos );

  // scan support

  inline size_type	scanMatchCount( void ) const;
  inline SubStr		scanMatch( size_type scanNum = 0 );
  inline size_type      scanMatch( Str & dest, size_type scanNum = 0 ) const;

  inline size_type	scanMatchStart( size_type scanNum = 0 ) const;
  inline size_type	scanMatchLength( size_type scanNum = 0 ) const;

  // io helpers

  std::istream &	    getline( std::istream & src );

  // from std::istream
  inline std::istream &  getline( char * dest, int size, char delim = '\n' );
  inline std::istream &  getline( unsigned char * dest, int size, char d = '\n' );

  std::istream & 	getDelim( std::istream & src,
				  char      	 delim,
				  bool 	    	 discard = true );

  std::istream & 	getDelim( std::istream & src,
				  const char *   delimChars,
				  bool 	    	 discard = true );

  std::istream &	    get( std::istream & src, size_type bytes );

  // from std::istream
  inline std::istream &  get( char & dest );
  inline std::istream &  get( char * dest, int size, char delim = '\n' );
  inline std::istream &  get( unsigned char * dest, int size, char delim = '\n' );
  inline std::istream &  get( unsigned char & dest );
  inline int	    get( void );
  inline std::istream &  get( std::streambuf & dest, char delim = '\n' );

  // operators

  inline       	    operator const char * ( void ) const;

  inline char &	    operator [] ( size_type index );
  inline char 	    operator [] ( size_type index ) const;

  inline SubStr     	operator () ( size_type start, size_type len );
  inline const SubStr   operator () ( size_type start, size_type len ) const;

  inline Str &	    operator =  ( const Str & rhs );
  inline Str &	    operator =  ( const SubStr & rhs );
  inline Str &	    operator =  ( const std::string & rhs );
  inline Str &      operator =  ( const char * rhs );
  inline Str &	    operator =  ( char rhs );

  inline Str &	    operator += ( const Str & rhs );
  inline Str &	    operator += ( const SubStr & rhs );
  inline Str &	    operator += ( const std::string & rhs );
  inline Str &      operator += ( const char * rhs );
  inline Str &	    operator += ( char rhs );

  inline bool       operator == ( const Str & rhs ) const;
  inline bool	    operator != ( const Str & rhs ) const;
  inline bool	    operator <  ( const Str & rhs ) const;
  inline bool	    operator >  ( const Str & rhs ) const;
  inline bool	    operator <= ( const Str & rhs ) const;
  inline bool	    operator >= ( const Str & rhs ) const;


  inline bool       operator == ( const std::string & rhs ) const;
  inline bool	    operator != ( const std::string & rhs ) const;
  inline bool	    operator <  ( const std::string & rhs ) const;
  inline bool	    operator >  ( const std::string & rhs ) const;
  inline bool	    operator <= ( const std::string & rhs ) const;
  inline bool	    operator >= ( const std::string & rhs ) const;

  inline bool	    operator == ( const SubStr & rhs ) const;
  inline bool	    operator != ( const SubStr & rhs ) const;
  inline bool	    operator <  ( const SubStr & rhs ) const;
  inline bool	    operator >  ( const SubStr & rhs ) const;
  inline bool	    operator <= ( const SubStr & rhs ) const;
  inline bool	    operator >= ( const SubStr & rhs ) const;

  inline bool	    operator == ( const char * rhs ) const;
  inline bool	    operator != ( const char * rhs ) const;
  inline bool	    operator <  ( const char * rhs ) const;
  inline bool	    operator >  ( const char * rhs ) const;
  inline bool	    operator <= ( const char * rhs ) const;
  inline bool	    operator >= ( const char * rhs ) const;
  // libStlUtils Common Class Methods

  virtual size_type	getBinSize( void ) const;

  virtual std::ostream & 	write( std::ostream & dest ) const;

  // from std::ostream
  virtual std::ostream &	write( const char * src, int size );
  virtual std::ostream &	write( const unsigned char * src, int size );
  virtual std::ostream &	write( const void * src, size_type size );

  virtual std::istream & 	read( std::istream & src );

  // from std::istream
  virtual std::istream &	read( char * dest, int size );
  virtual std::istream &	read( unsigned char * dest, int size );

  virtual std::istream &	fromStream( std::istream & src );
  virtual std::ostream &	toStream( std::ostream & dest = std::cout ) const;

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream & dest = std::cerr,
				      const char *   prefix = "    " ) const;

protected:

  friend class SubStr;

  inline const char *	strbase() const;

  bool writeNum( unsigned long long num,
		 unsigned short     base = 0,
		 bool               neg = false);

  struct ScanMatch
  {
    size_type  pos;
    size_type  len;
    ScanMatch( void ) { pos = 0; len = 0; };
    ScanMatch( size_type p, size_type l = 0 ) { pos = p; len = l; };
    ~ScanMatch( ) {};
  };

  std::vector<ScanMatch>  matches;

private:

  size_type length( const char * from );
  size_type pos( const char * at );

};

}; // namespace clue

#include <clue/SubStr.hpp>

namespace clue {

inline
bool
Str::operator == ( const std::string & rhs ) const
{
  return( compare( rhs ) == 0 );
}

inline
bool
Str::operator <  ( const std::string & rhs ) const
{
  return( compare( rhs ) < 0 );
}
inline
bool
Str::operator != ( const std::string & rhs ) const
{
  return( ! (*this == rhs) );
}

inline
bool
Str::operator > ( const std::string & rhs ) const
{
  return( compare( rhs ) > 0 );
}

inline
bool
Str::operator <= ( const std::string & rhs ) const
{
  return( ! (*this > rhs) );
}

inline
bool
Str::operator >= ( const std::string & rhs ) const
{
  return( ! (*this < rhs) );
}


inline
Str::Str( const std::string & src, size_type srcStart, size_type srcLen )
  : std::iostream( new StrStreambuf )
{
  append( src, srcStart, srcLen );
}

inline
Str &
Str::append( const std::string & src, size_type srcStart, size_type srcLen )
{
  return( append( src.c_str() + srcStart,
		  srcLen != npos ? srcLen : (src.length() - srcStart ) ) );
}

inline
Str &
Str::operator += ( const std::string & src )
{
  return( append( src ) );
}

inline
Str &
Str::assign( const std::string & src, size_type srcStart, size_type srcLen )
{
  seekp( 0, std::ios::beg );
  return( append( src, srcStart, srcLen ) );
}

inline
Str &
Str::operator =  ( const std::string & src )
{
  return( assign( src ) );
}

  // constructors  * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
Str::Str( const Str & src, size_type srcStart, size_type srcLen )
  : std::iostream( new StrStreambuf )
{
  append( src, srcStart, srcLen );
}

inline
Str::Str( const SubStr & src, size_type srcStart, size_type srcLen )
  : std::iostream( new StrStreambuf )
{
  append( src, srcStart, srcLen );
}

inline
Str::Str( const char * src, size_type srcLen )
  : std::iostream( new StrStreambuf )
{
  append( src, srcLen );
}

inline
Str::Str( size_type count, char src )
  : std::iostream( new StrStreambuf )
{
  append( count, src );
}

inline
Str::Str( InputIterator first, InputIterator last )
  : std::iostream( new StrStreambuf )
{
  append( first, last );
}

inline
Str::Str( std::istream & src, bool text, bool line )
  : std::iostream( new StrStreambuf )
{
  if( line )
    {
      getDelim( src, '\n', true );
      return;
    }

  if( text )
    {
      getDelim( src, " \t\r\n\f", true );
    }
  else
    {
      read( src );
    }
}



// append  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
Str &
Str::append( const Str & src, size_type srcStart, size_type srcLen )
{
  return( append( src.strbase() + srcStart,
		  std::min( (src.size() - srcStart ), srcLen ) ) );
}

inline
Str &
Str::append( const SubStr & src, size_type srcStart, size_type srcLen )
{
  return( append( src.strbase() + srcStart,
		  std::min( (src.size() - srcStart ), srcLen ) ) );
}

inline
Str &
Str::append( size_type count, char src )
{
  for( size_type c = 0; c < count; c++ )
    rdbuf()->sputc( src );
  return( *this );
}

inline
Str &
Str::append( char src )
{
  rdbuf()->sputc( src );
  return( *this );
}

inline
Str &
Str::append( InputIterator first, InputIterator last )
{
  for( InputIterator n = first; n != last; n++ )
    append( *n );
  return( *this );
}

// assignment  * * * * * * * * * * * * * * * * * * * * * * * * * * * *


inline
Str &
Str::assign( const Str & src, size_type srcStart, size_type srcLen )
{
  seekp( 0, std::ios::beg );

  if( ! good() )
    clear();

  return( append( src, srcStart, srcLen ) );
}

inline
Str &
Str::assign( const SubStr & src, size_type srcStart, size_type srcLen )
{
  seekp( 0, std::ios::beg );

  if( ! good() )
    clear();

  return( append( src, srcStart, srcLen ) );
}

inline
Str &
Str::assign( const char * src, size_type srcLen )
{
  seekp( 0, std::ios::beg );

  if( ! good() )
    clear();

  return( append( src, srcLen ) );
}

inline
Str &
Str::assign( size_type count, char src )
{
  seekp( 0, std::ios::beg );

  if( ! good() )
    clear();

  return( append( count, src ) );
}

inline
Str &
Str::assign( char src )
{
  seekp( 0, std::ios::beg );

  if( ! good() )
    clear();

  return( append( src ) );
}

inline
Str &
Str::assign( InputIterator first, InputIterator last )
{
  seekp( 0, std::ios::beg );

  if( ! good() )
    clear();

  return( append( first, last ) );
}


// insert  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


inline
Str &
Str::insert(
  size_type    	start,
  const Str & 	src,
  size_type    	srcStart,
  size_type    	srcLen
  )
{
  return( replace( start, 0, src, srcStart, srcLen ) );
}

inline
Str &
Str::insert(
  size_type    	    start,
  const SubStr &    src,
  size_type    	    srcStart,
  size_type    	    srcLen
  )
{
  return( replace( start, 0, src, srcStart, srcLen ) );
}

inline
Str &
Str::insert(
  size_type    	    start,
  const char *      src,
  size_type    	    srcLen
  )
{
  return( replace( start, 0, src, srcLen ) );
}

inline
Str &
Str::insert( size_type start, size_type count, char src )
{
  return( replace( start, 0, count, src ) );
}

inline
Str &
Str::insert( size_type start, char src )
{
  return( replace( start, 0, src ) );
}

inline
Str &
Str::insert( iterator before, InputIterator first, InputIterator last )
{
  return( replace( before, before, first, last ) );
}

// remove  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


inline
Str &
Str::remove( size_type start, size_type len )
{
  return( replace( start, len, (const char *)0, 0 ) );
}

inline
Str &
Str::remove( iterator which )
{
  return( replace( which - begin(), 1, (const char *)0, 0 ) );
}

inline
Str &
Str::remove( iterator first, iterator last )
{
  return( replace( first - begin(), last - first, (const char *)0, 0 ) );
}


// replace * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
Str &
Str::replace(
  size_type    	start,
  size_type    	len,
  const Str &  	src,
  size_type    	srcStart,
  size_type    	srcLen
  )
{

  return( replace( start,
		   len,
		   src.strbase() + srcStart,
		   std::min( srcLen, src.size() - srcStart ) ) );
}

inline
Str &
Str::replace(
  size_type    	    start,
  size_type    	    len,
  const SubStr &    src,
  size_type    	    srcStart,
  size_type    	    srcLen
  )
{

  return( replace( start,
		   len,
		   src.strbase() + srcStart,
		   std::min( srcLen, src.size() - srcStart ) ) );
}

inline
Str &
Str::replace(
  size_type    start,
  size_type    len,
  char 	    src
  )
{
  return( replace( start, len, &src, 1 ) );
}

inline
Str &
Str::replace(
  iterator  	first,
  iterator  	last,
  const Str &  	src,
  size_type    	srcStart,
  size_type    	srcLen
  )
{

  return( replace( first - begin(),
		   last - first,
		   src.strbase() + srcStart,
		   std::min( srcLen, src.size() - srcStart ) ) );
}

inline
Str &
Str::replace(
  iterator  	    first,
  iterator  	    last,
  const SubStr &    src,
  size_type    	    srcStart,
  size_type    	    srcLen
  )
{

  return( replace( first - begin(),
		   last - first,
		   src.strbase() + srcStart,
		   std::min( srcLen, src.size() - srcStart ) ) );
}


inline
Str &
Str::replace(
  iterator  	first,
  iterator  	last,
  const char *  src,
  size_type    	srcLen
  )
{

  return( replace( first - begin(),
		   last - first,
		   src,
		   srcLen ) );
}


// iterators * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


inline
Str::iterator
Str::begin( void )
{
  return( rdbuf()->pbase() );
}

inline
Str::iterator
Str::end( void )
{
  return( begin() + size() );
}

inline
Str::const_iterator
Str::begin( void ) const
{
  return( strbase() );
}

inline
Str::const_iterator
Str::end( void ) const
{
  return( begin() + size() );
}

inline
Str::reverse_iterator
Str::rbegin( void )
{
  return( reverse_iterator( end() ) );
}

inline
Str::reverse_iterator
Str::rend( void )
{
  return( reverse_iterator( begin() ) );
}

inline
Str::const_reverse_iterator
Str::rbegin( void ) const
{
  return( const_reverse_iterator( end() ) );
}

inline
Str::const_reverse_iterator
Str::rend( void ) const
{
  return( const_reverse_iterator( begin() ) );
}


// substr  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
char &
Str::at( size_type index )
{
  static char badChar = 0;

  return( rdbuf()->pbase()[index] );
}

inline
char
Str::at( size_type index ) const
{
  return( strbase()[index] );
}

inline
SubStr
Str::substr( size_type start, size_type len )
{
  SubStr sub(  *this, start, std::min( size() - start, len ) );

  return( sub );
}

inline
const SubStr
Str::substr( size_type start, size_type len ) const
{

  const SubStr sub( *this, start, std::min( size() - start, len ) );
  return( sub );
}

inline
SubStr
Str::at( size_type start, size_type len )
{
  return( substr( start, len ) );
}

inline
const SubStr
Str::at( size_type start, size_type len ) const
{
  return( substr( start, len ) );
}

inline
SubStr
Str::at( const char * pat, size_type start, size_type patLen )
{
  size_type pLen = (patLen == npos) ? (pat) ? strlen( pat ) : 0 : patLen;

  SubStr sub( *this, find( pat, start, pLen ), pLen );
  return( sub );
}

inline
const SubStr
Str::at( const char * pat, size_type start, size_type patLen ) const
{
  const SubStr sub( *this, find( pat, start, patLen ), patLen );
  return( sub );
}

inline
SubStr
Str::at( const Str & pat, size_type start )
{
  return( at( pat.strbase(), start, pat.size() ) );
}

inline
const SubStr
Str::at( const Str & pat, size_type start ) const
{
  return( at( pat.strbase(), start, pat.size() ) );
}

inline
SubStr
Str::at( const SubStr & pat, size_type start )
{
  return( at( pat.strbase(), start, pat.size() ) );
}

inline
const SubStr
Str::at( const SubStr & pat, size_type start ) const
{
  return( at( pat.strbase(), start, pat.size() ) );
}

inline
SubStr
Str::before( size_type end )
{
  return( at( (size_type)0, end ) );
}

inline
const SubStr
Str::before( size_type end ) const
{
  return( at( (size_type)0, end ) );
}

inline
SubStr
Str::after( size_type start )
{
  return( at( start, size() - start ) );
}

inline
const SubStr
Str::after( size_type start ) const
{
  return( at( start, size() - start ) );
}

// searching * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
Str::size_type
Str::find( const Str & str, size_type start ) const
{
  const char * pos = StringSearch( strbase() + start, size() - start,
				   str.strbase(), str.size() );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::find( const SubStr & str, size_type start ) const
{
  const char * pos = StringSearch( strbase() + start, size() - start,
				   str.strbase(), str.size() );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::find( const char * str, size_type start, size_type strLen ) const
{
  const char * pos = StringSearch( strbase() + start, size() - start,
				   str, strLen );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::find( char c, size_type start ) const
{
  const char * pos = strchr( cstr() + start, c );
  return( (pos == 0) ? npos : pos - strbase() );
}


inline
Str::size_type
Str::rfind( const Str & str, size_type end ) const
{
  const char * pos = StringReverseSearch( strbase(), std::min( end, size() ),
				   str.strbase(), str.size() );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::rfind( const SubStr & str, size_type end ) const
{
  const char * pos = StringReverseSearch( strbase(), std::min( end, size() ),
				   str.strbase(), str.size() );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::rfind( const char * str, size_type end, size_type strLen ) const
{
  const char * pos = StringReverseSearch( strbase(), std::min( end, size() ),
				   str, strLen );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::rfind( char c, size_type end ) const
{
  if( ! size() || end == 0 )
    return( npos );

  size_type e = std::min( end, size() ) - 1;
  for( ; e > 0 && c != at( e ); e-- );
  return( (c == at(e)) ? e :
	  (c == at((size_type)0)) ? 0 : npos );
}


inline
Str::size_type
Str::ffind( const Str & str, size_type start ) const
{
  const char * pos = StringCaseSearch( strbase() + start, size() - start,
				   str.strbase(), str.size() );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::ffind( const SubStr & str, size_type start ) const
{
  const char * pos = StringCaseSearch( strbase() + start, size() - start,
				   str.strbase(), str.size() );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::ffind( const char * str, size_type start, size_type strLen ) const
{
  const char * pos = StringCaseSearch( strbase() + start, size() - start,
				   str, strLen );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::ffind( char c, size_type start ) const
{
  size_type s = start;
  for( ; s < size() && tolower( c ) != tolower( at( s ) ); s++ );
  return( (tolower( c ) == tolower( at(s) )) ? s : npos );
}


inline
Str::size_type
Str::rffind( const Str & str, size_type end ) const
{
  const char * pos = StringCaseReverseSearch( strbase(), std::min( end, size() ),
				   str.strbase(), str.size() );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::rffind( const SubStr & str, size_type end ) const
{
  const char * pos = StringCaseReverseSearch( strbase(), std::min( end, size() ),
				   str.strbase(), str.size() );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::rffind( const char * str, size_type end, size_type strLen ) const
{
  const char * pos = StringCaseReverseSearch( strbase(), std::min( end, size() ),
				   str, strLen );

  return( (pos == 0) ? npos : pos - strbase() );
}

inline
Str::size_type
Str::rffind( char c, size_type end ) const
{
  size_type e = std::min( end, size() ) - 1;
  for( ; e > 0 && tolower( c ) != tolower( at( e ) ); e-- );
  return( (tolower( c ) == tolower( at(e) )) ? e :
	  (tolower( c ) == tolower( at((size_type)0) )) ? 0 : npos );
}

inline
Str::size_type
Str::find_first_of( const Str & str, size_type start ) const
{
  return( find_first_of( str.strbase(), start, str.size() ) );
}

inline
Str::size_type
Str::find_first_of( const SubStr & str, size_type start ) const
{
  return( find_first_of( str.strbase(), start, str.size() ) );
}

inline
Str::size_type
Str::find_first_of(
  const char * str,
  size_type start,
  size_type strLen ) const
{
  const char * nBeg = str;
  const char * nEnd = str + ( (strLen == npos) ? strlen( str ) : strLen );

  size_type  pos = size();

  for( const char * n = nBeg; n < nEnd; n++ )
    {
      const char * curPos;
      curPos = (const char *)memchr( (const void *)(strbase() + start),
				       *n ,
				       pos - start );

      if( curPos && (size_type)(curPos - strbase()) < pos )
	{
	  pos = curPos - strbase();
	}
    }

  return( pos < size() ? pos : npos );
}

inline
Str::size_type
Str::find_last_of( const Str & s, size_type end ) const
{
  return( find_last_of( s.strbase(), end, s.size() ) );
}

inline
Str::size_type
Str::find_last_of( const SubStr & s, size_type end ) const
{
  return( find_last_of( s.strbase(), end, s.size() ) );
}

inline
Str::size_type
Str::find_last_of( const char * str, size_type end, size_type strLen ) const
{
  const char * hBeg = strbase();
  const char * hEnd = strbase() + ((end == npos) ? size() : end);

  const char * nBeg = str;
  const char * nEnd = nBeg + ((strLen == npos) ? strlen( str ) : strLen);

  for( const char * h = hEnd - 1 ; h >= hBeg; h-- )
    {
      for( const char * n = nBeg; n < nEnd; n++ )
	{
	  if( *h == *n )
	    {
	      return( h - strbase() );
	    }
	}
    }

  return( npos );
}

inline
Str::size_type
Str::find_first_not_of( const Str & str, size_type start ) const
{
  return( find_first_not_of( str.strbase(), start, str.size() ) );
}

inline
Str::size_type
Str::find_first_not_of( const SubStr & str, size_type start ) const
{
  return( find_first_not_of( str.strbase(), start, str.size() ) );
}

inline
Str::size_type
Str::find_first_not_of(
  const char *	str,
  size_type	start,
  size_type	strLen
  ) const
{
  size_type pos = StringFirstNotOf( strbase() + start,
				    size() - start,
				    str,
				    strLen );
  return( pos == npos ? npos : pos + start );
}

inline
Str::size_type
Str::find_last_not_of( const Str & str, size_type end ) const
{
  return( find_last_not_of( str.strbase(), end, str.size() ) );
}

inline
Str::size_type
Str::find_last_not_of( const SubStr & str, size_type end ) const
{
  return( find_last_not_of( str.strbase(), end, str.size() ) );
}

inline
Str::size_type
Str::find_last_not_of( const char * str, size_type end, size_type strLen ) const
{
  const char * hBeg = strbase();
  const char * hEnd = strbase() + ((end == npos) ? size() : end);

  const char * nBeg = str;
  const char * nEnd = nBeg + ((strLen == npos) ? strlen( str ) : strLen);

  if( ! hBeg || ! nBeg)
    return( npos );

  for( const char * h = hEnd - 1; h >= hBeg; h-- )
    {
      const char * n = nBeg;
      for( ; n < nEnd ; n++ )
	{
	  if( *h == *n )
	    {
	      break;
	    }
	}
      if( n == nEnd )
	{
	  return( h - strbase() );
	}
    }

  return( npos );
}



// from  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
Str &
Str::from( int src, unsigned short base )
{
  if( base == 0 )
    {
      *this << src;
    }
  else
    {
      writeNum( ((src < 0 ) ? src * -1 : src) , base, (src < 0) );
    }
  return( *this );
}

inline
Str &
Str::from( short src, unsigned short base )
{
  if( base == 0 )
    {
      *this << src;
    }
  else
    {
      writeNum( ((src < 0 ) ? src * -1 : src) , base, (src < 0) );
    }
  return( *this );
}

inline
Str &
Str::from( long src, unsigned short base )
{
  if( base == 0 )
    {
      *this << src;
    }
  else
    {
      writeNum( ((src < 0 ) ? src * -1 : src) , base, (src < 0) );
    }
  return( *this );
}

inline
Str &
Str::from( unsigned int src, unsigned short base )
{
  if( base == 0 )
    {
      *this << src;
    }
  else
    {
      writeNum( src , base, false );
    }
  return( *this );
}

inline
Str &
Str::from( unsigned short src, unsigned short base )
{
  if( base == 0 )
    {
      *this << src;
    }
  else
    {
      writeNum( src , base, false );
    }
  return( *this );
}

inline
Str &
Str::from( unsigned long src, unsigned short base )
{
  if( base == 0 )
    {
      *this << src;
    }
  else
    {
      writeNum( src , base, false );
    }
  return( *this );
}

inline
Str &
Str::from( long long src, unsigned short base )
{
  if( base == 0 )
    {
      *this << src;
    }
  else
    {
      writeNum( src , base, false );
    }
  return( *this );
}

inline
Str &
Str::from( unsigned long long src, unsigned short base )
{
  if( base == 0 )
    {
      *this << src;
    }
  else
    {
      writeNum( src , base, false );
    }
  return( *this );
}

// to  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
bool
Str::to( bool & dest ) const
{
  return( size() ? StringTo( dest, strbase(),  length() ) : false );
}

inline
bool
Str::to( int & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base,  length(), sand ) : false );
}

inline
bool
Str::to( short & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
Str::to( long & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
Str::to( float & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
Str::to( double & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base,  length(), sand ) : false );
}

inline
bool
Str::to( unsigned int & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
Str::to( unsigned short & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
Str::to( unsigned long & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
Str::to( long long & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
Str::to( unsigned long long & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
Str::toBool( void ) const
{
  bool dest = false;
  StringTo( dest, strbase(), length());
  return( dest );
}

inline
int
Str::toInt( unsigned short base, bool sand ) const
{
  int dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
long
Str::toLong( unsigned short base, bool sand ) const
{
  long dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
double
Str::toDouble( unsigned short base, bool sand ) const
{
  double dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
unsigned int
Str::toUInt( unsigned short base, bool sand ) const
{
  unsigned int dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
unsigned long
Str::toULong( unsigned short base, bool sand ) const
{
  unsigned long dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
long long
Str::toLongLong( unsigned short base, bool sand ) const
{
  long long dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
unsigned long long
Str::toULongLong( unsigned short base, bool sand ) const
{
  unsigned long long dest = 0;
  to( dest, base, sand );
  return( dest );
}

// modifiers * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
void
Str::upcase( void )
{
  StringUpper( rdbuf()->pbase(), length() );
}

inline
void
Str::downcase( void )
{
  StringLower( rdbuf()->pbase(), length() );
}

inline
void
Str::capitalize( void )
{
  StringCapitalize( rdbuf()->pbase(), length() );
}

Str::size_type
Str::stripLeading( const char * stripChars )
{
  cstr();
  char * destStart = rdbuf()->pbase();

  size_type    srcPos = find_first_not_of( stripChars );

  if( srcPos == npos ) // no non-strip chars
    {
      size_type count = size();
      reset();
      return( count );
    }

  if( srcPos )
    {
      memmove( destStart,
	       destStart + srcPos,
	       length() - srcPos );
      seekp( length() - srcPos );
      return( srcPos );
    }
  else
    {
      return( 0 );
    }
}

Str::size_type
Str::stripTrailing( const char * stripChars )
{
  size_type last = find_last_not_of( stripChars );

  if( last != npos )
    {
      size_type count = length() - ( last + 1 );

      if( count )
	{
	  seekp( last + 1 );
	}
      return( count );
    }
  else
    {
      if( find_first_of( stripChars ) == 0 )
	{
	  size_type origSize = size();
	  reset();
	  return( origSize );
	}
      else
	{
	  return( 0 );
	}
    }
}

Str::size_type
Str::stripEnds( const char * stripChars )
{
  size_type count = stripLeading( stripChars );
  count += stripTrailing( stripChars );
  return( count );
}


// scan  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
Str::size_type
Str::scan( const Str & delimChars, bool multiDelim, size_type start )
{
  return( scan( delimChars.strbase(), multiDelim, start,
		delimChars.size() ) );
}

inline
Str::size_type
Str::scan( const SubStr & delimChars, bool multiDelim, size_type start )
{
  return( scan( delimChars.strbase(), multiDelim, start,
		delimChars.size() ) );
}

inline
Str::size_type
Str::scanString( const Str & delimStr, size_type start )
{
  return( scanString( delimStr.strbase(), start,
		      delimStr.size() ) );
}

inline
Str::size_type
Str::scanString( const SubStr & delimStr, size_type start )
{
  return( scanString( delimStr.strbase(), start,
		      delimStr.size() ) );
}


inline
Str::size_type
Str::scanMatchCount( void ) const
{
  return( matches.size() );
}

inline
SubStr
Str::scanMatch( size_type scanNum )
{
  SubStr sub( *this, scanMatchStart( scanNum ), scanMatchLength( scanNum ) );
  return( sub );
}

inline
Str::size_type
Str::scanMatch( Str & dest, size_type scanNum ) const
{
  dest.assign( *this, scanMatchStart( scanNum ), scanMatchLength( scanNum ) );

  return( dest.size() );
}

inline
Str::size_type
Str::scanMatchStart( size_type scanNum ) const
{
  return( matches[scanNum].pos );
}

inline
Str::size_type
Str::scanMatchLength( size_type scanNum ) const
{
  return( matches[scanNum].len );
}


// io helpers  * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
std::istream &
Str::getline( std::istream & src )
{
  return( getDelim( src, '\n', true ) );
}

// misc support  * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
void
Str::reset( void )
{
  seekp(0);
  seekg(0);
  clear();
}

inline
Str::size_type
Str::size( void ) const
{
  return( rdbuf()->plen() );
}

inline
Str::size_type
Str::length( void ) const
{
  return( size() );
}

inline
bool
Str::empty( void ) const
{
  return( size() == 0 );
}

inline
Str::size_type
Str::max_size( void ) const
{
  return( npos - 1 );
}

inline
const char *
Str::cstr( void ) const
{
  return( rdbuf()->cstr() );
}

inline
const char *
Str::c_str( void ) const
{
  return( rdbuf()->cstr() );
}

inline
Str::size_type
Str::copy( char * dest, size_type destLen, size_type start ) const
{
  size_type len = (destLen == npos ? size() - start :
		   std::min( destLen, size() - start ) );

  strncpy( dest, strbase() + start, len );
  if( destLen == npos || len < destLen )
    dest[ len ] = 0;
  return( len );
}

inline
StrStreambuf *
Str::rdbuf( void ) const
{
  return( (StrStreambuf *)std::ios::rdbuf() );
}

inline
StrStreambuf *
Str::rdbuf( void )
{
  return( (StrStreambuf *)std::ios::rdbuf() );
}


inline
std::istream &
Str::getline( char * dest, int size, char delim )
{
  return( std::istream::getline( dest, size, delim ) );
}

inline
std::istream &
Str::getline( unsigned char * dest, int size, char delim )
{
  return( std::istream::getline( (char *)dest, size, delim ) );
}

inline
std::istream &
Str::get( char & dest )
{
  return( std::istream::get( dest ) );
}

inline
std::istream &
Str::get( char * dest, int size, char delim )
{
  return( std::istream::get( dest, size, delim ) );
}

inline
std::istream &
Str::get( unsigned char * dest, int size, char delim )
{
  return( std::istream::get( (char *)dest, size, delim ) );
}

inline
std::istream &
Str::get( unsigned char & dest )
{
  return( std::istream::get( (char &)dest ) );
}

inline
int
Str::get( void )
{
  return( std::istream::get() );
}

inline
std::istream &
Str::get( std::streambuf & dest, char delim )
{
  return( std::istream::get( dest, delim ) );
}




inline
Str::operator const char * ( void ) const
{
  return( cstr() );
}

inline
char &
Str::operator [] ( size_type index )
{
  return( at(index) );
}

inline
char
Str::operator [] ( size_type index ) const
{
  return( at(index) );
}

inline
SubStr
Str::operator () ( size_type start, size_type len )
{
  return( at( start, len ) );
}

inline
const SubStr
Str::operator () ( size_type start, size_type len ) const
{
  return( at( start, len ) );
}

inline
Str &
Str::operator =  ( const Str & src )
{
  return( assign( src ) );
}

inline
Str &
Str::operator =  ( const SubStr & src )
{
  return( assign( src ) );
}

inline
Str &
Str::operator =  ( const char * src )
{
  return( assign( src ) );
}

inline
Str &
Str::operator =  ( char src )
{
  return( assign( src ) );
}

inline
Str &
Str::operator += ( const Str & src )
{
  return( append( src ) );
}

inline
Str &
Str::operator += ( const SubStr & src )
{
  return( append( src ) );
}

inline
Str &
Str::operator += ( const char * src )
{
  return( append( src ) );
}

inline
Str &
Str::operator += ( char src )
{
  return( append( src ) );
}

inline
bool
Str::operator == ( const Str & two ) const
{
  return( compare( two ) == 0 );
}

inline
bool
Str::operator <  ( const Str & two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
Str::operator != ( const Str & rhs ) const
{
  return( ! (*this == rhs) );
}

inline
bool
Str::operator > ( const Str & rhs ) const
{
  return( rhs < *this );
}

inline
bool
Str::operator <= ( const Str & rhs ) const
{
  return( ! (rhs < *this) );
}

inline
bool
Str::operator >= ( const Str & rhs ) const
{
  return( ! (*this < rhs) );
}

inline
bool
Str::operator == ( const SubStr & two ) const
{
  return( compare( two ) == 0 );
}

inline
bool
Str::operator <  ( const SubStr & two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
Str::operator != ( const SubStr & two ) const
{
  return( !( *this == two ) );
}

inline
bool
Str::operator >  ( const SubStr & two ) const
{
  return( compare( two ) > 0 );
}

inline
bool
Str::operator <= ( const SubStr & two ) const
{
  return( compare( two ) <= 0 );
}

inline
bool
Str::operator >= ( const SubStr & two ) const
{
  return( compare( two ) >= 0 );
}

inline
bool
Str::operator == ( const char * two ) const
{
  return( compare( two ) == 0 );
}


inline
bool
Str::operator <  ( const char * two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
Str::operator != ( const char * two ) const
{
  return( !( *this == two ) );
}

inline
bool
Str::operator >  ( const char * two ) const
{
  return( compare( two ) > 0 );
}

inline
bool
Str::operator <=  ( const char * two ) const
{
  return( compare( two ) <= 0 );
}

inline
bool
Str::operator >= ( const char * two ) const
{
  return( compare( two ) >= 0 );
}

inline
std::ostream &
operator << ( std::ostream & dest, const Str & str )
{
  return( str.toStream( dest ) );
}

inline
std::istream &
operator >> ( std::istream & src, Str & dest )
{
  return( dest.fromStream( src ) );
}

// PRIVATE  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
const char *
Str::strbase( void ) const
{
  return( rdbuf() ? rdbuf()->strbase() : 0 );
}


// NON MEMBERS  * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline
int
compare( const Str & one, const Str & two, Str::size_type len = Str::npos )
{
  return( one.compare( two, 0, len ) );
}

inline
int
compare( const Str & one, const SubStr & two, Str::size_type len = Str::npos )
{
  return( one.compare( two, 0, len ) );
}

inline
int
compare( const Str & one, const char * two, Str::size_type len = Str::npos )
{
  return( one.compare( two, 0, len ) );
}

inline
int
fcompare( const Str & one, const Str & two, Str::size_type len = Str::npos )
{
  return( one.fcompare( two, 0, len ) );
}

inline
int
fcompare( const Str & one, const SubStr & two, Str::size_type len = Str::npos )
{
  return( one.fcompare( two, 0, len ) );
}

inline
int
fcompare( const Str & one, const char * two, Str::size_type len = Str::npos )
{
  return( one.fcompare( two, 0, len ) );
}



inline
Str
operator + ( const Str & lhs, const Str & rhs )
{
  Str s( lhs );
  s += rhs;
  return( s );
}

inline
Str
operator + ( const Str & lhs, const SubStr & rhs )
{
  Str s( lhs );
  s += rhs;
  return( s );
}

inline
Str
operator + ( const Str & lhs, const char * rhs )
{
  Str s( lhs );
  s += rhs;
  return( s );
}

inline
Str
operator + ( const char * lhs, const Str & rhs )
{
  Str s( lhs );
  s += rhs;
  return( s );
}

inline
bool
operator == ( const char * lhs, const Str & rhs )
{
  return( compare( lhs, rhs ) == 0 );
}

inline
bool
operator <  ( const char * lhs, const Str & rhs )
{
  return( compare( lhs, rhs ) < 0 );
}

inline
bool
operator != ( const char * lhs, const Str & rhs )
{
  return( compare( lhs, rhs ) != 0 );
}

inline
bool
operator >  ( const char * lhs, const Str & rhs )
{
  return( compare( lhs, rhs ) > 0 );
}

inline
bool
operator <= ( const char * lhs, const Str & rhs )
{
  return( compare( lhs, rhs ) <= 0 );
}

inline
bool
operator >= ( const char * lhs, const Str & rhs )
{
  return( compare( lhs, rhs ) >= 0 );
}


inline
std::istream &
getline( std::istream & src, Str & dest, char delim = '\n' )
{
  return( dest.getDelim( src, delim ) );
}

inline
bool
StringToBool( const Str & str )
{
  return( str.toBool() );
}


inline
int
StringToInt( const Str & str, unsigned short base = 0 )
{
  return( str.toInt( base ) );
}

inline
long
StringToLong( const Str & str, unsigned short base = 0 )
{
  return( str.toLong( base ) );
}

inline
double
StringToDouble( const Str & str, unsigned short base = 0 )
{
  return( str.toDouble( base ) );
}

inline
unsigned int
StringToUInt( const Str & str, unsigned short base = 0 )
{
  return( str.toUInt( base ) );
}

inline
unsigned long
StringToULong( const Str & str, unsigned short base = 0 )
{
  return( str.toULong( base ) );
}


inline
Str &
Str::insert(
  size_type		start,
  const std::string &   src,
  size_type		srcStart,
  size_type		srcLen
  )
{
  return( replace( start, 0, src, srcStart, srcLen ) );
}

inline
Str &
Str::replace(
  size_type		start,
  size_type		len,
  const std::string &	src,
  size_type		srcStart,
  size_type		srcLen
  )
{

  return( replace( start,
		   len,
		   src.c_str() + srcStart,
		   std::min( srcLen, src.length() - srcStart ) ) );
}

inline
Str &
Str::replace(
  iterator		first,
  iterator		last,
  const std::string &   src,
  size_type		srcStart,
  size_type		srcLen
  )
{

  return( replace( first - begin(),
		   last - first,
		   src.c_str() + srcStart,
		   std::min( srcLen, src.length() - srcStart ) ) );
}

} // namespace clue

/**


    Data Types: - data types defined by this header

    	Str	class

    Constructors:

    	Str( void );

  	inline
    	Str( const Str & src, size_type srcStart = 0, size_type srcLen = npos )
    	    Str constructor requires at least a Str to be given, the
    	    srcStart if omitted will default to 0, the srcLen if not
    	    given will be calculated from the length of (src).

  	inline
    	Str( const SubStr & src,
  	     size_type srcStart = 0,
  	     size_type srcLen = npos )
    	    Str constructor requires at least a SubStr to be given, the
    	    srcStart if omitted will default to 0, the srcLen if not
    	    given will be calculated from the length of (src).

  	inline
    	Str( const char * src, size_type srcLen = npos )
    	    Str constructor requires at least a char *(src) to be given, the
    	    length (rscLen) if not given will be calculated from the
    	    length of (src).

  	inline
    	Str( size_type count, char src )
    	    Str constructor requires a value (count) and a char(src).

  	inline
    	Str( InputIterator first, InputIterator last )

    Destructors:

    	~Str( void )

    Public Interface:

    	void
    	reset( void )

    	size_type
    	size( void ) const;

    	size_type
    	length( void ) const;

    	bool
    	empty( void ) const;

    	size_type
    	max_size( void ) const;

    	const char *
    	cstr( void ) const;

	inline
    	size_type
    	copy( char * dest, size_type destLen, size_type start = 0 ) const;

    	StrStreambuf *
    	rdbuf( void ) const;

    	StrStreambuf *
    	rdbuf( void );

    	Str &
    	append( const char * src, size_type srcLen = npos );
    	    append onto a Str the contents of (src) for (srcLen)
  	    character(s) of (src).

    	Str &
    	append( const Str & src, size_type srcStart = 0, size_type srcLen = npos );
    	    append onto a Str the contents of (src), starting at position
    	    (srcStart), for (srcLen) number of characters..

    	Str &
    	append( const SubStr & src,
    	    	size_type srcStart = 0,
    	    	size_type srcLen = npos );
    	    append onto a Str, the contents of a Substr (src), starting
    	    at position (srcStart) of (src), for (srcLen) number of
  	    characters.

    	Str &
    	append( size_type count, char src );
    	    append onto a Str, for (count) a character of (src).
    	    ie. ( 5, 'x' )  appends "xxxxx"

    	Str &
    	append( char src );
    	    append onto a Str, a character (src).

    	Str &
    	append( InputIterator first, InputIterator last );

    	Str &
    	assign( const char * src, size_type srcLen = npos );
    	    assign will overwrite the contents of a Str, with the contents
    	    of (src), starting at position 0, for (srcLen) characters.

    	Str &
    	assign( const Str & src, size_type srcStart = 0, size_type srcLen = npos );
    	    assign will overwrite the contents of a Str, with the contents
    	    of (src), starting at (srcStart) for (srcLen) characters.

    	Str &
    	assign( const SubStr & src,
    	    	size_type srcStart = 0,
    	    	size_type srcLen = npos );
    	    assign will overwrite the contents of a Str, with the contents
    	    of the SubStr (src) starting at position (srcStart), for
    	    (srcLen) characters.

    	Str &
    	assign( size_type count, char src );
    	    assign will overwrite the contents of Str, by replicating
    	    (src) by (count) times.

    	Str &
    	assign( char src );
    	    assign will overwrite the contents of Str, with the contents
    	    of src.

    	Str &
    	assign( InputIterator first, InputIterator last );

    	Str &
    	insert( size_type before, const char * src, size_type srcLen = npos );
    	    insert will modify Str, by inserting (srcLen) characters from
    	    (src) before position (before) in Str.

    	Str &
    	insert( size_type before,
                const Str & src,
                size_type srcStart = 0,
                size_type srcLen = npos );
    	    insert will modify Str, by inserting (srcLen) characters,
    	    starting at (srcStart) from Str (src), into Str before
    	    (before).

    	Str &
    	insert( size_type before,
    	    	const SubStr & src,
    	    	size_type srcStart = 0,
    	    	size_type srcLen = npos );
    	    insert will modify Str, by inserting (srcLen) characters,
    	    starting at (srcStart) from SubStr (src), into Str before
    	    position (before)

    	Str &
    	insert( size_type before, size_type count, char src );
    	    insert will modify Str, by inserting the character (src),
            (count) number of times, before position (before) in Str.


    	Str &
    	insert( size_type before, char src );
    	    insert will modify Str, by inserting the character (src)
    	    before position (before) in Str.

    	Str &
    	insert( iterator before, InputIterator first, InputIterator last );

    	Str &
    	remove( size_type start, size_type len = npos );
    	    remove will modify Str, by removing (len) characters,
    	    starting at position (start) in Str. This will reduce the
    	    original length of Str by (len) characters.

    	Str &
    	remove( iterator which );

    	Str &
    	remove( iterator first, iterator last );

    	Str &
    	replace( size_type start,
    	    	 size_type len,
    	    	 const char * src,
                 size_type srcLen = npos );
    	    replace will modify Str, by replacing (srcLen) characters from
    	    (src) and replace these characters in the Str starting at
    	    position (start) for (len) number of characters.

    	Str &
    	replace( size_type start, size_type len, size_type count, char src );
    	    replace will modify Str, by using character( src) replicated
    	    (count) times, and replacing in Str starting at position (start)
    	    for (len) number of characters.

    	replace( size_type start,
    	    	 size_type len,
    	    	 const char * src,
                 size_type srcLen = npos );
    	    replace will modify Str, by replacing (srcLen) characters from
    	    (src) and replace these characters in the Str starting at
    	    position (start) for (len) number of characters.

    	Str &
    	replace( size_type start, size_type len, size_type count, char src );
    	    replace will modify Str, by using character( src) replicated
    	    (count) times, and replacing in Str starting at position (start)
    	    for (len) number of characters.

    	Str &
    	replace( size_type start,
    	    	 size_type len,
    	    	 const Str & src,
    	    	 size_type srcStart = 0,
    	    	 size_type srcLen = npos);
    	    replace will modify Str, starting at position (start) in Str,
    	    for (len) number of positions, with the characters starting at
    	    position (srcStart) of Str (src) for (srcLen) number of characters

    	Str &
    	replace( size_type start,
    	    	 size_type len,
    	    	 const SubStr & src,
    	    	 size_type srcStart = 0,
    	    	 size_type srcLen = npos);
    	    replace will modify Str, starting at position (start) for (len)
    	    number of positions, with the characters from SubStr (src)
    	    starting at position (start) for (srcLen) number of characters

    	Str &
    	replace( size_type start, size_type len, char src );
    	    replace will modify Str, starting at position (start) for (len)
    	    number of positions with character (src).

    	Str &
    	replace( iterator first,
    	    	 iterator last,
    	    	 const Str & src,
    	    	 size_type srcStart = 0,
    	    	 size_type srcLen = npos );
    	    replace will modify Str, starting at position (start) in Str,
    	    for (len) number of positions, with the characters starting at
    	    position (srcStart) of Str (src) for (srcLen) number of characters

    	Str &
    	replace( size_type start,
    	    	 size_type len,
    	    	 const SubStr & src,
    	    	 size_type srcStart = 0,
    	    	 size_type srcLen = npos);
    	    replace will modify Str, starting at position (start) for (len)
    	    number of positions, with the characters from SubStr (src)
    	    starting at position (start) for (srcLen) number of characters

    	Str &
    	replace( size_type start, size_type len, char src );
    	    replace will modify Str, starting at position (start) for (len)
    	    number of positions with character (src).

    	Str &
    	replace( iterator first,
    	    	 iterator last,
    	    	 const Str & src,
    	    	 size_type srcStart = 0,
    	    	 size_type srcLen = npos );
    	    replace will modify Str, starting at position (first) in Str,
    	    ending at (last -1), with the characters starting at
    	    position (srcStart) of Str (src) for (srcLen) number of characters

    	Str &
    	replace( iterator first,
    	    	 iterator last,
    	    	 const SubStr & src,
    	    	 size_type srcStart = 0,
    	    	 size_type srcLen = npos );
    	    replace will modify Str, starting at position (first) in Str
    	    ending at (last -1), with the characters from SubStr (src)
    	    starting at position (start) for (srcLen) number of characters

    	Str &
    	replace( iterator first,
    	    	 iterator last,
    	    	 const char * src,
    	    	 size_type srcLen = npos );
    	    replace will modify Str, starting at position (first) in Str
    	    ending at (last -1), with (srcLen) number of characters from (src)

    	Str &
    	replace( iterator first,
    	    	 iterator last,
    	    	 InputIterator srcFirst,
    	    	 InputIterator srcLast );

    	iterator
    	begin( void );

    	iterator
    	end( void );

    	const_iterator
    	begin( void ) const;

    	const_iterator
    	end( void ) const;

    	reverse_iterator
    	rbegin( void );

    	reverse_iterator
    	rend( void );

    	const_reverse_iterator
    	rbegin( void ) const;

    	const_reverse_iterator
    	rend( void ) const;

    	int
    	compare( const Str & two,
    	    	 size_type start = 0,
    	    	 size_type len = npos ) const;
    	    compares Str (one), starting at position (start) for (len)
    	    number of positions of Str (two).

    	int
    	compare( const SubStr & two,
    	    	 size_type start = 0,
    	    	 size_type len = Str::npos ) const;
    	    compares Str (one), starting at position (start) for (len)
    	    number of positions of SubStr (two).

    	int
    	compare( const char * two,
    	    	 size_type start = 0,
    	    	 size_type len = npos ) const;
    	    compares Str (one), starting at position (start) for (len)
    	    number of positions of (two).

    	friend int
    	compare( const char * one,
    	    	 const Str & two,
    	    	 size_type len = Str::npos );

    	int
    	fcompare( const Str & two,
    	    	  size_type start = 0,
    	    	  size_type len = npos ) const;
    	    compares Str (one), starting at position (start) for (len)
    	    number of positions of Str (two).

    	int
    	fcompare( const SubStr & two,
    	    	  size_type start = 0,
    	    	  size_type len = npos ) const;
    	    compares Str (one), starting at position (start) for (len)
    	    number of positions of SubStr (two).

    	int
    	fcompare( const char * two,
    	    	  size_type start = 0,
    	    	  size_type len = npos ) const;
    	    compares Str (one), starting at position (start) for (len)
    	    number of positions of (two).

    	friend int
    	fcompare( const SubStr & one,
    	    	  size_type start = 0,
    	    	  size_type len = Str::npos );

    	friend int
    	fcompare( const char * one,
    	    	  const Str & two,
    	    	  size_type len = Str::npos );

    	char &
    	at( size_type index );
    	    return the character at position (index) in an Str.

    	char
    	at( size_type index ) const;
    	    return the character at position (index) in an Str

    	SubStr
    	substr( size_type start = 0, size_type len = npos );
    	    return a Substr of the contents of a Str starting at position
    	    (start) for (len) number of positions.

    	const SubStr
    	substr( size_type start = 0, size_type len = npos ) const;
    	    return a Substr of the contents of a Str starting at position
    	    (start) for (len) number of positions.

    	SubStr
    	at( size_type start, size_type len );
    	    return a Substr of the contents of a Str starting at position
    	    (start) for (len) number of positions.

    	const SubStr
    	at( size_type start, size_type len ) const;
    	    return a Substr of the contents of a Str starting at position
    	    (start) for (len) number of positions.

  	inline
    	SubStr
    	at( const char * pat, size_type start = 0, size_type patLen = npos );
    	    return a SubStr of a Str, where a pattern (pat) occured starting
    	    at position (start) for (len) number of positions of the Str.

    	const SubStr
    	at( const char * pat, size_type start = 0, size_type patLen = npos ) const;
    	    return a SubStr of a Str, where a pattern (pat) occured starting
    	    at position (start) for (len) number of positions of the Str.

    	SubStr
    	at( const Str & pat, size_type start = 0 );

    	const SubStr
    	at( const Str & pat, size_type start = 0 ) const;
    	    return a SubStr of a Str, where a pattern (pat) occured starting
    	    at position (start) of the Str.

    	SubStr
    	at( const SubStr & pat, size_type start = 0 );
    	    return a SubStr of a Str, where a pattern (pat) occured starting
    	    at position (start) of the Str.

    	const SubStr
    	at( const SubStr & pat, size_type start = 0 ) const;
    	    return a SubStr of a Str, where a pattern (pat) occured starting
    	    at position (start) of the Str.

        SubStr
    	before( size_type end );
    	    creates a SubStr of all characters of a string from position
    	    (0) upto but not including position (end),

    	const SubStr
    	before( size_type end ) const;
    	    creates a SubStr of all characters of a string from position
    	    (0) upto but not including position (end),

        SubStr
    	after( size_type start );
    	    creates a SubStr of all characters of a string from position
    	    (start) to the end of the String

    	const SubStr
    	after( size_type start ) const;
    	    creates a SubStr of all characters of a string from position
    	    (start) to the end of the string(Str),

    	size_type
    	find( const Str & pat, size_type start = 0 )const;
    	    return the position in an Str, where the pattern (pat)
    	    first occurs starting at position (start) of the Str.

    	size_type
    	find( const SubStr & pat, size_type start = 0 )const;
    	    return the position in a Str, where the pattern (pat)
    	    first occurs starting at position (start) of the Str.

    	size_type
    	find( const char * pat, size_type start = 0, size_type patLen = npos )const;
    	    return the position in a Str, where the pattern (pat) of
    	    length (patLen)  first occured in Str, starting at position
    	    (start) of the Str.

    	size_type
    	find( char c, size_type start = 0 )const;
    	    return the position in an Str, where the character (c)
    	    first occurs starting at position (start) of the Str.

    	size_type
    	rfind( const Str & s, size_type end = npos )const;
    	    return the position in an Str, where the Str (s)
    	    first occurs starting at position (end) of the Str and
    	    ending at position (0).

    	size_type
    	rfind( const SubStr & s, size_type end = npos )const;
    	    return the position in an Str, where the SubStr (s)
    	    first occurs starting at position (end) of the Str and
    	    ending at position (0).

    	size_type
    	rfind( const char * s, size_type end = npos, size_type sLen = npos )const;
    	    return the position in an Str, where char (s) of length (sLen)
    	    first occurs starting at position (end) of the Str and
    	    ending at position (0).

    	size_type
    	rfind( char c, size_type end = npos )const;
    	    return the position in an Str, where the character (c)
    	    first occurs starting at position (end) of the Str and
    	    ending at position (0).


    	size_type
    	ffind( const Str & s, size_type start = 0 ) const;
    	    return the position in an Str, where the Str (s)
    	    first occurs starting at position (start) of the Str.

    	size_type
    	ffind( const SubStr & s, size_type start = 0 ) const;
    	    return the position in an Str, where the SubStr (s)
    	    first occurs starting at position (start) of the Str.

    	size_type
    	ffind( const char * s, size_type start = 0, size_type sLen = npos ) const;
    	    return the position in an Str, where the char (s) of length (sLen)
    	    first occurs starting at position (start) of the Str.

    	size_type
    	ffind( char c, size_type start = 0 ) const;
    	    return the position in an Str, where the character (c)
    	    first occurs starting at position (start) of the Str.

    	size_type
    	rffind( const Str & s, size_type end = npos ) const;
    	    return the position in an Str, where the Str (s)
    	    first occurs starting at position (end) of the Str and
    	    ending at position (0).

    	size_type
    	rffind( const SubStr & s, size_type end = npos ) const;
    	    return the position in an Str, where the SubStr (s)
    	    first occurs starting at position (end) of the Str and
    	    ending at position (0).

    	size_type
    	rffind( const char * s, size_type end = npos, size_type sLen = npos ) const;
    	    return the position in an Str, where the char (c) of length (sLen)
    	    first occurs starting at position (end) of the Str and
    	    ending at position (0).

    	size_type
    	rffind( char c, size_type end = npos ) const;
    	    return the position in an Str, where the character (c)
    	    first occurs starting at position (end) of the Str and
    	    ending at position (0).

    	size_type
    	find_first_of( const Str & s, size_type start = 0 ) const;
    	    return the position in a Str, where any character in the Str (s)
    	    first occurs starting at position (start) of the Str.

    	size_type
    	find_first_of( const SubStr & s, size_type start = 0 ) const;
    	    return the position in an Str, where  any character in SubStr (s)
    	    first occurs starting at position (start) of the Str.

    	size_type
    	find_first_of( const char * s,
    	    	       size_type start = 0,
    	    	       size_type sLen = npos ) const;
    	    return the position in an Str, where any character in the char (s)
            of length (sLen) first occurs starting at position
            (start) of the Str.

    	size_type
    	find_last_of( const Str & s, size_type end = npos ) const;
    	    return the position in an Str, where any character in the Str (s)
    	    last occurs starting at position (end) of the Str.

    	size_type
    	find_last_of( const SubStr & s, size_type end = npos ) const;
    	    return the position in an Str, where any character the SubStr (s)
    	    last occurs starting at position (end) of the Str.

    	size_type
    	find_last_of( const char * s,
    	    	      size_type end = npos,
    	    	      size_type sLen = npos ) const;
    	    return the position in an Str, where any character in the char (s)
            of length (sLen) last occurs starting at position (end) of the Str.
    	    and checking Str in reverse order.

    	size_type
    	find_first_not_of( const Str & s, size_type start = 0 ) const;
    	    return the position in a Str, where any character in the Str (s)
    	    does not occur starting at position (start) of the Str.

    	size_type
    	find_first_not_of( const SubStr & s, size_type start = 0 ) const;
    	    return the position in an Str, where  any character in SubStr (s)
    	    does not occur starting at position (start) of the Str.

    	size_type
    	find_first_not_of( const char * s,
    	    	    	   size_type start = 0,
    	    	    	   size_type sLen = npos ) const;
    	    return the position in an Str, where any character in the char (s)
            of length (sLen) does not occurs starting at position
            (start) of the Str.

    	size_type
    	find_last_not_of( const Str & s, size_type end = npos ) const;
    	    return the position in a Str, where any character in the Str (s)
    	    does not occur starting at position (end) of the Str.
    	    and moving towards the position (0)

    	size_type
    	find_last_not_of( const SubStr & s, size_type end = npos ) const;
    	    return the position in a Str, where any character in the SubStr (s)
    	    does not occur starting at position (end) of the Str.
    	    and moving towards the position (0)

    	size_type
    	find_last_not_of( const char * s,
    	    	    	  size_type end = npos,
    	    	    	  size_type sLen = npos ) const;
    	    return the position in a Str, where any character in char (s) of
    	    length (slen) does not occur starting at position (end) of the Str.
    	    and moving towards the position (0)

    	Str &
    	from( int src, unsigned short base = 0 );
    	    return an Str whose characters represent the value of (src)

    	Str &
    	from( short src, unsigned short base = 0 );
    	    return an Str whose characters represent the value of (src)

    	Str &
    	from( long src, unsigned short base = 0 );
    	    return an Str whose characters represent the value of (src)

    	Str &
    	from( unsigned int src,  unsigned short base = 0 );
    	    return an Str whose characters represent the value of (src)

    	Str &
    	from( unsigned short src, unsigned short base = 0 );
    	    return an Str whose characters represent the value of (src)

    	Str &
    	from( unsigned long src, unsigned short base = 0 );
    	    return an Str whose characters represent the value of (src)

    	bool
    	to( int & dest,
  	    unsigned short base = 0,
  	    bool stopAtNonDigit = false ) const;
    	    return a bool value(0) if a Str could convert to an int (dest)

    	bool
    	to( short & dest,
  	    unsigned short base = 0,
  	    bool stopAtNonDigit = false ) const;
    	    return a bool value(0) if a Str could convert to a short (dest)

    	bool
    	to( long & dest,
  	    unsigned short base = 0,
  	    bool stopAtNonDigit = false ) const;
    	    return a bool value(0) if a Str could convert to a long (dest)

    	bool
    	to( double & dest,
  	    unsigned short base = 0,
  	    bool stopAtNonDigit = false ) const;
    	    return a bool value(0) if a Str could convert to a double (dest)

    	bool
    	to( unsigned int & dest,
  	    unsigned short base = 0,
  	    bool stopAtNonDigit = false ) const;
    	    return a bool value(0) if a Str could convert to an unsigned
    	    int (dest)

    	bool
    	to( unsigned short & dest,
  	    unsigned short base = 0,
  	    bool stopAtNonDigit = false ) const;
    	    return a bool value(0) if a Str could convert to an unsigned
    	    short (dest)

    	bool
    	to( unsigned long & dest,
  	    unsigned short base = 0,
  	    bool stopAtNonDigit = false ) const;
    	    return a bool value(0) if a Str could convert to an unsigned
    	    long (dest)

    	bool
    	toBool( void ) const;

    	int
    	toInt( unsigned short base = 0,
  	       bool stopAtNonDigit = false ) const;
    	    return an int from a Str

    	long
    	toLong( unsigned short base = 0,
  		bool stopAtNonDigit = false ) const;
    	    return a long from a Str

    	double
    	toDouble( unsigned short base = 0,
  		  bool stopAtNonDigit = false ) const;
    	    return a double from a Str

    	unsigned int
    	toUInt( unsigned short base = 0,
  		bool stopAtNonDigit = false ) const;
    	    return an unsigned int from a Str

    	unsigned long
    	toULong( unsigned short base = 0,
  		 bool stopAtNonDigit = false ) const;
    	    return an unsigned long from a Str

  	RangeList::size_type
  	to( RangeList & range, unsigned short base = 0 ) const
  	    Convert the string into a list of numeric ranges and
  	    return the number of ranges found. A numberic range can be
  	    a single number (1962), or a number range (5-10, 35..47,
  	    13-). Either the ':' or '..' can be used to indicate a
  	    range of numbers. Numbers and ranges can be seperated by
  	    comma (,), space ( ), tab (\t), or semicolon (;).
  	    The 'range' is a list of pairs of unsigned long
  	    values. Where the first value is first (or only) number of
  	    a range and the second value is either 0 for a single
  	    number, the second number, or LLONG_MAX if a range is
  	    specificed without a second number.
  		Eample: "4-8,53,78,-90.."
  		Converts to:
  		    range[0] = {4,8}
  		    range[1] = {53,0}
  		    range[2] = {78,0}
  		    range[3] = {-90,LLONG_MAX}

    	void
    	upcase( void );
    	    convert lowercase characters to uppercase in a Str.

    	void
    	downcase( void );
    	    convert uppercase to lowercase in a Str

    	void
    	capitalize( void );
    	    capitalize each word within a Str.

    	size_type
    	strip( const char * stripChars );
    	    strip all characters in Str that match the characters contained
    	    in (stripChars) and return the number of characters removed.

    	size_type
    	stripLeading( const char * stripChars );
    	    starting a position (0) in a Str, strip out any characters
    	    that are contained in (stripChars) until a character is encounter
    	    that is NOt contained in (stripChars), return the number of
    	    characters removed.

    	size
    	stripTrailing( const char * strinpChars );
    	    starting at the last character in a Str, remove any character that
    	    matches a character contained in (strinpChars). When a character
    	    is encounter not in (strinpChars) it will stop, and return
    	    the number of characters removed.

    	size_type
    	stripEnds( const char * stripChars = " \t\n\r\f\v" );
    	    remove any character at the begining or end of a Str that
    	    matches those contained in (stripChars). when a character is
    	    encountered that does not match those in (stripChars) stop.
    	    return the number of characters removed.

        Str &
    	substitute( char from,
    	    	    char to,
    	    	    size_type start = 0,
    	    	    bool global = true );
    	    Substitute in a Str starting at position (start) any
    	    occurance of (from) with (to) while (global = true)

    	Str &
    	substitute( const char * from,
    	    	    const char * to,
    	    	    size_type start = 0,
    	    	    bool global = true );
    	    substitute in a Str starting at position (start) any occurance
    	    of (from) with (to) while (global = true ).

    	size_type
    	wrap( size_type width = 72, long pad = -1, long firstPad = -1 )
       	    wrap will reformat a string by inserting( firstPad) white spaces
    	    at the begining of an Str, insert a newline between words where
    	    they would extend beyond (width), and insert (pad) white spaces
    	    after each newline.

    	size_type
    	scan( const Str &	delimChars,
	      bool		multiDelim = true,
	      size_type		start = 0 );

    	size_type
    	scan( const SubStr &	delimChars,
	      bool		multiDelim = true,
	      size_type		start = 0 );


    	size_type
    	scan( const char *  delimChars,
	      bool	    multiDelim = true,
	      size_type	    start = 0,
	      size_type	    dLen = npos );

    	size_type
    	scan( const char *  quoteChars,
	      char	    escChar,
	      const char *  delimChars,
	      bool	    multiDelim = true,
	      size_type	    start = 0 );


    	size_type
    	scanString( const Str & delimStr, size_type start = 0 );

    	size_type
    	scanString( const SubStr & delimStr, size_type start = 0 );

    	size_type
    	scanString( const char * dStr,
		    size_type start = 0,
		    size_type dLen = npos );

    	size_type
    	scanMatchCount( void ) const;

    	SubStr
    	scanMatch( size_type scanNum = 0 );

    	size_type
    	scanMatch( Str & dest, size_type scanNum = 0 ) const;

    	size_type
    	scanMatchStart( size_type scanNum = 0 ) const;

    	size_type
    	scanMatchLength( size_type scanNum = 0 ) const;

    	friend std::ostream & operator << ( std::ostream & dest, const Str & str );

    	friend std::istream & operator >> ( std::istream & src, Str & dest );

    	std::istream &
    	getline( std::istream & src );

    	std::istream &
    	getDelim( std::istream & src, const char * delimChars, bool discard = true );

    	std::istream &
    	getDelim( std::istream & src, char delim, bool discard = true );

    	size_type
    	getBinSize( void ) const;

    	std::ostream &
    	write( std::ostream & dest ) const;

    	std::istream &
    	read( std::istream & src );

    	operator const char * ( void ) const;

    	char &
    	operator [] ( size_type index );

    	char
    	operator [] ( size_type index ) const;

    	SubStr
    	operator () ( size_type start, size_type len );

    	const SubStr
    	operator () ( size_type start, size_type len ) const;

    	Str &
    	operator = ( const Str & rhs );
    	    operator = acts like assign. it will copy the characters in (rhs)
    	    into an Str.

    	Str &
    	operator = ( const SubStr & rhs );
    	    operator = acts like assign. it will copy the characters in (rhs)
    	    into an Str.

    	Str &
    	operator = ( const char * rhs );
    	    operator = acts like assign. it will copy the characters in (rhs)
    	    into an Str.

    	Str &
    	operator = ( char rhs );
    	    operator = acts like assign. it will copy the character in (rhs)
    	    into an Str.

    	Str &
    	operator += ( const Str & rhs );
    	    operator += acts like append. It will add to the end of a Str
    	    the contents of (rhs).

    	Str &
    	operator += ( const SubStr & rhs );
    	    operator += acts like append. It will add to the end of a Str
    	    the contents of a SubStr (rhs) according to the arguments
    	    specified for the SubStr.

    	Str &
    	operator += ( const char * rhs );
    	    operator += acts like an append. It will add to the end of a Str
    	    the contents of (rhs).

    	Str &
    	operator += ( char rhs );
    	    operator += acts like and append. It will add to the end of a Str
    	    (rhs).

    	bool
    	operator == ( const Str & rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator == ( const SubStr & rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator == ( const char * rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator < ( const Str & rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator < ( const SubStr & rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator < ( const char * rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator != ( const SubStr & rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator != ( const char * rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator > ( const SubStr & rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator > ( const char * rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator <= ( const SubStr & rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator <= ( const char * rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator >= ( const SubStr & rhs ) const;
    	    operator == acts like a compare.

    	bool
    	operator >= ( const char * rhs ) const;
    	    operator == acts like a compare.

    	virtual std::ostream &
    	toStream( std::ostream & dest = std::cout ) const;

  	virtual
  	std::ostream &
  	dumpInfo( std::ostream &	dest = std::cerr,
  		  const char *	prefix = "    ",
  		  bool		showVer = true ) const;
  	    Output detailed information about the current
  	    state of the instance.

    	virtual const char *
    	getClassName( void ) const;
    	    Return the name of this class (i.e. Str )

    	virtual Bool
    	good( void ) const;
    	    Returns true if there are no detected errors associated
    	    with this class, otherwise FALSE.

    	virtual const char *
    	error( void ) const
    	    Returns as string description of the state of the class.

    Protected Interface:

    Private Methods:

    Other Associated Functions:

    	std::ostream &
    	operator <<( std::ostream & dest, const Str & obj );

**/

#endif // ! def _clue_Str_hh_
