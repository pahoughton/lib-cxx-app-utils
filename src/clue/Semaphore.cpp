// 1997-06-10 (cc) Paul Houghton <paul4hough@gmail.com>

#include "Semaphore.hpp"
#include "Str.hpp"
#include "Clue.hpp"

#include <cstring>

#include <sys/sem.h>
#include <errno.h>

#define CLUE_SEM_BADKEY -1
#define CLUE_SEM_BADSEM -1

namespace clue {

static struct sembuf	OpLock[2] =
{
  { 0, 0, IPC_NOWAIT },
  { 0, 1, SEM_UNDO }
};

static struct sembuf	OpLockWait[2] =
{
  { 0, 0, 0 },
  { 0, 1, SEM_UNDO }
};

static struct sembuf	OpUnlock[1] =
{
  { 0, -1, ( IPC_NOWAIT | SEM_UNDO ) }
};

static struct sembuf	OpWait[1] =
{
  { 0, 0, 0 }
};

const key_t	Semaphore::badKey( CLUE_SEM_BADKEY );
const int	Semaphore::badSem( CLUE_SEM_BADSEM );

Semaphore::Semaphore( void )
  : key( CLUE_SEM_BADKEY ),
    semId( CLUE_SEM_BADSEM ),
    osErrno( ENOENT )
{
}

Semaphore::Semaphore( key_t semKey, int numSems, int flags )
  : key( CLUE_SEM_BADKEY ),
    semId( CLUE_SEM_BADSEM ),
    osErrno( ENOENT )
{
  create( semKey, numSems, flags );
}

Semaphore::Semaphore(
  const char *	keyPath,
  char		proj,
  int		numSems,
  int		flags
  )
  : key( CLUE_SEM_BADKEY ),
    semId( CLUE_SEM_BADSEM ),
    osErrno( ENOENT )
{
  create( keyPath, proj, numSems, flags );
}

Semaphore::~Semaphore( void )
{
}

bool
Semaphore::create( key_t semKey, int numSems, int flags )
{
  key = semKey;
  semId = semget( key, numSems, flags );

  return( (semId == badSem ) ? setError( errno ) : setError( 0 ) );
}

bool
Semaphore::create(
  const char *	keyPath,
  char		proj,
  int		numSems,
  int		flags
  )
{
  key = ftok( (char *)keyPath, proj );

  return( (key == badKey) ?
	  setError( errno ) :
	  create( key, numSems, flags ) );
}

bool
Semaphore::open( key_t semKey, int numSems )
{
  key = semKey;
  semId = semget( key, numSems, 0 );
  return( (semId == badSem ) ? setError( errno ) : setError( 0 ) );
}

bool
Semaphore::open( const char * keyPath, char proj, int numSems )
{
  key = ftok( (char *)keyPath, proj );

  return( (key == badKey) ?
	  setError( errno ) :
	  open( key, numSems ) );
}

bool
Semaphore::remove( void )
{
  if( semId != badSem )
    {
      long OpRemove = 0;

      if( semctl( semId, 0, IPC_RMID, OpRemove ) != -1 )
	{
	  semId = badSem;
	  setError( 0 );
	  return( true );
	}
      else
	{
	  return( setError( errno ) );
	}
    }

  return( true );
}

bool
Semaphore::lock( bool wait )
{
  if( semId != badSem )
    {
      if( wait )
	{
	  if( semop( semId, OpLockWait, ArraySize( OpLockWait ) ) != -1 )
	    return( setError( 0 ) );
	  else
	    return( setError( errno ) );
	}
      else
	{
	  if( semop( semId, OpLock, ArraySize( OpLock ) ) != -1 )
	    return( setError( 0 ) );
	  else
	    return( setError( errno ) );
	}
    }
  return( false );
}

bool
Semaphore::unlock( void )
{
  if( semId != badSem )
    {
      if( semop( semId, OpUnlock, ArraySize( OpUnlock ) ) != -1 )
	return( setError( 0 ) );
      else
	return( setError( errno ) );
    }

  return( false );
}

bool
Semaphore::islocked( void ) const
{
  if( semId != badSem )
    {
      long OpGetVal = 0;

      int semVal = semctl( semId, 0, GETVAL, OpGetVal );

      if( semVal != -1 )
	return( semVal != 0 );
      else
	return( false );

    }
  return( false );
}

bool
Semaphore::waitfor( void )
{
  if( semId != badSem )
    {
      if( semop( semId, OpWait, ArraySize( OpWait ) ) != -1 )
	return( setError( 0 ) );
      else
	return( setError( errno ) );
    }
  return( false );
}

bool
Semaphore::clear( void )
{
  osErrno = 0;
  return( good() );
}

bool
Semaphore::good( void ) const
{
  return( osErrno == 0 && semId != badSem );
}

const char *
Semaphore::error( void ) const
{
  static Str errStr;

  errStr = "Semaphore";

  if( good() )
    {
       errStr += ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( semId == badSem )
	errStr << ": no semaphore!";
      else
	errStr << '(' << semId << ')';

      if( osErrno != 0 )
	errStr << ": " << strerror( errno );

      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}

std::ostream &
Semaphore::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! Semaphore::good() )
    dest << prefix << "Error: " << Semaphore::error() << '\n';
  else
    dest << prefix << "Good" << '\n';

  dest << prefix << "key:      " << key << '\n'
       << prefix << "semId:    " << semId << '\n'
    ;

  if( semId != badSem )
    {
      struct semid_ds	semInfo;
      struct semid_ds *	    buff;
      buff = &semInfo;

      if( semctl( semId, 0, IPC_STAT, buff ) != -1 )
	{
	  dest << prefix << "perm:     " << semInfo.sem_perm.mode << '\n'
	       << prefix << "otime:    " << semInfo.sem_otime << '\n'
	       << prefix << "ctime:    " << semInfo.sem_ctime << '\n'
	    ;
	}
      else
	{
	  dest << prefix << "error getting info: "
	       << strerror( errno )
	       << '\n'
	    ;
	}
    }

  return( dest );
}
}; // namespace clue
