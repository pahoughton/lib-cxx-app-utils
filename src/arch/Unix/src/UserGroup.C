//
// File:        UserGroup.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/09/95 06:30 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 12:56:02  houghton
// Initial implementation of Unix Group info Class
//
//

#include "UserGroup.hh"
#include "User.hh"
#include "Compare.hh"

#include <climits>
#include <cerrno>

#include <pwd.h>


#if defined( AIX )
extern "C" { void endpwent( void ); };
#endif

UserGroup   UserGroup::eff( getegid() );

const gid_t    UserGroup::bad = (gid_t) ULONG_MAX;

#ifdef   CLUE_DEBUG
#define  inline
#include <UserGroup.ii>
#endif

const char UserGroup::version[] =
LIB_CLUE_VERSION
"$Id$";


const UserGroup &
UserGroup::effective( void )
{
  return( eff );
}

size_t
UserGroup::findMembers( void )
{
  if( members.size() != 0 )
    return( members.size() );

  if( gid == bad )
    return( 0 );
  
  struct group * gr = getgrgid( gid );
  
  for( int m = 0; gr->gr_mem[m]; m++ )
    {
      members.insert( gr->gr_mem[m] );
    }

  for( struct passwd * pw = getpwent();
      pw;
      pw = getpwent() )
    {
      if( pw->pw_gid == gid )
	{
	  members.insert( pw->pw_name );
	}
    }

  endpwent();

  return( members.size() );
  
}

bool
UserGroup::set( const struct group * gr, bool findMemb )
{
  members.erase( members.begin(), members.end() );
  
  if( gr )
    {
      gid = gr->gr_gid;
      name = gr->gr_name;

      if( findMemb )
	findMembers();
      
      return( true );
    }
  else
    {
      name.clear();
      gid = bad;
      osError = errno;      
      return( false );
    }
}

// getClassName - return the name of this class
const char *
UserGroup::getClassName( void ) const
{
  return( "UserGroup" );
}

// good - return TRUE if no detected errors
bool
UserGroup::good( void ) const
{
  return( gid != bad );
}

// error - return a string describing the current state
const char *
UserGroup::error( void ) const
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
      if( osError )
	{
	  errStr << strerror( osError );
	}
      else
	{
	  errStr << ": unknown error";
	}
    }

  return( errStr.cstr() );
}



ostream &
UserGroup::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << "    gid:	    " << gid << '\n'
       << "    name:        " << name << '\n'
    ;

  if( members.size() == 0 )
    {
      dest << "    No members:\n";
    }
  else
    {
      dest << "    Members:\n";
	  
      for( Members::iterator them = members.begin();
	   them != members.end();
	   them++ )
	{
	  dest << "      " << *them << endl;
	}
    }

  if( eff.gid == gid )
    {
      dest << "    Effective:  Same\n";
    }
  else
    {
      dest << "    effective gid:    " << eff.gid << '\n'
	   << "    effective name:   " << eff.name << '\n'
	;
    }

  dest << '\n';

  return( dest );
  
}
  
