#ifndef _Group_hh_
#define _Group_hh_
//
// File:        Group.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     12/23/94 12:34
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1995/02/13 16:08:44  houghton
// New Style Avl an memory management. Many New Classes
//
//

#include <Clue.hh>

#include <unistd.h>
#include <grp.h>
#include <sys/types.h>
#include <limits.h>

class Group
{

public:

  Group( void );
  Group( gid_t group );
  Group( const char * group );

  int	    	operator()( gid_t grp );
  int	    	operator()( const char * grp );

  int	    	group( gid_t grp );
  int	    	group( const char * grp );
  int	    	group( const struct group * gr );
  
  int	    	firstEntry( void );
  inline int   	nextEntry( void );

  const char * 	firstMember( void );
  const char *	nextMember( void );
  
  gid_t	    	getGID( void ) const;
  const char *	getName( char * buf = 0 ) const;
  const char * 	getMembers( char * buf = 0 ) const;

  gid_t	    	getEGID( void ) const;
  const char *	getEName( char * buf = 0 ) const;  
  
  Bool	    	isIn( gid_t group, uid_t uid = USHRT_MAX );
  Bool	    	isIn( const char * group, uid_t = USHRT_MAX );

  Bool	    	good( void ) const;
  const char *	error( void ) const;

  friend ostream & operator<<( ostream & dest, const Group & gr );
  
protected:

private:

  void initialize( void );
  void freeGrData( void );
  
  Group( const Group & copyFrom );
  Group & operator=( const Group & assignFrom );

  int	    	errorNum;
  
  gid_t	    	gid;
  gid_t	    	egid;

  char *    	name;
  char *    	members;
  char *    	ename;

  char *    	eachMember;
  
};


//
// Inline methods
//

inline
Group::Group( void )
{
  initialize();
  group( getgid() );
}

inline
Group::Group( gid_t grp )
{
  initialize();
  group( grp );
}

inline
Group::Group( const char * grp )
{
  initialize();
  group( grp );
}

inline
int
Group::operator()( gid_t grp )
{
  return( group( grp ) );
}

inline
int
Group::operator()( const char * grp )
{
  return( group( grp ) );
}

inline
int
Group::firstEntry( void ) 
{
  endgrent();

  return( nextEntry() );
}

inline
int
Group::nextEntry( void ) 
{
  struct group * grp = getgrent();

  if( grp != 0 )
    {
      return( group( grp ) );
    }
  else
    {
      errorNum = errno;
      return( -1 );
    }
}

inline
gid_t
Group::getGID( void ) const
{
  return( gid );
}

inline
const char *
Group::getName( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, name );
      return( buf );
    }
  else
    {
      return( name );
    }
}

inline
const char *
Group::getMembers( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, members );
      return( buf );
    }
  else
    {
      return( members );
    }
}

inline
gid_t
Group::getEGID( void ) const
{
  return( egid );
}

inline
const char *
Group::getEName( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, ename );
      return( buf );
    }
  else
    {
      return( ename );
    }
}

inline
Bool
Group::good( void ) const
{
  return( errorNum == 0 );
}

inline
const char *
Group::error( void ) const
{
  if( good() )
    {
      return( "Ok" );
    }
  else
    {
      return( strerror( errorNum ) );
    }
}


#endif // ! def _Group_hh_ 
//
//              This software is the sole property of
// 
//                 The Williams Companies, Inc.
//                        1 Williams Center
//                          P.O. Box 2400
//        Copyright (c) 1994 by The Williams Companies, Inc.
// 
//                      All Rights Reserved.  
// 
//
