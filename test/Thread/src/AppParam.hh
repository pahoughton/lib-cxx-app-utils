#ifndef _AppParam_hh_
#define _AppParam_hh_
//
// File:        AppParam.hh
// Desc:        
//
//
//  Quick Start: - short example of class usage
//
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     07/16/96 06:52
//
// Revision History:
//
// $Log$
// Revision 4.1  1997/09/17 15:15:08  houghton
// Changed to Version 4
//
// Revision 3.1  1996/11/14 01:28:07  houghton
// Changed to Release 3
//
// Revision 1.1  1996/07/16 13:54:07  houghton
// *** empty log message ***
//
//

#include <Param.hh>

class AppParam : public Param
{

public:

  AppParam( int & argv, char ** argc, const char * ver = 0 );

  ~AppParam( void );

  long	    threads( void ) { return( vThreads ); };
  bool	    detach( void ) { return( vDetach ); };
  long	    sleep( void ) { return( vSleep ); };
  
  long	    subThreads( void ) { return( vSubThreads ); };
  bool	    subDetach( void ) { return( vSubDetach ); };
  long	    subSleep( void ) { return( vSubSleep ); };
  long	    subLife( void ) { return( vSubLife ); };
  
protected:

private:

  AppParam( const AppParam & copyFrom );
  AppParam & operator=( const AppParam & assignFrom );

  long	vThreads;
  bool	vDetach;
  long	vSleep;
  
  long	vSubThreads;
  bool	vSubDetach;
  long	vSubSleep;
  long  vSubLife;
  
  
};


//
// Inline methods
//

inline
AppParam::AppParam( int & argc, char ** argv, const char * ver )
  : Param( argc, argv, ver, "ALL" ),
    vThreads( 5 ),
    vDetach( false ),
    vSleep( 5 ),
    vSubThreads( 5 ),
    vSubDetach( false ),
    vSubSleep( 5 ),
    vSubLife( 2 )
{
  argLong( vThreads, "number of base threads to start", "t" );
  argFlag( vDetach, "detach thread", "detach" );
  argLong( vSleep, "seconds to sleep between threads", "sleep" );
  
  argLong( vSubThreads, "number of sub threads to start", "st" );
  argFlag( vSubDetach, "detach sub thread", "sd" );
  argLong( vSubSleep, "seconds to sleep between sub threads", "ss" );
  argLong( vSubLife, "seconds sub threads sleeps", "sl" );
}

inline
AppParam::~AppParam( void )
{
  
}

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

#endif // ! def _AppParam_hh_ 
