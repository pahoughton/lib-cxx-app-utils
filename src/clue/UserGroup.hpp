#ifndef _clue_UserGroup_hpp_
#define _clue_UserGroup_hpp_
/* 1995-05-09 (cc) Paul Houghton <paul4hough@gmail.com>

   Provide a Unix user's Group information.
*/

#include <clue/Str.hpp>
#include <clue/compare>
#include <set>
#include <functional>
#include <climits>
#include <cstddef>
#include <cerrno>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>


namespace clue {

class User;

class UserGroup
{

public:

  typedef std::set< Str, std::less<Str> >	    Members;

  inline UserGroup( bool findMembers = false );
  inline UserGroup( gid_t group, bool findMembers = false );
  inline UserGroup( const char * groupName, bool findMembers = false );
  inline UserGroup( const struct group * grpEnt, bool findMembers = false );

  inline UserGroup( std::istream & src, bool text = false, bool findMemb = false );

  virtual ~UserGroup( void );

  inline gid_t	    	    getGID( void ) const;
  inline const char *	    getName( void ) const;

  static const UserGroup &  effective( void );

  size_t		    findMembers( void );

  inline const Members &    getMembers( void ) const;

  bool		isMember( const User & user );
  bool		isMember( const User & user ) const;
  inline bool	isMember( uid_t user );
  inline bool	isMember( uid_t user ) const;
  inline bool	isMember( const char * userName );
  inline bool	isMember( const char * userName ) const;

  inline bool	set( gid_t group, bool findMemb = false );
  inline bool	set( const char * groupName, bool findMemb = false );
  bool	    	set( const struct group * grpEnt, bool findMemb = false );

  inline int	    compare( const UserGroup & two ) const;

  inline bool	    operator == ( const UserGroup & two ) const;
  inline bool	    operator <  ( const UserGroup & two ) const;
  inline bool	    operator != ( const UserGroup & rhs ) const;
  inline bool	    operator >  ( const UserGroup & rhs ) const;
  inline bool	    operator <= ( const UserGroup & rhs ) const;
  inline bool	    operator >= ( const UserGroup & rhs ) const;

  inline   	    operator const char * ( void ) const;
  inline   	    operator gid_t ( void ) const;

  virtual size_t	    getBinSize( void ) const;

  virtual std::ostream &    write( std::ostream & dest ) const;
  virtual std::istream &    read( std::istream & src );

  virtual std::ostream &    toStream( std::ostream & dest = std::cout ) const;
  virtual std::istream &    fromStream( std::istream & src );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  static const gid_t	bad;

protected:

private:

  gid_t	    	gid;

  Str    	name;
  Members   	members;

  int	    	osError;

};


inline
UserGroup::UserGroup( bool findMemb )
{
  gid = bad;
  osError = 0;
  set( getgid(), findMemb );
}

inline
UserGroup::UserGroup( gid_t group, bool findMemb )
{
  gid = bad;
  osError = 0;
  set( group, findMemb );
}

inline
UserGroup::UserGroup( const char * groupName, bool findMemb )
{
  gid = bad;
  osError = 0;
  set( groupName, findMemb );
}

inline
UserGroup::UserGroup( const struct group * groupEntry, bool findMemb )
{
  gid = bad;
  osError = 0;
  set( groupEntry, findMemb );
}
inline
UserGroup::UserGroup( std::istream & src, bool text, bool findMemb )
{
  if( text )
    {
      char gname[ 50 ];
      src >> gname;
      set( gname, findMemb );
    }
  else
    {
      read( src );
      if( findMemb )
	findMembers();
    }
}

inline
gid_t
UserGroup::getGID( void ) const
{
  return( gid );
}

inline
const char *
UserGroup::getName( void ) const
{
  return( name );
}

inline
const UserGroup::Members &
UserGroup::getMembers( void ) const
{
  return( members );
}

inline
bool
UserGroup::isMember( uid_t  user )
{
  struct passwd * pw = getpwuid( user );

  if( members.size() == 0 )
    findMembers();

  return( pw ? members.find( pw->pw_name ) != members.end() : false );
}

inline
bool
UserGroup::isMember( uid_t  user ) const
{
  struct passwd * pw = getpwuid( user );

  if( members.size() == 0 )
    return( false );

  // STUPID - end() first or sun cc 5.0 wines
  return( pw ? members.end() != members.find( pw->pw_name ) : false );
}

inline
bool
UserGroup::isMember( const char * user )
{
  if( members.size() == 0 )
    findMembers();

  return( members.find( user ) != members.end() );
}

inline
bool
UserGroup::isMember( const char * user ) const
{
  if( members.size() == 0 )
    return( false );

  return( members.end() != members.find( user ) );
}

inline
bool
UserGroup::set( gid_t group, bool findMemb )
{
  return( set( getgrgid( group ), findMemb ) );
}

inline
bool
UserGroup::set( const char * groupName, bool findMemb )
{
  return( set( getgrnam( groupName ), findMemb ) );
}

inline
int
UserGroup::compare( const UserGroup & two ) const
{
  return( clue::compare( name, two.name ) );
}

inline
bool
UserGroup::operator == ( const UserGroup & two ) const
{
  return( compare( two ) == 0 );
}

inline
bool
UserGroup::operator <  ( const UserGroup & two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
UserGroup::operator != ( const UserGroup & rhs ) const
{
  return( ! (*this == rhs) );
}

inline
bool
UserGroup::operator > ( const UserGroup & rhs ) const
{
  return( rhs < *this );
}

inline
bool
UserGroup::operator <= ( const UserGroup & rhs ) const
{
  return( ! (rhs < *this) );
}

inline
bool
UserGroup::operator >= ( const UserGroup & rhs ) const
{
  return( ! (*this < rhs) );
}

inline
UserGroup::operator const char * ( void ) const
{
  return( name );
}

inline
UserGroup::operator gid_t ( void ) const
{
  return( gid );
}

inline
int
compare( const UserGroup & one, const UserGroup & two )
{
  return( one.compare( two ) );
}

inline
std::ostream &
operator <<( std::ostream & dest, const UserGroup & obj )
{
  return( obj.toStream( dest ) );
}
}; // namespace clue

#endif // ! def _clue_UserGroup_hpp_
