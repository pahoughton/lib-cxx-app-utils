#ifndef _Str_hh_
#define _Str_hh_
/**
   File:        Str.hh
   Project:	StlUtils (%PP%)
   Item:   	%PI% (%PF%)
   Desc:        
  
    A 'Str' provides many methods to manipulate sequences
    of characters (i.e. strings). It is a 'iostream' so you
    can use the '<<' and '>>' operators.
  
   Author:      Paul Houghton - (houghton@cworld.wiltel.com)
   Created:     05/30/95 15:04
  
   Revision History: (See end of file for Revision Log)
  
    Last Mod By:    %PO%
    Last Mod:	    %PRT%
    Version:	    %PIV%
    Status: 	    %PS%
  
    %PID%
    
**/

#include <StlUtilsConfig.hh>
#include <DumpInfo.hh>
#include <iostream>
#include <iterator>
#include <functional>
#include <utility>
#include <vector>
#include <cstddef>



#if defined( STLUTILS_DEBUG )
#define inline
#endif

class STLUTILS_CLASS_T StrStreambuf;
class STLUTILS_CLASS_T SubStr;
class STLUTILS_CLASS_T RegexScan;

class STLUTILS_CLASS_T Str : public iostream
{

public:

  typedef STLUTILS_U32_SIZE_T			size_type;
  typedef ptrdiff_t				difference_type;
  typedef char &				reference;
  typedef const char &				const_reference;
  typedef char *				pointer;
  typedef const char *				const_pointer;
  typedef pointer				iterator;
  typedef const_pointer				const_iterator;

#if defined( STLTUTILS_STD_ITERATORS )

  typedef std::reverse_iterator< iterator,
    random_access_iterator_tag,
    char >					    reverse_iterator;
  typedef std::reverse_iterator< const_iterator,
    random_access_iterator_tag,
    const char >				    const_reverse_iterator;
  
#else
  
#if defined( STDCXX_PARTIAL_SPECIALIZATION )
  typedef ::reverse_iterator< iterator >	reverse_iterator;
  typedef ::reverse_iterator< const_iterator >	const_reverse_iterator;
#else
  typedef ::reverse_iterator< iterator, char, char &, ptrdiff_t >
	reverse_iterator;
  
  typedef ::reverse_iterator< const_iterator, char, const char &, ptrdiff_t >
	const_reverse_iterator;
#endif
#endif
  
#if defined( STLUTILS_HAVE_LONG_LONG )
  typedef pair< long long, long long >	Range;
#else
  typedef pair< long, long >	Range;
#endif
  
  typedef vector< Range >   RangeList;
  
  typedef const_iterator    InputIterator; // work around no compiler support
  
  static const size_type npos;
  
  // constructors
  
  Str( void );

  inline Str( const Str &    src,
	      size_type      srcStart = 0,
	      size_type      srcLen = npos );

  inline Str( const SubStr & src,
	      size_type 	     srcStart = 0,
	      size_type 	     srcLen = npos );

  inline Str( const char * src, size_type srcLen = npos );
  inline Str( size_type count, char src );

  inline Str( InputIterator first, InputIterator last ); 

  inline Str( istream & src, bool text = false, bool line = false );
  
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
			size_type 	    	srcStart = 0,
			size_type 	    	srcLen = npos );

  inline Str &	append( const SubStr & 	src,
			size_type 	    	srcStart = 0,
			size_type 	    	srcLen = npos );

  inline Str &  append( size_type count, char src );
  inline Str &  append( char src );
  inline Str &  append( InputIterator first, InputIterator last );

  
  // assignment
  
  inline Str &	assign( const Str & 	src,
		    	size_type 	    	srcStart = 0,
			size_type 	    	srcLen = npos );

  inline Str &	assign( const SubStr & 	src,
		        size_type 	    	srcStart = 0,
			size_type srcLen = npos );

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
  
  inline Str &	replace( size_type start, size_type len, char src );

  inline Str &	replace( iterator   	first,
			 iterator   	last, 
			 const Str & 	src,
			 size_type     	srcStart = 0,
			 size_type     	srcLen = npos );
  
  inline Str &	replace( iterator   	first,
			 iterator   	last, 
			 const SubStr & src,
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
  
  inline SubStr	    	at( const RegexScan & pat, size_type start = 0 );
  inline const SubStr	at( const RegexScan & pat, size_type start = 0 ) const;
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
  inline size_type	find( const RegexScan & exp, size_type start = 0) const;
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

#if defined( STLUTILS_HAVE_LONG_LONG )
  inline Str &	from( long long		src, unsigned short base = 0);
  inline Str &	from( unsigned long long src, unsigned short base = 0);
#endif

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
  
#if defined( STLUTILS_HAVE_LONG_LONG )
  inline bool	to( long long &	    	dest,
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
  inline long long    	toLongLong( unsigned short base = 0,
				    bool       stopAtNonDigit = false ) const;
  
  inline unsigned long long toULongLong( unsigned short base = 0,
					 bool	stopAtNonDigit = false ) const;
#endif
  
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

  Str &	    substitute( const RegexScan &    exp,
		       const char * 	    to,
		       size_type 	    	    start = 0,
		       bool 	    	    global = true );

  size_type    wrap( size_type width = 72, long pad = -1, long firstPad = -1 );
  
  // scan - scan for substrings
  
  size_type    scan( const RegexScan & exp, size_type start = 0 );
  
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

  size_type    scanPattern( const RegexScan & delimExp, size_type start = 0 );
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

  istream &	    getline( istream & src );
  
  // from istream
  inline istream &  getline( char * dest, int size, char delim = '\n' );
  inline istream &  getline( unsigned char * dest, int size, char d = '\n' );
  
  istream & 	getDelim( istream & 	src,
			  char      	delim,
			  bool 	    	discard = true );

  istream & 	getDelim( istream & 	src,
			  const char *  delimChars,
			  bool 	    	discard = true );
  
  istream &	    get( istream & src, size_type bytes );

  // from istream
  inline istream &  get( char & dest );
  inline istream &  get( char * dest, int size, char delim = '\n' );
  inline istream &  get( unsigned char * dest, int size, char delim = '\n' );
  inline istream &  get( unsigned char & dest );
  inline int	    get( void );
  inline istream &  get( streambuf & dest, char delim = '\n' );
  
  // operators
  
  inline       	    operator const char * ( void ) const;
  
  inline char &	    operator [] ( size_type index );
  inline char 	    operator [] ( size_type index ) const;

  inline SubStr     	operator () ( size_type start, size_type len );
  inline const SubStr   operator () ( size_type start, size_type len ) const;

  inline Str &	    operator =  ( const Str & rhs );
  inline Str &	    operator =  ( const SubStr & rhs );
  inline Str &      operator =  ( const char * rhs );
  inline Str &	    operator =  ( char rhs );
  
  inline Str &	    operator += ( const Str & rhs );
  inline Str &	    operator += ( const SubStr & rhs );
  inline Str &      operator += ( const char * rhs );
  inline Str &	    operator += ( char rhs );
  
  inline bool       operator == ( const Str & rhs ) const;
  inline bool	    operator <  ( const Str & rhs ) const;

#if defined( STLUTILS_RELOPS_BROKEN )
  inline bool		operator != ( const Str & rhs ) const;
  inline bool		operator >  ( const Str & rhs ) const;
  inline bool		operator <= ( const Str & rhs ) const;
  inline bool		operator >= ( const Str & rhs ) const;
#endif
  
  inline bool	    operator == ( const SubStr & rhs ) const;
  inline bool	    operator <  ( const SubStr & rhs ) const;
  inline bool	    operator != ( const SubStr & rhs ) const;
  inline bool	    operator >  ( const SubStr & rhs ) const;
  inline bool	    operator <  ( const char * rhs ) const;
  inline bool	    operator <= ( const SubStr & rhs ) const;
  inline bool	    operator >= ( const SubStr & rhs ) const;

  inline bool	    operator == ( const char * rhs ) const;
  inline bool	    operator != ( const char * rhs ) const;
  inline bool	    operator >  ( const char * rhs ) const;
  inline bool	    operator <= ( const char * rhs ) const;
  inline bool	    operator >= ( const char * rhs ) const;
  // libStlUtils Common Class Methods
  
  virtual size_type	getBinSize( void ) const;
    
  virtual ostream & 	write( ostream & dest ) const;

  // from ostream
  virtual ostream &	write( const char * src, int size );
#if defined( STLUTILS_STR_UNSIGNED )
  virtual ostream &	write( const unsigned char * src, int size );
#endif
  
#if defined( STLUTILS_STR_WCHAR )
  virtual ostream &	write( const wchar_t * src, int size );
#endif
  virtual ostream &	write( const void * src, size_type size );
  
  virtual istream & 	read( istream & src );

  // from istream
  virtual istream &	read( char * dest, int size );
  
#if defined( STLUTILS_STR_UNSIGNED )
  virtual istream &	read( unsigned char * dest, int size );
#endif
  
  virtual istream &	fromStream( istream & src );
  virtual ostream &	toStream( ostream & dest = cout ) const;
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
				  bool		showVer = true ) const;
    
  inline DumpInfo< Str >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  static const ClassVersion version;
  
protected:

  friend class SubStr;
  
  inline const char *	strbase() const;

#if defined( STLUTILS_HAVE_LONG_LONG )
  bool writeNum( unsigned long long num,
		 unsigned short base = 0,
		 bool neg = false);
#else
  bool writeNum( unsigned long num, unsigned short base = 0, bool neg = false);
#endif
  struct ScanMatch
  {
    size_type  pos;
    size_type  len;
    ScanMatch( void ) { pos = 0; len = 0; };
    ScanMatch( size_type p, size_type l = 0 ) { pos = p; len = l; };
    ~ScanMatch( ) {};
  };
  
  vector<ScanMatch>  matches;
  
private:

  size_type length( const char * from );
  size_type pos( const char * at );
  
};

#if !defined( inline )
#include <Str.ii>
#else
#undef inline

// These are always defined, the ifndef is just
// to keep the compiler from getting mad

int
compare( const Str &    one,
	 const Str &    two,
	 Str::size_type         len = Str::npos );
  
int
compare( const Str & 	one,
	 const SubStr & two,
	 Str::size_type         len = Str::npos );
  
int
compare( const Str &    one,
	 const char *   two,
	 Str::size_type         len = Str::npos );
  
int
fcompare( const Str &    one,
	  const Str &    two,
	  Str::size_type         len = Str::npos );
  
int
fcompare( const Str & 	one,
	  const SubStr & two,
	  Str::size_type         len = Str::npos );
  
int
fcompare( const Str &    one,
	  const char *   two,
	  Str::size_type         len = Str::npos );
  

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
operator <  ( const char * lhs, const Str & rhs );

bool
operator != ( const char * lhs, const Str & rhs );

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

ostream &
operator << ( ostream & dest, const Str & src );

istream &
operator >> ( istream & src, Str & dest );

#endif

#include <SubStr.hh>


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
    	at( const RegexScan & pat, size_type start = 0 );
  
    	const SubStr
    	at( const RegexScan & pat, size_type start = 0 ) const;
  
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
    	find( const RegexScan & exp, size_type start = 0 )const;
  
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
  
    	Str &
    	substitute( const RegexScan & exp,
                    const char * to,
                    size_type start = 0,
                    bool global = true );
    	    substitute in a Str starting a position(start) any occurance
    	    of (exp) with (to) while(global = true).
  
    	size_type
    	wrap( size_type width = 72, long pad = -1, long firstPad = -1 )
       	    wrap will reformat a string by inserting( firstPad) white spaces
    	    at the begining of an Str, insert a newline between words where
    	    they would extend beyond (width), and insert (pad) white spaces
    	    after each newline.
  
    	size_type
    	scan( const RegexScan & exp, size_type start = 0 );
  
    	size_type
    	scan( const Str & delimCharts, size_type start = 0 );
  
    	size_type
    	scan( const SubStr & delimChars, size_type start = 0 );
  
    	size_type
    	scan( const char * delimChars, size_type start = 0, size_type dLen = npos );
  
    	size_type
    	scan( char delim, size_type start = 0 );
  
    	size_type
    	scanPattern( const RegexScan & delimExp, size_type start = 0 );
  
    	size_type
    	scanString( const Str & delimStr, size_type start = 0 );
  
    	size_type
    	scanString( const SubStr & delimStr, size_type start = 0 );
  
    	size_type
    	scanString( const char * dStr, size_type start = 0, size dLen = npos );
  
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
  
    	friend ostream & operator << ( ostream & dest, const Str & str );
  
    	friend istream & operator >> ( istream & src, Str & dest );
  
    	istream &
    	getline( istream & src );
  
    	istream &
    	getDelim( istream & src, const char * delimChars, bool discard = true );
  
    	istream &
    	getDelim( istream & src, char delim, bool discard = true );
  
    	size_type
    	getStreamSize( void ) const;
  
    	ostream &
    	write( ostream & dest ) const;
  
    	istream &
    	read( istream & src );
  
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
  
    	virtual ostream &
    	toStream( ostream & dest = cout ) const;
  
    	virtual ostream &
    	dumpInfo( ostream & dest = cerr ) const;
  
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
  
    	ostream &
    	operator <<( ostream & dest, const Str & obj );

**/

//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.7  2001/07/29 19:56:38  houghton
// *** empty log message ***
//
// Revision 5.6  2001/07/28 01:15:00  houghton
// *** empty log message ***
//
// Revision 5.5  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
// Revision 5.4  2000/06/27 11:58:11  houghton
// Added dump().
//
// Revision 5.3  2000/06/04 17:58:05  houghton
// Updated documentation.
//
// Revision 5.2  2000/05/25 17:05:46  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:17  houghton
// Changed Version Num to 5
//
// Revision 4.14  2000/04/19 10:13:32  houghton
// Changed Range to use 'long long' vs unsigned long.
// Changed to support -range value.
//
// Revision 4.13  1999/05/09 13:00:50  houghton
// Added long long support.
//
// Revision 4.12  1999/05/01 12:53:36  houghton
// Added scan( quotechars ) to support delimited files with quoted fields.
//
// Revision 4.11  1999/03/02 12:49:27  houghton
// Cleanup.
//
// Revision 4.10  1998/10/23 13:07:05  houghton
// Changed to support both new (Std) and old types of reverse_iterator.
//
// Revision 4.9  1998/10/13 16:23:48  houghton
// Changed to use new standard include files.
// Cleanup.
//
// Revision 4.8  1998/10/13 15:24:47  houghton
// Port(AIX41): write( wchar_t *) not available.
//
// Revision 4.7  1998/07/20 11:26:53  houghton
// Port(Hpux): wchar not supported.
//
// Revision 4.6  1998/04/02 14:18:13  houghton
// Port(Linux): functional.h implements != operator.
//
// Revision 4.5  1998/03/30 14:06:32  houghton
// Removed get( wchar ) and getline( wchar ) - not standard.
//
// Revision 4.4  1998/03/23 10:45:45  houghton
// Changed to eliminate Sun5 compiler warnings.
//
// Revision 4.3  1998/02/17 13:50:25  houghton
// Added stopAtNonDigit arg to to() methods.
//
// Revision 4.2  1997/09/19 11:21:10  houghton
// Changed to use new portable types (STLUTILS*_T).
//
// Revision 4.1  1997/09/17 15:12:53  houghton
// Changed to Version 4
//
// Revision 3.10  1997/09/17 11:08:45  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.9  1997/09/02 13:08:28  houghton
// Added to( Range )
// Added to( RangeList )
//
// Revision 3.8  1997/08/08 13:24:25  houghton
// Changed copy() to const.
//
// Revision 3.7  1997/07/18 19:29:02  houghton
// Added fromStream.
// Port(Sun5): had to create a default constructor for 'ScanMatch' to
//     prevent the compiler from CRASHING.
// Chagned: istream operator >> Str and ostream operator << Str do not
//     need to be freinds of Str.
//
// Revision 3.6  1997/04/03 23:23:21  houghton
// Changed include stddef to stddef.h
//
// Revision 3.5  1997/03/07 11:53:54  houghton
// Cleanup.
//
// Revision 3.4  1997/03/02 13:20:24  houghton
// Changed to use 'size_type'
//
// Revision 3.3  1997/01/18 17:34:21  houghton
// Bug-Fix: Linux - had to remove (actually ifdef out) functions that can
//     be created with functional.h.
//
// Revision 3.2  1996/11/20 12:12:18  houghton
// Removed support for BinStream.
//
// Revision 3.1  1996/11/14 01:24:12  houghton
// Changed to Release 3
//
// Revision 2.8  1996/10/11 17:43:01  houghton
// Changed: Added new 'multiDelim' arg to scan methods. This arg
//   specifies if multiple consecutive instances of the delimiter are
//   ignored or create separate matches.
//      Example: 'this,is,,a,test'
//               mutliDelim == true:  4 fields
//               multiDelim == false: 5 fields (the third has a 0 length).
//
// Revision 2.7  1996/07/04 10:28:49  houghton
// Added to( bool ).
//
// Revision 2.6  1996/05/03 16:13:41  houghton
// AIX Port cleanup.
//
// Revision 2.5  1996/04/27 13:08:50  houghton
// Cleanup includes.
//
// Revision 2.4  1996/02/29 19:07:08  houghton
// Added some ifndefs for GNU
//
// Revision 2.3  1995/12/04 11:18:27  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.2  1995/11/10  14:08:39  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:41:04  houghton
// Change to Version 2
//
// Revision 1.6  1995/11/05  15:28:47  houghton
// Revised
//
//

#endif // ! def _Str_hh_ 

