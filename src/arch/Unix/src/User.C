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
// Revision 1.1  1995/11/05 12:41:09  houghton
// Initial User Class Implementation
//
//

#include "User.hh"

#include <Compare.hh>
#include <iostream>

const char User::version[] =
LIB_CLUE_VERSION
"$Id$";

const uid_t User::bad = (uid_t) ULONG_MAX;

const User	User::eff( geteuid(), false );

#ifdef   CLUE_DEBUG
#define  inline
#include <User.ii>
#endif


const User &
User::effective( void )
{
  return( eff );
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

  
// getClassName - return the name of this class
const char *
User::getClassName( void ) const
{
  return( "User" );
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
  errStr.reset();

  errStr << getClassName();

  if( good() )
    {
       errStr << ": Ok";
    }
  else
    {
      errStr << ": unknown error";
    }

  return( errStr.cstr() );
}


ostream &
User::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << "    uid:	    " << uid << '\n'
       << "    name:        " << name << '\n'
       << "    passwd:      " << passwd << '\n'
       << "    gecos:       " << gecos << '\n'
       << "    home:        " << home << '\n'
       << "    shell:       " << shell << '\n'
    ;

  dest << primeGroup;

  if( groups.size() == 0 )
    {
      dest << "    No groups:\n";
    }
  else
    {
      dest << "    Groups:\n";
	  
      for( Groups::iterator them = groups.begin();
	   them != groups.end();
	   them++ )
	{
	  dest << "      " << *them << endl;
	}
    }

  if( eff.uid == uid )
    {
      dest << "    Effective:  Same\n";
    }
  else
    {
      dest << "    effective uid:    " << eff.uid << '\n'
	   << "    effective name:   " << eff.name << '\n'
	   << "    effective passwd: " << eff.passwd << '\n'
	   << "    effective gecos:  " << eff.gecos << '\n'
	   << "    effective home:   " << eff.home << '\n'
	   << "    effective shell:  " << eff.shell << '\n'
	;
    }

  dest << '\n';

  return( dest );
  
}
  
