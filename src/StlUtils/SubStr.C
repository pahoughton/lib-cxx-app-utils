//
// File:        SubStr.C
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  Compiled source for SubStr
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     06/04/95 07:32 
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//

#if !defined( STLUTILS_SHORT_FN )
#include "SubStr.hh"
#include "StlUtilsExceptions.hh"
#include "Str.hh"
#include "Compare.hh"
#include "StringUtils.hh"
#include <algorithm>
#else
#include "SubStr.hh"
#include "StlUtilsExcp.hh"
#include "Str.hh"
#include "Compare.hh"
#include "StrUtil.hh"
#include <algorithm>
#endif

#if defined( STLUTILS_DEBUG )
#include <SubStr.ii>
#endif

STLUTILS_VERSION(
  SubStr,
  "%PID%" );


const SubStr::size_type SubStr::npos = NPOS;

Str SubStr::dummyStr("dummy");

// compare * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


int
SubStr::compare( const Str & two, size_type start, size_type compLen ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, compLen );
  size_t twoLen = min( two.size(), compLen );

  int diff = strncmp( strbase() + start, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
SubStr::compare( const SubStr & two, size_type start, size_type compLen ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = min( size() - start, compLen );
  size_type twoLen = min( two.size(), compLen );

  int diff = strncmp( strbase() + start, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  


int
SubStr::compare( const char * two, size_type start, size_type compLen ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = min( size() - start, compLen );
  size_type twoLen = min( (size_type)strlen( two ), compLen );

  int diff = strncmp( strbase() + start, two, min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
SubStr::fcompare( const Str & two, size_type start, size_type compLen ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = min( size() - start, compLen );
  size_type twoLen = min( two.size(), compLen );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
SubStr::fcompare( const SubStr & two, size_type start, size_type compLen ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = min( size() - start, compLen );
  size_type twoLen = min( two.size(), compLen );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

int
SubStr::fcompare( const char * two, size_type start, size_type compLen ) const
{
  size_type oneLen = min( size() - start, compLen );
  size_type twoLen = min( (size_type)strlen( two ), compLen );

  int diff = StringCaseCompare( strbase() + start, two,
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}


int
compare( const char * one, const SubStr & two, SubStr::size_type len )
{
  SubStr::size_type oneLen = min( (SubStr::size_type)strlen( one ), len );
  SubStr::size_type twoLen = min( two.size(), len );

  int diff = strncmp( one, two.strbase(), min( oneLen, twoLen ) );
  
  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
fcompare( const char * one, const SubStr & two, SubStr::size_type len )
{
  SubStr::size_type oneLen = min( (SubStr::size_type)strlen( one ), len );
  SubStr::size_type twoLen = min( two.size(), len );

  int diff = StringCaseCompare( one, two.strbase(), min( oneLen, twoLen ) );
  
  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

SubStr::size_type
SubStr::getBinSize( void ) const
{
  return( sizeof( size_type ) + len );
}

ostream &
SubStr::write( ostream & dest ) const
{
  size_type sLen = len;
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

ostream &
SubStr::toStream( ostream & dest ) const
{
#if defined( STLUTILS_HAS_IOSTREAM_SENTRY )
  ostream::sentry   opfx( dest );
  if( ! opfx )
    return( dest );
#else
  if( ! dest.opfx() )
    return( dest );
#endif
  
  if( dest.width()
      && (dest.flags() & (ios::right | ios::internal ))
      || ! (dest.flags() & ios::adjustfield) )
    {
      for( int fcnt = size(); fcnt < dest.width(); ++ fcnt )
	{
	  if( ! dest.put( dest.fill() ).good() )
	      return( dest );
	}
    }
  
  if( dest.write( strbase(), size() ).good() )
    {
      if( dest.width() && ( dest.flags() & ios::left) )
	{
	  for( int fcnt = size(); fcnt < dest.width(); ++ fcnt )
	    {
	      if( ! dest.put( dest.fill() ).good() )
		return( dest );
	    }
	}
    }
  dest.width(0);
#if ! defined( STLUTILS_HAS_IOSTREAM_SENTRY )
  dest.osfx();
#endif
  
  return( dest );
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


// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.3  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.2  2000/05/25 17:05:46  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.2  1997/09/19 11:22:26  houghton
// Changed to use size_type.
//
// Revision 4.1  1997/09/17 15:13:05  houghton
// Changed to Version 4
//
// Revision 3.6  1997/09/17 11:08:55  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.5  1997/08/28 16:35:01  houghton
// Bug-Fix: added toStream (was inline) and added support
//     for setw(n) (the width was being ignored).
//
// Revision 3.4  1997/08/17 22:35:33  houghton
// Added size_type.
//
// Revision 3.3  1997/07/18 19:30:08  houghton
// Port(Sun5): changed local variable names to eliminate compiler warnings.
//
// Revision 3.2  1996/11/20 12:13:02  houghton
// Removed support for BinStream.
//
// Revision 3.1  1996/11/14 01:24:23  houghton
// Changed to Release 3
//
// Revision 2.2  1995/12/04 11:18:29  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:41:16  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:49  houghton
// Revised
//
//
