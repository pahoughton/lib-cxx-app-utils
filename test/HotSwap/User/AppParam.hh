#ifndef _AppParam_hh_
#define _AppParam_hh_
//
// File:        AppParam.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/13/97 12:27
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

  const FilePath &  lockFn( void ) const { return( lockFnV ); };
  long		    swapCount( void ) const { return( swapCountV ); };
  int		    sleepTime( void ) const { return( sleepTimeV ); };
  
  bool		parseArgs( void );
  bool		parseArgs( int argc, char * argv[] );

protected:

  FilePath  lockFnV;
  long	    swapCountV;
  int	    sleepTimeV;

private:

  AppParam( const AppParam & copyFrom );
  AppParam & operator=( const AppParam & assignFrom );

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
// Revision 6.1  2003/08/09 11:22:53  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:33  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:58  houghton
// Changed to Version 4
//
// Revision 1.2  1997/09/17 11:10:19  houghton
// Changed: renamed library to StlUtils.
//
// Revision 1.1  1997/09/16 11:31:26  houghton
// Initial Version.
//
//

#endif // ! def _AppParam_hh_ 
