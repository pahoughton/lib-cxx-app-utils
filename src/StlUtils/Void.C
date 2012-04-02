/**
   File:        Void.C
   Project:	StlUtils ()
   Desc:        
  
    Compiled sources for Void.
    
   Author:      Paul Houghton - (paul4hough@gmail.com)
   Created:     11/11/95 06:21
  
   Revision History: (See end of file for Revision Log)
  
    $Author$ 
    $Date$ 
    $Name$ 
    $Revision$ 
    $State$ 
**/

#include "Void.hh"
#include <Str.hh>
#include <FileStat.hh>
#include <Compare.hh>
#include <iomanip>
#include <cctype>
#include <fstream>

#if defined( STLUTILS_DEBUG )
#include "Void.ii"
#endif

STLUTILS_VERSION(
  Void,
  "$Id$ ");


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
    dataBufSize( 0 ),
    errorNum( E_NODATA )
{
}

Void::Void( const void * src, size_type size )
  : data( 0 ),
    dataSize( 0 ),
    dataBufSize( 0 ),
    errorNum( E_NODATA )
{
  assign( src, size );
}

Void::Void( const Void & src )
  : data( 0 ),
    dataSize( 0 ),
    dataBufSize( 0 ),
    errorNum( E_NODATA )
{
  assign( src );
}


Void::~Void( void )
{
  if( data ) delete [] data;
}

Void &
Void::append( const void * src, size_type srcSize )
{
  if( ! src || ! srcSize )
    return( *this );
  
  if( ! resize( size() + srcSize ) )
    return( *this );

  memcpy( data + size(), src, srcSize );
  dataSize += srcSize;
  
  if( errorNum == E_NODATA )
    setError( E_OK );
  
  return( *this );
}


Void &
Void::replace( size_type start, size_type len, const void * src, size_type srcSize )
{
  if( start > size() )
    return( setError( E_RANGE ) );
  
  size_type    replaceLen = min( len, size() - start );
  
  size_type    keepSize = size() - ( start + replaceLen );
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
Void::resize( size_type newSize, bool trunc )
{
  if( newSize < dataBufSize && ! trunc )
    return( true );

  char * buf = new char[ newSize + (newSize / 2 ) ];
  
  if( ! buf )
    return( setError( E_ALLOC ).good() );

  dataBufSize = newSize + (newSize / 2 );

  memcpy( buf, data, size() );
  delete data;
  data = buf;
  return( true );
}

int
Void::compare( const Void & rhs ) const
{
  
  if( data && rhs.data )
    {
      int diff = memcmp( data, rhs.data, min( size(), rhs.size() ) );

      if( diff )
	return( diff );
      else
	return( ::compare( size(), rhs.size() ) );
    }
  else
    {
      return( data ? 1 : ( rhs.data ) ? -1 : 0 );
    }
}

Void::size_type
Void::getBinSize( void ) const
{
  return( sizeof( size_type ) + size() );
}

ostream &
Void::write( ostream & dest ) const
{
  size_type len = size();
  dest.write( (const char *)&len, sizeof( len ) );
  dest.write( data, size() );
  return( dest );
}

istream &
Void::read( istream & src )
{
  size_type len;
  src.read( (char *) &len, sizeof( len ) );
  
  if( len && resize( len ) )
    {
      src.read( data, len );
      dataSize = len;
      if( errorNum == E_NODATA )
	setError( E_OK );
    }
  return( src );
}

bool
Void::fromFile( const char * fn )
{
  FileStat stat( fn );

  if( ! stat.good() || stat.getSize() < 1 ) {
    return false;
  } else {
    resize( stat.getSize() );
    if( ! good() ) {
      if( errorNum != E_NODATA ) {
	return false;
      }
    }
    ifstream ifile( fn );
    if( ! ifile.good() ) {
      return false;
    }
    ifile.read( data, stat.getSize() );
    if( ifile.gcount() == stat.getSize() ) {
      dataSize = ifile.gcount();
      if( errorNum == E_NODATA )
        setError( E_OK );
      return true;
    }
  }
    return false;
}
ostream &
Void::toStream( ostream & dest ) const
{
  unsigned char * d = (unsigned char *)data;

  char	    oldFill  = dest.fill( '0' );
  ios::fmtflags  oldFlags = dest.setf( ios::hex, ios::basefield );
  // dest.setf( ios::uppercase );
  
  for( size_type pos = 0; pos < dataSize; pos++ )
    {
      
      if( pos )
	dest << ' ';
      
      dest << setw(2) << (unsigned int)d[pos];
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
      size_type eSize = errStr.size();

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

  dest << prefix << "data:    " << "0x0000 ";

  char		oldFill = dest.fill( '0' );
  ios::fmtflags	oldFlags = dest.setf( ios::hex, ios::basefield );
  
  dest.setf( ios::uppercase );

  char * d = (char *)data;
  
  for( size_type pos = 0 ; pos < dataSize; pos++ )
    {
      if( pos && ! (pos % 8) )
	dest << '\n' << prefix << "         0x" << setw(4) << pos << ' ';
      
      if( isprint( d[pos] ) )
	dest << d[pos] << ' ';
      else
	dest << "0x" << setw(2) << (unsigned int)(unsigned char)d[pos] << ' ' ;
    }

  dest.fill( oldFill );
  dest.flags( oldFlags );

  dest << '\n';
    
  return( dest );
}

