#ifndef _LogLevel_hh_
#define _LogLevel_hh_
//
// File:        LogLevel.hh
// Project:	StlUtils
// Desc:        
//              
//	A LogLevel should be used in conjuntion with a Log and LogBuf.
//	The LogBuf contains a LogLevel to determine which log messages
//	it should output.
//
//	The LogLevel has two states. The first is the 'output'. It is a
//	mask of all levels that should be output. The second is 'current',
//	which is the level for the current log message.
//	
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 12:27
//
// Revision History: (See end of file for Revision Log);
//
// $Id$
//


#include <StlUtilsConfig.hh>
#include <Bitmask.hh>
#include <iostream>
#include <map>

#include <Common.h>

#if defined( STLUTILS_DEBUG )
#define inline
#endif

class LogLevel 
{
  
public:

  typedef Bitmask Level;
  
  typedef map< LogLevelBit, Level, less< LogLevelBit > >  CommonLevelMap;
  
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
  
  inline LogLevel( const Level out = None,
		   const Level current = Error );
  inline LogLevel( const char * out );
  inline LogLevel( const LogLevel & from );
  
  inline Level	    setOutput( const Level & out );
  inline Level	    setOutput( const char * out );
  
  inline Level	    setCurrent( const Level & cur );
  inline Level	    setCurrent( const char * cur );

  inline Level	    getOutput( void ) const;
  inline Level	    getCurrent( void  ) const;
  
  static const char *	getName( const Level & level );
  static const char *	getLevelNames( const Level & level );
  
  static bool		setName( const Level & level, const char * name );

  inline bool 	    shouldOutput( void ) const;
  inline bool	    willOutput( const Level & curLevel ) const;

  inline int	    compare( const LogLevel & two ) const;

  inline LogLevel & operator =  ( const LogLevel & rhs );
  
  inline bool	    operator == ( const LogLevel & rhs ) const;
  inline bool	    operator <  ( const LogLevel & rhs ) const;
  
  // libStlUtils Common Class Methods
    
  virtual size_t	getBinSize( void ) const;
  
  virtual ostream &	write( ostream & dest ) const;
  virtual istream &	read( istream & src );

  virtual ostream &	toStream( ostream & dest = cout ) const;
  
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;

  // do NOT use this.
  struct Name2Level
  {
    const char **   name;
    const Level *   level;
  };

protected:
  
  Level	    levelFromString( const char * level, Level curLevel );
  
private:

  static const Name2Level Name2LevelList[];
  static const char * LevelNames[];
  
  Level	    output;
  Level     current;

};

#if !defined( inline )
#if !defined( STLUTILS_SHORT_FN )
#include <LogLevel.ii>
#else
#include <LogLvl.ii>
#endif
#else
#undef inline

ostream &
operator << ( ostream & dest, const LogLevel & obj );

#endif


//  Quick Start:
//
//  Types:
//
//	LogLevel
//
//	LogLevel::Level
//	    This is a Bitmask for the current or output level
//
//  Constructors:
//
//	inline
//	LogLevel( const Level out = None,
//		  const Level cur = Error )
//	    Construct a LogLevel setting output to 'out' and
//	    current to 'cur'.
//
//	inline
//	LogLevel( const char * out )
//	    Construct a LogLevel setting output by converting
//	    the string to a level (see setOutput( const char *)).
//	    current is set to Error.
//
//	inline
//	LogLevel( const LogLevel & from )
//	    Copy constructor. Initialize the LogLevel using the
//	    values in from.
//
//	
//  Public Interface:
//
//
//	static const Level	None;
//	static const Level	Error;
//	static const Level	Err;
//	static const Level	Warning;
//	static const Level	Warn;
//	static const Level	App1;
//	static const Level	App2;
//	static const Level	App3;
//	static const Level	App4;
//	static const Level	App5;
//	static const Level	App6;
//	static const Level	Lib1;
//	static const Level	Lib2;
//	static const Level	Lib3;
//	static const Level	Lib4;
//	static const Level	Info;
//	static const Level	Test;
//	static const Level	Debug;
//	static const Level	Funct;
//	static const Level	All;
//	    These are all the available Logging Levels.
//
//	inline
//  	Level
//  	setOutput( const Level out );
//	    Set the output level to out. Returns the
//	    old value.
//	    (i.e. setOutput( LogLevel::ERR | LogLevel::WARN ) )
//
//	inline
//  	Level
//  	setOutput( const char * out );
//	    Set the output level to out by converting the string
//	    to a LogLevel::Level. Case is ignored in the string and
//	    it can contain '|' characters to set multiple levels. Also,
//	    If a Level's name was set using 'setName' (see below),
//	    The new level name will be used for Translation.
//	    (i.e. setOutput( "err| INFO | warining | Debug" ) will set
//	    the output level to 'Error | Info | Warning | Debug'.
//	    Returns the old value.
//
//	inline
//  	Level
//  	setCurrent( const Level cur );
//	    Set the current log message's level. This should only be
//	    one Level ( not Debug | Test ) to avoid confusion. An
//	    or'd value will work as expected, but only one level
//	    descriptor will be returned by 'getName' (see below).
//	    Returns the old value.
//
//	inline
//  	Level
//  	setCurrent( const char * cur );
//	    Set the current level to out by converting the string
//	    to a LogLevel::Level. Case is ignored in the string and
//	    it can contain '|' characters to set multiple levels (the use
//	    of the '|' for current level is discouraged). Also,
//	    If a Level's name was set using 'setName' (see below),
//	    The new level name will be used for Translation.
//	    (i.e. setCurrent( "err" ) set the current Level to
//	    Error. Returns the old value.
//
//
//	inline
//  	Level
//  	getOutput( void ) const;
//	    Return the output level.
//
//	inline
//  	Level
//  	getCurrent( void  ) const;
//	    Return the current level.
//
//  	const char *
//  	getName( const Level level ) const;
//	    Return the name (possible changed by 'setName') for
//	    'level'. If multiple Levels are set in 'level' only
//	    the first (top down from Error to Funct) will be returned.
//	    (i.e. getName( Warning | Info | Test ) == "WARINING" ).
//
//  	const char *
//  	getLevelNames( const Level level ) const
//	    Return a string containing all the level names
//	    (possibly changed by setName) in the level. If
//	    multiple levels are set in 'level' they are seperated
//	    by ' | ' in the output string.
//	    (i.e. getLevelNames( Err | Warn ) == "ERROR | WARNING").
//	    The return value is a static char that is modified by
//	    each call to getLevelNames.
//
//  	void
//  	setName( const Level level, const char * name );
//	    Change the name of a level. This changes the translation
//	    for all the calls in this class that use strings (char *).
//	    (i.e. setName( App1, "Crash" ) will change getName( App1 )
//	    to now return "Crash", and setCurrent( "Crash" ) to
//	    set the current level to App1 ).
//
//	inline
//  	bool
//  	shouldOutput( void ) const;
//	    Return true if the current level should be output.
//	    (i.e. returns (current & output)).
//
//	inline
//  	bool
//  	willOutput( const Level curLevel ) const;
//	    Returns true if 'curLevel' would be output.
//	    (i.e. return (curLevel & output)).
//
//	inline
//	int
//	compare( const LogLevel & two )
//	    Returns the differance between the LogLevel and 'two'.
//	    (i.e. l.compre( l2 ) == 0 if l == l2, l.compare( l2 ) < 0 if
//	    l < l2, l.compare( l2 ) > 0 if l > l2 ).
//	
//	inline
//	LogLevel &
//	operator =  ( const LogLevel & rhs )
//	    Sets the LogLevel from 'rhs'.
//
//	inline
//	bool
//	operator == ( const LogLevel & rhs ) const
//	    Returns true if the LogLevel == rhs.
//
//	inline
//	bool
//	operator <  ( const LogLevel & rhs ) const
//	    Returns true if the LogLevel < rhs.
//
//	virtual
//	size_t
//	getBinSize( void ) const
//	    Return the number of bytes that would be written to
//	    a ostream to store the data for this instance.
//
//	virtual
//	ostream &
//	write( ostream & dest ) const
//	    Write the LogLevel in binary to an ostream.
//	    Format: BitMask BitMask
//
//	virtual
//	istream &
//	read( istream & src ) const
//	    Set the LogLevel by reading the binary form from an istream.
//
//	virtual
//	ostream &
//	toStream( ostream & dest = out )
//	    Write the text of the current level to the ostream.
//	    Uses getName( current ). Returns dest.
//
//  	const char *
//  	getClassName( void ) const;
//  	    return the name of this class (i.e. "LogLevel").
//
//	virtual
//	const char *
//	getVersion( bool withPrjVer = true ) const
//	    Return the version string for the LogLevel. If
//	    withPrjVer == true, the project version info will also
//	    be returned.
//
//	virtual
//	ostream &
//	dumpInfo( ostream &	dest = cerr,
//		  const char *	prefix = "    ",
//		  bool		showVer = true );
//	    Output detailed information about the current
//	    state of the LogLevel. 
//
//	static const ClassVersion version;
//	    This contains the version information for the LogLevel class.
//
//  Accociated Functions:
//
//	inline
//  	ostream &
//  	operator <<( ostream & dest, const Bitmask & obj );
//	    Uses LogLevel::toStream to write the LogLevel as a string
//	    to the ostream.
//
//  See Also:
//
//	Log(3), LogBuf(3), Bitmask(3)
//
//  Files:
//
//	LogLevel.hh, LogLevel.ii, libStlUtils.a
//
// Documented Ver: 2.5
// Tested Ver: 2.5
//
// Revision Log:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:16  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:38  houghton
// Changed to Version 4
//
// Revision 3.6  1997/09/17 11:08:32  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.5  1997/07/18 19:24:26  houghton
// Port(Sun5): had to make 'struct Name2Level' a public member to eliminate
//     compiler errors.
//
// Revision 3.4  1997/05/02 12:17:19  houghton
// Changed all LogLevel::Level args to const & to avoid copy constructor calls.
//
// Revision 3.3  1997/04/26 14:10:33  houghton
// Cleanup.
// Added CommonLevelMap to support Log::tieCommonLogger().
//
// Revision 3.2  1997/03/21 12:24:05  houghton
// Changed string to log level converter to support +level and
//     -level. These will turn the level on or off respectivly without
//     changeing the state of other levels.
//
// Revision 3.1  1996/11/14 01:23:49  houghton
// Changed to Release 3
//
// Revision 2.5  1996/11/04 14:17:16  houghton
// Restructure header comments layout.
// Updated and verified header comment documentation.
// Removed BinStream/BinObject support.
// Changed setOutput( const char * ) and setCurrent( const char * ) to
//     be inlines.
// Changed getName and getLevelNames to static.
// Changed setName to static.
// Added operator = ( const LogLevel & rhs ).
//
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

#endif // ! def _LogLevel_hh_ 
