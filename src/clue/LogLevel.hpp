#ifndef _clue_LogLevel_hpp_
// 1995-01-29 (cc) Paul Houghton <paul4hough@gmail.com>
#define _clue_LogLevel_hpp_
/*
  A LogLevel should be used in conjuntion with a Log and LogBuf.
  The LogBuf contains a LogLevel to determine which log messages
  it should output.

  The LogLevel has two states. The first is the 'output'. It is a
  mask of all levels that should be output. The second is 'current',
  which is the level for the current log message.
*/

#include <clue/bitmask>
#include <iostream>
#include <map>

namespace clue {

class LogLevel
{

public:

  typedef enum {
    LOG_NONE  = 0x0000,
    LOG_ERROR = 0x0001,
    LOG_WARN  = 0x0002,
    LOG_APP1  = 0x0004,
    LOG_APP2  = 0x0008,
    LOG_APP3  = 0x0010,
    LOG_APP4  = 0x0020,
    LOG_APP5  = 0x0040,
    LOG_APP6  = 0x0080,
    LOG_LIB1  = 0x0100, /* WARNING: used by Wcf */
    LOG_LIB2  = 0x0200, /* WARNING: used by Wcf */
    LOG_LIB3  = 0x0400, /* WARNING: used by Wcf */
    LOG_LIB4  = 0x0800, /* WARNING: used by Wcf */
    LOG_INFO  = 0x1000,
    LOG_TEST  = 0x2000,
    LOG_DEBUG = 0x4000,
    LOG_FUNCT = 0x8000,
    LOG_ALL   = 0xffff
  } LogLevelBit;

  typedef bitmask            Level;
  typedef bitmask::size_type size_type;

  typedef std::map< LogLevelBit,
		    Level,
		    std::less< LogLevelBit > >  CommonLevelMap;

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

#if !defined( CLUE_USE_RELOPS )
  inline bool		operator != ( const LogLevel & rhs ) const;
  inline bool		operator >  ( const LogLevel & rhs ) const;
  inline bool		operator <= ( const LogLevel & rhs ) const;
  inline bool		operator >= ( const LogLevel & rhs ) const;
#endif

  virtual std::ostream & toStream( std::ostream & dest = std::cout ) const;

  virtual const char *	 getClassName( void ) const;
  virtual std::ostream & dumpInfo( std::ostream & dest = std::cerr,
				   const char *	  prefix = "    " ) const;

  // internal
  struct Name2Level
  {
    const char **   name;
    const Level *   level;
  };

protected:

  Level	    levelFromString( const char * level, Level curLevel );

private:

  static const Name2Level Name2LevelList[];
  static const char *     LevelNames[];

  Level	    output;
  Level     current;

};


inline
LogLevel::LogLevel( const Level out, const Level cur )
  : output( out ),
    current( cur )
{
}

inline
LogLevel::LogLevel( const char * out )
{
  setCurrent( Error );
  setOutput( out );
}

inline
LogLevel::LogLevel( const LogLevel & from )
  : output( from.output ),
    current( from.current )
{
}

inline
LogLevel::Level
LogLevel::setOutput( const Level & out )
{
  Level	old = output;
  output = out;
  return( old );
}

inline
LogLevel::Level
LogLevel::setOutput( const char * level )
{
  return( setOutput( levelFromString( level, output ) ) );
}

inline
LogLevel::Level
LogLevel::setCurrent( const Level & cur )
{
  Level	old = current;
  current = cur;
  return( old );
}

inline
LogLevel::Level
LogLevel::setCurrent( const char * lvl )
{
  return( setCurrent( levelFromString( lvl, current ) ) );
}

inline
LogLevel::Level
LogLevel::getOutput( void ) const
{
  return( output );
}

inline
LogLevel::Level
LogLevel::getCurrent( void  ) const
{
  return( current );
}


inline
bool
LogLevel::shouldOutput( void ) const
{
  return( output & current );
}

inline
bool
LogLevel::willOutput( const Level & level ) const
{
  return( level & output );
}

inline
int
LogLevel::compare( const LogLevel & two ) const
{
  int diff = current.compare( two.current );
  if( ! diff )
    return( output.compare( two.output ) );
  else
    return( diff );
}

inline
LogLevel &
LogLevel::operator =  ( const LogLevel & rhs )
{
  output  = rhs.output;
  current = rhs.current;
  return( *this );
}

inline
bool
LogLevel::operator == ( const LogLevel & rhs ) const
{
  return( compare( rhs ) == 0 );
}

inline
bool
LogLevel::operator <  ( const LogLevel & rhs ) const
{
  return( compare( rhs ) < 0 );
}

#if !defined( CLUE_USE_RELOPS )
inline
bool
LogLevel::operator != ( const LogLevel & rhs ) const
{
  return( ! (*this == rhs) );
}

inline
bool
LogLevel::operator > ( const LogLevel & rhs ) const
{
  return( rhs < *this );
}

inline
bool
LogLevel::operator <= ( const LogLevel & rhs ) const
{
  return( ! (rhs < *this) );
}

inline
bool
LogLevel::operator >= ( const LogLevel & rhs ) const
{
  return( ! (*this < rhs) );
}
#endif

inline
std::ostream &
operator << ( std::ostream & dest, const LogLevel & obj )
{
  return( obj.toStream( dest ) );
}


} // namespace clue

/*

  Types:

	class LogLevel

	class LogLevel::Level : public Bitmask
	    This is a Bitmask for the current or output level

  Constructors:

	inline
	LogLevel( const Level out = None,
		  const Level cur = Error )
	    Construct a LogLevel setting output to 'out' and
	    current to 'cur'.

	inline
	LogLevel( const char * out )
	    Construct a LogLevel setting output by converting
	    the string to a level (see setOutput( const char *)).
	    current is set to Error.

	inline
	LogLevel( const LogLevel & from )
	    Copy constructor. Initialize the LogLevel using the
	    values in from.


  Public Interface:


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
	    These are all the available Logging Levels.

	inline
  	Level
  	setOutput( const Level out );
	    Set the output level to out. Returns the
	    old value.
	    (i.e. setOutput( LogLevel::ERR | LogLevel::WARN ) )

	inline
  	Level
  	setOutput( const char * out );
	    Set the output level to out by converting the string
	    to a LogLevel::Level. Case is ignored in the string and
	    it can contain '|' characters to set multiple levels. Also,
	    If a Level's name was set using 'setName' (see below),
	    The new level name will be used for Translation.
	    (i.e. setOutput( "err| INFO | warining | Debug" ) will set
	    the output level to 'Error | Info | Warning | Debug'.
	    Returns the old value.

	inline
  	Level
  	setCurrent( const Level cur );
	    Set the current log message's level. This should only be
	    one Level ( not Debug | Test ) to avoid confusion. An
	    or'd value will work as expected, but only one level
	    descriptor will be returned by 'getName' (see below).
	    Returns the old value.

	inline
  	Level
  	setCurrent( const char * cur );
	    Set the current level to out by converting the string
	    to a LogLevel::Level. Case is ignored in the string and
	    it can contain '|' characters to set multiple levels (the use
	    of the '|' for current level is discouraged). Also,
	    If a Level's name was set using 'setName' (see below),
	    The new level name will be used for Translation.
	    (i.e. setCurrent( "err" ) set the current Level to
	    Error. Returns the old value.


	inline
  	Level
  	getOutput( void ) const;
	    Return the output level.

	inline
  	Level
  	getCurrent( void  ) const;
	    Return the current level.

  	const char *
  	getName( const Level level ) const;
	    Return the name (possible changed by 'setName') for
	    'level'. If multiple Levels are set in 'level' only
	    the first (top down from Error to Funct) will be returned.
	    (i.e. getName( Warning | Info | Test ) == "WARINING" ).

  	const char *
  	getLevelNames( const Level level ) const
	    Return a string containing all the level names
	    (possibly changed by setName) in the level. If
	    multiple levels are set in 'level' they are seperated
	    by ' | ' in the output string.
	    (i.e. getLevelNames( Err | Warn ) == "ERROR | WARNING").
	    The return value is a static char that is modified by
	    each call to getLevelNames.

  	void
  	setName( const Level level, const char * name );
	    Change the name of a level. This changes the translation
	    for all the calls in this class that use strings (char *).
	    (i.e. setName( App1, "Crash" ) will change getName( App1 )
	    to now return "Crash", and setCurrent( "Crash" ) to
	    set the current level to App1 ).

	inline
  	bool
  	shouldOutput( void ) const;
	    Return true if the current level should be output.
	    (i.e. returns (current & output)).

	inline
  	bool
  	willOutput( const Level curLevel ) const;
	    Returns true if 'curLevel' would be output.
	    (i.e. return (curLevel & output)).

	inline
	int
	compare( const LogLevel & two )
	    Returns the differance between the LogLevel and 'two'.
	    (i.e. l.compre( l2 ) == 0 if l == l2, l.compare( l2 ) < 0 if
	    l < l2, l.compare( l2 ) > 0 if l > l2 ).

	inline
	LogLevel &
	operator =  ( const LogLevel & rhs )
	    Sets the LogLevel from 'rhs'.

	inline
	bool
	operator == ( const LogLevel & rhs ) const
	    Returns true if the LogLevel == rhs.

	inline
	bool
	operator <  ( const LogLevel & rhs ) const
	    Returns true if the LogLevel < rhs.

	virtual
	size_t
	getBinSize( void ) const
	    Return the number of bytes that would be written to
	    a std::ostream to store the data for this instance.

	virtual
	std::ostream &
	write( std::ostream & dest ) const
	    Write the LogLevel in binary to an std::ostream.
	    Format: BitMask BitMask

	virtual
	std::istream &
	read( std::istream & src ) const
	    Set the LogLevel by reading the binary form from an std::istream.

	virtual
	std::ostream &
	toStream( std::ostream & dest = out )
	    Write the text of the current level to the std::ostream.
	    Uses getName( current ). Returns dest.

  	const char *
  	getClassName( void ) const;
  	    return the name of this class (i.e. "LogLevel").

	virtual
	const char *
	getVersion( bool withPrjVer = true ) const
	    Return the version string for the LogLevel. If
	    withPrjVer == true, the project version info will also
	    be returned.

	virtual
	std::ostream &
	dumpInfo( std::ostream &	dest = std::cerr,
		  const char *	prefix = "    ",
		  bool		showVer = true );
	    Output detailed information about the current
	    state of the LogLevel.

	static const ClassVersion version;
	    This contains the version information for the LogLevel class.

  Accociated Functions:

	inline
  	std::ostream &
  	operator <<( std::ostream & dest, const Bitmask & obj );
	    Uses LogLevel::toStream to write the LogLevel as a string
	    to the std::ostream.

*/
#endif // ! def _LogLevel_hh_
