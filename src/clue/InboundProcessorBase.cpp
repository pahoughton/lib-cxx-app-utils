// 1997-07-20 (cc) Paul Houghton <paul4hough@gmail.com>

#include "InboundProcessorBase.hpp"
#include "Str.hpp"
#include "Directory.hpp"
#include "FileOp.hpp"
#include "Semaphore.hpp"
#include "SigCatcher.hpp"
#include "LibLog.hpp"

#include <cstdio>

#include <unistd.h>

namespace clue {

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
		   << std::endl;
	}
    }
  else
    {
      fnPatList.push_back( fnPattern );
      LLgDebug << "looking for:\n"
	       << "  '" << inDir << "'\n"
	       << "  '" << fnPattern << "'"
	       << std::endl;

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
				      << (*them).getName() << '\'' << std::endl;

	      if( sigCatcher && sigCatcher->caught().size() )
		return( true );

	      {
		char semPrj = 1;
		bool reScan( false );
		for( ; semPrj < CHAR_MAX; ++ semPrj ) {

		  if( ! sem.create( (*them).getName(), semPrj ) ) {
		    // maybe someone move the file
		    FileStat semStat( (*them).getName() );

		    if( ! semStat.good() ) {
		      // best rescan the dir, something has changed.
		      // lie about didit so we don't go to sleep yet.
		      LLgDebug << "file moved:\n"
			       << (*them).getName()
			       << std::endl;
		      didit = true;
		      reScan = true;
		      break;
		    }
		    LLgDebug << "sem failed retrying (prj "
			     << (int) semPrj
			     << ')'
			     << std::endl;
		    // else try w/ diff semPrj
		  } else {
		    // sem created
		    break;
		  }
		}

		if( reScan )
		  break;
	      }

	      if( ! sem.good() )
		return( setError( sem.error(), (*them).getName() ) );

	      if( sem.lock( false ) )
		{
		  FileOp	fileOp;

		  LLgDebug << "locked: '"
			   << (*them).getName() << '\'' << std::endl;

		  FilePath	destFn( procDir,
					(*them).getName().getFileName() );
		  FileStat	destStat( destFn );

		  LLgDebug << "dup check:\n   '"
			   << destStat.getName() << '\'' << std::endl;

		  if( destStat.good() ) {
		    if( tossDups ) {
		      if( ! fileOp.remove( (*them).getName() ) ) {
			LLgError << "remove dup failed:\n"
				 << "  " << (*them).getName()
				 << std::endl;
			return( setError( fileOp.error(),
					  destStat.getName() ) );
		      } else {
			LLgDebug << "removed dup:\n     '"
				 << (*them).getName() << '\''
				 << std::endl;
		      }
		      if( ! sem.remove() )
			return( setError( sem.error() ) );

		      ++ fileProcCounter;
		      didit = true;
		      continue;
		    } else {
		      LLgError << "dup input file:\n    '"
			       << '\'' << std::endl;
		      return( setError( "dup input file in proc dir",
					destFn ) );
		    }
		  }

		  // this one is mine to process.
		  if( ! fileOp.move( (*them).getName().c_str(),
				     procDir.c_str() ) )
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
		    _LLg( LogLevel::Debug ) << sem.error() << std::endl;
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

  errStr = "InboundProcessorBase";

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


std::ostream &
InboundProcessorBase::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

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
      sigCatcher->dumpInfo( dest, pre );
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

}; // namespace clue
