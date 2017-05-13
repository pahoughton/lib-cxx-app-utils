#ifndef _clue_FileBatch_hpp_
#define _clue_FileBatch_hpp_
/* 1999-03-24 (cc) Paul Houghton <paul4hough@gmail.com>

   Provides an iterator interface to a file containing fixed length records.
*/
#include <clue/FileStat.hpp>
#include <clue/DumpInfo.hpp>

#include <iterator>
#include <fstream>
#include <cerrno>

namespace clue {

class FileBatchBase
{
public:
  inline const char *	getFileName( void ) const {
    return( name );
  };

protected:

  typedef uint64_t	size_type;

  FileBatchBase( const char * fileName, size_type recordSize );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;

  enum ErrorNum
  {
    E_OK,
    E_OPEN,
    E_SIZE,
    E_READ,
    E_WRITE,
    E_UNDEFINED
  };

  bool		setError( ErrorNum errNum, std::streampos pos, int osErr );

  FilePath	    name;
  std::fstream *    batch;
  size_type	    recSize;

  ErrorNum	    errorNum;
  std::streampos    errorPos;
  int		    osErrno;
};

template< class T >
class FileBatch : public FileBatchBase
{

public:

  typedef FileBatch< T >	self;

  typedef T			Rec;

  typedef uint64_t	size_type;
  typedef ptrdiff_t	difference_type;
  typedef Rec &		reference;
  typedef const Rec &	const_reference;

  class const_iterator;

  // * iterator *
  class iterator
    : public std::iterator< std::bidirectional_iterator_tag,
                            Rec,
                            difference_type,
                            Rec *,
                            Rec & >
  {
  public:

    inline iterator( void )
      : owner( 0 ), pos( 0 ), readPos( 0 )
      {};

    inline iterator( const iterator & from )
      : owner( from.owner ),
	rec( from.rec ),
	pos( from.pos ),
	readPos( from.readPos )
      {};

    inline iterator &	operator ++ ( void ) {
      pos += (std::streampos) sizeof( Rec );
      return( *this );
    };

    inline iterator &	operator ++ (int) {
      iterator it( *this );
      ++ *this;
      return( it );
    };

    inline iterator &	operator -- ( void ) {
      pos -= (std::streampos) sizeof( Rec );
      return( *this );
    };

    inline iterator &	operator -- (int) {
      iterator it( *this );
      -- *this;
      return( it );
    };

    inline reference	operator *  ( void ) {
      if( readPos != pos )
	{
	  std::streampos cur( (*owner).file().tellg() );
	  readPos = pos;
	  (*owner).file().seekg( pos, std::ios::beg );
	  (*owner).read( rec );
	  (*owner).file().seekg( cur, std::ios::beg );
	}
      return( rec );
    };

    inline iterator &	operator = ( const iterator & rhs ) {
      owner	= rhs.owner;
      rec	= rhs.rec;
      pos	= rhs.pos;
      readPos	= rhs.readPos;
      return( *this );
    };

    inline bool	    operator == ( const iterator & rhs ) const {
      return( owner == rhs.owner && pos == rhs.pos );
    };

  protected:

    friend class const_iterator;
    friend class FileBatch< T >;

    inline iterator( FileBatch< T > * o, size_type recNum )
      : owner( o ),
	readPos( NPOS )
      {
	std::streampos cur( (*owner).file().tellg() );

	if( recNum == NPOS )
	  (*owner).file().seekg( 0, std::ios::end );
	else
	  (*owner).file().seekg( recNum * sizeof( rec ), std::ios::beg );

	pos = (*owner).file().tellg();

	(*owner).file().seekg( cur, std::ios::beg );
      };

    FileBatch< T > *	    owner;
    Rec			    rec;
    std::streampos		    pos;
    std::streampos		    readPos;
  };


  // * const_iterator *
  class const_iterator
    : public std::iterator< std::bidirectional_iterator_tag,
                            Rec,
                            difference_type,
                            Rec *,
                            Rec & >
  {
  public:
    inline const_iterator( void )
      : owner( 0 ), pos( 0 ), readPos( 0 )
      {};

    inline const_iterator( const const_iterator & from )
      : owner( from.owner ),
	rec( from.rec ),
	pos( from.pos ),
	readPos( from.readPos )
      {};

    inline const_iterator( const typename self::iterator & from )
      : owner( from.owner ),
	rec( from.rec ),
	pos( from.pos ),
	readPos( from.readPos )
      {};

    inline const_iterator &	operator ++ ( void ) {
      pos += (std::streampos) sizeof( Rec );
      return( *this );
    };

    inline const_iterator &	operator ++ (int) {
      const_iterator it( *this );
      ++ *this;
      return( it );
    };

    inline const_iterator &	operator -- ( void ) {
      pos -= (std::streampos) sizeof( Rec );
      return( *this );
    };

    inline const_iterator &	operator -- (int) {
      const_iterator it( *this );
      -- *this;
      return( it );
    };

    inline const reference	operator *  ( void ) {
      if( readPos != pos )
	{
	  std::streampos cur( (*owner).file().tellg() );
	  readPos = pos;
	  (*owner).file().seekg( pos, std::ios::beg );
	  (*owner).read( rec );
	  (*owner).file().seekg( cur, std::ios::beg );
	}
      return( rec );
    };

    inline const_iterator &	operator = ( const const_iterator & rhs ) {
      owner	= rhs.owner;
      rec	= rhs.rec;
      pos	= rhs.pos;
      readPos	= rhs.readPos;
      return( *this );
    };

    inline const_iterator &	operator = (
      const typename self::iterator & rhs
      ) {
      owner	= rhs.owner;
      rec	= rhs.rec;
      pos	= rhs.pos;
      readPos	= rhs.readPos;
      return( *this );
    };

    inline bool	    operator == ( const const_iterator & rhs ) const {
      return( owner == rhs.owner && pos == rhs.pos );
    };

    inline bool	    operator != ( const const_iterator & rhs ) const {
      return( ! (*this == rhs) );
    };

    inline bool	    operator == ( const typename self::iterator & rhs ) const {
      return( owner == rhs.owner && pos == rhs.pos );
    };

    inline bool	    operator != ( const typename self::iterator & rhs ) const {
      return( !(*this == rhs));
    };

  protected:

    friend class iterator;
    friend class FileBatch< T >;

    inline const_iterator( const FileBatch< T > * o, size_type recNum )
      : owner( o ),
	readPos( NPOS )
      {
	std::streampos cur( (*owner).file().tellg() );

	if( recNum == NPOS )
	  (*owner).file().seekg( 0, std::ios::end );
	else
	  (*owner).file().seekg( recNum * sizeof( rec ), std::ios::beg );

	pos = (*owner).file().tellg();

	(*owner).file().seekg( cur, std::ios::beg );
      };

    const FileBatch< T > *	owner;
    Rec				rec;
    std::streampos			pos;
    std::streampos			readPos;
  };

  FileBatch( const char *   fileName,
	     std::ios::openmode  mode = std::ios::in );

  FileBatch( const char *   fileName,
	     std::ios::openmode  mode,
	     bool	    create );

  virtual ~FileBatch( void ) {
    if( batch )	    delete batch;
  };

  const_iterator	    begin( void ) const;
  const_iterator	    end( void ) const;

  iterator		    begin( void );
  iterator		    end( void );

  Rec			    front( void ) const;
  Rec			    back( void ) const;

  iterator		    append( void );
  bool			    append( const Rec & src );

  FileBatch< T > &	    read( Rec & dest );
  bool			    read( Rec & dest ) const;

  FileBatch< T > &	    read( Rec & dest, size_type recNum );
  bool			    read( Rec & dest, size_type recNum ) const;

  FileBatch< T > &	    write( const Rec & src );
  FileBatch< T > &	    write( iterator & it );

  size_type		    size( void ) const;

  Rec			    operator [] ( size_type rec ) const;

  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual std::ostream &     dumpInfo( std::ostream &	dest = std::cerr,
				       const char *	prefix = "    " ) const;

  inline DumpInfo< FileBatch >
  dump( const char * prefix = "    " ) const {
    return( DumpInfo< FileBatch >( *this, prefix ) );
  }



protected:

  friend class const_iterator;
  friend class iterator;

  std::fstream &	file( void ) const;

  size_type	fileSize;

private:

  FileBatch( const FileBatch & from );
  FileBatch & operator =( const FileBatch & from );

};

template< class Rec >
inline
FileBatch< Rec >::FileBatch(
  const char *	fileName,
  std::ios::openmode    mode
  )
  : FileBatchBase( fileName, sizeof( Rec ) ),
    fileSize( 0 )
{
  batch = new std::fstream( name, mode );

  std::streampos cur( 0 );
  std::streampos endPos( 0 );

  if( batch && (*batch).good() )
    {
      cur = (*batch).tellg();
      (*batch).seekg( 0, std::ios::end );
      endPos = (*batch).tellg();

      if( endPos % sizeof( Rec ) )
	{
	  setError( E_SIZE, endPos, 0 );
	  return;
	}
      fileSize = endPos / sizeof( Rec );
      (*batch).seekg( cur, std::ios::beg );
    }
  else
    {
      setError( E_OPEN, 0, errno );
    }

  return;
}

template< class Rec >
inline
FileBatch< Rec >::FileBatch(
  const char *	fileName,
  std::ios::openmode    mode,
  bool		    create
  )
  : FileBatchBase( fileName, sizeof( Rec ) ),
    fileSize( 0 )
{
  if( ! create ) {
    FileStat fStat( fileName );
    if( ! fStat.good() ) {
      setError( E_OPEN, 0, ENOENT );
      return;
    }
  } else {
    // create is true, make sure the file exists
    std::fstream tmp(name, std::ios::out );
  }

  batch = new std::fstream( name, mode );

  std::streampos cur( 0 );
  std::streampos endPos( 0 );

  if( batch && (*batch).good() )
    {
      cur = (*batch).tellg();
      (*batch).seekg( 0, std::ios::end );
      endPos = (*batch).tellg();

      if( endPos % sizeof( Rec ) )
	{
	  setError( E_SIZE, endPos, 0 );
	  return;
	}
      fileSize = endPos / sizeof( Rec );
      (*batch).seekg( cur, std::ios::beg );
    }
  else
    {
      setError( E_OPEN, 0, errno );
    }

  return;
}

template< class Rec >
inline
typename FileBatch< Rec >::const_iterator
FileBatch< Rec >::begin( void ) const
{
  return( const_iterator( this, 0 ) );
}

template< class Rec >
inline
typename FileBatch< Rec >::const_iterator
FileBatch< Rec >::end( void ) const
{
  return( const_iterator( this, NPOS ) );
}

template< class Rec >
inline
typename FileBatch< Rec >::iterator
FileBatch< Rec >::begin( void )
{
  return( iterator( this, 0 ) );
}

template< class Rec >
inline
typename FileBatch< Rec >::iterator
FileBatch< Rec >::end( void )
{
  return( iterator( this, NPOS ) );
}

template< class Rec >
inline
Rec
FileBatch< Rec >::front( void ) const
{
  return( (*this)[0] );
}

template< class Rec >
inline
Rec
FileBatch< Rec >::back( void ) const
{
  return( (*this)[ size() - 1 ] );
}

template< class Rec >
inline
typename FileBatch< Rec >::iterator
FileBatch< Rec >::append( void )
{
  (*batch).seekg( 0, std::ios::end );

  std::streampos endPos( (*batch).tellg() );

  size_type endRecNum( endPos / sizeof( Rec ) );

  Rec r;

  if( (*batch).write( (const char *)&r, sizeof( r ) ).good() )
    {
      ++ fileSize;
      return( iterator( this, endRecNum ) );
    }
  else
    {
      setError( E_WRITE, (*batch).tellp(), errno );
      return( end() );
    }
}

template< class Rec >
inline
bool
FileBatch< Rec >::append( const Rec & r )
{
  (*batch).seekg( 0, std::ios::end );

  if( (*batch).write( (const char *)&r, sizeof( r ) ).good() )
    {
      ++ fileSize;
      return( true );
    }
  else
    {
      setError( E_WRITE, (*batch).tellp(), errno );
      return( false );
    }
}

template< class Rec >
inline
FileBatch< Rec > &
FileBatch< Rec >::read( Rec & dest )
{
  if( ! (*batch).read( (char *)&dest, sizeof( dest ) ).good() )
    {
      setError( E_READ, (*batch).tellg(), errno );
    }

  return( *this );
}

template< class Rec >
inline
bool
FileBatch< Rec >::read( Rec & dest ) const
{
  return( (*batch).read( (char *)&dest, sizeof( dest ) ).good() );
}

template< class Rec >
inline
FileBatch< Rec > &
FileBatch< Rec >::read( Rec & dest, size_type recNum )
{
  (*batch).seekg( recNum * sizeof( Rec ), std::ios::beg );
  return( read( dest ) );
}

template< class Rec >
inline
bool
FileBatch< Rec >::read( Rec & dest, size_type recNum ) const
{
  (*batch).seekg( recNum * sizeof( Rec ), std::ios::beg );
  return( read( dest ) );
}

template< class Rec >
inline
FileBatch< Rec > &
FileBatch< Rec >::write( const Rec & src )
{
  if( ! (*batch).write( (const char *)&src, sizeof( src ) ).good() )
    {
      setError( E_WRITE, (*batch).tellp(), errno );
    }

  return( *this );
}

template< class Rec >
inline
FileBatch< Rec > &
FileBatch< Rec >::write( iterator & it )
{
  (*batch).seekp( it.pos, std::ios::beg );
  return( write( it.rec ) );
}

template< class Rec >
inline
typename FileBatch< Rec >::size_type
FileBatch< Rec >::size( void ) const
{
  return( fileSize );
}

template< class Rec >
inline
Rec
FileBatch< Rec >::operator [] ( size_type rec ) const
{
  Rec r;
  read( r, rec );
  return( r );
}

template< class Rec >
inline
bool
FileBatch< Rec >::good( void ) const
{
  return( FileBatchBase::good() );
}

template< class Rec >
inline
const char *
FileBatch< Rec >::error( void ) const
{
  return( FileBatchBase::error() );
}

template< class Rec >
inline
std::ostream &
FileBatch< Rec >::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! FileBatch< Rec >::good() )
    dest << prefix << "Error: " << FileBatch< Rec >::error() << '\n';
  else
    dest << prefix << "Good!\n";

  dest << prefix << "name:     " << name << '\n'
       << prefix << "size:     " << fileSize << '\n'
    ;

  return( dest );
}

template< class Rec >
inline
std::fstream &
FileBatch< Rec >::file( void ) const
{
  return( *batch );
}


};
#endif // ! def _clue_FileBatch_hpp_
