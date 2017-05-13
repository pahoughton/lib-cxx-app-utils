#ifndef _clue_User_hpp_
#define _clue_User_hpp_
/* 1995-05-18 (cc) Paul Houghton <paul4hough@gmail.com>

   A User provide logon information about a user on a Unix system.
*/

#include <clue/UserGroup.hpp>
#include <clue/compare>
#include <set>

namespace clue {

class User
{

public:

  typedef std::set< UserGroup, std::less<UserGroup> >	Groups;

  inline User( bool findGroups = false );
  inline User( uid_t user, bool findGroups = false );
  inline User( const char * userName, bool findGroups = false );
  inline User( const struct passwd * passwdEntry, bool findGroups = false );

  inline User( std::istream & src, bool text = false, bool findGroups = false );

  virtual ~User( void );

  inline uid_t		getUID( void ) const;
  inline const char * 	getName( void ) const;
  inline const char *	getPassword( void ) const;
  inline const char *   getRealName( void ) const;
  inline const char *   getGecos( void ) const;
  inline const char *   getHome( void ) const;
  inline const char *   getShell( void ) const;

  inline const UserGroup & 	getPrimaryGroup( void ) const;

  static const User &		effective( void );

  size_t    	findGroups( void );

  inline bool	isMember( gid_t group );
  inline bool	isMember( gid_t group ) const;
  inline bool	isMember( const char * groupName );
  inline bool	isMember( const char * groupName ) const;

  inline const Groups &	getGroups( void ) const;
  inline const Groups &	getGroups( void );

  inline bool	set( uid_t user, bool findGroups = false );
  inline bool	set( const char * userName, bool findGroups = false );
  bool		set( const struct passwd * pwdEnt, bool findGrps = false );

  inline int		compare( const User & two ) const;

  inline User &		operator =  ( uid_t user );

  inline bool		operator == ( const User & two ) const;
  inline bool		operator <  ( const User & two ) const;
  inline bool		operator != ( const User & rhs ) const;
  inline bool		operator >  ( const User & rhs ) const;
  inline bool		operator <= ( const User & rhs ) const;
  inline bool		operator >= ( const User & rhs ) const;

  inline		operator const char * () const;
  inline		operator uid_t () const;

  virtual size_t	    getBinSize( void ) const;

  virtual std::ostream &    write( std::ostream & dest ) const;
  virtual std::istream &    read( std::istream & src );

  virtual std::ostream &    toStream( std::ostream & dest = std::cout ) const;
  virtual std::istream &    fromStream( std::istream & src );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  static const uid_t	bad;

protected:

private:

  uid_t	    	uid;

  UserGroup 	primeGroup;

  Str	    	name;
  Str	    	passwd;
  Str	    	gecos;
  Str	    	home;
  Str	    	shell;

  Groups    	groups;

};


inline
User::User( bool findGroups )
{
  if( ! set( getuid(), findGroups ) )
    uid = bad;
}

inline
User::User( uid_t user, bool findGroups )
{
  if( ! set( user, findGroups ) )
    uid = bad;
}

inline
User::User( const char * user, bool findGrps )
{
  if( ! set( user, findGrps ) )
    uid = bad;
}

inline
User::User( const struct passwd * passwdEntry, bool findGrps )
{
  if( ! set( passwdEntry, findGrps ) )
    uid = bad;
}

inline
User::User( std::istream & src, bool text, bool findGrps )
{
  if( text )
    {
      char gname[ 50 ];
      src >> gname;
      set( gname, findGrps );
    }
  else
    {
      read( src );
      if( findGrps )
	findGroups();
    }
}

inline
uid_t
User::getUID( void ) const
{
  return( uid );
}

inline
const char *
User::getName( void ) const
{
  return( name );
}

inline
const char *
User::getPassword( void ) const
{
  return( passwd );
}

inline
const char *
User::getRealName( void ) const
{
  return( gecos );
}

inline
const char *
User::getGecos( void ) const
{
  return( gecos );
}

inline
const char *
User::getHome( void ) const
{
  return( home );
}

inline
const char *
User::getShell( void ) const
{
  return( shell );
}

inline
const UserGroup &
User::getPrimaryGroup( void ) const
{
  return( primeGroup );
}

inline
bool
User::isMember( gid_t group )
{
  UserGroup g( group, false );

  if( groups.size() == 0 )
    findGroups();

  return( groups.find( g ) != groups.end() );
}

inline
bool
User::isMember( gid_t group ) const
{
  UserGroup g( group, false );
  return( groups.end() != groups.find( g ) );
}

inline
bool
User::isMember( const char * group )
{
  UserGroup g( group, false );

  if( groups.size() == 0 )
    findGroups();

  return( groups.find( g ) != groups.end() );
}

inline
bool
User::isMember( const char * group ) const
{
  UserGroup g( group, false );
  return( groups.end() != groups.find( g )  );
}

inline
const User::Groups &
User::getGroups( void ) const
{
  return( groups );
}

inline
const User::Groups &
User::getGroups( void )
{
  if( groups.size() == 0 )
    findGroups();
  return( groups );
}

inline
bool
User::set( uid_t user, bool findGrps )
{
  return( set( getpwuid( user ), findGrps ) );
}

inline
bool
User::set( const char * userName, bool findGrps )
{
  return( set( getpwnam( userName ), findGrps ));
}

inline
int
User::compare( const User & two ) const
{
  return( clue::compare( name, two.name ) );
}

inline
User &
User::operator =  ( uid_t user )
{
  set( user );
  return( *this );
}

inline
bool
User::operator == ( const User & two ) const
{
  return( compare( two ) == 0 );
}

inline
bool
User::operator < ( const User & two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
User::operator != ( const User & rhs ) const
{
  return( ! (*this == rhs) );
}

inline
bool
User::operator > ( const User & rhs ) const
{
  return( rhs < *this );
}

inline
bool
User::operator <= ( const User & rhs ) const
{
  return( ! (rhs < *this) );
}

inline
bool
User::operator >= ( const User & rhs ) const
{
  return( ! (*this < rhs) );
}

inline
User::operator const char * ( void ) const
{
  return( name );
}

inline
User::operator uid_t ( void ) const
{
  return( uid );
}

inline
int
compare( const User & one, const User & two )
{
  return( one.compare( two ) );
}

inline
std::ostream &
operator << ( std::ostream & dest, const User & obj )
{
  return( obj.toStream( dest ) );
}


}; // namespace clue

/* Types:

  	User

	Groups
	    This is a typedef set< UserGroup, less< UserGroup > >
	    It provides the interface to the groups a user belongs to.

  Constructors:

	inline
  	User( bool findGroups = false );
	    Intialize the user using the application's uid. If find
	    groups is true, The groups that the user belongs to
	    will be initialized. If it is false a call to any method
	    that nees this information will initialze it at that time.

  Destructors:

  Public Interface:

  	virtual const char *
  	getClassName( void ) const;
  	    Return the name of this class (i.e. User )

  	virtual Bool
  	good( void ) const;
  	    Returns true if there are no detected errors associated
  	    with this class, otherwise FALSE.

  	virtual const char *
  	error( void ) const
  	    Returns as string description of the state of the class.

  Other Associated Functions:

  	ostream &
  	operator <<( ostream & dest, const User & obj );


*/

#endif // ! def _User_hh_
