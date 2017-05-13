#ifndef _clue_SubStr_hh_
#define _clue_SubStr_hh_
/* 1995-05-30 (cc) Paul Houghton - (paul4hough@gmail.com)

  A 'SubStr' is a section of a 'Str'. Any modifications to
  the 'SubStr' modify the 'Str' it is a section of.
*/

#include <cstddef>
#include <iostream>

#if !defined(NPOS)
#define NPOS static_cast<size_t>(-1)
#endif

namespace clue {
class Str;

class SubStr
{

public:

  typedef size_t	size_type;

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

  inline bool	to( long long  &	dest,
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


  inline long long	toLongLong( unsigned short base = 0,
				    bool stopAtNonDigit = false ) const;

  inline unsigned long long toULongLong( unsigned short base = 0,
					 bool stopAtNonDigit = false ) const;

  int 	    compare( const Str &    two,
		     size_type      start = 0,
		     size_type      len = npos ) const;
  int	    compare( const SubStr & two,
		     size_type      start = 0,
		     size_type      len = npos ) const;
  int	    compare( const std::string & two,
		     size_type		 start = 0,
		     size_type		 len = npos ) const;
  int	    compare( const char *   two,
		     size_type      start = 0,
		     size_type      len = npos ) const;

  friend int	compare( const std::string & one,
			 const SubStr &	     two,
			 size_type	     len = SubStr::npos );

  friend int	compare( const char * 	one,
			 const SubStr & two,
			 size_type      len = SubStr::npos );

  int	    fcompare( const Str &    two,
		      size_type      start = 0,
		      size_type      len = npos ) const;
  int	    fcompare( const SubStr & two,
		      size_type      start = 0,
		      size_type      len = npos ) const;
  int	    fcompare( const std::string & two,
		      size_type		  start = 0,
		      size_type		  len = npos ) const;
  int	    fcompare( const char *   two,
		      size_type      start = 0,
		      size_type      len = npos ) const;

  friend int	fcompare( const std::string & one,
			  const SubStr &      two,
			  size_type	      len = SubStr::npos );

  friend int	fcompare( const char *    one,
			  const SubStr &  two,
			  size_type       len = SubStr::npos );

  inline char &     operator [] ( size_type index );
  inline char       operator [] ( size_type index ) const;

  inline SubStr &   operator =  ( const SubStr & rhs );
  inline SubStr &   operator =  ( const Str & rhs );
  inline SubStr &   operator =  ( const std::string & rhs );
  inline SubStr &   operator =  ( const char * rhs );
  inline SubStr &   operator =  ( char rhs );

  inline SubStr &   operator += ( const SubStr & rhs );
  inline SubStr &   operator += ( const Str & rhs );
  inline SubStr &   operator += ( const std::string & rhs );
  inline SubStr &   operator += ( const char * rhs );
  inline SubStr &   operator += ( char rhs );

  inline bool       operator == ( const SubStr & rhs ) const;
  inline bool       operator == ( const Str & rhs ) const;
  inline bool       operator == ( const std::string & rhs ) const;
  inline bool       operator == ( const char * rhs ) const;

  inline bool       operator <  ( const SubStr & rhs ) const;
  inline bool       operator <  ( const Str & rhs ) const;
  inline bool       operator <  ( const std::string & rhs ) const;
  inline bool       operator <  ( const char * rhs ) const;

  inline bool       operator != ( const SubStr & rhs ) const;
  inline bool       operator != ( const Str & rhs ) const;
  inline bool       operator != ( const std::string & rhs ) const;
  inline bool       operator != ( const char * rhs ) const;

  inline bool       operator >  ( const SubStr & rhs ) const;
  inline bool       operator >  ( const Str & rhs ) const;
  inline bool       operator >  ( const std::string & rhs ) const;
  inline bool       operator >  ( const char * rhs ) const;

  inline bool       operator <= ( const SubStr & rhs ) const;
  inline bool       operator <= ( const Str & rhs ) const;
  inline bool       operator <= ( const std::string & rhs ) const;
  inline bool       operator <= ( const char * rhs ) const;

  inline bool       operator >= ( const SubStr & rhs ) const;
  inline bool       operator >= ( const Str & rhs ) const;
  inline bool       operator >= ( const std::string & rhs ) const;
  inline bool       operator >= ( const char * rhs ) const;

  // libStlUtils Common Class Methods

  size_type	    getBinSize( void ) const;

  std::ostream &	    write( std::ostream & dest ) const;
  std::istream &	    read( std::istream & src );

  virtual std::ostream & toStream( std::ostream & dest = std::cout ) const;

  friend inline std::ostream &  operator << ( std::ostream & dest, const SubStr & src );
  friend inline std::istream &  operator >> ( std::istream & src, SubStr & dest );

  inline bool	    good( void ) const;
  const char *	    error( void ) const;
  std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
			      const char *	prefix = "    " ) const;

private:

  friend class 	Str;

  inline const char * 	strbase( void ) const;
  static Str dummyStr;

  Str &	    	str;
  const Str &   constStr;
  size_type    	pos;
  size_type    	len;

};

}; // namespace clue

#include <clue/Str.hpp>

namespace clue {
inline
SubStr::SubStr( Str & src, size_type start, size_type length )
  : str( src ),
    constStr( src ),
    pos( start ),
    len( std::min( src.size() - start, length ) )
{
}

inline
SubStr::SubStr( const Str & src, size_type start, size_type length )
  : str(dummyStr),
    constStr( src ),
    pos( start ),
    len( std::min( src.size() - start, length ) )
{
  ;
}

inline
SubStr::size_type
SubStr::size( void ) const
{
  return( len );
}

inline
SubStr::size_type
SubStr::length( void ) const
{
  return( size() );
}

inline
bool
SubStr::empty( void ) const
{
  return( size() == 0 );
}

inline
Str &
SubStr::of( void )
{
  return( str );
}

inline
const Str &
SubStr::of( void ) const
{
  return( str );
}

inline
SubStr::size_type
SubStr::copy( char * dest, size_type destLen, size_type start ) const
{
  size_type copyLen = (destLen == npos ? size() - start :
		       std::min( destLen, size() - start ) );

  strncpy( dest, strbase() + start, copyLen );
  if( destLen == npos || copyLen < destLen )
    dest[ copyLen ] = 0;
  return( copyLen );
}

inline
bool
SubStr::to( bool & dest ) const
{
  return( size() ? StringTo( dest, strbase(), length() ) : false );
}

inline
bool
SubStr::to( int & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
SubStr::to( short & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
SubStr::to( long & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
SubStr::to( long long & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
SubStr::to( float & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
SubStr::to( double & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
SubStr::to( unsigned int & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
SubStr::to( unsigned short & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
SubStr::to( unsigned long & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
SubStr::to( unsigned long long & dest, unsigned short base, bool sand ) const
{
  return( size() ? StringTo( dest, strbase(), base, length(), sand ) : false );
}

inline
bool
SubStr::toBool( void ) const
{
  bool dest = false;
  StringTo( dest, strbase(), length());
  return( dest );
}

inline
int
SubStr::toInt( unsigned short base, bool sand ) const
{
  int dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
long
SubStr::toLong( unsigned short base, bool sand ) const
{
  long dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
double
SubStr::toDouble( unsigned short base, bool sand ) const
{
  double dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
unsigned int
SubStr::toUInt( unsigned short base, bool sand ) const
{
  unsigned int dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
unsigned long
SubStr::toULong( unsigned short base, bool sand ) const
{
  unsigned long dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
long long
SubStr::toLongLong( unsigned short base, bool sand ) const
{
  long long dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
unsigned long long
SubStr::toULongLong( unsigned short base, bool sand ) const
{
  unsigned long long dest = 0;
  to( dest, base, sand );
  return( dest );
}

inline
char &
SubStr::operator [] ( size_type index )
{
  static char bad = 0;
  return( str[ pos + index ] );
}

inline
char
SubStr::operator [] ( size_type index ) const
{
  return( constStr[ pos + index ] );
}

inline
SubStr &
SubStr::operator =  ( const SubStr & src )
{
  str.replace( pos, len, src );
  len = src.size();
  return( *this );
}

inline
SubStr &
SubStr::operator =  ( const Str & src )
{
  str.replace( pos, len, src );
  len = src.size();
  return( *this );
}

inline
SubStr &
SubStr::operator =  ( const char * src )
{
  str.replace( pos, len, src );
  len = strlen( src );
  return( *this );
}

inline
SubStr &
SubStr::operator =  ( char src )
{
  str.replace( pos, len, src );
  len = 1;
  return( *this );
}


inline
SubStr &
SubStr::operator += ( const SubStr & src )
{
  str.replace( pos + len, 0, src );
  len += src.size();
  return( *this );
}

inline
SubStr &
SubStr::operator += ( const Str & src )
{
  str.replace( pos + len, 0, src );
  len += src.size();
  return( *this );
}

inline
SubStr &
SubStr::operator += ( const char * src )
{
  str.replace( pos + len, 0, src );
  len += strlen( src );
  return( *this );
}

inline
SubStr &
SubStr::operator += ( char src )
{
  str.replace( pos + len, 0, src );
  len += 1;
  return( *this );
}

inline
bool
SubStr::operator == ( const SubStr & two ) const
{
  return( compare( two ) == 0 );
}

inline
bool
SubStr::operator == ( const Str & two ) const
{
  return( compare( two ) == 0 );
}

inline
bool
SubStr::operator == ( const char * two ) const
{
  return( compare( two ) == 0 );
}


inline
bool
SubStr::operator <  ( const SubStr & two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
SubStr::operator <  ( const Str & two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
SubStr::operator <  ( const char * two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
SubStr::operator != ( const SubStr & two ) const
{
  return( ! ( *this == two ) );
}

inline
bool
SubStr::operator != ( const Str & two ) const
{
  return( ! ( *this == two ) );
}

inline
bool
SubStr::operator != ( const char * two ) const
{
  return( ! ( *this == two ) );
}

inline
bool
SubStr::operator >  ( const SubStr & two ) const
{
  return( compare( two ) > 0 );
}

inline
bool
SubStr::operator >  ( const Str & two ) const
{
  return( compare( two ) > 0 );
}

inline
bool
SubStr::operator >  ( const char * two ) const
{
  return( compare( two ) > 0 );
}

inline
bool
SubStr::operator <=  ( const SubStr & two ) const
{
  return( compare( two ) <= 0 );
}

inline
bool
SubStr::operator <=  ( const Str & two ) const
{
  return( compare( two ) <= 0 );
}

inline
bool
SubStr::operator <=  ( const char * two ) const
{
  return( compare( two ) <= 0 );
}

inline
bool
SubStr::operator >=  ( const SubStr & two ) const
{
  return( compare( two ) >= 0 );
}

inline
bool
SubStr::operator >=  ( const Str & two ) const
{
  return( compare( two ) >= 0 );
}

inline
bool
SubStr::operator >=  ( const char * two ) const
{
  return( compare( two ) >= 0 );
}


inline
bool
SubStr::good( void ) const
{
  return( constStr.good() && str.good() );
}

inline
std::ostream &
operator << ( std::ostream & dest, const SubStr & src )
{
  return( src.toStream( dest ) );
}

inline
std::istream &
operator >> ( std::istream & src, SubStr & dest )
{
  Str tmp( src );
  if( src.good() )
    dest = tmp;
  return( src );
}

inline
const char *
SubStr::strbase( void ) const
{
  return( constStr.strbase() + pos );
}


inline
int
compare(
  const SubStr &    one,
  const char *	    two,
  SubStr::size_type len = NPOS )
{
  return( one.compare( two, 0, len ) );
}

inline
int
fcompare(
  const SubStr &    one,
  const char *	    two,
  SubStr::size_type len = NPOS )
{
  return( one.fcompare( two, 0, len ) );
}

inline
Str
operator + ( const SubStr & lhs, const Str & rhs )
{
  Str s( lhs );
  s += rhs;
  return( s );
}

inline
Str
operator + ( const SubStr & lhs, const SubStr & rhs )
{
  Str s( lhs );
  s += rhs;
  return( s );
}

inline
Str
operator + ( const SubStr & lhs, const char * rhs )
{
  Str s( lhs );
  s += rhs;
  return( s );
}

inline
Str
operator + ( const char * lhs, const SubStr & rhs )
{
  Str s( lhs );
  s += rhs;
  return( s );
}

inline
bool
operator == ( const char * lhs, const SubStr & rhs )
{
  return( compare( lhs, rhs ) == 0 );
}

inline
bool
operator <  ( const char * lhs, const SubStr & rhs )
{
  return( compare( lhs, rhs ) < 0 );
}

inline
bool
operator != ( const char * lhs, const SubStr & rhs )
{
  return( compare( lhs, rhs ) != 0 );
}


inline
bool
operator >  ( const char * lhs, const SubStr & rhs )
{
  return( compare( lhs, rhs ) >  0 );
}

inline
bool
operator <= ( const char * lhs, const SubStr & rhs )
{
  return( compare( lhs, rhs ) <= 0 );
}

inline
bool
operator >= ( const char * lhs, const SubStr & rhs )
{
  return( compare( lhs, rhs ) >= 0 );
}


inline
bool
StringToBool( const SubStr & str )
{
  return( str.toBool() );
}

inline
int
StringToInt( const SubStr & str, unsigned short base = 0 )
{
  return( str.toInt( base ) );
}

inline
long
StringToLong( const SubStr & str, unsigned short base = 0 )
{
  return( str.toLong( base ) );
}

inline
double
StringToDouble( const SubStr & str, unsigned short base = 0 )
{
  return( str.toDouble( base ) );
}

inline
unsigned int
StringToUInt( const SubStr & str, unsigned short base = 0 )
{
  return( str.toUInt( base ) );
}

inline
unsigned long
StringToULong( const SubStr & str, unsigned short base = 0 )
{
  return( str.toULong( base ) );
}


inline
bool
SubStr::operator <  ( const std::string & two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
SubStr::operator == ( const std::string & two ) const
{
  return( compare( two ) == 0 );
}

inline
SubStr &
SubStr::operator += ( const std::string & src )
{
  str.replace( pos + len, 0, src );
  len += src.size();
  return( *this );
}

inline
SubStr &
SubStr::operator =  ( const std::string & src )
{
  str.replace( pos, len, src );
  len = src.size();
  return( *this );
}

} // namespace clue

#endif // ! def _SubStr_hh_
