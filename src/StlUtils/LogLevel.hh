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
// Revision 2.4  1995/11/12 18:05:09  houghton
// Change LogLevel::XXXX to LogLevel::Xxxxx.
// Change setName to return true if changed, false if not.
//
// Revision 2.3  1995/11/10  14:11:43  houghton
// Cleanup (move final endif)
//
// Revision 2.2  1995/11/10  14:08:37  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:47  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  15:28:40  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <BinStream.hh>
#include <Bitmask.hh>
#include <iostream>
#else
#include <ClueCfg.hh>
#include <BinStrm.hh>
#include <Bitmask.hh>
#include <iostream>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class LogLevel : public BinObject
{
  
public:

  typedef Bitmask Level;

  static const Level	None;
  static const Level	Error;
  static const Level	Err;
  static const Level	Warning;
  static const Level	Warn;
  static const Level	App1;
  static const Level	App2;
  static const Level	App3;
  static const Level	App4;
  static const Level	App5;
  static const Level	App6;
  static const Level	Lib1;
  static const Level	Lib2;
  static const Level	Lib3;
  static const Level	Lib4;
  static const Level	Info;
  static const Level	Test;
  static const Level	Debug;
  static const Level	Funct;
  static const Level	All;
  
  inline LogLevel( const Level out = None );
  inline LogLevel( const char * out );
  
  inline Level	    setOutput( const Level out );
  Level		    setOutput( const char * out );
  
  inline Level	    setCurrent( const Level cur );
  Level		    setCurrent( const char * cur );

  inline Level	    getOutput( void ) const;
  inline Level	    getCurrent( void  ) const;
  
  const char *	    getName( const Level level ) const;
  const char *	    getLevelNames( const Level level ) const;
  
  bool		    setName( const Level level, const char * name );

  inline bool 	    shouldOutput( void ) const;
  inline bool	    willOutput( const Level outLevel ) const;

  inline int	    compare( const LogLevel & two ) const;
  
  inline bool	    operator == ( const LogLevel & rhs ) const;
  inline bool	    operator <  ( const LogLevel & rhs ) const;
  
  // libClue Common Class Methods
    
  virtual size_t	getBinSize( void ) const;
  virtual BinStream &	write( BinStream & dest ) const;
  virtual BinStream &	read( BinStream & src );
  
  virtual ostream &	write( ostream & dest ) const;
  virtual istream &	read( istream & src );

  virtual ostream &	toStream( ostream & dest = cout ) const;
  
  friend inline ostream & operator << ( ostream & dest, const LogLevel & obj );
  
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
private:

  static const char * LevelNames[];

  Level	    output;
  Level     current;
  
};

#if !defined( inline )
#if !defined( CLUE_SHORT_FN )
#include <LogLevel.ii>
#else
#include <LogLvl.ii>
#endif
#else
#undef inline
#endif


//  Quick Start:
//
//  DataTypes:
//
//  Constructors:
//
//  Destructors:
//
//
//  Public Interface:
//
//
//  	static const Level	NONE;
//  	static const Level	ERROR;
//  	static const Level	ERR;
//  	static const Level	WARNING;
//  	static const Level	WARN;
//  	static const Level	USER_1;
//  	static const Level	USER_2;
//  	static const Level	USER_3;
//  	static const Level	USER_4;
//  	static const Level	INFO;
//  	static const Level	TEST;
//  	static const Level	DEBUG;
//  	static const Level	FUNCT;
//  	static const Level	ALL;
//  
//  	LogLevel( const Level out = NONE );
//
//  	LogLevel( const char * out );
//
//  	Level
//  	setOutput( const Level out );
//
//  	level
//  	setoutput( const char * out );
//
//  	Level
//  	setCurrent( const Level cur );
//
//  	Level
//  	setCurrent( const char * cur );
//
//  	Level
//  	getOutput( void ) const;
//
//  	Level
//  	getCurrent( void  ) const;
//
//  	const char *
//  	getName( const Level level ) const;
//
//  	const char *
//  	getLevelNames( const Level level ) const;
//
//  	void
//  	setName( const Level level, const char * name );
//
//  	bool
//  	shouldOutput( void ) const;
//
//  	bool
//  	willOutput( const Level outLevel ) const;
//
//  	const char *
//  	getClassName( void ) const;
//  	    return the name of this class.
//
//  	ostream &
//  	dumpInfo( ostream & dest = cerr ) const;
//
//  Other Accociated Functions:
//

#endif // ! def _LogLevel_hh_ 
