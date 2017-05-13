// 1994-12-23 (cc) Paul Houghton <paul4hough@gmail.com>

#include "Password.hpp"

namespace clue {

Password &
Password::set( uid_t user )
{
  struct passwd * pw = getpwuid( user );

  if( pw != 0 )
    {
      set( pw ) ;
    }
  else
    {
      m_err = errno;
    }
  return( *this );
}

Password &
Password::set( const char * user )
{
  struct passwd * pw = getpwnam( user );

  if( pw != 0 )
    {
      return( set( pw ) );
    }
  else
    {
      m_err = errno;
    }
  return(*this);
}

Password &
Password::set( const struct passwd * pw )
{
  if( pw != 0 )
    {
      m_uid = pw->pw_uid;
      m_gid = pw->pw_gid;

      freePwData();

      m_name  	= strdup( pw->pw_name );
      m_passwd  = strdup( pw->pw_passwd );
      m_gecos 	= strdup( pw->pw_gecos );
      m_home   	= strdup( pw->pw_dir );
      m_shell 	= strdup( pw->pw_shell );

    }
  return(*this);
}

std::ostream &
operator<<( std::ostream & dest, const Password & pw )
{
  if( pw.good() )
    {
      dest << pw.name() << ' '
	   << pw.passwd() << ' '
	   << pw.uid() << ' '
	   << pw.gid() << ' '
	   << pw.home() << ' '
	   << pw.shell()
	;
    }
  else
    {
      dest << pw.error();
    }

  return( dest );
}


void
Password::freePwData( void )
{
  if( m_name ) { free( m_name ); m_name = 0; }
  if( m_passwd ) { free( m_passwd ); m_passwd = 0; }
  if( m_gecos ) { free( m_gecos ); m_gecos = 0; }
  if( m_home ) { free( m_home ); m_home = 0; }
  if( m_shell ) { free( m_shell ); m_shell = 0; }
}


void
Password::initialize( void )
{
  m_err = 0;
  m_uid = 0;
  m_gid = 0;
  m_name = 0;
  m_passwd = 0;
  m_gecos = 0;
  m_home = 0;
  m_shell = 0;

  m_euid = geteuid();
}

};
