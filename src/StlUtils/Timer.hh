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
// Revision 1.4  1995/11/05 14:44:55  houghton
// Ports and Version ID changes
//
//
//

#ifdef CLUE_SHORT_FN
#include <ClueCfg.hh>
#else
#include <ClueConfig.hh>
#endif

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
