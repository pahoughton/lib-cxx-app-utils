//
// File:        MapFile.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     08/02/95 06:13
//
// Revision History:
//
// $Log$
// Revision 3.2  1997/09/17 11:09:14  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:25:25  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:14  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  13:13:49  houghton
// Initial implementation
//
//
#include "MapFile.hh"

#include <StlUtils.hh>

#include <cerrno>

#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

#ifdef   STLUTILS_DEBUG
#define  inline
#include <MapFile.ii>
#endif

#ifdef AIX
extern "C" size_t getpagesize( void );
#endif

const char MapFile::version[] =
LIB_STLUTILS_VERSION
"$Id$";

const size_t MapFile::pageSize = getpagesize();

MapFile::~MapFile( void )
{
  close();
}
  
bool
MapFile::open(
  const char *	    fileName,
  ios::open_mode    mode,
  int		    perm,
  caddr_t	    mapOpenAddr,
  streampos	    mapOpenPos,
  size_t	    mapOpenSize 
  )
{
  mapBase = 0;
  
  close();
  
  if( ! file.open( fileName, mode, perm ) )
    return( false );

  openBase = mapOpenAddr;
  openPos  = mapOpenPos;
  openSize = mapOpenSize;

  if( openSize )
    mapSize = openSize;
  else
    mapSize = max( pageSize,
		   (size_t)( file.getFileStat().getSize() - openPos ));

  mapEnd = file.getFileStat().getSize();

  if( mode & ios::app )
    mapPos = mapEnd;
  else
    mapPos = 0;
  
  return( map( mapSize ) != 0 );
}

void
MapFile::close( void )
{
  if( mapBase )
    {
      munmap( mapBase, mapSize );
      mapBase = 0;
      mapSize = 0;
    }
  file.truncate( mapEnd );
  file.close();
}

bool
MapFile::is_open( void ) const
{
  return( file.is_open() && mapBase != 0 );
}

streampos
MapFile::seek( ios::seek_dir dir, streamoff offset )
{
  streampos  pos = (dir == ios::beg ? 0 :
		    dir == ios::cur ? mapPos : mapEnd );

  pos += offset;

  if( pos < 0 )
    return( -1 );
  
  if( (size_t)pos >= mapSize  )
    {
      if( (size_t)file.seek( ios::end, 0 ) < pageAlign( pos + openPos) )
	{
	  int i = 0;
	  file.seekpos( pageAlign( pos + openPos) );
	  if( ! file.write( &i, sizeof( i ) ).good() )
	    return( -1 );
	}
      
      if( ! map( pos ) )
	return( -1 );
    }

  mapPos = pos;

  return( mapPos );
}

streampos
MapFile::tell( void ) const
{
  return( mapPos );
}

MapFile &
MapFile::read( void * dest, size_t amount )
{
  bytesRead = min( amount, (size_t)( mapSize - mapPos) );

  if( bytesRead )
    memcpy( dest, mapBase + mapPos, bytesRead );

  mapPos += bytesRead;
  
  if( bytesRead < (ssize_t)amount )
      state = ios::eofbit | ios::badbit;
  
  return( *this );
}

MapFile &
MapFile::write( const void * src, size_t amount )
{
  if( mapPos + amount >= mapSize )
    {
      if( ! map( mapPos + amount ) )
	{
	  state = ios::eofbit | ios::badbit;
	  return( *this );
	}
    }

  memcpy( mapBase + mapPos, src, amount );

  mapPos += amount;
  
  if( mapPos > mapEnd )
    mapEnd = mapPos;
  
  return( *this );
}

size_t
MapFile::size( void )
{
  return( mapSize );
}

int
MapFile::sync( void )
{
  return( 0 );
}


  
// getClassName - return the name of this class
const char *
MapFile::getClassName( void ) const
{
  return( "MapFile" );
}

// good - return TRUE if no detected errors
bool
MapFile::good( void ) const
{
  return( file.good() && mapBase != 0 );
}

// error - return a string describing the current state
const char *
MapFile::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName() << ": '" << file.getFileStat().getName() << "' - ";

  if( good() )
    {
       errStr << "ok.";
    }
  else
    {
      if( ! file.good() )
	errStr << file.error();

      if( mapErrno )
	errStr << " Map Error: " << strerror( mapErrno ) ;
    }

  return( errStr.cstr() );
}

ostream &
MapFile::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << "    openBase:    " << (void*)openBase << '\n'
       << "    openPos:     " << openPos << '\n'
       << "    openSize:    " << openSize << '\n'
       << "    mapBase:     " << (void*)mapBase << '\n'
       << "    mapSize:     " << mapSize << '\n'
       << "    mapPos:      " << mapPos << '\n'
    ;

  dest << "    file:        " ;
  file.dumpInfo( dest );
  
  dest << '\n';

  return( dest );
}

  
caddr_t
MapFile::map( size_t size )
{
  if( ! file.good() )
    return( 0 );

#ifdef __linux__
  int first = (mapBase ? *(int *)mapBase : 0 );
#endif
  if( mapBase )
    munmap( mapBase, mapSize );
  
  mapErrno = 0;

  int mapProt = 0;
  
  if( file.getOpenMode() & ios::in )
    {
      mapProt = PROT_READ;
    }

  if( file.getOpenMode() & (ios::out | ios::app ) )
    {
      mapProt |= PROT_WRITE;
    }

  if( ! mapProt )
    {
      mapBase = 0;
      mapErrno = EPERM;
      return( 0 );
    }

  mapSize = pageAlign( max( size, pageSize ) );

  if( ! (size_t)(file.seek( ios::end, 0 ) >= (mapSize + openPos) ) )
    {
      int i = 0;
      file.seekpos( mapSize + openPos - sizeof( i ) );
      if( ! file.write( &i, sizeof( i ) ).good() )
	return( 0 );
#ifdef __linux__
      file.seekpos( 0 );
      file.write( &first, sizeof( first ) );
#endif
    }
		  
  mapBase = mmap( openBase,
		  mapSize,
		  mapProt,
#ifdef __linux__
		  MAP_SHARED | (openBase == 0 ? 0 : MAP_FIXED ),
#else
		  MAP_SHARED | (openBase == 0 ? MAP_VARIABLE : MAP_FIXED ),
#endif
		  file.getFD(),
		  openPos );

  if( ! mapBase )
    mapErrno = ::errno;

  return( mapBase );
}


  
