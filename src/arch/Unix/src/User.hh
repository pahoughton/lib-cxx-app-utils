#ifndef _User_hh_
#define _User_hh_
//
// File:        User.hh
// Project:	StlUtils ()
// Desc:        
//
//  A User provide logon information about a user on a Unix system.
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/11/95 09:43
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
//

#include <StlUtilsConfig.hh>
#include <UserGroup.hh>
#include <set>
#include <pwd.h>

#if defined( STLUTILS_DEBUG )
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

#if defined( STLUTILS_RELOPS_BROKEN )
  inline bool		operator != ( const User & rhs ) const;
  inline bool		operator >  ( const User & rhs ) const;
  inline bool		operator <= ( const User & rhs ) const;
  inline bool		operator >= ( const User & rhs ) const;
#endif
  
  inline		operator const char * () const;
  inline		operator uid_t () const;

  // libStlUtils Common Class Methods
  // note: write/read only stores the UID
  
  virtual size_t	getBinSize( void ) const;
  
  virtual ostream & 	write( ostream & dest ) const;
  virtual istream & 	read( istream & src );

  virtual ostream &	toStream( ostream & dest = cout ) const;
  virtual istream &	fromStream( istream & src );
  
  virtual bool		good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
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

#if !defined( inline )
#include <User.ii>
#else
#undef inline

ostream &
operator << ( ostream & dest, const User & obj );

int
compare( const User & one, const User & two );

#endif // ! def inline


// Types:
//
//  	User
//
//	Groups
//	    This is a typedef set< UserGroup, less< UserGroup > >
//	    It provides the interface to the groups a user belongs to.
//
//  Constructors:
//
//	inline
//  	User( bool findGroups = false );
//	    Intialize the user using the application's uid. If find
//	    groups is true, The groups that the user belongs to
//	    will be initialized. If it is false a call to any method
//	    that nees this information will initialze it at that time.
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
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.1  2003/08/09 11:22:47  houghton
// Changed to version 6
//
// Revision 5.4  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.3  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.2  2000/05/25 17:07:31  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:23  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:40  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:09:28  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/03/03 14:38:21  houghton
// Removed support for RW Tools++.
//
// Revision 3.1  1996/11/14 01:25:10  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/06 18:11:09  houghton
// Changed how effective user is handled.
// Changed use of Str to RWCString.
//     (as required per Mike Alexander)
// Added fromStream function.
//
// Revision 2.3  1996/05/01 11:01:26  houghton
// Bug-Fix: static const User eff was causing segv.
//   change so the effective() method just returns a new 'User'
//
// Revision 2.2  1995/12/04 11:20:21  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:46:57  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:49:17  houghton
// Revised
//
//

#endif // ! def _User_hh_ 
