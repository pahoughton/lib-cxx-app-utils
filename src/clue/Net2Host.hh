#ifndef _Net2Host_hh_
#define _Net2Host_hh_
//
// File:        Net2Host.hh
// Project:	StlUtils ()
// Desc:        
//
//  Provides fucntions for converting data between host and network format.
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     10/31/96 06:01
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
#include <Common.h>

inline
short
Net2Host( short num )
{
  return( Net2HostShort( num ) );
}

inline
short
Host2Net( short num )
{
  return( Host2NetShort( num ) );
}

inline
unsigned short
Net2Host( unsigned short num )
{
  return( Net2HostUShort( num ) );
}

inline
unsigned short
Host2Net( unsigned short num )
{
  return( Host2NetUShort( num ) );
}

inline
int
Net2Host( int num )
{
  return( Net2HostInt( num ) );
}

inline
int
Host2Net( int num )
{
  return( Host2NetInt( num ) );
}

inline
unsigned int
Net2Host( unsigned int num )
{
  return( Net2HostUInt( num ) );
}

inline
unsigned int
Host2Net( unsigned int num )
{
  return( Host2NetUInt( num ) );
}

inline
long
Net2Host( long num )
{
  return( Net2HostLong( num ) );
}

inline
long
Host2Net( long num )
{
  return( Host2NetLong( num ) );
}

inline
unsigned long
Net2Host( unsigned long num )
{
  return( Net2HostULong( num ) );
}

inline
unsigned long
Host2Net( unsigned long num )
{
  return( Host2NetULong( num ) );
}




//
// Detail Documentation
//
//
// Revision Log
//
// 
// %PL%
// 
// $Log$
// Revision 6.2  2011/12/30 23:57:17  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:42  houghton
// Changed to version 6
//
// Revision 5.4  2003/08/09 11:20:59  houghton
// Changed ver strings.
//
// Revision 5.3  2001/07/29 19:56:38  houghton
// *** empty log message ***
//
// Revision 5.2  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:16  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:42  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:35  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/03/21 15:43:07  houghton
// Changed base version to 3
//
// Revision 2.2  1997/03/02 13:19:40  houghton
// Changed includes.
//
// Revision 2.1  1996/11/04 14:20:41  houghton
// Initial Version.
//
#endif // ! def _Net2Host_hh_ 

