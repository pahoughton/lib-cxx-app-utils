//
// File:        Log.C
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     03/14/94 12:22 
//
// Revision History:
//
// $Log$
// Revision 2.4  1995/12/04 11:17:23  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.3  1995/11/12  18:49:31  houghton
// Bug fix - current (not lvl).
//
// Revision 2.2  1995/11/12  18:00:02  houghton
// Added srcFile, srcLine args to level().
//
// Revision 2.1  1995/11/10  12:40:42  houghton
// Change to Version 2
//
// Revision 1.6  1995/11/05  15:28:36  houghton
// Revised
//
//

#include "Log.hh"
#include "DateTime.hh"

#if defined( CLUE_DEBUG )
#include <Log.ii>
#endif

CLUE_VERSION(
  Log,
  "$Id$" );

Log &
Log::level( LogLevel::Level current, const char * srcFile, long srcLine )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate(failbit|eofbit);
      return( *this );
    }
  
  rdbuf()->level().setCurrent( current );

  if( timeStamp )
    {
      DateTime  now( time(0), true );

      *this << now << ' ';
    }

  if( levelStamp )
    {
      *this << rdbuf()->level().getName( current ) << ' ';
    }

  if( srcFile )
    {
      *this << srcFile << ':' << srcLine << ' ';
    }
  
  return( *this );
}

Log &
Log::level( const char * lvl )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate( failbit | eofbit );
      return( *this );
    }
  
  rdbuf()->level().setCurrent( lvl );

  if( timeStamp )
    {
      DateTime  now( time(0), true );

      *this << now << ' ';
    }

  if( levelStamp )
    {
      *this << lvl  << ' ';
    }
  
  return( *this );
}

bool
Log::good( void ) const
{
  return( rdbuf() != 0 && ostream::good() );
}

const char *
Log::error( void ) const
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
      size_t eSize = errStr.size();

      if( rdbuf() == 0 )
	errStr << ": no 'streambuf'";
      
      if( ! ios::good() )
	{
	  if( ios::rdstate() & ios::eofbit )
	    errStr << ": EOF bit set";
	  if( ios::rdstate() & ios::failbit )
	    errStr << ": FAIL bit set";
	  if( ios::rdstate() & ios::badbit )
	    errStr << ": BAD bit set";
	}
      
      if( eSize == errStr.size() )
	errStr << ": unknown error";
      
    }

  return( errStr.cstr() );
}
  
const char *
Log::getClassName( void ) const
{
  return( "Log" );
}

const char *
Log::getVersion( bool withPrjVer ) const
{
  if( rdbuf() )
    return( version.getVer( withPrjVer, rdbuf()->getVersion( false ) ) );
  else
    return( version.getVer( withPrjVer ) );
}

ostream &
Log::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Log::getClassName() << ":\n"
	 << Log::getVersion() << '\n';
  
  if( ! Log::good() )
    dest << prefix << "Error: " << Log::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "timeStamp:    " << (timeStamp == true ? "on" : "off" ) << '\n';
  dest << prefix << "levelStamp:   " << (levelStamp == true ? "on" : "off" ) << '\n';

  if( rdbuf() )
    {
      Str pre;
      pre = prefix;
      pre << "rdbuf: " << rdbuf()->getClassName() << "::";

      rdbuf()->dumpInfo( dest, pre, false );
    }
  
  dest << '\n';
  
  return( dest  );
}
