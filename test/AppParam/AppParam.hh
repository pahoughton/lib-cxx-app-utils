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
// Created:     03/21/97 06:59
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
#include <Str.hh>

class AppParam : public Param
{

public:

  AppParam( int & argv, char ** argc, const char * ver = 0 );

  ~AppParam( void );

  bool		parseArgs( void );
  bool		parseArgs( int argc, char * argv[] );

  const Str &	tOne( void ) const { return( tOneV ); };
  const Str &	tTwo( void ) const { return( tTwoV ); };
  const long	tThree( void ) const { return( tThreeV ); };
  
protected:

private:

  Str	tOneV;
  Str	tTwoV;
  long	tThreeV;
  
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
// Revision 6.1  2003/08/09 11:22:48  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:24  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:44  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:30  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/03/21 15:58:13  houghton
// Changed base version to 3
//
// Revision 1.1  1997/03/21 15:57:48  houghton
// Initial Version.
//
// Revision 1.2  1997/03/21 15:47:50  houghton
// Initial Version
//
//

#endif // ! def _AppParam_hh_ 
