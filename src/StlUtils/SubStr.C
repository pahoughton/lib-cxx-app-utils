//
// File:        SubStr.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     06/04/95 07:32 
//
// Revision History:
//
// $Log$
// Revision 3.1  1996/11/14 01:24:23  houghton
// Changed to Release 3
//
// Revision 2.2  1995/12/04 11:18:29  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:41:16  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:49  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include "SubStr.hh"
#include "ClueExceptions.hh"
#include "Str.hh"
#include "Compare.hh"
#include "StringUtils.hh"
#include <algorithm>
#else
#include "SubStr.hh"
#include "ClueExcp.hh"
#include "Str.hh"
#include "Compare.hh"
#include "StrUtil.hh"
#include <algorithm>
#endif

#if defined( CLUE_DEBUG )
#include <SubStr.ii>
#endif

CLUE_VERSION(
  SubStr,
  "$Id$" );


const size_t SubStr::npos = NPOS;

Str SubStr::dummyStr("dummy");

// compare * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


int
SubStr::compare( const Str & two, size_t start, size_t len ) const
{
  CLUE_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = strncmp( strbase() + start, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
SubStr::compare( const SubStr & two, size_t start, size_t len ) const
{
  CLUE_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = strncmp( strbase() + start, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  


int
SubStr::compare( const char * two, size_t start, size_t len ) const
{
  CLUE_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( strlen( two ), len );

  int diff = strncmp( strbase() + start, two, min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
SubStr::fcompare( const Str & two, size_t start, size_t len ) const
{
  CLUE_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
SubStr::fcompare( const SubStr & two, size_t start, size_t len ) const
{
  CLUE_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

int
SubStr::fcompare( const char * two, size_t start, size_t len ) const
{
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( strlen( two ), len );

  int diff = StringCaseCompare( strbase() + start, two,
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}


int
compare( const char * one, const SubStr & two, size_t len )
{
  size_t oneLen = min( strlen( one ), len );
  size_t twoLen = min( two.size(), len );

  int diff = strncmp( one, two.strbase(), min( oneLen, twoLen ) );
  
  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
fcompare( const char * one, const SubStr & two, size_t len )
{
  size_t oneLen = min( strlen( one ), len );
  size_t twoLen = min( two.size(), len );

  int diff = StringCaseCompare( one, two.strbase(), min( oneLen, twoLen ) );
  
  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

size_t
SubStr::getBinSize( void ) const
{
  return( sizeof( ULong ) + len );
}

BinStream &
SubStr::write( BinStream & dest ) const
{
  ULong sLen = len;
  dest.write( sLen );
  dest.write( strbase(), len );
  return( dest );
}

BinStream &
SubStr::read( BinStream & src )
{
  Str tmp;
  tmp.read( src );

  if( ! tmp.good() || ! src.good() )
    return( src );

  str.replace( pos, len, tmp );
  len = tmp.size();
    
  return( src );
}

ostream &
SubStr::write( ostream & dest ) const
{
  ULong sLen = len;
  dest.write( (const char *)&sLen, sizeof( sLen ) );
  dest.write( strbase(), len );
  return( dest );
}

istream &
SubStr::read( istream & src )
{
  Str tmp;
  tmp.read( src );
  if( src.good() )
    str.replace( pos, len, tmp );
  len = tmp.size();
  return( src );
}

const char *
SubStr::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName();

  if( good() )
    {
       errStr << ": Ok";
    }
  else
    {
      errStr << ": " << constStr.error();
    }

  return( errStr.cstr() );
}

const char *
SubStr::getClassName( void ) const
{
  return( "SubStr" );
}

ostream &
SubStr::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << SubStr::getClassName() << ":\n"
	 << SubStr::getVersion() << '\n';

  if( ! SubStr::good() )
    dest << prefix << "Error: " << SubStr::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  Str pre;
  pre << prefix << "str: " << constStr.getClassName() << "::";
  
  constStr.dumpInfo( dest, pre, false );
  
  dest << prefix << "pos:        " << pos << "'\n";
  dest << prefix << "len:        " << len << "\n";
  dest << prefix << "SubString:  '" << *this << "'\n";
  
  dest << '\n';

  return( dest  );
}  

const char *
SubStr::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer, constStr.getVersion( false ) ) );
}




#ifdef STD_STRING
int
SubStr::fcompare( const string & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.length(), len );

  int diff = StringCaseCompare( strbase() + start, two.c_str(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

int
compare( const string & one, const SubStr & two, size_t len )
{
  size_t oneLen = min( one.length(), len );
  size_t twoLen = min( two.size(), len );

  int diff = strncmp( one.c_str(), two.strbase(), min( oneLen, twoLen ) );
  
  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
fcompare( const string & one, const SubStr & two, size_t len )
{
  size_t oneLen = min( one.length(), len );
  size_t twoLen = min( two.size(), len );

  int diff = StringCaseCompare( one.c_str(), two.strbase(), min( oneLen, twoLen ) );
  
  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
SubStr::compare( const string & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.length(), len );

  int diff = strncmp( strbase() + start, two.c_str(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}
#endif


