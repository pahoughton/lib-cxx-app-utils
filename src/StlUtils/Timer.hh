#ifndef _Timer_hh_
#define _Timer_hh_
//
// File:        Timer.hh
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     10/31/94 13:58
//
// Revision History:
//
// 
// $Log$
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:08  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:58  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:24:27  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:41:19  houghton
// Change to Version 2
//
// Revision 1.5  1995/11/05  15:28:50  houghton
// Revised
//
//
//

#if !defined( STLUTILS_SHORT_FN )
#include <StlUtilsConfig.hh>
#include <ctime>
#include <iostream>
#else
#include <StlUtilsCfg.hh>
#include <ctime>
#include <iostream>
#endif


#if defined( STLUTILS_DEBUG )
#define inline
#endif

class Timer
{

public:

  inline Timer( time_t startTime = 0 );

  virtual ~Timer( void ) {};
  
  inline time_t    	start( time_t startTime = 0 );
  inline time_t    	stop( time_t stopTime = 0 );

  inline time_t    	getDur( void ) const;
  inline time_t    	getStart( void ) const;
  inline time_t    	getStop( void ) const;

  virtual ostream &	toStream( ostream & dest = cout ) const;
  
  friend inline ostream & operator<<( ostream & dest, const Timer & timer );
  
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
protected:

private:

  time_t    startSec;
  time_t    stopSec;
  
};


#if !defined( inline )
#include <Timer.ii>
#else
#undef inline
#endif

#endif // ! def _Timer_hh_ 
