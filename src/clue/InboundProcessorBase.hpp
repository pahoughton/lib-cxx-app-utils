#ifndef _InboundProcessorBase_hh_
#define _InboundProcessorBase_hh_
//
// File:        InboundProcessorBase.hh
// Project:	StlUtils ()
// Desc:        
//
//  The InboundProcessor watches an inbound directory for file
//  names that match a specified pattern. When a matching file
//  name is found, it is moved to the processing directory and
//  the pure virtual processInbound( const FilePath & fn ) method is 
//  called for the file.
//
//  The application needs to call the run() method to start watching
//  for files. It will not return unless processInbound() returns false, a
//  signal is caught (with SigCatcher) or an error occures (See
//  run() below).
//
//  Files are processed in order of oldest to newest.
//
//  Multiple applications can use the inbound processor to watch for the
//  same file names. The InboundProcessor uses semaphores to to guarantee
//  only one application will process a specific file.
//
//  Matching files are moved from the inbound directory to a
//  processing direcotry. The processInbound() method is responsible
//  for any post processing cleanup of the file. Once run() has called
//  processInbound() for a specific file, it will ignore the file.
//
// Notes:
//
//  The SigCatcher passed will NOT be deleted.
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     07/20/97 06:21
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
//  $Id$ 
//

#include <StlUtilsConfig.hh>
#include <FilePath.hh>
#include <DumpInfo.hh>
#include <iostream>

#if defined( STLUTILS_DEBUG )
#define inline
#endif

class SigCatcher;

class InboundProcessorBase
{

public:

  InboundProcessorBase( const char *    fileNamePattern,
			const char *    inDirName,
			const char *    procDirName,
			long		rescanWaitSecs,
			const SigCatcher *	sigCatcher = 0 );
  
  virtual ~InboundProcessorBase( void );

  bool		run( bool tossDups = false );

  bool		caughtSignal( void ) const;
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual std::ostream &     dumpInfo( std::ostream &	dest = std::cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< InboundProcessorBase >
  dump( const  char * prefix = "    ", bool showVer = true ) const;
  
  static const ClassVersion version;

  typedef std::vector< FilePath >	FnPatList;
  
protected:

  virtual bool	    prescanProc( void );
  virtual bool	    processInbound( const FilePath & filePath ) = 0;
  
private:

  InboundProcessorBase( const InboundProcessorBase & from );
  InboundProcessorBase & operator =( const InboundProcessorBase & from );

  bool	setError( const char * desc, const char * name = 0 );
  
  FilePath		fnPattern;
  FnPatList		fnPatList;
  
  FilePath		inDir;
  FilePath		procDir;
  long			waitSecs;

  const SigCatcher *	sigCatcher;

  long			dirScanCounter;
  long			fileFoundCounter;
  long			fileProcCounter;
  
  Str			errDesc;
  Str			errName;
  
};

#if !defined( inline )
#include <InboundProcessorBase.ii>
#else
#undef inline


#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	InboundProcessorBase	class
//
//  Constructors:
//
//  	InboundProcessorBase( const char *	    fileNamePattern,
//			      const char *	    inDirName,
//			      const char *	    procDirName,
//			      long		    rescanWaitSecs,
//			      const SigCatcher *    sigCatcher = 0 ); );
//	    Construct an InboundProcessorBase instance.
//		'fileNamePattern' is a shell style file name pattern
//		    (i.e. shell wildcards work as expeced). It should
//		    not include any directory components (i.e. '/' char).
//		    The inbound direcotry (inDir) will be search for files
//		    that match this pattern.
//		'inDirName' is the name of the directory to search for
//		    files that match 'fileNamePattern'.
//		'procDirName' is the name of a directory to move files
//		    that match 'fileNamePattern' to before the
//		    'fileProcessor' is called.
//		'rescanWaitSecs' is the number of seconds to wait (sleep)
//		    between directory scans.
//		'sigCatcher' is the applications signal catcher. It is
//		    used by the InboundProcessorBase::run() method to
//		    detect if any signals have be caught. It is NOT
//		    deleted by the destructor.
//
//  Public Interface:
//
//	bool
//	run( void )
//	    Start processing files that match 'fileNamePattern' found
//	    in the 'inDirName' directory. When a matching file name is
//	    found, it is moved to the 'procDirName' directory and the
//	    processInbound() method is called with the full name of the
//	    file (i.e. "procDirName/matchfilename"). Once processInbound()
//	    is called, the matching file is ignored and run() starts
//	    looking for another matching file in the 'inDirName' direcotry.
//
//	    Semaphore(3)s are used to guarantee only one process will
//	    get a specific file in the 'inDirName' directory. So,
//	    multiple processes can use this to wait for the same
//	    file names.
//
//	    Matching files are processed in oldest to newest order
//	    according to there modification time.
//
//	    Returns true if either processInbound() returns false, or
//	    a signal is caught by the 'sigCatcher'. 'false' is returned
//	    only when an error occures.
//
//	bool
//	caughtSignal( void ) const
//	    Returns true if a signal was caught by the 'sigCatcher'
//	    otherwise false is returned.
//
//  	virtual Bool
//  	good( void ) const;
//  	    Return true if there are no detected errors associated
//  	    with this class, otherwise false.
//
//  	virtual const char *
//  	error( void ) const;
//  	    Return a string description of the state of the class.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. InboundProcessorBase )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream & dest, const char * prefix, bool showVer );
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	inline
//	DumpInfo< InboundProcessorBase >
//	dump( const char * prefix = "    ", bool showVer = true ) const
//	    return an object that can be passed to operator << ( ostream & )
//	    which will generate the same output as 'dumpInfo'.
//
//	static const ClassVersion version
//	    Class and project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//	virtual
//	bool
//	processInbound( const FilePath & filePath ) = 0
//	    This pure virtual method is called for each file that
//	    is found in the 'inDirName' direcotry that matches
//	    'fileNamePattern'. It should return true to continue
//	    watching for files. If it returns false, the run() method
//	    will return a true.
//
// Example: See InboundProcessor( 3 )
//
// See Also:
//
//  InboundProcessor(3), FilePath(3), SigCatcher(3)
//
//  libStlUtils3/docs/design/InboundProcessorBase.txt
//
// Files:
//
//  InboundProcessorBase.hh, InboundProcessorBase.ii
//
//  libStlUtils3.a
//
// Documented Ver: 3.2
//
// Tested Ver:
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.4  2012/04/26 20:08:46  paul
// *** empty log message ***
//
// Revision 6.3  2011/12/30 23:57:32  paul
// First go at Mac gcc Port
//
// Revision 6.2  2005/03/01 21:45:32  ptpogue
// change to deal with duplicate batches
//
// Revision 6.1  2003/08/09 11:22:46  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:22  houghton
// Changed Version Num to 5
//
// Revision 4.4  1999/10/28 14:19:50  houghton
// Added support for multiple file name patterns.
//
// Revision 4.3  1998/11/02 19:21:40  houghton
// Changed: the File class was renamed to FileOp().
//
// Revision 4.2  1998/03/11 16:10:27  houghton
// Changed to use new File class.
//
// Revision 4.1  1997/09/17 15:13:33  houghton
// Changed to Version 4
//
// Revision 3.5  1997/09/17 11:09:21  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.4  1997/09/16 11:27:20  houghton
// Added prescan support (ie do 'prescan' before scanning dir and after
//     processing each file.
//
// Revision 3.3  1997/07/25 13:54:40  houghton
// Changed caughtSignal to non-inline.
//
// Revision 3.2  1997/07/25 12:55:48  houghton
// Added documentation.
//
// Revision 3.1  1997/07/25 12:26:55  houghton
// Changed version number to 3.
//
// Revision 1.2  1997/07/25 12:18:26  houghton
// Added SigCatcher support to detect signals.
// Added counters for directory scans, files found and files processed.
//
// Revision 1.1  1997/07/20 18:52:02  houghton
// Initial Version.
//
//
#endif // ! def _InboundProcessorBase_hh_ 

