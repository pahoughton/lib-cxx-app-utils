//
// File:        Log.C
// Project:	Clue
// Desc:        
//              
//  Compiled source for Log class.
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     03/14/94 12:22 
//
// Revision History: (See end of file for Revision Log)
//

#include "Log.hh"
#include <rw/rwtime.h>
#include <rw/cstring.h>

#if defined( CLUE_DEBUG )
#include "Log.ii"
#endif

CLUE_VERSION(
  Log,
  "$Id$" );


Log * _LibLog = 0;

Log &
Log::level( LogLevel::Level current, const char * srcFile, long srcLine )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate(failbit|eofbit);
      return( *this );
    }
  
  rdbuf()->setCurrentLevel( current );

  if( timeStamp )
    {
      RWTime  now;

      *this << now << ' ';
    }

  if( levelStamp )
    {
      *this << rdbuf()->getLogLevel() << ' ';
    }

  if( locStamp && srcFile )
    {
      *this << srcFile << ':' << srcLine << ' ';
    }
  
  return( *this );
}

Log &
Log::level( const char * lvl, const char * srcFile, long srcLine )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate( failbit | eofbit );
      return( *this );
    }
  
  rdbuf()->setCurrentLevel( lvl );

  if( timeStamp )
    {
      RWTime  now;

      *this << now << ' ';
    }

  if( levelStamp )
    {
      *this << rdbuf()->getLogLevel() << ' ';
    }
  
  if( locStamp && srcFile )
    {
      *this << srcFile << ':' << srcLine << ' ';
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
  static RWCString errStr;

  errStr = getClassName();

  if( good() )
    {
       errStr += ": Ok";
    }
  else
    {
      size_t eSize = errStr.length();

      if( rdbuf() == 0 )
	errStr += ": no 'streambuf'";

      if( ! ios::good() )
	{
	  if( ios::rdstate() & ios::eofbit )
	    errStr += ": EOF bit set";
	  if( ios::rdstate() & ios::failbit )
	    errStr += ": FAIL bit set";
	  if( ios::rdstate() & ios::badbit )
	    errStr += ": BAD bit set";
	}
      
      if( eSize == errStr.length() )
	errStr += ": unknown error";      
    }

  return( errStr );
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

#define bool2str( _b_ ) ((_b_) == true ? "on" : "off" )

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

  dest << prefix << "timeStamp:    " << bool2str( timeStamp ) << '\n'
       << prefix << "levelStamp:   " << bool2str( levelStamp ) << '\n'
       << prefix << "locStamp:     " << bool2str( locStamp ) << '\n'
    ;
  
  if( rdbuf() )
    {
      RWCString pre;
      pre = prefix;
      pre += "rdbuf: " ;
      pre += rdbuf()->getClassName() ;
      pre += "::";
      
      rdbuf()->dumpInfo( dest, pre, false );
    }
  
  dest << '\n';
  
  return( dest  );
}

//
// Revision Log:
//
// $Log$
// Revision 3.1  1996/11/14 01:23:45  houghton
// Changed to Release 3
//
// Revision 2.9  1996/11/13 16:25:41  houghton
// Changed include lines to use "file" instead of <file> to
//     accomidate rpm.
// Changed to use ios::setstate (instead of clear) to be compilant
//     with the ios class beheavior defined by the standard.
// Bug-Fix: Fixed some compile errors that were do to the change
//     to RWCString.
//
// Revision 2.8  1996/11/11 13:33:47  houghton
// Changed to use RWCString instead of strstream where possible because
//     of an inconsitancy in the public member of strstream.
//
// Revision 2.7  1996/11/04 13:39:33  houghton
// Restructure header comments layout.
// Changed to use rwtime instead of DateTime for time stamp output.
//     (as required by Mike Alexandar).
// Changed to work with modifications to LogBuf class.
// Changed error to use a strstream instead of an Str
//     (as required by Mike Alexandar).
//
// Revision 2.6  1996/10/22 22:05:33  houghton
// Change: Added locStamp to turn on/off output of src file & line.
//
// Revision 2.5  1996/04/27 13:02:32  houghton
// Added global _LibLog variable.
//
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
