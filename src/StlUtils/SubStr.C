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
// Revision 1.1  1995/11/05 13:23:41  houghton
// Initaial implementation
//
//

#include "SubStr.hh"
#include "ClueExceptions.hh"

#include "Str.hh"
#include "Compare.hh"
#include "StringUtils.hh"

#include <algorithm>

#ifdef   CLUE_DEBUG
#define  inline
#include <SubStr.ii>
#endif

const char SubStr::version[] =
LIB_CLUE_VERSION
"$Id$";

const size_t SubStr::npos = NPOS;

Str SubStr::dummyStr("dummy");

// compare * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


int
SubStr::compare( const Str & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = strncmp( strbase() + start, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
SubStr::compare( const SubStr & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = strncmp( strbase() + start, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  


int
SubStr::compare( const char * two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( strlen( two ), len );

  int diff = strncmp( strbase() + start, two, min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
SubStr::fcompare( const Str & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
SubStr::fcompare( const SubStr & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
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
SubStr::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  constStr.dumpInfo( dest );
  
  dest << "    Pos:        " << pos << "'\n";
  dest << "    Len:        " << len << "\n";
  dest << "    SubString:  '" << *this << "'\n";
  
  dest << '\n';

  return( dest  );
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


