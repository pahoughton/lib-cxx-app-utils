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
// Revision 3.6  1997/03/16 08:56:50  houghton
// Cleanup dump output.
//
// Revision 3.5  1997/03/16 07:38:36  houghton
// Bug-Fix: reset error in read.
//
// Revision 3.4  1997/03/15 18:06:12  houghton
// Bug-Fix: dumpInfo & toStream - AIX was not outputing hex values.
//     had to change iostream::setf calls.
//
// Revision 3.3  1997/03/07 11:56:04  houghton
// Bug-Fix: append was not setting data size.
// Bug-Fix: set error if an alloc fails.
// Bug-Fix: dumpInfo output format.
//
// Revision 3.2  1996/11/20 12:13:10  houghton
// Removed support for BinStream.
//
// Revision 3.1  1996/11/14 01:24:28  houghton
// Changed to Release 3
//
// Revision 2.2  1995/11/13 11:30:45  houghton
// Added compare function.
// Changed date type from void * to char *.
//
// Revision 2.1  1995/11/12  18:33:33  houghton
// Initial Version.
//
//

#include "Void.hh"
#include <Str.hh>
#include <Compare.hh>
#include <iomanip>
#include <cctype>

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
    dataBufSize( 0 ),
    errorNum( E_NODATA )
{
}

Void::Void( const void * src, size_t size )
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
  if( data ) delete data;
}

Void &
Void::append( const void * src, size_t srcSize )
{
  if( ! resize( size() + srcSize ) )
    return( *this );

  memcpy( data + size(), src, srcSize );
  dataSize += srcSize;
  
  if( errorNum == E_NODATA )
    setError( E_OK );
  
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

size_t
Void::getBinSize( void ) const
{
  return( sizeof( CLUE_U32 ) + size() );
}

ostream &
Void::write( ostream & dest ) const
{
  CLUE_U32 len = size();
  dest.write( (const char *)&len, sizeof( len ) );
  dest.write( data, size() );
  return( dest );
}

istream &
Void::read( istream & src )
{
  CLUE_U32 len;
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

ostream &
Void::toStream( ostream & dest ) const
{
  char * d = (char *)data;

  char	oldFill  = dest.fill( '0' );
  int	oldFlags = dest.setf( ios::hex, ios::basefield );
  dest.setf( ios::uppercase );
  
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

  dest << prefix << "data:    " << "0x0000 ";

  char  oldFill = dest.fill( '0' );
  int	oldFlags = dest.setf( ios::hex, ios::basefield );
  dest.setf( ios::uppercase );

  char * d = (char *)data;
  
  for( size_t pos = 0 ; pos < dataSize; pos++ )
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

