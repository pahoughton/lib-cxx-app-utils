#ifndef _LogBuf_hh_
#define _LogBuf_hh_
//
// File:        LogBuf.hh
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 12:32
//
// Revision History:
//
// 
// $Log$
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

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <LogLevel.hh>
#include <FilePath.hh>
#include <iostream>
#include <fstream>
#else
#include <ClueCfg.hh>
#include <LogLvl.hh>
#include <FilePath.hh>
#include <iostream>
#include <fstream>
#endif


#if defined( CLUE_DEBUG )
#define inline
#endif

class LogBuf : public streambuf
{
  
public:
  
  inline LogBuf( LogLevel::Level   outLevel,
		 streambuf * 	   outStream );

  inline LogBuf( const char * 	outLevel,
		 streambuf * 	outStream );

  inline LogBuf( const char *	    fileName,
		 LogLevel::Level    outLevel = LogLevel::Error, 
		 ios::open_mode	    mode = ios::app,
		 int		    prot = filebuf::openprot,
		 size_t		    maxSize = 0,
		 size_t		    trimSize = 0 );
  
  inline LogBuf( const char *	    fileName,
		 const char *	    outLevel,
		 ios::open_mode	    mode = ios::app,
		 int		    prot = filebuf::openprot,
		 size_t		    maxSize = 0,

		 size_t		    trimSize = 0 );
  
  virtual ~LogBuf( void );

  inline bool		willOutput( LogLevel::Level outputLevel ) const;

  
  inline streambuf *	tee( streambuf * teeStreambuf );
  filebuf *		open( const char *	name,
			      ios::open_mode    mode,
			      int	        prot = filebuf::openprot,
			      size_t	        maxSize = 0,
			      size_t	        trimSize = 0 );
  
  void			close (void);

  size_t		trim( size_t maxSize = 0 );
  inline size_t	        setMaxSize( size_t maxSize );
  inline size_t		setTrimSize( size_t trimSize );
  
  inline bool		isFile( void ) const;
  
  inline LogLevel &	   level( void );
  inline const LogLevel &  level( void ) const;

  virtual int	    overflow(int=EOF);
  virtual int	    underflow();
  virtual int	    sync() ;

  virtual const char *  getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
protected:
  
private:

  void initLogBuffer( void );
  void initbuf( streambuf * outStream );
  void initbuf( const char * fn,
		ios::open_mode mode,
		int prot,
		size_t m,
		size_t t );
  

  filebuf *	openLog( void );
  size_t	trimLog( size_t curSize, size_t maxLogSize );
  void		closeLog( void );
  
  FilePath	    logFileName;
  size_t	    maxSize;
  size_t	    trimSize;
  ios::open_mode    openMode;
  int		    openProt;
  bool		    streamIsFile;
  
  char *    	buffer;
  streambuf *	stream;
  streambuf * 	teeStream;
  
  LogLevel 	logLevel;
  
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

#endif // ! def _LogBuf_hh_ 
