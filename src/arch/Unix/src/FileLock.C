//
// File:        FileLock.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for FileLock
//  
// Author:      Paul A. Houghton - (paul.houghton@mci.com)
// Created:     09/12/97 11:35
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "FileLock.hh"
#include <Str.hh>
#include <StlUtilsMisc.hh>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>

#if defined( STLUTILS_DEBUG )
#include "FileLock.ii"
#endif

STLUTILS_VERSION(
  FileLock,
  "$Id$ ");

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

FileLock::FileLock( const char * fileName, ios::open_mode mode )
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
  Type		type,
  streamoff	offset,
  ios::seek_dir	dir,
  size_t	amount,
  bool		block )
{
  struct flock lock;

  lock.l_type	= FileLock_FcntlLockTypes[ type ];
  lock.l_whence	= Whence( dir );
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

  errStr = FileLock::getClassName();

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

const char *
FileLock::getClassName( void ) const
{
  return( "FileLock" );
}

const char *
FileLock::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
FileLock::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << FileLock::getClassName() << ":\n"
	 << FileLock::getVersion() << '\n';

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

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.4  2003/08/09 11:21:00  houghton
// Changed ver strings.
//
// Revision 5.3  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.2  2000/07/31 13:38:37  houghton
// Bug-Fix: was not removing locks correctly.
//
// Revision 5.1  2000/05/25 10:33:22  houghton
// Changed Version Num to 5
//
// Revision 4.4  1997/10/22 16:03:10  houghton
// Added file name so it could be placed in the error string.
//
// Revision 4.3  1997/09/21 21:20:42  houghton
// Port(Sun5): added include <cstring>
//
// Revision 4.2  1997/09/21 13:18:13  houghton
// Port(Aix41): needed to add include errno.h
//
// Revision 4.1  1997/09/17 15:13:30  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 15:10:28  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.2  1997/09/17 11:09:18  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/09/16 11:21:12  houghton
// Initial Version.
//
//
