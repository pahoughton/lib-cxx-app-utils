//
// File:        Semaphore.C
// Project:	Clue
// Desc:        
//
//  Compiled sources for Semaphore
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     06/10/97 05:33
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "Semaphore.hh"
#include <Str.hh>
#include <ClueUtils.hh>

#if defined( CLUE_DEBUG )
#include "Semaphore.ii"
#endif

CLUE_VERSION(
  Semaphore,
  "$Id$");

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
Semaphore::remove( void )
{
  if( semId != badSem )
    {
#if defined( Linux )
      static union semun  OpRemove = { 0 };
#endif

#if defined( AIX41 )
      long OpRemove = 0;
#endif
      
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
Semaphore::good( void ) const
{
  return( osErrno == 0 && semId != badSem );
}

const char *
Semaphore::error( void ) const
{
  static Str errStr;

  errStr = Semaphore::getClassName();

  if( good() )
    {
       errStr += ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( semId == badSem )
	errStr << ": no semaphore!";

      if( osErrno != 0 )
	errStr << ": " << strerror( errno );
      
      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}

const char *
Semaphore::getClassName( void ) const
{
  return( "Semaphore" );
}

const char *
Semaphore::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
Semaphore::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Semaphore::getClassName() << ":\n"
	 << Semaphore::getVersion() << '\n';

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
#if defined( Linux )
      union semun	buff;
      buff.buf =	&semInfo;
#endif

#if defined( AIX41 )
      struct semid_ds *	    buff;
      buff = &semInfo;
#endif
      
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

// Revision Log:
//
// $Log$
// Revision 3.3  1997/07/15 20:20:45  houghton
// Bug-Fix: changed defined( LINUX ) to defined( Linux ).
//
// Revision 3.2  1997/07/14 10:32:42  houghton
// Port: short term fix because aix does not have semun. The long
//     term solution should eliminate the #if defined().
//
// Revision 3.1  1997/06/10 13:54:25  houghton
// Initial Version.
//
//
