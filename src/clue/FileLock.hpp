#ifndef _FileLock_hh_
#define _FileLock_hh_
/* 1997-09-12 (cc) Paul Houghton <paul4hough@gmail.com>

   Provides unix file locking (flock) functionallity.
*/

#include <clue/FilePath.hpp>
#include <clue/DumpInfo.hpp>
#include <iostream>
#include <vector>

namespace clue {

class FileLock
{

public:

  enum Type
  {
    Read = 0,
    Shared = 0,
    Write = 1,
    Exclusive = 1,
    Unlock = 2,
    T_Undefined
  };

  FileLock( const char * fileName, std::ios::openmode mode = std::ios::in );
  FileLock( int fd );

  virtual ~FileLock( void );

  inline bool	lockread( std::streamoff	offset = 0,
			  std::ios::seek_dir dir = std::ios::beg,
			  size_t	amount = 0,
			  bool		block = true );

  inline bool	lockwrite( std::streamoff	    offset = 0,
			   std::ios::seek_dir    dir = std::ios::beg,
			   size_t	    amount = 0,
			   bool		    block = true );

  inline bool	unlock( std::streamoff	offset = 0,
			std::ios::seek_dir	dir = std::ios::beg,
			size_t		amount = 0 );

  bool	lock( Type  type,
	      std::streamoff	    offset = 0,
	      std::ios::seek_dir dir = std::ios::beg,
	      size_t	    amount = 0,
	      bool	    block = true );


  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  bool			blocked( void ) const;
  virtual int		oserror( void ) const;
  virtual bool		clear( void );

  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  inline DumpInfo< FileLock >
  dump( const char * preifx = "    " ) const;

  static const char *	typeName( Type t );

protected:

  FilePath  lockFn;
  int	    fd;

  struct Lock
  {
    Type	    type;
    std::streamoff	    offset;
    std::ios::seek_dir   dir;
    size_t	    amount;

    Lock( void )
      : type( T_Undefined ), offset( 0 ), dir( std::ios::beg ), amount( 0 ) {};

    Lock( Type		t,
	  std::streamoff	o = 0,
	  std::ios::seek_dir	d = std::ios::beg,
	  size_t	a = 0 )
      : type( t ), offset( o ), dir( d ), amount( a ) {};

  };

  typedef std::vector< Lock >	LockList;

  LockList	locks;
  int		oserrno;
  bool		closefd;

private:

  FileLock( const FileLock & from );
  FileLock & operator =( const FileLock & from );

};

inline
bool
FileLock::lockread(
  std::streamoff	offset,
  std::ios::seek_dir	dir,
  size_t	amount,
  bool		block
  )
{
  return( lock( Read, offset, dir, amount, block ) );
}

inline
bool
FileLock::lockwrite(
  std::streamoff	offset,
  std::ios::seek_dir	dir,
  size_t	amount,
  bool		block
  )
{
  return( lock( Write, offset, dir, amount, block ) );
}

inline
bool
FileLock::unlock(
  std::streamoff	offset,
  std::ios::seek_dir	dir,
  size_t	amount
  )
{
  return( lock( Unlock, offset, dir, amount, false ) );
}


inline
DumpInfo< FileLock >
FileLock::dump( const char * prefix ) const
{
  return( DumpInfo< FileLock >( *this, prefix ) );
}

}; // namespace clue
#endif // ! def _FileLock_hh_
