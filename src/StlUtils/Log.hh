#ifndef _Log_hh_
#define _Log_hh_
//
// File:        Log.hh
// Project:	Clue
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     03/14/94 10:49
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <Mutex.hh>
#include <LogBuf.hh>
#include <iostream>
#include <iomanip>
#include <fstream>
#else
#include <Mutex.hh>
#include <ClueCfg.hh>
#include <LogBuf.hh>
#include <iostream>
#include <iomanip>
#include <fstream>
#endif



#if defined( CLUE_LOG_WHERE )
#define LogIf( lg, lvl ) \
  if( (lg)(lvl, __FILE__, __LINE__ ).willOutput( lvl ) ) (lg)
#else
#define LogIf( lg, lvl ) \
  if( (lg)(lvl, 0, 0 ).willOutput( lvl ) ) (lg)
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class Log : public ostream
{

public:

  inline Log( ostream & 	outStream = cout,
	      LogLevel::Level 	outLevel = LogLevel::Error,
	      bool		stampLevel = true,
	      bool		stampTime = true,
	      bool		stampLoc = true );

  inline Log( ostream & 	outStream,
	      const char *      outLevel,
	      bool		stampLevel = true,
	      bool		stampTime = true,
	      bool		stampLoc = true ); 
  
  inline Log( const char * 	fileName,
	      LogLevel::Level 	outLevel = LogLevel::Error,
	      ios::open_mode	mode = ios::app,
	      int		prot = filebuf::openprot,
	      bool		stampLevel = true,
	      bool		stampTime = true,
	      bool		stampLoc = true,
	      size_t		maxSize = 0,
	      size_t		trimSize = 0 );
	      
  inline Log( const char * 	fileName,
	      const char *	outLevel,
	      ios::open_mode	mode = ios::app,
	      int		prot = filebuf::openprot,
	      bool		stampLevel = true,
	      bool		stampTime = true,
	      bool		stampLoc = true,
	      size_t		maxSize = 0,
	      size_t		trimSize = 0 );

  inline ~Log( void );

  inline LogLevel::Level    getCurrent( void  ) const;
  inline LogLevel::Level    getOutput( void ) const;

  inline bool	    	    willOutput( LogLevel::Level outLevel ) const;
  
  Log &		    level( LogLevel::Level  current = LogLevel::Error,
			   const char *	    srcFile = 0,
			   long		    srcLine = 0 );
  
  inline Log &	    operator () ( void );
  inline Log &	    operator () ( LogLevel::Level   current );
  Log &		    operator () ( LogLevel::Level   current,
				  const char *	    srcFile,
				  long		    srcLine );

  Log &		    level( const char *	    current,
			   const char *	    srcFile = 0,
			   long		    srcLine = 0 );
  
  inline Log &      operator () ( const char *	    current );
  inline Log &      operator () ( const char *	    current,
				  const char *	    srcFile,
				  long		    srcLine );
  
  inline bool		    setLevelStamp( bool stamp );
  inline bool		    setTimeStamp( bool stamp );
  inline bool		    setLocStamp( bool stamp );

  inline LogLevel::Level    setOutputLevel( const char * output );
  inline LogLevel::Level    setOutputLevel( LogLevel::Level output );

  inline void		    on( LogLevel::Level output );
  inline void		    off( LogLevel::Level output );
  
  inline void 	    	    tee( ostream & teeStream = cerr );

  inline bool		    addTee( streambuf *	    destBuf );
  
  inline size_t		    trim( size_t maxSize = 0 );
  inline size_t		    setMaxSize( size_t maxSize );
  inline size_t		    setTrimSize( size_t trimSize );
  
  inline void		    open( const char *	    fileName,
				  ios::open_mode    mode = ios::app );
  
  inline void		    setFileName( const char *	    fileName,
					 ios::open_mode	    mode = ios::app );
  
  inline void		    close( void );

  bool			filter( const char * regex );
  LogBuf::FilterId	addFilter( streambuf *     destBuf,
				   LogLevel::Level outputLevel,
				   const char *    regex = 0 );

  bool			delFilter( LogBuf::FilterId id );

  
  inline LogBuf *	    rdbuf( void );
  inline const LogBuf *	    rdbuf( void ) const;

  // mutex locking

  inline bool		    lock( void );
  inline bool		    unlock( void );
  
  virtual bool 		good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
protected:

private:

  Log( const Log & copyFrom );
  Log & operator=( const Log & assignFrom );

  bool		timeStamp;
  bool		levelStamp;
  bool		locStamp;
  
  Mutex		mutex;
  
};

#ifndef inline
#include <Log.ii>
#else
#undef inline
#endif


//  Quick Start : - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	Log class
//
//  Constructors:
//
//  	log( ostream & outStream = cout,
//  	     LogLevel::Level outLevel = LogLevel::ERROR,
//  	     bool stampLevel = true,
//  	     bool stampTime = true );
//
//  	log( ostream & outStream,
//  	     const char * outLevel,
//  	     bool stampLevel = true,
//  	     bool stampTime = true );
//
//  	log( const char * fileName,
//  	     LogLevel::Level outLevel = LogLevel::ERROR,
//  	     bool stampLevel = true,
//  	     bool stampTime = true,
//  	     ios::open_mode mode = ios::app,
//  	     int prot = filebuf::openprot,
//  	     size_t maxSize = 0,
//  	     size_t trimSize = 0 );
//
//  	log( const char * fileName,
//  	     const char * outLevel,
//  	     bool stampLevel = true,
//  	     bool stampTime = true,
//  	     ios::open_mode mode = ios::app,
//  	     int prot = filebuf::openprot,
//  	     size_t maxSize = 0,
//  	     size_t trimSize = 0 );
//
//  Destructors:
//
//  	~Log( void );
//
//  Public Interface:
//
//  	void
//  	tee( ostream & teeStream = cerr );
//
//  	size_t
//  	trim( size_t maxSize = 0 );
//
//  	size_t
//  	setMaxSize( size_t maxSize );
//
//  	size_t
//  	setTrimSize( size_t trimSize );
//
//  	virtual Log &
//  	level( LogLevel::Level curren = LogLevel::ERROR );
//
//  	Log &
//  	operator () ( LogLevel::Level curren = LogLevel::ERROR );
//
// 	virtual Log &
//  	level( const char * current );
//
// 	Log &
//  	operator () ( const char * current );
//
//  	void
//  	on( LogLevel::Level output );
//
//  	void
//  	off( LogLevel::Level ouput );
//
//  	LogLevel::Level
//  	getCurrent( void ) const;
//
//  	LogLevel::Level
//  	getOutput( void ) const;
//
//  	void
//  	setFileName( const char * f, int mode = ios::app );
//
//  	void
//  	open( const char * f, int mode = ios::app );
//
//  	void
//  	close( void );
//
//  	LogLevel::Level
//  	setOutputLevel( const char * output );
//
//  	LogLevel::Level
//  	setOutputLevel( LogLevel::Level output );
//
//  	bool
//  	setLevelStamp( bool stamp );
//
//  	bool
//  	setTimeStamp( bool stamp );
//
//  	LogBuf *
//  	rdbuf( void );
//
//  	const LogBuf *
//  	rdbuf( void ) const;
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Returns the name of this class ( i.e. Log )
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
// Revision Log:
//
// $Log$
// Revision 2.7  1996/11/04 13:43:35  houghton
// Restructure header comments layout.
// Changed order of constructor args.
// Reorder method declarations.
// Added filter support. Only output log messages that contain a regex.
// Added multiple log message destination. (addFilter & delFilter).
//
// Revision 2.6  1996/10/22 22:05:45  houghton
// Change: Added locStamp to turn on/off output of src file & line.
//
// Revision 2.5  1996/04/27 13:02:48  houghton
// Added thread locking support.
//
// Revision 2.4  1995/11/12 18:01:16  houghton
// Added srcFile, srcLine args to level().
// Change LogIf macro to use __FILE__ and __LINE__.
// Change LogLevel::XXXX to LogLevel::Xxxxx.
//
// Revision 2.3  1995/11/10  14:11:42  houghton
// Cleanup (move final endif)
//
// Revision 2.2  1995/11/10  14:08:37  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:43  houghton
// Change to Version 2
//
// Revision 1.7  1995/11/05  15:28:37  houghton
// Revised
//
//

#endif // ! def _Log_hh_ 

