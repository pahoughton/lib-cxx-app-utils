#ifndef _Str_hh_
#define _Str_hh_
//
// File:        Str.hh
// Desc:        
//
//  	A 'Str' provides many methods to manipulate sequences
//  	of characters. It is a 'iostream' so you can use the '<<'
//  	and '>>' operators.
//
//  	Detailed documentation is at the end of the file
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/30/95 15:04
//
// Revision History:
//
// $Log$
// Revision 1.4  1995/11/05 13:29:09  houghton
// Major Implementation Changes.
// Made more consistant with the C++ Standard
//
//

#include <ClueConfig.hh>

#include <StrStreambuf.hh>
#include <SubStr.hh>

#include <iostream>
#include <algorithm>
#include <vector>

// I'll support string when I can find an implmentation that
// follows the standard
// #include <string>

#include <iterator>
#include <climits>

#ifdef  CLUE_DEBUG
#define inline
#endif


class SubStr;
class RegexScan;
class File;

class Str : public iostream
{

public:

  typedef char *    	iterator;
  typedef const char * 	const_iterator;

  typedef reverse_iterator< char *, char, char &, ptrdiff_t >
    reverse_iterator;
  
  typedef reverse_iterator< const char *, char, const char &, ptrdiff_t >
    const_reverse_iterator;
  
  typedef const_iterator    InputIterator; // work around no compiler support
  
  static const size_t npos;
  
  // constructors
  
  inline Str( void );

  inline Str( const Str &    src,
	      size_t 	     srcStart = 0,
	      size_t 	     srcLen = NPOS );

  inline Str( const SubStr & src,
	      size_t 	     srcStart = 0,
	      size_t 	     srcLen = NPOS );

  inline Str( const char * src, size_t srcLen = NPOS );
  inline Str( size_t count, char src );

  inline Str( InputIterator first, InputIterator last ); 

  inline Str( istream & src, bool text = false, bool line = false );
  
  inline ~Str( void );

  
  // misc support
  
  inline void 	    	    reset( void );

  inline size_t    	    size( void ) const;
  inline size_t    	    length( void ) const;
  inline bool	    	    empty( void ) const;
  inline size_t    	    max_size( void ) const;
  
  inline const char *	    cstr( void ) const;

  inline size_t    	    copy( char * dest,
				  size_t destLen,
				  size_t start = 0 );

  inline StrStreambuf *     rdbuf( void ) const;
  inline StrStreambuf *     rdbuf( void );


  // append

  Str &	        append( const char * src, size_t srcLen = NPOS );
  
  inline Str &	append( const Str & 	src,
			size_t 	    	srcStart = 0,
			size_t 	    	srcLen = NPOS );

  inline Str &	append( const SubStr & 	src,
			size_t 	    	srcStart = 0,
			size_t 	    	srcLen = NPOS );

  inline Str &  append( size_t count, char src );
  inline Str &  append( char src );
  inline Str &  append( InputIterator first, InputIterator last );

  
  // assignment
  
  inline Str &	assign( const Str & 	src,
		    	size_t 	    	srcStart = 0,
			size_t 	    	srcLen = NPOS );

  inline Str &	assign( const SubStr & 	src,
		        size_t 	    	srcStart = 0,
			size_t srcLen = NPOS );

  inline Str &	assign( const char * src, size_t srcLen = NPOS );
  inline Str &  assign( size_t count, char src );
  inline Str &  assign( char src );
  inline Str &  assign( InputIterator first, InputIterator last );

  
  // insert

  inline Str &	insert( size_t 	    	before,
			const Str & 	src,
			size_t 	    	srcStart = 0,
			size_t 	    	srcLen = NPOS );

  inline Str &	insert( size_t 	    	before,
			const SubStr &	src,
			size_t 	    	srcStart = 0,
			size_t 	    	srcLen = NPOS );

  inline Str &	insert( size_t 	    	before,
			const char * 	src,
			size_t      	srcLen = NPOS );

  inline Str &	insert( size_t start, size_t count, char src );
  inline Str &	insert( size_t start, char src );

  inline Str &  insert( iterator    	before,
			InputIterator   first,
			InputIterator   last );

  
  // remove

  inline Str &	remove( size_t start, size_t len = NPOS );
  inline Str &	remove( iterator which );
  inline Str &	remove( iterator first, iterator last );
  
  
  // replacement
  
  Str &	    	replace( size_t     	start,
			 size_t     	len,
			 const char * 	src,
			 size_t     	srcLen = NPOS );
  
  Str &	    	replace( size_t start, size_t len, size_t count, char src );
  
  inline Str &	replace( size_t     	start,
			 size_t     	len,
			 const Str & 	src,
			 size_t     	srcStart = 0,
			 size_t     	srcLen = NPOS );
  
  inline Str &	replace( size_t     	start,
			 size_t     	len,
			 const SubStr & src,
			 size_t     	srcStart = 0,
			 size_t     	srcLen = NPOS );
  
  inline Str &	replace( size_t start, size_t len, char src );

  inline Str &	replace( iterator   	first,
			 iterator   	last, 
			 const Str & 	src,
			 size_t     	srcStart = 0,
			 size_t     	srcLen = NPOS );
  
  inline Str &	replace( iterator   	first,
			 iterator   	last, 
			 const SubStr & src,
			 size_t		srcStart = 0,
			 size_t		srcLen = NPOS );
  
  inline Str &	replace( iterator   	first,
			 iterator	last, 
			 const char *	src,
			 size_t		srcLen = NPOS );
  
  Str &	    	replace( iterator   	first,
			 iterator	last,
			 InputIterator	srcFirst,
			 InputIterator	srcLast );


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
		     size_t	    start = 0,
		     size_t	    len = NPOS ) const;
  
  int 	    compare( const SubStr & two,
		     size_t	    start = 0,
		     size_t	    len = NPOS ) const;
  
  int 	    compare( const char *   two,
		     size_t	    start = 0,
		     size_t	    len = NPOS ) const;
  
  friend int	compare( const SubStr & one,
			 const Str &    two,
			 size_t         len = Str::npos );
  
  friend int	compare( const char *   one,
			 const Str &    two,
			 size_t         len = Str::npos );
  
  int 	    fcompare( const Str &    two,
		      size_t	     start = 0,
		      size_t	     len = npos ) const;
  
  int 	    fcompare( const SubStr & two,
		      size_t	     start = 0,
		      size_t	     len = npos ) const;
  
  int 	    fcompare( const char *   two,
		      size_t	     start = 0,
		      size_t	     len = npos ) const;

  friend int	fcompare( const SubStr & one,
			  const Str &    two,
			  size_t         len = Str::npos );
  
  friend int	fcompare( const char *   one,
			  const Str &    two,
			  size_t         len = Str::npos );
  
  
  // substring

  inline char &     at( size_t index );
  inline char 	    at( size_t index ) const;

  inline SubStr     	substr( size_t start = 0, size_t len = npos );
  inline const SubStr   substr( size_t start = 0, size_t len = npos ) const;
  inline SubStr     	at( size_t start, size_t len );
  inline const SubStr   at( size_t start, size_t len ) const;

  inline SubStr	    	at( const char *    pat,
			    size_t  	    start = 0,
			    size_t  	    patLen = npos );
  inline const SubStr	at( const char *    pat,
			    size_t  	    start = 0,
			    size_t  	    patLen = npos ) const;
  
  inline SubStr	    	at( const RegexScan & pat, size_t start = 0 );
  inline const SubStr	at( const RegexScan & pat, size_t start = 0 ) const;
  inline SubStr	    	at( const Str & pat, size_t start = 0 );
  inline const SubStr	at( const Str & pat, size_t start = 0 ) const;
  inline SubStr	    	at( const SubStr & pat, size_t start = 0 );
  inline const SubStr	at( const SubStr & pat, size_t start = 0 ) const;
  
  inline SubStr     	before( size_t end );
  inline const SubStr   before( size_t end ) const;
  inline SubStr	    	after( size_t start );
  inline const SubStr	after( size_t start ) const;
 
  // searching

  inline size_t	find( const Str & pat, size_t start = 0) const;
  inline size_t	find( const SubStr & pat, size_t start = 0) const;
  inline size_t	find( const RegexScan & exp, size_t start = 0) const;
  inline size_t	find( const char *  pat,
		      size_t 	    start = 0,
		      size_t 	    patLen = npos) const;
  inline size_t	find( char c, size_t start = 0 ) const;
  
  inline size_t	rfind( const Str & s, size_t end = npos) const;
  inline size_t	rfind( const SubStr & s, size_t end = npos) const;
  inline size_t	rfind( const char * s,
		       size_t	    end = npos,
		       size_t	    sLen = npos) const;
  inline size_t	rfind( char c, size_t end = npos ) const;

  // fold (ignore case)
  
  inline size_t	ffind( const Str & s, size_t start = 0) const;
  inline size_t	ffind( const SubStr & s, size_t start = 0) const;
  inline size_t	ffind( const char * s,
		       size_t start = 0,
		       size_t sLen = npos) const;
  inline size_t	ffind( char c, size_t start = 0 ) const;
  
  inline size_t	rffind( const Str & s, size_t end = npos) const;
  inline size_t	rffind( const SubStr & s, size_t end = npos) const;
  inline size_t	rffind( const char * s,
			size_t	     end = npos,
			size_t	     sLen = npos) const;
  inline size_t	rffind( char c, size_t end = npos ) const;

  
  inline size_t find_first_of( const Str & s, size_t start = 0 ) const;
  inline size_t find_first_of( const SubStr & s, size_t start = 0 ) const;
  inline size_t find_first_of( const char * s,
			       size_t start = 0,
			       size_t sLen = npos ) const;

  inline size_t find_last_of( const Str & s, size_t end = npos ) const;
  inline size_t find_last_of( const SubStr & s, size_t end = npos ) const;
  inline size_t find_last_of( const char * s,
			      size_t end = npos,
			      size_t sLen = npos ) const;
  
  inline size_t find_first_not_of( const Str & s, size_t start = 0 ) const;
  inline size_t find_first_not_of( const SubStr & s, size_t start = 0 ) const;
  inline size_t find_first_not_of( const char * s,
				   size_t start = 0,
				   size_t sLen = npos ) const;

  inline size_t find_last_not_of( const Str & s, size_t end = npos ) const;
  inline size_t find_last_not_of( const SubStr & s, size_t end = npos ) const;
  inline size_t find_last_not_of( const char * s,
				  size_t end = npos,
				  size_t sLen = npos ) const;
  
  // converters

  // NOTE: from appends
  
  inline Str &	from( int   	    	src, unsigned short base = 0);
  inline Str &	from( short 	    	src, unsigned short base = 0);
  inline Str &	from( long  	    	src, unsigned short base = 0);
  inline Str &	from( unsigned int  	src, unsigned short base = 0);
  inline Str &	from( unsigned short 	src, unsigned short base = 0);
  inline Str &	from( unsigned long 	src, unsigned short base = 0);
  
  inline bool	to( int &   	    	dest, unsigned short base = 0 ) const;
  inline bool	to( short & 	    	dest, unsigned short base = 0 ) const;
  inline bool	to( long &  	    	dest, unsigned short base = 0 ) const;
  inline bool	to( float & 	    	dest, unsigned short base = 0 ) const;
  inline bool	to( double & 	    	dest, unsigned short base = 0 ) const;
  inline bool	to( unsigned int &  	dest, unsigned short base = 0 ) const;
  inline bool	to( unsigned short &  	dest, unsigned short base = 0 ) const;
  inline bool	to( unsigned long  &	dest, unsigned short base = 0 ) const;
  
  inline bool	    	toBool( void ) const;
  inline int	    	toInt( unsigned short base = 0 ) const;
  inline long	    	toLong( unsigned short base = 0 ) const;
  inline double    	toDouble( unsigned short base = 0 ) const;
  inline unsigned int	toUInt( unsigned short base = 0 ) const;
  inline unsigned long	toULong( unsigned short base = 0 ) const;

  // modifications

  inline void	    	upcase( void );
  inline void	    	downcase( void );
  inline void 	    	capitalize( void );

  size_t        	strip( const char * stripChars );
  inline size_t    	stripLeading( const char * stripChars );
  inline size_t    	stripTrailing( const char * strinpChars );
  inline size_t    	stripEnds( const char * stripChars = " \t\n\r\f\v" );

  Str &     substitute( char 	from,
			char 	to,
			size_t 	start = 0,
			bool 	global = true );
  
  Str &     substitute( const char * 	from,
			const char * 	to,
			size_t 	    	start = 0,
			bool 	    	global = true );

  Str &	    substitute( const RegexScan &    exp,
		       const char * 	    to,
		       size_t 	    	    start = 0,
		       bool 	    	    global = true );

  size_t    wrap( size_t width = 72, long pad = -1, long firstPad = -1 );
  
  // scan - scan for substrings
  
  size_t    scan( const RegexScan & exp, size_t start = 0 );
  size_t    scan( const Str & delimChars, size_t start = 0 );
  size_t    scan( const SubStr & delimChars, size_t start = 0 );
  size_t    scan( const char * delimChars, size_t start = 0, size_t dLen = npos );
  size_t    scan( char delim, size_t start = 0 );

  size_t    scanPattern( const RegexScan & delimExp, size_t start = 0 );
  size_t    scanString( const Str & delimStr, size_t start = 0 ); 
  size_t    scanString( const SubStr & delimStr, size_t start = 0 );
  size_t    scanString( const char * dStr, size_t start = 0, size_t dLen = npos );
  
  // scan support

  inline size_t	    scanMatchCount( void ) const;
  inline SubStr	    scanMatch( size_t scanNum = 0 );
  inline size_t     scanMatch( Str & dest, size_t scanNum = 0 ) const;

  inline size_t	    scanMatchStart( size_t scanNum = 0 ) const;
  inline size_t	    scanMatchLength( size_t scanNum = 0 ) const;

  // io helpers

  friend ostream & operator << ( ostream & dest, const Str & str );

  friend istream & operator >> ( istream & src, Str & dest );

  istream & 	getline( istream & src );
  istream & 	getDelim( istream & 	src,
			  char      	delim,
			  bool 	    	discard = true );

  istream & 	getDelim( istream & 	src,
			  const char *  delimChars,
			  bool 	    	discard = true );
  
  istream &	get( istream & src, size_t bytes );
  
  inline size_t getStreamSize( void ) const;
  ostream & 	write( ostream & dest ) const;
  istream & 	read( istream & src );
    
  File & 	write( File & dest ) const;
  File & 	read( File & src );
    
  // operators
  
  inline       	    operator const char * ( void ) const;
  
  inline char &	    operator [] ( size_t index );
  inline char 	    operator [] ( size_t index ) const;

  inline SubStr     	operator () ( size_t start, size_t len );
  inline const SubStr   operator () ( size_t start, size_t len ) const;

  inline Str &	    operator =  ( const Str & src );
  inline Str &	    operator =  ( const SubStr & src );
  inline Str &      operator =  ( const char * src );
  inline Str &	    operator =  ( char src );
  
  inline Str &	    operator += ( const Str & src );
  inline Str &	    operator += ( const SubStr & src );
  inline Str &      operator += ( const char * src );
  inline Str &	    operator += ( char src );
  
  inline bool       operator == ( const Str & two ) const;
  inline bool	    operator == ( const SubStr & two ) const;
  inline bool	    operator == ( const char * two ) const;
  
  inline bool	    operator <  ( const Str & two ) const;
  inline bool	    operator <  ( const SubStr & two ) const;
  inline bool	    operator <  ( const char * two ) const;

  // Str !=, >, <=, >= Str provided by <algorithm>

  inline bool	    operator !=  ( const SubStr & two ) const;
  inline bool	    operator !=  ( const char * two ) const;
  
  inline bool	    operator >  ( const SubStr & two ) const;
  inline bool	    operator >  ( const char * two ) const;
  
  inline bool	    operator <= ( const SubStr & two ) const;
  inline bool	    operator <= ( const char * two ) const;
  
  inline bool	    operator >= ( const SubStr & two ) const;
  inline bool	    operator >= ( const char * two ) const;
  
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream & 	toStream( ostream & dest = cout ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
				  bool		showVer = true ) const;
  
  virtual const char *	getVersion( void ) const;
  
  static const char version[];
  
protected:

  friend class SubStr;
  
  inline const char *	strbase() const;

  bool writeNum( unsigned long num, unsigned short base = 0, bool neg = false);

  struct ScanMatch
  {
    size_t  pos;
    size_t  len;
    ScanMatch( size_t p = 0, size_t l = 0 ) { pos = p; len = l; };
    ~ScanMatch( ) {};
  };
  
  vector<ScanMatch>  matches;
  
private:

  size_t length( const char * from );
  size_t pos( const char * at );
  
};

#ifndef inline
#include <Str.ii>
#else
#undef inline

// These are always defined, the ifndef is just
// to keep the compiler from getting mad

int
compare( const Str &    one,
	 const Str &    two,
	 size_t         len = Str::npos );
  
int
compare( const Str & 	one,
	 const SubStr & two,
	 size_t         len = Str::npos );
  
int
compare( const Str &    one,
	 const char *   two,
	 size_t         len = Str::npos );
  
int
fcompare( const Str &    one,
	  const Str &    two,
	  size_t         len = Str::npos );
  
int
fcompare( const Str & 	one,
	  const SubStr & two,
	  size_t         len = Str::npos );
  
int
fcompare( const Str &    one,
	  const char *   two,
	  size_t         len = Str::npos );
  

Str
operator + ( const Str & lhs, const Str & rhs );

Str
operator + ( const Str & lhs, const SubStr & rhs );

Str
operator + ( const Str & lhs, const char * rhs );

Str
operator + ( const char * lhs, const Str & rhs );

bool
operator == ( const char * lhs, const Str & rhs );

bool
operator != ( const char * lhs, const Str & rhs );

bool
operator <  ( const char * lhs, const Str & rhs );

bool
operator >  ( const char * lhs, const Str & rhs );

bool
operator <= ( const char * lhs, const Str & rhs );

bool
operator >= ( const char * lhs, const Str & rhs );

istream &
getline( istream & src, Str & dest, char delim = '\n' );


bool	    	StringToBool( const Str & str );
int 	    	StringToInt( const Str & str, unsigned short base = 0 );
long	    	StringToLong( const Str & str, unsigned short base = 0 );
double	    	StringToDouble( const Str & str, unsigned short base = 0 );
unsigned int 	StringToUInt( const Str & str, unsigned short base = 0 );
unsigned long	StringToULong( const Str & str, unsigned short base = 0 );

#endif



//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	Str	class
//
//  Constructors:
//
//  	Str( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. Str )
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
//  	operator <<( ostream & dest, const Str & obj );
//

#endif // ! def _Str_hh_ 

