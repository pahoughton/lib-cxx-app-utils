//
// File:        Void.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for Void.
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     11/11/95 06:21
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "Void.hh"
#include <Str.hh>
#include <Compare.hh>
#include <iomanip>
#include <cctype>

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
  if( data ) delete data;
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

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.2  2011/12/30 23:57:23  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:44  houghton
// Changed to version 6
//
// Revision 5.4  2003/08/09 11:21:00  houghton
// Changed ver strings.
//
// Revision 5.3  2003/06/07 16:48:45  houghton
// Cleanup dump output.
//
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.2  1997/09/19 11:22:33  houghton
// Changed to use size_type.
//
// Revision 4.1  1997/09/17 15:13:09  houghton
// Changed to Version 4
//
// Revision 3.8  1997/09/17 11:08:58  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.7  1997/04/01 13:39:55  houghton
// Bug-Fix: correctly handle empty data.
//
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
