//
// File:        Semaphore.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for Semaphore
//  
// Author:      Paul A. Houghton - (paul4hough@gmail.com)
// Created:     06/10/97 05:33
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "Semaphore.hh"
#include <Str.hh>
#include <StlUtilsMisc.hh>
#include <cstring>

#if defined( STLUTILS_DEBUG )
#include "Semaphore.ii"
#endif

STLUTILS_VERSION(
  Semaphore,
  "$Id$ ");

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

const key_t	Semaphore::badKey( STLUTILS_SEM_BADKEY );
const int	Semaphore::badSem( STLUTILS_SEM_BADSEM );

Semaphore::Semaphore( void )
  : key( STLUTILS_SEM_BADKEY ),
    semId( STLUTILS_SEM_BADSEM ),
    osErrno( ENOENT )
{
}

Semaphore::Semaphore( key_t semKey, int numSems, int flags )
  : key( STLUTILS_SEM_BADKEY ),
    semId( STLUTILS_SEM_BADSEM ),
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
  : key( STLUTILS_SEM_BADKEY ),
    semId( STLUTILS_SEM_BADSEM ),
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
#if defined( STLUTILS_HAS_SEMUN )
      static union semun  OpRemove = { 0 };
#else
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
Semaphore::islocked( void ) const
{
  if( semId != badSem )
    {
#if defined( STLUTILS_HAS_SEMUN )
      static union semun  OpGetVal = { 0 };
#else
      long OpGetVal = 0;
#endif
      
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
      else
	errStr << '(' << semId << ')';
      
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
#if defined( STLUTILS_HAS_SEMUN )
      union semun	buff;
      buff.buf =	&semInfo;
#else
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
// 
// %PL%
// 
// $Log$
// Revision 6.3  2011/12/30 23:57:33  paul
// First go at Mac gcc Port
//
// Revision 6.2  2006/05/11 19:37:39  houghton
// Added sem id to error output.
//
// Revision 6.1  2003/08/09 11:22:47  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:23  houghton
// Changed Version Num to 5
//
// Revision 4.2  1998/03/30 14:17:52  houghton
// Added open() and clear() methods.
//
// Revision 4.1  1997/09/17 15:13:35  houghton
// Changed to Version 4
//
// Revision 3.7  1997/09/17 15:10:29  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.6  1997/09/17 11:09:23  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.5  1997/09/16 11:28:22  houghton
// Added islocked method().
//
// Revision 3.4  1997/07/18 21:30:44  houghton
// Cleanup
// Port(Sun5): reworked to use STLUTILS_HAS_SEMUN define.
//
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
