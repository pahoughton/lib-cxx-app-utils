#ifndef _clue_FileOp_hpp_
#define _clue_FileOp_hpp_
/* 1998-03-08 (cc) Paul Houghton <paul4hough@gmail.com>

   FileOp provides operations on entire files, such as copy and
   move (rename).

**/

#include <clue/FileStat.hpp>
#include <clue/DumpInfo.hpp>

#include <iostream>

namespace clue {

class FileOp
{

public:

  typedef ssize_t	size_type;

  FileOp( void );
  FileOp( const char * src );

  virtual ~FileOp( void );

  inline bool	copy( const char * dest,
		      bool overwrite = true );

  inline bool	copy( const char * src,
		      const char * dest,
		      bool overwrite = true );

  inline bool	move( const char * dest,
		      bool overwrite = true );
  inline bool	move( const char * src,
		      const char * dest,
		      bool overwrite = true );

  inline bool	cat( const char * dest );
  inline bool	cat( const char * src,
		     const char * dest );

  inline bool	remove( void );
  inline bool	remove( const char * src );

  inline bool	rmdir( const char * dirName, bool recurs = false );

  inline const FileStat &   getSrc( void ) const;
  inline const FileStat &   getDest( void ) const;

  virtual bool		clear( void );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  inline DumpInfo< FileOp >
  dump( const char * prefix = "    " ) const {
    return( DumpInfo< FileOp >( *this, prefix ) );
  }


protected:

  enum OpType
  {
    OT_Copy,
    OT_Move,
    OT_Cat,
    OT_Remove,
    OT_Unknown
  };

  static const char *	OpTypeName[];

  bool		setDest( OpType op, const char * fn, bool overwrite );
  bool		copyFile( void );
  bool		moveFile( void );
  bool		removeFile( const char * fn );
  bool		removeDir( const char * fn, bool recurs );
  bool		catFile( void );
  bool		setDestStat( void );

  size_type	readfd( int fd, void * dest, size_t destSize );
  size_type	writefd( int fd, const void * src, size_t srcLen );

  bool	setError( int osErr, const char * desc, const char * fn );
  bool	setError( int osErr, OpType op, const char * desc, const char * fn );


  FileStat  src;
  FileStat  dest;

  Str	errorDesc;
  int	osError;

};

inline
bool
FileOp::copy( const char * destFn, bool overwrite )
{
  if( ! good() )
    return( false );

  if( ! setDest( OT_Copy, destFn, overwrite ) )
    return( false );

  return( copyFile() );
}

inline
bool
FileOp::copy( const char * srcFn, const char * destFn, bool overwrite )
{
  clear();
  src( srcFn );
  return( copy( destFn, overwrite ) );
}

inline
bool
FileOp::move( const char * destFn, bool overwrite )
{
  if( ! good() )
    return( false );

  if( ! setDest( OT_Move, destFn, overwrite ) )
    return( false );

  return( moveFile() );
}

inline
bool
FileOp::move( const char * srcFn, const char * destFn, bool overwrite )
{
  clear();
  src( srcFn );
  return( move( destFn, overwrite ) );
}

inline
bool
FileOp::cat( const char * destFn )
{
  if( ! good() )
    return( false );

  if( ! setDest( OT_Cat, destFn, true ) )
    return( false );

  return( catFile() );
}

inline
bool
FileOp::cat( const char * srcFn, const char * destFn )
{
  clear();
  src( srcFn );
  return( cat( destFn ) );
};

inline
bool
FileOp::remove( void )
{
  return( removeFile( src.getName() ) );
}

inline
bool
FileOp::remove( const char * fn )
{
  src( fn );
  return( remove() );
}

inline
bool
FileOp::rmdir( const char * dn, bool recurse )
{
  return( removeDir( dn, recurse ) );
}

inline
const FileStat &
FileOp::getSrc( void ) const
{
  return( src );
}

inline
const FileStat &
FileOp::getDest( void ) const
{
  return( dest );
}



}; // namespace clue

#endif // ! def _clue_FileOp_hpp_
