//
// File:        InboundProcessorBase.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for InboundProcessorBase
//  
// Author:      Paul Houghton - (paul.houghton@mci.com)
// Created:     07/20/97 06:26
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "InboundProcessorBase.hh"

#include <Str.hh>
#include <Directory.hh>
#include <FileOp.hh>
#include <Semaphore.hh>
#include <SigCatcher.hh>
#include <LibLog.hh>

#include <cstdio>

#include <unistd.h>

#if defined( STLUTILS_DEBUG )
#include "InboundProcessorBase.ii"
#endif

STLUTILS_VERSION(
  InboundProcessorBase,
  "$Id$ ");


InboundProcessorBase::InboundProcessorBase(
  const char *		fileNamePattern,
  const char *		inDirName,
  const char *		procDirName,
  long			rescanWaitSecs,
  const SigCatcher *	signalCatcher
  )
  : fnPattern( fileNamePattern ),
    inDir( inDirName ),
    procDir( procDirName ),
    waitSecs( rescanWaitSecs ),
    sigCatcher( signalCatcher ),
    dirScanCounter( 0 ),
    fileFoundCounter( 0 ),
    fileProcCounter( 0 )
{
  if( fnPattern.scan( "|", false ) > 1 )
    {
      for( Str::size_type p = 1; p < fnPattern.scanMatchCount(); ++ p )
	{
	  FilePath  tmp;
	  tmp.assign( fnPattern.scanMatch( p ) );
	  tmp.stripEnds( "\t \n" );
	  fnPatList.push_back( tmp );
	  LLgDebug << "looking for(" << p << "):\n"
		   << "  '" << inDir << "'\n"
		   << "  '" << tmp << "'"
		   << endl;
	}
    }
  else
    {
      fnPatList.push_back( fnPattern );
      LLgDebug << "looking for:\n"
	       << "  '" << inDir << "'\n"
	       << "  '" << fnPattern << "'"
	       << endl;
      
    }
}

InboundProcessorBase::~InboundProcessorBase( void )
{
}

bool
InboundProcessorBase::run( bool tossDups )
{

  bool	    didit;

  Directory	dirList;
  Semaphore	sem;
  
  for( ;; )
    {
      
      if( sigCatcher && sigCatcher->caught().size() )
	return( true );

      // run prescanProc before we scan the dir
      if( ! prescanProc() )
	return( true );	    // prescan wants to skip the scan
      
      didit = false;

      for( FnPatList::const_iterator patThem = fnPatList.begin();
	   patThem != fnPatList.end();
	   ++ patThem )
	{
	  FilePath  inPath( inDir, *patThem );
	  
	  dirList.set( inPath, Directory::SortTime );

	  ++ dirScanCounter;
      
	  if( ! dirList.good() )
	    return( setError( dirList.error(), inPath ) );

	  for( Directory::iterator them = dirList.begin();
	       them != dirList.end();
	       ++ them )
	    {
	      ++ fileFoundCounter;
	  
	      _LLg( LogLevel::Debug ) << "found: '"
				      << (*them).getName() << '\'' << endl;

	      if( sigCatcher && sigCatcher->caught().size() )
		return( true );
	  
	      if( ! sem.create( (*them).getName() ) )
		{
		  // maybe someone move the file
		  FileStat semStat( (*them).getName() );

		  if( semStat.good() )
		    {
		      return( setError( sem.error(), (*them).getName() ) );
		    }
		  else
		    {
		      // best rescan the dir, something has changed.
		      // lie about didit so we don't go to sleep yet.
		      didit = true;
		      break;
		    }
		}

	      if( sem.lock( false ) )
		{
		  FileOp	fileOp;
	      
		  _LLg( LogLevel::Debug ) << "locked: '"
					  << (*them).getName() << '\'' << endl;

		  FilePath	destFn( procDir,
					(*them).getName().getFileName() );
		  FileStat	destStat( destFn );
		  
		  LLgDebug << "dup check:\n   '"
			   << destStat.getName() << '\'' << endl;
		    
		  if( destStat.good() ) {
		    if( tossDups ) {
		      if( ! fileOp.remove( (*them).getName() ) ) {
			LLgError << "remove dup failed:\n"
				 << "  " << (*them).getName()
				 << endl;
			return( setError( fileOp.error(),
					  destStat.getName() ) );
		      } else {
			LLgDebug << "removed dup:\n     '"
				 << (*them).getName() << '\''
				 << endl;
		      }
		      if( ! sem.remove() )
			return( setError( sem.error() ) );
		      
		      ++ fileProcCounter;
		      didit = true;
		      continue;
		    } else {
		      LLgError << "dup input file:\n    '"
			       << '\'' << endl;
		      return( setError( "dup input file in proc dir",
					destFn ) );
		    }
		  }
	      
		  // this one is mine to process.
		  if( ! fileOp.move( (*them).getName(), procDir ) )
		    {
		      // rename failed.
		  
		      // is it because the file is nolonger there?
		  
		      FileStat  inStat( *them );
		      if( inStat.good() )
			{
			  // nope, I can NOT move it
			  return( setError( fileOp.error(),
					    fileOp.getDest().getName() ) );
			}
		      else
			{
			  break;
			}
		    }
		  else
		    {
		      // ok, the file has been moved to 'procFn'
		      if( ! sem.remove() )
			return( setError( sem.error() ) );

		      ++ fileProcCounter;
	      
		      if( ! processInbound( fileOp.getDest().getName() ) )
			return( true );

		      if( sigCatcher && sigCatcher->caught().size() )
			return( true );

		      // we just processed something, so run prescan again.
		      if( ! prescanProc() )
			return( true );
		  
		      didit = true;
		    }
		}
	      else
		{
		  if( ! sem.good() )
		    _LLg( LogLevel::Debug ) << sem.error() << endl;
		}
	    }

	}
      if( ! didit )
	sleep( waitSecs );
    }
  return( false );
}

bool
InboundProcessorBase::caughtSignal( void ) const
{
  return( sigCatcher && sigCatcher->caught().size() != 0 );
}

bool
InboundProcessorBase::good( void ) const
{
  return( errDesc.size() == 0 );
}

const char *
InboundProcessorBase::error( void ) const
{
  static Str errStr;

  errStr = InboundProcessorBase::getClassName();

  if( good() )
    {
       errStr += ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( errName.size() )
	errStr << ": '" << errName << "' - " << errDesc;
      else
	errStr << ": " << errDesc;
      
      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}

const char *
InboundProcessorBase::getClassName( void ) const
{
  return( "InboundProcessorBase" );
}

const char *
InboundProcessorBase::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
InboundProcessorBase::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << InboundProcessorBase::getClassName() << ":\n"
	 << InboundProcessorBase::getVersion() << '\n';

  if( ! InboundProcessorBase::good() )
    dest << prefix << "Error: " << InboundProcessorBase::error() << '\n';
  else
    dest << prefix << "Good" << '\n';

  dest << prefix << "file pattern:     " << fnPattern << '\n'
       << prefix << "in dir:           " << inDir << '\n'
       << prefix << "proc dir:         " << procDir << '\n'
       << prefix << "wait secs:        " << waitSecs << '\n'
       << prefix << "dir scan count:   " << dirScanCounter << '\n'
       << prefix << "file found count: " << fileFoundCounter << '\n'
       << prefix << "file proc count:  " << fileProcCounter << '\n'
    ;

  if( sigCatcher )
    {
      Str pre;
      pre = prefix;
      pre << "sigCatcher:";
      sigCatcher->dumpInfo( dest, pre, false );
    }
  
  return( dest );
}

bool
InboundProcessorBase::prescanProc( void )
{
  return( true );
}

bool
InboundProcessorBase::setError(
  const char *	desc,
  const char *  name
  )
{
  if( ! desc )
    errDesc = "";
  else
    errDesc = desc;

  if( ! name )
    errName = "";
  else
    errName = name;

  return( good() );
}

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.2  2005/03/01 21:45:32  ptpogue
// change to deal with duplicate batches
//
// Revision 6.1  2003/08/09 11:22:46  houghton
// Changed to version 6
//
// Revision 5.4  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.3  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.2  2000/12/28 01:47:40  houghton
// Added some debug output.
//
// Revision 5.1  2000/05/25 10:33:22  houghton
// Changed Version Num to 5
//
// Revision 4.6  2000/03/10 11:40:04  houghton
// Bug-Fix: strip white space from multi filename patterns.
//
// Revision 4.5  1999/10/28 14:19:44  houghton
// Added support for multiple file name patterns.
//
// Revision 4.4  1999/05/14 11:34:24  houghton
// Port(Linux): port for Gnu Libc 2
//
// Revision 4.3  1998/11/02 19:21:33  houghton
// Changed: the File class was renamed to FileOp().
//
// Revision 4.2  1998/03/11 16:09:44  houghton
// Changed to use new File class.
//
// Revision 4.1  1997/09/17 15:13:32  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:09:21  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/09/16 11:27:04  houghton
// Added prescan support (ie do 'prescan' before scanning dir and after
//     processing each file.
// Bug-Fix: changed so it does not go to sleep when the sem. was bad.
//
// Revision 3.2  1997/07/25 13:54:13  houghton
// Added caughtSignal.
//
// Revision 3.1  1997/07/25 12:26:55  houghton
// Changed version number to 3.
//
// Revision 1.2  1997/07/25 12:18:22  houghton
// Added SigCatcher support to detect signals.
// Added counters for directory scans, files found and files processed.
//
// Revision 1.1  1997/07/20 18:52:02  houghton
// Initial Version.
//
//
