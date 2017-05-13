// 1997-09-12 (cc) Paul Houghton <paul4hough@gmail.com>

#include "FileLock.hpp"
#include "Str.hpp"
#include "Clue.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>

namespace clue {

// NOTE these expects the 'Type' enum values to be correct
//   if you change one, you need to change the other
static int  FileLock_FcntlLockTypes[] =
{
  F_RDLCK, F_WRLCK, F_UNLCK, -1
};

static const char * FileLock_TypeName[] =
{
  "read", "write", "unlock", "UNDEFINED", 0
};

FileLock::FileLock( const char * fileName, std::ios::openmode mode )
  : lockFn( fileName ),
    fd( -1 ),
    oserrno( ENOENT ),
    closefd( false )
{
  // do not allow create
  fd = ::open( fileName,
	       OpenFlags( mode ) & ~O_CREAT );

  if( fd < 0 )
    oserrno = errno;
  else
    oserrno = 0;

  closefd = true;
}

FileLock::FileLock( int fileDescriptor )
  : fd( fileDescriptor ),
    oserrno( fd < 0 ? ENOENT : 0 ),
    closefd( false )
{
}

FileLock::~FileLock( void )
{
  // remove any existing locks
  for( LockList::iterator them = locks.begin();
       them != locks.end();
       them = locks.begin() )
    {
      if( (*them).type != T_Undefined )
	{
	  unlock( (*them).offset, (*them).dir, (*them).amount);
	}
      else
	{
	      locks.erase( them );
	}
    }

  if( closefd )
    ::close( fd );
}

bool
FileLock::lock(
  Type			type,
  std::streamoff	offset,
  std::ios::seek_dir	dir,
  size_t		amount,
  bool			block )
{
  struct flock lock;

  lock.l_type	= FileLock_FcntlLockTypes[ type ];
  lock.l_whence	= ( dir == std::ios::beg ? SEEK_SET :
		    dir == std::ios::cur ? SEEK_CUR :
		    dir == std::ios::end ? SEEK_END : -1 );
  lock.l_start	= offset;
  lock.l_len	= amount;

  if( fcntl( fd, (block ? F_SETLKW : F_SETLK), &lock ) == -1 )
    {
      oserrno = errno;
      return( false );
    }
  else
    {
      if( type == Unlock )
	{
	  LockList::iterator them( locks.begin() );

	  for( ;; )
	    {

	      for( them = locks.begin();
		   them != locks.end();
		   ++ them )
		{
		  if( offset == (*them).offset
		      && dir == (*them).dir
		      && amount == (*them ).amount )
		    break;
		}
	      if( them != locks.end() )
		locks.erase( them );
	      else
		break;
	    }
	}
      else
	{
	  locks.push_back( Lock( type,
				 offset,
				 dir,
				 amount ) );
	}
      return( true );
    }
}


bool
FileLock::good( void ) const
{
  return( oserrno == 0 );
}

const char *
FileLock::error( void ) const
{
  static Str errStr;

  errStr = "FileLock";

  if( good() )
    {
      errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();


      if( oserrno != 0 )
	errStr << ": os error(" << oserrno << ") '"
	       << ( lockFn.empty() ?  "(unknown)" : lockFn.c_str() )
	       << "' - "
	       << strerror( oserrno );

      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}

bool
FileLock::blocked( void ) const
{
  return( oserrno == EAGAIN );
}

int
FileLock::oserror( void ) const
{
  return(  oserrno );
}

bool
FileLock::clear( void )
{
  oserrno = 0;
  return( good() );
}

std::ostream &
FileLock::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{
  if( ! FileLock::good() )
    dest << prefix << "Error: " << FileLock::error() << '\n';
  else
    dest << prefix << "Good" << '\n';

  dest << prefix << "fd:        " << fd << '\n'
       << prefix << "locks:     " << locks.size() << '\n'
    ;

  if( locks.size() )
    {
      for( LockList::const_iterator them = locks.begin();
	   them != locks.end();
	   ++ them )
	{
	  dest << prefix << "  lock:    "
	       << typeName( (*them).type )
	       << ' ' << (*them).offset
	       << ' ' << IosSeekDirToString( (*them).dir )
	       << ' ' << (*them).amount << '\n'
	    ;
	}
    }

  return( dest );
}

const char *
FileLock::typeName( Type t )
{
  return( t >= Read && t <= T_Undefined ? FileLock_TypeName[ t ] : "BAD TYPE" );
}

}; // namespace clue
