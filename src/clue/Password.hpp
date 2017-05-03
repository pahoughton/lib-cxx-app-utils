#ifndef _Password_hh_
#define _Password_hh_
//
// File:        Password.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     12/23/94 11:52
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1995/02/13 16:08:54  houghton
// New Style Avl an memory management. Many New Classes
//
//

#if defined( AIX )
#define _POSIX_SOURCE
#define _ALL_SOURCE
#endif

#if defined( AIX )
extern "C" void endpwent();
#endif

#ifdef HAVE_SHADOW
#include <shadow.h>
#endif

#include <Clue.hh>

#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <iostream.h>

class Password
{

public:

  Password( void );
  Password( uid_t   user );
  Password( const char * user );

  ~Password( void );
  
  int	    	operator()( uid_t user );
  int	    	operator()( const char * user );

  int	    	password( uid_t user );
  int	    	password( const char * name );
  int	    	password( const struct passwd * pw );
  
  inline int   	firstEntry( void );
  inline int   	nextEntry( void );
  
  const char *	getName( char * buf = 0 ) const;
  const char * 	getPassword( char * buf = 0 ) const;
  const char * 	getRealName( char * buf = 0 ) const;
  const char * 	getGecos( char * buf = 0 ) const;
  const char * 	getDir( char * buf = 0 ) const;
  const char *	getShell( char * buf = 0 ) const;
  
  const char *	getEName( char * buf = 0 ) const;
  
  uid_t	    	getUID( void ) const;
  gid_t	    	getGID( void ) const;

  uid_t	    	getEUID( void ) const;

  Bool	    	good( void ) const;
  const char *	error( void ) const;

  friend ostream & operator<<( ostream & dest, const Password & pw );
  
protected:

private:

  void initialize( void );
  void freePwData( void );
  
  Password( const Password & copyFrom );
  Password & operator=( const Password & assignFrom );

  int	    	errorNum;
  
  uid_t	    	uid;
  gid_t	    	gid;
  uid_t	    	euid;
  
  char *    	name;
  char *    	passwd;
  char *    	gecos;
  char *    	dir;
  char *    	shell;

  char *    	ename;
  
};


//
// Inline methods
//

inline
Password::Password( void )
{
  initialize();
  password( getuid() );
}

inline
Password::Password( uid_t user )
{
  initialize();
  password( user );
}

inline
Password::Password( const char * user )
{
  initialize();
  password( user );
}

inline
Password::~Password( void )
{
  freePwData();

  if( ename ) free(ename);
}

inline
int
Password::operator()( uid_t user )
{
  return( password( user ) );
}

inline
int
Password::operator()( const char * user )
{
  return( password( user ) ); 
}

inline
int
Password::firstEntry( void )
{
  endpwent();

  return( nextEntry() );
}

inline
int
Password::nextEntry( void )
{
  struct passwd * pw = getpwent();

  if( pw != 0 )
    {
      return( password( pw ) );       
    }
  else
    {
      errorNum = errno;
      return( -1 );
    }
}

inline
const char *
Password::getName( char * buf ) const
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
Password::getPassword( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, passwd );
      return( buf );
    }
  else
    {
      return( passwd );
    }
}

inline
const char *
Password::getRealName( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, gecos );
      return( buf );
    }
  else
    {
      return( gecos );
    }
}

inline
const char *
Password::getGecos( char * buf ) const
{
  return( getRealName( buf ) );
}

inline
const char *
Password::getDir( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, dir );
      return( buf );
    }
  else
    {
      return( dir );
    }
}

inline
const char *
Password::getShell( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, shell );
      return( buf );
    }
  else
    {
      return( shell );
    }
}

inline
const char *
Password::getEName( char * buf ) const
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
uid_t
Password::getUID( void ) const
{
  return( uid );
}

inline
gid_t
Password::getGID( void ) const
{
  return( gid );
}

inline
uid_t
Password::getEUID( void ) const
{
  return( euid );
}

inline
Bool
Password::good( void ) const
{
  return( errorNum == 0 );
}

inline
const char *
Password::error( void ) const
{
  if( errorNum )
    {
      return( strerror( errorNum ) );
    }
  else
    {
      return( "Ok" );
    }
}




#endif // ! def _Password_hh_ 
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
