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
// Revision 1.5  1995/11/05 15:28:50  houghton
// Revised
//
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <ctime>
#include <iostream>
#else
#include <ClueCfg.hh>
#include <ctime>
#include <iostream>
#endif


#if defined( CLUE_DEBUG )
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
