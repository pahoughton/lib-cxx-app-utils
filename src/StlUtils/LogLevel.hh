#ifndef _LogLevel_hh_
#define _LogLevel_hh_
//
// File:        LogLevel.hh
// Desc:        
//              
//
// Notes:   	default copy construtor and assignment operators are ok.
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 12:27
//
// Revision History:
//
// 
// $Log$
// Revision 1.3  1995/11/05 14:44:39  houghton
// Ports and Version ID changes
//
//

#ifdef CLUE_SHORT_FN
#include <ClueCfg.hh>
#else
#include <ClueConfig.hh>
#endif

#include <Bitmask.hh>

#include <iostream>

#ifdef  CLUE_DEBUG
#define inline
#endif

class LogLevel 
{
  
public:

  typedef Bitmask Level;

  static const Level	NONE;
  static const Level	ERROR;
  static const Level	ERR;
  static const Level	WARNING;
  static const Level	WARN;
  static const Level	USER_1;
  static const Level	USER_2;
  static const Level	USER_3;
  static const Level	USER_4;
  static const Level	INFO;
  static const Level	TEST;
  static const Level	DEBUG;
  static const Level	FUNCT;
  static const Level	ALL;
  
  inline LogLevel( const Level out = NONE );
  inline LogLevel( const char * out );
  
  inline Level	    setOutput( const Level out );
  Level		    setOutput( const char * out );
  
  inline Level	    setCurrent( const Level cur );
  Level		    setCurrent( const char * cur );

  inline Level	    getOutput( void ) const;
  inline Level	    getCurrent( void  ) const;
  
  const char *	    getName( const Level level ) const;
  const char *	    getLevelNames( const Level level ) const;
  
  inline void	    setName( const Level level, const char * name );

  inline bool 	    shouldOutput( void ) const;
  inline bool	    willOutput( const Level outLevel ) const;

  const char *	    getClassName( void ) const;
  ostream &	    dumpInfo( ostream & dest = cerr ) const;

  static const char version[];
  
private:

  static const char * LevelNames[];

  Level	    output;
  Level     current;
  
};

#ifndef inline
#include <LogLevel.ii>
#else
#undef inline
#endif

#endif // ! def _LogLevel_hh_ 
