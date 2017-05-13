#ifndef _clue_Password_hpp_
#define _clue_Password_hpp_
// 1994-12-23 (cc) Paul Houghton <paul4hough@gmail.com>

#include <iostream>

#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <shadow.h>
#include <cstring>

namespace clue {

class Password
{

public:

  Password( void ) { initialize(); set( getuid() ); };
  Password( uid_t user ) { initialize(); set( user ); };;
  Password( const char * user ) { initialize(); set( user ); };

  ~Password( void ) { freePwData(); };

  Password &   	set( uid_t user );
  Password &   	set( const char * name );
  Password &   	set( const struct passwd * pw );

  inline const char *	name( char * buf = 0 ) const { return m_name; };
  inline const char * 	passwd( char * buf = 0 ) const { return m_passwd; };
  inline const char * 	gecos( char * buf = 0 ) const { return m_gecos; };
  inline const char * 	home( char * buf = 0 ) const { return m_home; };
  inline const char *	shell( char * buf = 0 ) const { return m_shell; };
  inline uid_t	    	uid( void ) const { return m_uid; };
  inline gid_t	    	gid( void ) const { return m_gid; };
  inline uid_t	    	euid( void ) const { return m_euid; };

  bool	    	good( void ) const { return( m_err == 0); };
  const char *	error( void ) const { return( good() ? "" : strerror( m_err ) ); }

  friend std::ostream & operator<<( std::ostream & dest, const Password & pw );

protected:

  void freePwData( void );

private:

  void initialize( void );

  Password( const Password & copyFrom );
  Password & operator=( const Password & assignFrom );

  int	    	m_err;

  uid_t	    	m_uid;
  gid_t	    	m_gid;
  uid_t	    	m_euid;

  char *    	m_name;
  char *    	m_passwd;
  char *    	m_gecos;
  char *    	m_home;
  char *    	m_shell;

};


}
#endif // ! def _clue_Password_hpp_
