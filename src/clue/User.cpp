// 1995-05-18 (cc) Paul Houghton <paul4hough@gmail.com>

#include "User.hpp"
#include "LibLog.hpp"
#include "Str.hpp"

namespace clue {

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
	  if( ! clue::compare( name, gr->gr_mem[m], Str::npos )  )
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

  errStr = "User";

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

std::ostream &
User::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! User::good() )
    dest << prefix << "Error: " << User::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  {
    Str pre;
    pre << prefix << "primeGroup:" << std::ends;

    primeGroup.dumpInfo( dest, pre.c_str() );

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

};
