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
// Revision 1.5  1995/11/05 14:44:35  houghton
// Ports and Version ID changes
//
//

#include "Log.hh"

#include "DateTime.hh"

#ifdef   CLUE_DEBUG
#define  inline
#include <Log.ii>
#endif


const char Log::version[] =
LIB_CLUE_VERSION
"$Id$";

Log &
Log::level( LogLevel::Level lvl )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate(failbit|eofbit);
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
      *this << rdbuf()->level().getName( lvl ) << ' ';
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

const char *
Log::getClassName( void ) const
{
  return( "Log" );
}

ostream &
Log::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  dest << "    Good:       " << (good() == true ? "yes" : "no" ) << '\n';
  dest << "    TimeStamp:  " << (timeStamp == true ? "on" : "off" ) << '\n';
  dest << "    LevelStamp: " << (levelStamp == true ? "on" : "off" ) << '\n';
  
  dest << "    " << getClassName() << "::" ;
  rdbuf()->dumpInfo( dest );

  dest << '\n';
  
  return( dest  );
}
