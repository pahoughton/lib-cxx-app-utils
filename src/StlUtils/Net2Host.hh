#ifndef _Net2Host_hh_
#define _Net2Host_hh_
//
// File:        Net2Host.hh
// Project:	StlUtils
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     10/31/96 06:01
//
// Revision History: (See end of file for Revision Log)
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
//  Data Types: - data types defined by this header
//
//  	Net2Host	class
//
//  Constructors:
//
//  	Net2Host( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	toStream( ostream & dest ) const
//	    output class as a string to dest (used by operator <<)
//
//  	virtual Bool
//  	good( void ) const;
//  	    Return true if there are no detected errors associated
//  	    with this class, otherwise false.
//
//  	virtual const char *
//  	error( void ) const
//  	    Return a string description of the state of the class.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. Net2Host )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream & dest, const char * prefix, bool showVer )
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	static const ClassVersion
//	version
//	    class & project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const Net2Host & obj );
//
// Revision Log
//
// $Log$
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

