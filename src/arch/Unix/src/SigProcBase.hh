#ifndef _SigProcBase_hh_
#define _SigProcBase_hh_
//
// File:        SigProcBase.hh
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  Base class for a signal processor.
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     04/11/97 08:11
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//
//  %PID%
//

#include <StlUtilsConfig.hh>
#include <iostream>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class SigProcBase
{

public:

  SigProcBase( void );

  virtual ~SigProcBase( void );

  virtual ostream &	    write( ostream & dest ) const;
  virtual istream &	    read( istream & src );

  virtual ostream &	    toStream( ostream & dest ) const;
  virtual istream &	    fromStream( istream & src );

  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;

protected:

private:

  SigProcBase( const SigProcBase & from );
  SigProcBase & operator =( const SigProcBase & from );

};

#if !defined( inline )
#include <SigProcBase.ii>
#else
#undef inline

ostream &
operator << ( ostream & dest, const SigProcBase & src );

istream &
operator >> ( istream & src, const SigProcBase & dest );


#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	SigProcBase	class
//
//  Constructors:
//
//  	SigProcBase( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	write( ostream & dest ) const;
//	    write the data for this class in binary form to the ostream.
//
//	virtual istream &
//	read( istream & src );
//	    read the data in binary form from the istream. It is
//	    assumed it stream is correctly posistioned and the data
//	    was written to the istream with 'write( ostream & )'
//
//	virtual ostream &
//	toStream( ostream & dest ) const;
//	    output class as a string to dest (used by operator <<)
//
//	virtual istream &
//	fromStream( istream & src );
//	    Set this class be reading a string representation from
//	    src. Returns src.
//
//  	virtual Bool
//  	good( void ) const;
//  	    Return true if there are no detected errors associated
//  	    with this class, otherwise false.
//
//  	virtual const char *
//  	error( void ) const;
//  	    Return a string description of the state of the class.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. SigProcBase )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream & dest, const char * prefix, bool showVer );
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	static const ClassVersion version
//	    Class and project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const SigProcBase & src );
//
//	istream &
//	operator >> ( istream & src, SigProcBase & dest );
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.2  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:23  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:37  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:25  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/04/19 09:53:05  houghton
// Initial Version.
//
//
#endif // ! def _SigProcBase_hh_ 

