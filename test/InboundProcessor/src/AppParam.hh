#ifndef _AppParam_hh_
#define _AppParam_hh_
//
// File:        AppParam.hh
// Project:	Clue
// Desc:        
//
//
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
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
// Revision 3.1  1997/07/25 12:27:32  houghton
// Changed version number to 3.
//
// Revision 1.1  1997/07/20 18:55:52  houghton
// Initial Version.
//
//

#endif // ! def _AppParam_hh_ 
