#ifndef _UserGroup_hh_
#define _UserGroup_hh_
//
// File:        UserGroup.hh
// Desc:        
//
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/09/95 06:06
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:46:58  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:49:19  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <BinStream.hh>
#include <Str.hh>
#include <set>
#include <functional>
#include <cstddef>
#include <unistd.h>
#include <grp.h>
#else
#include <ClueCfg.hh>
#include <BinStrm.hh>
#include <Str.hh>
#include <set>
#include <functional>
#include <cstddef>
#include <unistd.h>
#include <grp.h>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class User;

class UserGroup : public BinObject
{

public:

  typedef set< Str, less<Str> >	    Members;
    
  inline UserGroup( bool findMembers = false );
  inline UserGroup( gid_t group, bool findMembers = false );
  inline UserGroup( const char * groupName, bool findMembers = false );
  inline UserGroup( const struct group * grpEnt, bool findMembers = false );

  inline UserGroup( istream & src, bool text = false, bool findMemb = false );

  inline gid_t	    	    getGID( void ) const;
  inline const char *	    getName( void ) const;

  static const UserGroup &  effective( void );
  
  size_t		    findMembers( void );
  
  inline const Members &    getMembers( void ) const;

  inline bool	isMember( const User & user );
  inline bool	isMember( const User & user ) const;
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

  inline   	    operator const char * ( void ) const;
  inline   	    operator gid_t ( void ) const;

  // libClue Common Class Methods
  // note: write/read only stores the GID
  
  virtual size_t	getBinSize( void ) const;
  virtual BinStream &	write( BinStream & dest ) const;
  virtual BinStream &	read( BinStream & src );
  
  virtual ostream & 	write( ostream & dest ) const;
  virtual istream & 	read( istream & src );

  virtual ostream &	toStream( ostream & dest = cout ) const;

  friend inline ostream & operator << ( ostream & dest,
					const UserGroup & obj );
    
  virtual bool		good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
  static const gid_t	bad;
  
protected:

private:

  gid_t	    	gid;

  Str	    	name;
  Members   	members;

  int	    	osError;
  
  static UserGroup  eff;
  
};

#if !defined( inline )
#if !defined( CLUE_SHORT_FN )
#include <UserGroup.ii>
#else
#include <UserGrp.ii>
#endif
#else
#undef inline

int
compare( const UserGroup & one, const UserGroup & two );

#endif // ! def inline

//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	UserGroup	class
//
//  Constructors:
//
//  	UserGroup( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. UserGroup )
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
//  	operator <<( ostream & dest, const UserGroup & obj );
//
#endif // ! def _UserGroup_hh_ 
