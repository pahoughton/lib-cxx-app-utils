//
// File:        Void.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     11/11/95 06:21
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/12 18:33:33  houghton
// Initial Version.
//
//

#if !defined( CLUE_SHORT_FN )
#include "Void.hh"
#include <Str.hh>
#include <iomanip>
#else
#include "Void.hh"
#include <Str.hh>
#include <iomanip>
#endif

#if defined( CLUE_DEBUG )
#include "Void.ii"
#endif

CLUE_VERSION(
  Void,
  "$Id$");


const char * Void::ErrorStrings[] =
{
  "ok",
  "no data",
  "invalid range",
  "can't allocate",
  "unknown"
};

Void::Void( void )
  : data( 0 ),
    dataSize( 0 ),
    dataBufSize( 0 )
{
}

Void::Void( const void * src, size_t size )
  : data( 0 ),
    dataSize( 0 ),
    dataBufSize( 0 )
{
  assign( src, size );
}

Void::Void( const Void & src )
  : data( 0 ),
    dataSize( 0 ),
    dataBufSize( 0 )
{
  assign( src );
}


Void::~Void( void )
{
  if( data ) delete data;
}

Void &
Void::append( const void * src, size_t srcSize )
{
  if( ! resize( size() + srcSize ) )
    return( *this );

  memcpy( data + size(), src, srcSize );
  return( *this );
}


Void &
Void::replace( size_t start, size_t len, const void * src, size_t srcSize )
{
  if( start > size() )
    return( setError( E_RANGE ) );
  
  size_t    replaceLen = min( len, size() - start );
  
  size_t    keepSize = size() - ( start + replaceLen );
  char *    keepBuf = 0;

  if( keepSize )
    {
      keepBuf = new char[ keepSize + 1];
      if( ! keepBuf )
	return( setError( E_ALLOC ) );
      
      memcpy( keepBuf, data + ( start + replaceLen ), keepSize );
    }

  dataSize = start;

  if( src )
    append( src, srcSize );

  if( keepBuf )
    {
      append( keepBuf, keepSize );
      delete keepBuf;
    }

  return( *this );
}

bool
Void::resize( size_t newSize, bool trunc )
{
  if( newSize < dataBufSize && ! trunc )
    return( true );

  void * buf = new char[ newSize + (newSize / 2 ) ];
  
  if( ! buf )
    return( false );

  dataBufSize = newSize + (newSize / 2 );

  memcpy( buf, data, size() );
  delete data;
  data = buf;
  return( true );
}

  

size_t
Void::getBinSize( void ) const
{
  return( sizeof( ULong ) + size() );
}

BinStream &
Void::write( BinStream & dest ) const
{
  ULong len = size();
  dest.write( len );
  dest.write( data, size() );
  return( dest );
}

BinStream &
Void::read( BinStream & src )
{
  ULong len;
  src.read( len );
  if( len && resize( len ) )
    src.read( data, len );
  dataSize = len;
  return( src  );
}
      
ostream &
Void::write( ostream & dest ) const
{
  ULong len = size();
  dest.write( &len, sizeof( len ) );
  dest.write( data, size() );
  return( dest );
}

istream &
Void::read( istream & src )
{
  ULong len;
  src.read( &len, sizeof( len ) );
  if( len && resize( len ) )
    src.read( data, len );
  dataSize = len;
  return( src );
}

ostream &
Void::toStream( ostream & dest ) const
{
  char * d = (char *)data;

  char	oldFill  = dest.fill( '0' );
  int	oldFlags = dest.setf( ios::hex );
  
  for( size_t pos = 0; pos < dataSize; pos++ )
    {
      if( pos )
	dest << ' ';
      
      dest << setw(2) << d[pos];
    }

  dest.fill( oldFill );
  dest.flags( oldFlags );
  
  return( dest );
}
	


bool
Void::good( void ) const
{
  return( errorNum == E_OK );
}

const char *
Void::error( void ) const
{
  static Str errStr;

  errStr = Void::getClassName();

  if( good() )
    {
       errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( errorNum < E_UNDEFINED )
	errStr << ": " << ErrorStrings[ errorNum ] ;
      
      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.cstr() );
}

const char *
Void::getClassName( void ) const
{
  return( "Void" );
}

const char *
Void::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
Void::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Void::getClassName() << ":\n"
	 << Void::getVersion() << '\n';

  if( ! Void::good() )
    dest << prefix << "Error: " << Void::error() << '\n';
  else
    dest << prefix << "Good" << '\n';

  dest << prefix << "size:    " << size() << endl
       << prefix << "bufSize: " << dataBufSize << endl
    ;

  dest << prefix << "data:    " << "0000 ";

  char  oldFill = dest.fill( '0' );
  int	oldFlags = dest.setf( ios::uppercase | ios::hex );

  char * d = (char *)data;
  
  for( size_t pos = 0 ; pos < dataSize; pos++ )
    {
      if( pos && ! (pos % 8) )
	dest << '\n' << prefix << "         " << setw(4) << pos << ' ';
      dest << d[pos] << ' ';
    }

  dest.fill( oldFill );
  dest.flags( oldFlags );
  
  return( dest );
}

