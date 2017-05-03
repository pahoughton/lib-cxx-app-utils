#ifndef _AppParam_hh_
#define _AppParam_hh_
//
// File:        AppParam.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     07/20/97 07:08
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <Param.hh>
#include <FilePath.hh>

class AppParam : public Param
{

public:

  AppParam( int & argv, char ** argc, const char * ver = 0 );

  ~AppParam( void );

  const Str &	    fnPattern( void ) const { return( fnPatternV ); };
  const FilePath &  inDir( void ) const { return( inDirV ); };
  const FilePath &  procDir( void ) const { return( procDirV ); };
  long		    waitSecs( void ) const { return( waitSecsV ); };
  
  bool		parseArgs( void );
  bool		parseArgs( int argc, char * argv[] );

protected:

private:

  AppParam( const AppParam & copyFrom );
  AppParam & operator=( const AppParam & assignFrom );

  Str	    fnPatternV;
  FilePath  inDirV;
  FilePath  procDirV;
  long	    waitSecsV;
  
};

extern AppParam * App;


//  Data Types: - data types defined by this header
//
//  	AppParam	class
//
//  Constructors:
//
//  	AppParam( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. AppParam )
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
//  	operator <<( ostream & dest, const AppParam & obj );
//
// Revision Log:
//
// $Log$
// Revision 6.2  2011/12/30 23:57:50  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:54  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:33  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:15:00  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:21  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/07/25 12:27:32  houghton
// Changed version number to 3.
//
// Revision 1.1  1997/07/20 18:55:52  houghton
// Initial Version.
//
//

#endif // ! def _AppParam_hh_ 
