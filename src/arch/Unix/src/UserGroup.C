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

UserGroup   UserGroup::eff( getegid() );

const gid_t    UserGroup::bad = (gid_t) ULONG_MAX;

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
      name.clear();
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

BinStream &
UserGroup::write( BinStream & dest ) const
{
  dest.write( gid );
  return( dest );
}

BinStream &
UserGroup::read( BinStream & src )
{
  gid_t	grp;
  src.read( grp );
  if( src.good() )
    set( grp );
  return( src );
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

inline
ostream &
UserGroup::toStream( ostream & dest ) const
{
  dest << name;
  return( dest );
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

// getClassName - return the name of this class
const char *
UserGroup::getClassName( void ) const
{
  return( "UserGroup" );
}

const char *
UserGroup::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer, name.getVersion( false ) ) );
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

  if( eff.gid == gid )
    {
      dest << prefix << "Effective:  Same\n";
    }
  else
    {
      dest << prefix << "effective gid:    " << eff.gid << '\n'
	   << prefix << "effective name:   " << eff.name << '\n'
	;
    }

  dest << '\n';

  return( dest );
  
}
  
