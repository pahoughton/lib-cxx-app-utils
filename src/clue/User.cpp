//
// File:        User.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled source for User.
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     05/18/95 06:37 
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
// $Id$ 

#include "User.hh"
#include "Compare.hh"
#include "LibLog.hh"
#include "Str.hh"

#if defined( STLUTILS_DEBUG )
#include "User.ii"
#endif

STLUTILS_VERSION(
  User,
  "$Id$ " );


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

  bool	foundPrime( false );
  
  for( struct group * gr = getgrent();
      gr;
      gr = getgrent() )
    {
      for( int m = 0; gr->gr_mem[m]; m++ )
	{
	  if( ! ::compare( name, gr->gr_mem[m], Str::npos )  )
	    {
	      UserGroup g( gr, false );
	      _LLgLock;
	      _LLg( LogLevel::Debug )
		<< "Inserting group: " << g
		<< " size: " << groups.size()
		<< std::endl;
	      
	      _LLgUnLock;

	      if( g.getGID() == primeGroup.getGID() )
		{
		  foundPrime = true;
		}
	      groups.insert( g );
	    }
	}
    }

  if( ! foundPrime )
    groups.insert( primeGroup );
    
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

std::ostream &
User::write( std::ostream & dest ) const
{
  dest.write( (const char *)&uid, sizeof( uid ) );
  return( dest );
}

std::istream &
User::read( std::istream & src )
{
  uid_t	user;
  src.read( (char *)&user, sizeof( user ) );
  set( user );
  return( src );
}


std::ostream &
User::toStream( std::ostream & dest ) const
{
  dest << name;
  return( dest );
}

std::istream &
User::fromStream( std::istream & src )
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


std::ostream &
User::dumpInfo( 
  std::ostream &	dest,
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
    Str pre;
    pre << prefix << "primeGroup:"
	<< primeGroup.getClassName() << "::" << std::ends;
    
    primeGroup.dumpInfo( dest, pre.c_str(), false );
    
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
	  
      for( Groups::const_iterator them = groups.begin();
	   them != groups.end();
	   them++ )
	{
	  dest << prefix << *them << std::endl;
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
  
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.3  2012/04/26 20:08:45  paul
// *** empty log message ***
//
// Revision 6.2  2011/12/30 23:57:34  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:47  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:23  houghton
// Changed Version Num to 5
//
// Revision 4.4  1998/10/13 16:34:09  houghton
// Change to ensure 'primary' group is included in the user's groups.
//
// Revision 4.3  1998/07/20 11:30:20  houghton
// Port(Hpux): had to specify default function arg.
//
// Revision 4.2  1997/12/19 12:51:51  houghton
// Bug-Fix: groups is const, so i need to use a const iterator.
//
// Revision 4.1  1997/09/17 15:13:39  houghton
// Changed to Version 4
//
// Revision 3.5  1997/09/17 11:09:27  houghton
// Changed: renamed library to StlUtils.
//
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
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:46:56  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:49:17  houghton
// Revised
//
//
