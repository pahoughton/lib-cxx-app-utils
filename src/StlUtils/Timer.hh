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
// Revision 1.3  1995/11/05 13:29:09  houghton
// Major Implementation Changes.
// Made more consistant with the C++ Standard
//
//
//

#include <ClueConfig.hh>
#include <time.h>

#include <iostream>

#ifdef  CLUE_DEBUG
#define inline
#endif

class Timer
{

public:

  inline Timer( time_t startTime = 0 );

  inline time_t    	start( time_t startTime = 0 );
  inline time_t    	stop( time_t stopTime = 0 );

  inline time_t    	getDur( void ) const;
  inline time_t    	getStart( void ) const;
  inline time_t    	getStop( void ) const;

  inline const char *	getClassName( void ) const;
  inline ostream &	toStream( ostream & dest = cout ) const;
  ostream &		dumpInfo( ostream & dest = cerr ) const;

  static const char version[];
  
protected:

private:

  time_t    startSec;
  time_t    stopSec;
  
};


#ifndef	 inline
#include <Timer.ii>
#else
#undef inline

ostream &
operator<<( ostream & dest, const Timer & timer );

#endif

#endif // ! def _Timer_hh_ 
