#ifndef _User_hh_
#define _User_hh_
//
// File:        User.hh
// Desc:        
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/11/95 09:43
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 12:41:09  houghton
// Initial User Class Implementation
//
//

#include <ClueConfig.hh>
#include <UserGroup.hh>
#include <Str.hh>

#include <set>

#include <pwd.h>

#ifdef  CLUE_DEBUG
#define inline
#endif


class User
{

public:

  typedef set< UserGroup, less<UserGroup> >	Groups;
  
  inline User( bool findGroups = false );
  inline User( uid_t user, bool findGroups = false );
  inline User( const char * userName, bool findGroups = false );
  inline User( const struct passwd * passwdEntry, bool findGroups = false );

  inline User( istream & src, bool text = false, bool findGroups = false );
  
  inline ~User( void );

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
  
  inline bool	set( uid_t user, bool findGroups = false );
  inline bool	set( const char * userName, bool findGroups = false );
  bool		set( const struct passwd * pwdEnt, bool findGrps = false );
  
  inline size_t    	getStreamSize( void ) const;
  inline ostream & 	write( ostream & dest ) const;
  inline istream & 	read( istream & src );

  inline int		compare( const User & two ) const;
  
  inline bool		operator == ( const User & two ) const;
  inline bool		operator <  ( const User & two ) const;

  inline		operator const char * () const;
  inline		operator uid_t () const;

  inline bool		good( void ) const;
  const char *		error( void ) const;
  const char *		getClassName( void ) const;
  inline ostream &	toStream( ostream & dest = cout ) const;
  ostream &		dumpInfo( ostream & dest = cerr ) const;
  
  static const uid_t	bad;
  static const char	version[];
  
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

  static const User	eff;
};

#ifndef inline
#include <User.ii>
#else
#undef inline

int
compare( const User & one, const User & two );

ostream &
operator <<( ostream & dest, const User & user );

#endif // ! def inline


//  Data Types: - data types defined by this header
//
//  	User	class
//
//  Constructors:
//
//  	User( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. User )
//
//  	virtual Bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const User & obj );
//

#endif // ! def _User_hh_ 
