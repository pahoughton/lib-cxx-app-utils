//
// File:        FileStat.C
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     12/22/94 17:18 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/02/13 16:08:41  houghton
// New Style Avl an memory management. Many New Classes
//
//
static const char * RcsId =
"$Id$";

#include "FileStat.hh"
#include <Common.h>
#include <iomanip.h>


#include <Password.hh>
#include <Group.hh>
#include <DateTime.hh>

void
FileStat::setStrings( void )
{
  Password  pwd( getUID() );
  Group	    grp( getGID() );
  
  strcpy( user, pwd.getName() );
  strcpy( group, grp.getName() );

  FileModeString( getMode(), mode );  
}


Bool
FileStat::canRead( void ) const
{
  Password  pwd;
  
  if( getUID() == pwd.getUID() || getUID() == pwd.getEUID() )
    {
      if( getMode() & S_IRUSR ) 
	{
	  return( TRUE );
	}
      else
	{
	  return( FALSE );
	}
    }

  Group	    grp;

  if( grp.isIn( getGID() ) )
    {
      if( ( getMode() & S_IRGRP ) )
	{
	  return( TRUE );
	}
      else
	{
	  return( FALSE );
	}
    }

  if( getMode() & S_IROTH )
    {
      return( TRUE );
    }
  else
    {
      return( FALSE );
    }
}
  
Bool
FileStat::canWrite( void ) const
{
  Password  pwd;
  
  if( getUID() == pwd.getUID() || getUID() == pwd.getEUID() )
    {
      if( getMode() & S_IWUSR ) 
	{
	  return( TRUE );
	}
      else
	{
	  return( FALSE );
	}
    }

  Group	    grp;

  if( grp.isIn( getGID() ) )
    {
      if( ( getMode() & S_IWGRP ) )
	{
	  return( TRUE );
	}
      else
	{
	  return( FALSE );
	}
    }

  if( getMode() & S_IWOTH )
    {
      return( TRUE );
    }
  else
    {
      return( FALSE );
    }
}
  
  
Bool
FileStat::canExec( void ) const
{
  Password  pwd;
  
  if( getUID() == pwd.getUID() || getUID() == pwd.getEUID() )
    {
      if( getMode() & S_IXUSR ) 
	{
	  return( TRUE );
	}
      else
	{
	  return( FALSE );
	}
    }

  Group	    grp;

  if( grp.isIn( getGID() ) )
    {
      if( ( getMode() & S_IXGRP ) )
	{
	  return( TRUE );
	}
      else
	{
	  return( FALSE );
	}
    }

  if( getMode() & S_IXOTH )
    {
      return( TRUE );
    }
  else
    {
      return( FALSE );
    }
}


const char *
FileStat::error( void ) const
{
  if( good() )
    {
      static char errStr[512];

      strcpy( errStr, "FileStat: " );
      strcat( errStr, strerror( osErrno ) );
      
      return( errStr );
    }
  else
    {
      return( "FileStat: Ok" );
    }
}


ostream &
operator<<( ostream & dest, const FileStat & fs )
{

  if( fs.good() )
    {
      DateTime mdt( fs.getMtime(), TRUE );

      dest.setf( ios::left );       
      dest << fs.getModeString() << ' '
	   << setw(8) << fs.getUserName() << ' '
	   << setw(8) << fs.getGroupName() << ' '
	;
      
      dest.setf( ios::right );
      dest << setw(10) << fs.getSize() << ' '
	   << mdt
	;
    }
  else
    {
      dest << fs.error() ;
    }

  return( dest );
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
