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
// Revision 3.3  1997/03/03 14:38:22  houghton
// Removed support for RW Tools++.
//
// Revision 3.2  1996/11/19 12:30:04  houghton
// Changed include from strstream to strstream.h because strstream
//     is not part of the standard.
//
// Revision 3.1  1996/11/14 01:25:11  houghton
// Changed to Release 3
//
// Revision 2.5  1996/11/06 18:12:27  houghton
// Removed BinStream support.
// Changed use of Str to RWCString.
//     (as required per Mike Alexander)
//
// Revision 2.4  1996/05/01 11:01:41  houghton
// Bug-Fix: static const UserGroup eff was causing segv.
//   change so the effective() method just returns a new 'UserGroup'
//
// Revision 2.3  1995/12/31 11:24:28  houghton
// Bug Fix - Removed 'inline' statement.
//
// Revision 2.2  1995/12/04 11:20:22  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:46:58  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:49:18  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include "UserGroup.hh"
#include "User.hh"
#include "Compare.hh"
#include <strstream.h>
#include <climits>
#include <cerrno>
#include <pwd.h>
#else
#include "UserGrp.hh"
#include "User.hh"
#include "Compare.hh"
#include <climits>
#include <cerrno>
#include <pwd.h>
#endif

#if defined( CLUE_DEBUG )
#if !defined( CLUE_SHORT_FN )
#include <UserGroup.ii>
#else
#include <UserGrp.ii>
#endif
#endif

CLUE_VERSION(
  UserGroup,
  "$Id$" );
  

#if defined( AIX )
extern "C" { void endpwent( void ); };
#endif

// UserGroup   UserGroup::eff( getegid() );

const gid_t    UserGroup::bad = (gid_t) ULONG_MAX;

const UserGroup &
UserGroup::effective( void )
{
  static UserGroup * effGroup = 0;
  if( ! effGroup )
    effGroup = new UserGroup( getegid() );

  return( *effGroup );
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
UserGroup::isMember( const User & user )
{
  if( members.size() == 0 )
    findMembers();

  return( members.find( user.getName() ) != members.end() );
}

bool
UserGroup::isMember( const User & user ) const
{
  if( members.size() == 0 )
    return( false );

  return( members.find( user.getName() ) != members.end() );
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
      name = "";
      gid = bad;
      osError = errno;      
      return( false );
    }
}

size_t
UserGroup::getBinSize( void ) const
{
  return( sizeof( gid ) );
}

ostream &
UserGroup::write( ostream & dest ) const
{
  dest.write( (const char *)&gid, sizeof( gid ) );
  return( dest );
}

istream &
UserGroup::read( istream & src )
{
  gid_t	grp;
  src.read( (char *)&grp, sizeof( grp ) );
  if( src.good() )
    set( grp );
  return( src );
}

ostream &
UserGroup::toStream( ostream & dest ) const
{
  dest << name;
  return( dest );
}

istream &
UserGroup::fromStream( istream & src )
{
  Str inName;

  src >> inName;
  set( inName );
  return( src );
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
  static strstream errStr;
  errStr.freeze(0);
  errStr.seekp(0);
  errStr.seekg(0);

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

  errStr << ends;
  return( errStr.str() );
}

// getClassName - return the name of this class
const char *
UserGroup::getClassName( void ) const
{
  return( "UserGroup" );
}

const char *
UserGroup::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}
  

ostream &
UserGroup::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << UserGroup::getClassName() << ":\n"
	 << UserGroup::getVersion() << '\n';
  
  
  if( ! UserGroup::good() )
    dest << prefix << "Error: " << UserGroup::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "gid:	  " << gid << '\n'
       << prefix << "name:        " << name << '\n'
    ;

  if( members.size() == 0 )
    {
      dest << prefix << "No members:\n";
    }
  else
    {
      dest << prefix << "Members:\n";
	  
      for( Members::iterator them = members.begin();
	   them != members.end();
	   them++ )
	{
	  dest << prefix << *them << endl;
	}
    }

  if( effective().gid == gid )
    {
      dest << prefix << "Effective:  Same\n";
    }
  else
    {
      dest << prefix << "effective gid:    " << effective().gid << '\n'
	   << prefix << "effective name:   " << effective().name << '\n'
	;
    }

  dest << '\n';

  return( dest );
  
}
  
