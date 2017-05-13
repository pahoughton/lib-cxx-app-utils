// 1995-05-09 (cc) Paul Houghton <paul4hough@gmail.com>

#include "UserGroup.hpp"
#include "User.hpp"

namespace clue {

const gid_t    UserGroup::bad = (gid_t) ULONG_MAX;

UserGroup::~UserGroup( void )
{
}

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

  return( members.end() != members.find( user.getName() ) );
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

std::ostream &
UserGroup::write( std::ostream & dest ) const
{
  dest.write( (const char *)&gid, sizeof( gid ) );
  return( dest );
}

std::istream &
UserGroup::read( std::istream & src )
{
  gid_t	grp;
  src.read( (char *)&grp, sizeof( grp ) );
  if( src.good() )
    set( grp );
  return( src );
}

std::ostream &
UserGroup::toStream( std::ostream & dest ) const
{
  dest << name;
  return( dest );
}

std::istream &
UserGroup::fromStream( std::istream & src )
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
  static Str errStr;

  errStr = "UserGroup";

  if( good() )
    {
       errStr << ": ok";
    }
  else
    {
      if( osError )
	{
	  errStr << ": " << strerror( osError );
	}
      else
	{
	  errStr << ": unknown error";
	}
    }

  return( errStr.cstr() );
}

std::ostream &
UserGroup::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{
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

      for( Members::const_iterator them = members.begin();
	   them != members.end();
	   them++ )
	{
	  dest << prefix << *them << std::endl;
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

}; // namespace clue
