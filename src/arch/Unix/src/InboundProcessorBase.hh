#ifndef _InboundProcessorBase_hh_
#define _InboundProcessorBase_hh_
//
// File:        InboundProcessorBase.hh
// Project:	Clue
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     07/20/97 06:21
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <ClueConfig.hh>
#include <FilePath.hh>
#include <DumpInfo.hh>
#include <iostream>

#if defined( CLUE_DEBUG )
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

  bool	    run( void );
  bool	    caughtSignal( void ) const;
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< InboundProcessorBase >
  dump( const  char * prefix = "    ", bool showVer = true ) const;
  
  static const ClassVersion version;

protected:

  virtual bool	    processInbound( const FilePath & filePath ) = 0;
  
private:

  InboundProcessorBase( const InboundProcessorBase & from );
  InboundProcessorBase & operator =( const InboundProcessorBase & from );

  bool	setError( const char * desc, const char * name = 0 );
  
  FilePath		fnPattern;
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
//  	InboundProcessorBase( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	write( ostream & dest ) const;
//	    write the data for this class in binary form to the ostream.
//
//	virtual istream &
//	read( istream & src );
//	    read the data in binary form from the istream. It is
//	    assumed it stream is correctly posistioned and the data
//	    was written to the istream with 'write( ostream & )'
//
//	virtual ostream &
//	toStream( ostream & dest ) const;
//	    output class as a string to dest (used by operator <<)
//
//	virtual istream &
//	fromStream( istream & src );
//	    Set this class be reading a string representation from
//	    src. Returns src.
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
//	static const ClassVersion version
//	    Class and project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const InboundProcessorBase & src );
//
//	istream &
//	operator >> ( istream & src, InboundProcessorBase & dest );
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// $Log$
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

