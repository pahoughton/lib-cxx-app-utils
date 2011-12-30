#ifndef _PidFile_hh_
#define _PidFile_hh_
//
// File:        PidFile.hh
// Project:	StlUtils ()
// Desc:        
//
//  Create a file containing the applications pid.
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul4hough@gmail.com)
// Created:     04/15/97 06:26
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
//  $Id$ 
//

#include <StlUtilsConfig.hh>
#include <FilePath.hh>
#include <DumpInfo.hh>
#include <iostream>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class PidFile
{

public:

  PidFile( const char * fullName );
  PidFile( const char * path, const char * name, const char * ext = ".pid" );

  virtual ~PidFile( void );

  bool	    removePidFile( void );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;

  inline
  DumpInfo< PidFile >	dump( const char *  prefix = "    ",
			      bool	    showVer = true ) const;
  
protected:

  bool	    createPidFile( void );
  
private:

  FilePath	fileName;
  int		osErrno;
  
  PidFile( const PidFile & from );
  PidFile & operator =( const PidFile & from );

};

#if !defined( inline )
#include <PidFile.ii>
#else
#undef inline


#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	PidFile	class
//
//  Constructors:
//
//  	PidFile( );
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
//  	    Return the name of this class (i.e. PidFile )
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
//  	operator <<( ostream & dest, const PidFile & src );
//
//	istream &
//	operator >> ( istream & src, PidFile & dest );
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
// Revision 6.2  2011/12/30 23:57:33  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:47  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:22  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:34  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:22  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/04/19 09:53:03  houghton
// Initial Version.
//
//
#endif // ! def _PidFile_hh_ 

