#ifndef _LogBuf_hh_
#define _LogBuf_hh_
//
// File:        LogBuf.hh
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//              
//  This is a specialized streambuf used by Log to
//  output log messages.
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 12:32
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//
// %PID%
//

#include <StlUtilsConfig.hh>

#include <LogLevel.hh>
#include <FilePath.hh>

#include <vector>
#include <iostream>
#include <fstream>


#if defined( STLUTILS_DEBUG )
#define inline
#endif

class RegexScan;

class LogBuf : public streambuf
{
  
public:

  typedef long	FilterId;
  
  LogBuf( LogLevel::Level   outLevel,
		 streambuf * 	   outStream );

  LogBuf( const char * 	outLevel,
		 streambuf * 	outStream );

  LogBuf( const char *	    fileName,
		 LogLevel::Level    outLevel = LogLevel::Error, 
		 ios::open_mode	    mode = ios::app,
		 int		    prot = 0664,
		 size_t		    maxSize = 0,
		 size_t		    trimSize = 0 );
  
  LogBuf( const char *	    fileName,
		 const char *	    outLevel,
		 ios::open_mode	    mode = ios::app,
		 int		    prot = 0664,
		 size_t		    maxSize = 0,
		 size_t		    trimSize = 0 );
  
  virtual ~LogBuf( void );

  inline LogLevel::Level    setCurrentLevel( const LogLevel::Level & level );
  inline LogLevel::Level    setCurrentLevel( const char * level );

  inline LogLevel::Level    setOutputLevel( const LogLevel::Level & level );
  inline LogLevel::Level    setOutputLevel( const char * level );
  
  inline const LogLevel &   getLogLevel( void ) const;
  
  size_t		trim( size_t maxSize = 0 );
  
  inline size_t	        setMaxSize( size_t maxSize );
  inline size_t		setTrimSize( size_t trimSize );
  inline size_t		getMaxSize( void ) const;
  inline size_t		getTrimSize( void ) const;
  
  inline streambuf *	tee( streambuf * teeStreambuf );
  
  inline const FilePath &	getLogFileName( void ) const;

  filebuf *		open( const char *	name,
			      ios::open_mode    mode,
			      int	        prot,
			      size_t	        maxSize,
			      size_t	        trimSize );
  
  filebuf *		open( const char *	name,
			      ios::open_mode    mode,
			      int	        prot = 0664 );
  
  void			close (void);
  
  inline bool		is_file( void ) const;
  inline bool		is_open( void ) const;
  
  bool		    filter( const char * regex );
  const char *	    getFilter( void ) const;
  
  FilterId	    addFilter( streambuf *		destBuf,
			       const LogLevel::Level &	outputLevel,
			       const char *		regex = 0 );

  streambuf *	    getFilterStream( LogBuf::FilterId filter );
  LogLevel::Level   getFilterLogLevel( LogBuf::FilterId filter );
  const char *	    getFilterRegex( LogBuf::FilterId filter );
  
  streambuf *	    delFilter( FilterId id );

  inline bool		willOutput( const LogLevel::Level & lvl ) const;
  
  // streambuf virtuals
  virtual int	    overflow(int=EOF);
  virtual int	    underflow();
  virtual int	    sync() ;

  virtual bool		good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char *  getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  static const FilterId	    badFilterId;

  // do NOT use this.
  class Filter
  {
  public:
    inline Filter( void );
    inline Filter( const Filter & from );
    inline ~Filter( void );

    inline Filter & operator = ( const Filter & rhs );
      
    streambuf *	    dest;
    LogLevel::Level outputLevel;
    RegexScan *	    regex;
  };

  // do NOT use this
protected:
  
  void initLogBuffer( void );
  void initbuf( streambuf * outStream );
  void initbuf( const char * fn,
		ios::open_mode mode,
		int prot,
		size_t m,
		size_t t );
  
  size_t	sendToStream( streambuf * dest, char * base, size_t len );
  
  filebuf *	openLog( ios::open_mode modeMask );
  size_t	trimLog( size_t curSize, size_t maxLogSize );
  void		closeLog( void );

  typedef vector< Filter > FilterList;

  FilePath	    logFileName;
  size_t	    maxSize;
  size_t	    trimSize;
  ios::open_mode    openMode;
  int		    openProt;
  bool		    streamIsFile;
  int		    logFd;
  
  char *    	buffer;
  
  streambuf *	stream;
  streambuf * 	teeStream;

  LogLevel 	logLevel;
  RegexScan *	regex;
  bool		newMesg;

  FilterList	filters;
  
  Str		    errorDesc;
private:

};

#if !defined( inline )
#include <LogBuf.ii>
#else
#undef inline
#endif

//  Quick Start : - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	LogBuf class
//
//  Constructors:
//
//  	LogBuf( LogLevel::Level   outLevel,
//    	    	streambuf * 	  outStream );
//
//  	LogBuf( const char * 	outLevel,
//		streambuf * 	outStream );
//
//  	LogBuf( const char *	    fileName,
//		LogLevel::Level    outLevel = LogLevel::ERROR, 
//		ios::open_mode	    mode = ios::app,
//		int		    prot = filebuf::openprot,
//		size_t		    maxSize = 0,
//		size_t		    trimSize = 0 );
//  
//  	LogBuf( const char *	    fileName,
//		const char *	    outLevel,
//		ios::open_mode	    mode = ios::app,
//		int		    prot = filebuf::openprot,
//		size_t		    maxSize = 0,
//		size_t		    trimSize = 0 );
//
//  Destructors:
//
//  	virtual ~LogBuf( void );
//
//  Public Interface:
//
//  	bool
//  	willOutput( LogLevel::Level outputLevel ) const;
//
//  	filebuf *
//  	open( const char *	name,
//	      ios::open_mode    mode,
//	      int	        prot = filebuf::openprot,
//	      size_t	        maxSize = 0,
//	      size_t	        trimSize = 0 );
//
//  	void
//  	close( void );
//
//  	size_t
//  	trim( size_t maxSize = 0 );
//
//  	size_t
//  	setMaxSize( size_t maxSize );
//
//  	size_t
//  	setTrimSize( size_t trimSize );;
//
//  	bool
//  	isFile( void ) const;
//
//  	LogLevel &
//  	level( void );
//
//  	const LogLevel &
//  	level( void ) const;
//
//  	virtual int
//  	overflow(int=EOF);
//
//  	virtual int
//  	underflow();
//
//  	virtual int
//  	sync() ;
//
//  	const char *
//  	getClassName( void ) const;
//
//  	ostream &
//  	dumpInfo( ostream & dest = cerr ) const;
//
//  Private interface:
//
//  	void
//  	initLogBuffer( void )
//
//  	void
//  	initLogBuffer( void );
//
//  	void
//  	initbuf( const char * fn,
//		 ios::open_mode mode,
//	    	 int prot,
//		 size_t m,
//
//  	filebuf *
//  	openLog( void );
//
//  	size_t
//  	trimLog( size_t curSize, size_t maxLogSize );
//
//  	void
//  	closeLog( void );
//
//  Private Methods:
//
//  Other Associated Functions:
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.4  2003/07/19 09:17:12  houghton
// Port to 64 bit.
//
// Revision 5.3  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
// Revision 5.2  2000/05/25 17:05:46  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:16  houghton
// Changed Version Num to 5
//
// Revision 4.4  1999/11/09 11:01:33  houghton
// Added open( name, mode, prot ).
//
// Revision 4.3  1999/05/01 12:52:45  houghton
// Cleanup.
//
// Revision 4.2  1999/03/02 12:47:59  houghton
// Added getLogFileName().
// Cleanup.
//
// Revision 4.1  1997/09/17 15:12:36  houghton
// Changed to Version 4
//
// Revision 3.12  1997/09/17 11:08:30  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.11  1997/07/18 19:23:38  houghton
// Port(Sun5): had to make 'class Filter' a public member to eliminate
//     compiler errors.
//
// Revision 3.10  1997/05/02 12:16:12  houghton
// Changed all LogLevel::Level args to const & to avoid copy constructor calls.
//
// Revision 3.9  1997/04/04 20:53:31  houghton
// Added log file error checking.
// Cleanup.
//
// Revision 3.8  1997/04/04 15:06:34  houghton
// Changed default prot to 0666 for constructor.
//
// Revision 3.7  1997/04/04 03:10:28  houghton
// Changed constructors (and some other methods) to non-inline.
// Added getFilterStream
// Added getFilterLogLevel
// Added getFilterRegex
//
// Revision 3.6  1997/04/02 13:44:33  houghton
// Added getMaxSize().
// Added getTrimSize().
// Added getFilter().
//
// Revision 3.5  1997/04/01 15:09:38  houghton
// Added willOutput method that also check if any filters will output.
//
// Revision 3.4  1997/03/03 19:01:22  houghton
// Moved code for Filter class to LogBuf.ii.
// Added Filter copy constructor.
// Added Filter destructor.
// Added Filter operator =.
//
// Revision 3.3  1997/03/03 14:36:36  houghton
// Removed support for RW Tools++
//
// Revision 3.2  1996/11/19 12:21:32  houghton
// Added getLogFileName method.
//
// Revision 3.1  1996/11/14 01:23:47  houghton
// Changed to Release 3
//
// Revision 2.6  1996/11/13 16:51:11  houghton
// Changed include lines from "file" to <file"
//     to accomidate rpm.
// Changed isFile() to is_file() to be more consistant with the
//     standard filebuf::is_open().
// Added is_open() to detect if there is a valid primary stream open.
// Changed delFitler to return the streambuf that was given as
//     the filter's destination.
// Changed openLog to take an ios::open_mode arg that will be
//     or'ed (|) with the original open mode. This allows the
//     log to be appended if it was not opened with 'ios::app', but
//     it was reopened from within LogBuf.
//
// Revision 2.5  1996/11/04 14:04:07  houghton
// Restructure header comments layout.
// Added FilterId type for multiple destination support.
// Removed willOutput method (can use getLogLevel().willOutput()).
// Removed level() which provided direct modification access to the
//     LogLevel.
// Added setCurrentLevel method to change the current level.
// Added setOutputLevel method to change the output level.
// Added getLogLevel method to provide const access to the LogLevel.
// Added addFilter method to provide mutliple filtered destinations.
// Added delFilter method to remove a destination filter that is no
//     longer needed.
// Added static const badFilterId to detect a failed addFilter return.
// Changed logFileName to a RWCString instead of FilePath.
//     (as required by Mike Alexandar).
//
// Revision 2.4  1995/11/12 18:02:42  houghton
// Change LogLevel::XXXX to LogLevel::Xxxxx.
//
// Revision 2.3  1995/11/10  14:11:42  houghton
// Cleanup (move final endif)
//
// Revision 2.2  1995/11/10  14:08:37  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:45  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  15:28:39  houghton
// Revised
//
//

#endif // ! def _LogBuf_hh_ 
