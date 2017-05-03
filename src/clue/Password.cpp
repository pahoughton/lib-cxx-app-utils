//
// File:        Password.C
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     12/23/94 12:22 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/02/13 16:08:54  houghton
// New Style Avl an memory management. Many New Classes
//
//
static const char * RcsId =
"$Id$";

#include "Password.hh"

int
Password::password( uid_t user )
{
  struct passwd * pw = getpwuid( user );

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

int
Password::password( const char * user )
{
  struct passwd * pw = getpwnam( user );
  
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

int
Password::password( const struct passwd * pw )
{ 
  if( pw != 0 )
    {
      uid = pw->pw_uid;
      gid = pw->pw_gid;

      freePwData();
      
      name  	= strdup( pw->pw_name );
      passwd    = strdup( pw->pw_passwd );
      gecos 	= strdup( pw->pw_gecos );
      dir   	= strdup( pw->pw_dir );
      shell 	= strdup( pw->pw_shell );

      return( 0 );
    }
  else
    {
      return( -1 );
    }
}

ostream &
operator<<( ostream & dest, const Password & pw )
{
  if( pw.good() )
    {
      dest << pw.getName() << ' '
	   << pw.getPassword() << ' '
	   << pw.getUID() << ' '
	   << pw.getGID() << ' '
	   << pw.getRealName() << ' '
	   << pw.getDir() << ' '
	   << pw.getShell() 
	;
      if( pw.getEUID() != pw.getUID() )
	{
	  dest << " Effecive: " << pw.getEName() << ' '
	       << pw.getEUID()
	    ;
	}      
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
  if( name ) { free( name ); name = 0; }
  if( passwd ) { free( passwd ); passwd = 0; }
  if( gecos ) { free( gecos ); gecos = 0; }
  if( dir ) { free( dir ); dir = 0; }
  if( shell ) { free( shell ); shell = 0; }
}

  
void
Password::initialize( void )
{
  errorNum = 0;
  uid = 0;
  gid = 0;
  name = 0;
  passwd = 0;
  gecos = 0;
  dir = 0;
  shell = 0;
  ename = 0;
  
  euid = geteuid();
  
  struct passwd * pwd = getpwuid( euid );

  if( pwd != 0 )
    {
      ename = strdup( pwd->pw_name );
    }
  else
    {
      errorNum = errno;
      return;
    }
}


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
