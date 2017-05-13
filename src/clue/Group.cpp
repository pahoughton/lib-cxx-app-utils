// 1994-12-23 (cc) Paul Houghton <paul4hough@gmail.com>

#include "Group.hpp"

#include <pwd.h>

int
Group::group( gid_t grp )
{
  struct group * gr = getgrgid( grp );

  if( gr != 0 )
    {
      return( group( gr ) );
    }
  else
    {
      errorNum = errno;
      return( -1 );
    }
}

int
Group::group( const char * grp )
{
  struct group * gr = getgrnam( grp );

  if( gr != 0 )
    {
      return( group( gr ) );
    }
  else
    {
      errorNum = errno;
      return( -1 );
    }
}

int
Group::group( const struct group * gr )
{
  if( gr != 0 )
    {
      gid = gr->gr_gid;

      freeGrData();

      name = strdup( gr->gr_name );

      int len = 0;
      int g;

      for( g = 0; gr->gr_mem[g] != 0; g++ )
	{
	  len += strlen( gr->gr_mem[g] ) + 3;
	}

      members = new char[len];

      strcpy( members, gr->gr_mem[0] );

      for( g = 1; gr->gr_mem[g] != 0 ; g++ )
	{
	  strcat( members,", " );
	  strcat( members, gr->gr_mem[g] );
	}

      return( 0 );
    }
  else
    {
      return( -1 );
    }
}

const char *
Group::firstMember( void )
{
  if( eachMember ) free( eachMember );

  eachMember = strdup( eachMember );

  return( strtok( eachMember, ", " ) );
}

const char *
Group::nextMember( void )
{
  return( strtok( 0, ", ") );
}

Bool
Group::isIn( const char * grp, uid_t uid )
{
  struct group * gr = getgrnam( grp );

  if( gr != 0 )
    {
      return( isIn( gr->gr_gid, uid ) );
    }
  else
    {
      return( FALSE );
    }
}

Bool
Group::isIn( gid_t grp, uid_t uid )
{
  uid_t	    euid;

  if( uid == ULONG_MAX )
    {
      uid = getuid();
      euid = geteuid();
    }
  else
    {
      euid = uid;
    }

  struct passwd * pw = getpwuid( uid );
  char * uname = 0;
  char * euname = 0;

  if( pw != 0 )
    {
      if( pw->pw_gid == grp )
	{
	  return( TRUE );
	}
      else
	{
	  uname = strdup( pw->pw_name );
	}
    }

  if( euid != uid )
    {
      pw = getpwuid( euid );

      if( pw != 0 )
	{
	  if( pw->pw_gid == grp )
	    {
	      if( uname ) free( uname );
	      return( TRUE );
	    }
	  else
	    {
	      euname = strdup( pw->pw_name );
	    }
	}
    }

  if( uid == getuid() && getegid() == grp )
    {
      if( uname ) free( uname );
      if( euname ) free( euname );
      return( TRUE );
    }

  struct group * gr = getgrgid( grp );

  if( gr != 0 )
    {
      for( int g = 0; gr->gr_mem[g] != 0; g++ )
	{
	  if( uname && ( strcmp( uname, gr->gr_mem[g] ) == 0 ) )
	    {
	      if( uname ) free( uname );
	      if( euname ) free( euname );
	      return( TRUE );
	    }

	  if( euname && ( strcmp( uname, gr->gr_mem[g] ) == 0 ) )
	    {
	      if( uname ) free( uname );
	      if( euname ) free( euname );
	      return( TRUE );
	    }
	}
    }

  if( uname ) free( uname );
  if( euname ) free( euname );

  return( FALSE );
}

ostream &
operator<<( ostream & dest, const Group & gr )
{
  if( gr.good() )
    {
      dest << gr.getName() << ' '
	   << gr.getGID() << ' '
	   << gr.getMembers()
	;

      if( gr.getEGID() != gr.getGID() )
	{
	  dest << " Effective: "
	       << gr.getEName() << ' '
	       << gr.getEGID()
	    ;
	}
    }
  else
    {
      dest << gr.error();
    }

  return( dest );
}


void
Group::freeGrData( void )
{
  if( name ) { free( name ); name = 0; }
  if( members ) { free( members ); members = 0; }
  if( eachMember ) { free( eachMember ); eachMember = 0; }
}

void
Group::initialize( void )
{
  errorNum = 0;
  gid = 0;
  name = 0;
  members = 0;
  eachMember = 0;

  egid = getegid();

  struct group * gr = getgrgid( egid );

  if( gr != 0 )
    {
      ename = strdup( gr->gr_name );
    }
  else
    {
      errorNum = errno;
    }
}
