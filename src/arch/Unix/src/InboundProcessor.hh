#ifndef _InboundProcessor_hh_
#define _InboundProcessor_hh_
//
// File:        InboundProcessor.hh
// Project:	StlUtils
// Desc:        
//
//  The InboundProcessor watches an inbound directory for file
//  names that match a specified pattern. When a matching file
//  name is found, it is moved to the processing directory and
//  the Proc::operator () ( const FilePath & fn ) method is 
//  called for the file.
//
//  The application needs to call run() method (from InboundProcessorBase)
//  to start watching for files. It will not return unless the Proc
//  returns false, a signal is caught (with SigCatcher) or an
//  error occures (See InboundProcessorBase::run()).
//
//  Files are processed in order of oldest to newest.
//
//  Multiple applications an use the inbound processor to watch for the
//  same file names. The InboundProcessor uses semaphores to to guarantee
//  only one application will process a specific file.
//
//  Matching files are moved from the inbound directory to a processing
//  direcotry. The 'Proc' is responsible for any post processing cleanup
//  of the file. Once the InboundProcessor has called 'Proc' for a
//  specific file, it will ignore the file.
//
// Notes:
//
//  Most of the functionallity is provided by InboundProcessorBase
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     07/20/97 06:10
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <StlUtilsConfig.hh>
#include <InboundProcessorBase.hh>

class SigCatcher;

class IbpDefaultPreScan
{
public:
  inline bool	operator () ( void ) {
    return( true );
  };
};

template< class Proc, class PreScan >
class InboundProcessor : public InboundProcessorBase
{

public:

  InboundProcessor( const char *    fileNamePattern,
		    const char *    inDirName,
		    const char *    procDirName,
		    long	    rescanWaitSecs,
		    Proc &	    fileProccessor,
		    PreScan &	    prescanProcessor );

  InboundProcessor( const char *	fileNamePattern,
		    const char *	inDirName,
		    const char *	procDirName,
		    long		rescanWaitSecs,
		    const SigCatcher *	sigCatcher,
		    Proc &		fileProccessor,
		    PreScan &		prescanProcessor );

  virtual ~InboundProcessor( void ) {};

protected:

  inline bool	    processInbound( const FilePath & filePath ) {
    return( proc( filePath ) );
  };
  
  inline bool	    prescanProc( void ) {
    return( prescan() );
  };
  
private:

  // InboundProcessor( const InboundProcessor & from );
  // InboundProcessor & operator =( const InboundProcessor & from );

  Proc &    proc;
  PreScan & prescan;
  
};

#include <InboundProcessor.ii>


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	InboundProcessor	class
//
//	Proc: template arg.
//	    Proc needs to be a class (or struct) that has an
//	    operator () method that matches:
//
//		bool operator () ( const FilePath & fn );
//
//	    This method will be called for each file that matches
//	    the file name pattern. 
//
//	PreScan: template arg.
//	    PreScan needs to be a class (or struct) that has an
//	    opreator () method that matches:
//
//		bool operator () ( void );
//
//	    This method will be called before each directory scan and after
//	    each call to 'Proc'. If returns false, run() will return true. If
//	    it returns true, run will keep processing.
//
//  Constructors:
//
//  	InboundProcessor( const char *    fileNamePattern,
//			  const char *    inDirName,
//			  const char *    procDirName,
//			  long		  rescanWaitSecs,
//			  Proc &	  fileProccessor );
//	    Construct an InboundProcessor instance.
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
//		'fileProcessor' is the object that will process the files
//		    that have been moved to the 'procDirName'.
//
//  	InboundProcessor( const char *		fileNamePattern,
//			  const char *		inDirName,
//			  const char *		procDirName,
//			  long			rescanWaitSecs,
//			  const SigCatcher *	sigCatcher,
//			  Proc &		fileProccessor );
//	    Construct an InboundProcessor instance.
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
//		'fileProcessor' is the object that will process the files
//		    that have been moved to the 'procDirName'.
//
//  Public Interface: See InboundProcessorBase
//
// Example:
//	
//	
//	class FileProc
//	{
//	public:
//	
//	  inline bool	operator () ( const FilePath & fn ) {
//	    cout << "processing: " << fn << endl;
//	  };
//	};
//	
//	SigCatcher  signals;
//	
//	FileProc	    fileProc;
//	IbpDefaultPreScan   prescan;
//
//	InboundProcessor< FileProc, IbpDefaultPreScan >
//	    ibp( "*.rdy",
//		 "/prj/data/in",
//		 "/prj/data/proc",
//		 5,
//		 &signals,
//		 fileProc,
//		 prescan );
//	
//	while( ibp.run() )
//	{
//	  if( signals.caught().size() )
//	    {
//	      cout << "some signal was caught" << endl;
//	      signals.reset();
//	    }
//	
//	  if( ! fileProc.good() )
//	    {
//	      cout << fileProc.error() << endl;
//	      break;
//	    }
//	}
//	
//	if( ! ibp.good() )
//	{
//	  cout << ibp.error() << endl;
//	}
//					     
//	  
// See Also:
//
//  InboundProcessorBase(3), FilePath(3), SigCatcher(3)
//
//  libStlUtils3/docs/design/InboundProcessor.txt
//  libStlUtils3/docs/design/InboundProcessorBase.txt
//
// Files:
//
//  InboundProcessor.hh, InboundProcessor.ii
//  InboundProcessorBase.hh, InboundProcessorBase.ii
//  FilePath.hh
//
//  libStlUtils3.a
//
// Documented Ver: 3.1
//
// Tested Ver:
//
// Revision Log:
//
// $Log$
// Revision 3.3  1997/09/17 11:09:19  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/09/16 11:26:04  houghton
// Added prescan support (ie do 'prescan' before scanning dir and after
//     processing each file.
//
// Revision 3.1  1997/07/25 12:05:46  houghton
// Added constructor that takes a SigCatcher.
// Added documentation.
// Changed version number to 3.
//
// Revision 1.1  1997/07/20 18:52:01  houghton
// Initial Version.
//
//
#endif // ! def _InboundProcessor_hh_ 

