//
// File:        User.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/18/95 06:37 
//
// Revision History:
//
// $Log$
// Revision 3.4  1997/03/03 19:12:14  houghton
// Changed from useing strstream to Str.
//
// Revision 3.3  1997/03/03 14:38:21  houghton
// Removed support for RW Tools++.
//
// Revision 3.2  1996/11/19 12:29:58  houghton
// Changed include from strstream to strstream.h because strstream
//     is not part of the standard.
//
// Revision 3.1  1996/11/14 01:25:09  houghton
// Changed to Release 3
//
// Revision 2.5  1996/11/06 18:10:41  houghton
// Changed how effective user is handled.
// Changed use of Str to RWCString.
//     (as required per Mike Alexander)
//
// Revision 2.4  1996/06/20 15:25:25  houghton
// Added Debugging loging
//
// Revision 2.3  1996/05/01 11:01:21  houghton
// Bug-Fix: static const User eff was causing segv.
//   change so the effective() method just returns a new 'User'
//
// Revision 2.2  1995/12/04 11:20:20  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:46:56  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:49:17  houghton
// Revised
//
//

#include "User.hh"
#include "Compare.hh"
#include "LibLog.hh"
#include <strstream.h>

#if defined( CLUE_DEBUG )
#include "User.ii"
#endif

CLUE_VERSION(
  User,
  "$Id$" );


const uid_t User::bad = (uid_t) ULONG_MAX;
// const User  User::eff( geteuid(), false );

User::~User( void )
{
}

const User &
User::effective( void )
{
  static User * effUser = 0;

  if( ! effUser )
    effUser = new User( geteuid(), false );
  return( *effUser );
}


size_t
User::findGroups( void )
{
  setgrent();
  
  for( struct group * gr = getgrent();
      gr;
      gr = getgrent() )
    {
      for( int m = 0; gr->gr_mem[m]; m++ )
	{
	  if( ! ::compare( name, gr->gr_mem[m] )  )
	    {
	      UserGroup g( gr, false );
	      _LLgLock;
	      _LLg( LogLevel::Debug )
		<< "Inserting group: " << g
		<< " size: " << groups.size()
		<< endl;
	      
	      _LLgUnLock;
	      
	      groups.insert( g );
	    }
	}
    }
  
  endgrent();

  return( groups.size() );
}

bool
User::set( const struct passwd * pw, bool findGrps )
{
  if( ! pw )
    return( false );
  
  uid	    = pw->pw_uid;
  name 	    = pw->pw_name;
  passwd    = pw->pw_passwd;
  gecos	    = pw->pw_gecos;
  home	    = pw->pw_dir;
  shell	    = pw->pw_shell;

  primeGroup.set( pw->pw_gid );

  if( findGrps )
    findGroups();

  return( true );
}

size_t
User::getBinSize( void ) const
{
  return( sizeof( uid_t ) );
}

ostream &
User::write( ostream & dest ) const
{
  dest.write( (const char *)&uid, sizeof( uid ) );
  return( dest );
}

istream &
User::read( istream & src )
{
  uid_t	user;
  src.read( (char *)&user, sizeof( user ) );
  set( user );
  return( src );
}


ostream &
User::toStream( ostream & dest ) const
{
  dest << name;
  return( dest );
}

istream &
User::fromStream( istream & src )
{
  Str inName;
  src >> inName;
  set( inName );
  return( src );
}

// good - return TRUE if no detected errors
bool
User::good( void ) const
{
  return( uid != bad );
}

// error - return a string describing the current state
const char *
User::error( void ) const
{
  static Str errStr;
  
  errStr = User::getClassName();

  if( good() )
    {
       errStr << ": Ok";
    }
  else
    {
      errStr << ": uid not set";
    }

  return( errStr.cstr() );
}

// getClassName - return the name of this class
const char *
User::getClassName( void ) const
{
  return( "User" );
}

const char *
User::getVersion( bool withPrjVer ) const
{
  static Str ver;
  
  ver = version.getVer( withPrjVer );

  ver << '\n';
  
  if( withPrjVer )
    ver << "    " << primeGroup.getVersion( false ) << '\n';

  return( ver.cstr() );
}


ostream &
User::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << User::getClassName() << ":\n"
	 << User::getVersion() << '\n';
  
  
  if( ! User::good() )
    dest << prefix << "Error: " << User::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  {
    strstream pre;
    pre << prefix << "primeGroup:"
	<< primeGroup.getClassName() << "::" << ends;
    
    primeGroup.dumpInfo( dest, pre.str(), false );
    
    dest << prefix << "uid:	  " << uid << '\n'
	 << prefix << "name:        " << name << '\n'
	 << prefix << "passwd:      " << passwd << '\n'
	 << prefix << "gecos:       " << gecos << '\n'
	 << prefix << "home:        " << home << '\n'
	 << prefix << "shell:       " << shell << '\n'
      ;
    
  }

  if( groups.size() == 0 )
    {
      dest << prefix << "No groups:\n";
    }
  else
    {
      dest << prefix << "Groups:\n";
	  
      for( Groups::iterator them = groups.begin();
	   them != groups.end();
	   them++ )
	{
	  dest << prefix << *them << endl;
	}
    }

  if( effective().uid == uid )
    {
      dest << prefix << "Effective:  Same\n";
    }
  else
    {
      dest << prefix << "effective uid:    " << effective().uid << '\n'
	   << prefix << "effective name:   " << effective().name << '\n'
	   << prefix << "effective passwd: " << effective().passwd << '\n'
	   << prefix << "effective gecos:  " << effective().gecos << '\n'
	   << prefix << "effective home:   " << effective().home << '\n'
	   << prefix << "effective shell:  " << effective().shell << '\n'
	;
    }

  dest << '\n';

  return( dest );
  
}
  
