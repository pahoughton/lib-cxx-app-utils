//
// File:        InboundProcessorBase.C
// Project:	Clue
// Desc:        
//
//  Compiled sources for InboundProcessorBase
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     07/20/97 06:26
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "InboundProcessorBase.hh"
#include <Str.hh>
#include <Directory.hh>
#include <Semaphore.hh>
#include <LibLog.hh>
#include <cstdio>

#if defined( CLUE_DEBUG )
#include "InboundProcessorBase.ii"
#endif

CLUE_VERSION(
  InboundProcessorBase,
  "$Id$");


InboundProcessorBase::InboundProcessorBase(
  const char *  fileNamePattern,
  const char *  inDirName,
  const char *  procDirName,
  long		rescanWaitSecs
  )
  : fnPattern( fileNamePattern ),
    inDir( inDirName ),
    procDir( procDirName ),
    waitSecs( rescanWaitSecs )
{
}

InboundProcessorBase::~InboundProcessorBase( void )
{
}

bool
InboundProcessorBase::run( void )
{

  bool	    didit;
  FilePath  inPath( inDir, fnPattern );

  Directory	dirList;
  Semaphore	sem;
  FilePath	procFn;
  
  for( ;; )
    {
      didit = false;

      dirList.set( inPath );

      if( ! dirList.good() )
	return( setError( dirList.error(), inPath ) );

      for( Directory::iterator them = dirList.begin();
	   them != dirList.end();
	   ++ them )
	{
	  _LLg( LogLevel::Debug ) << "found: '"
				  << (*them).getName() << '\'' << endl;
	  
	  if( ! sem.create( (*them).getName() ) )
	    {
	      FileStat semStat( (*them).getName() );

	      if( semStat.good() )
		return( setError( sem.error(), (*them).getName() ) );
	      else
		break;
	    }

	  if( sem.lock( false ) )
	    {
	      _LLg( LogLevel::Debug ) << "locked: '"
				      << (*them).getName() << '\'' << endl;
	  
	      // this one is mine to process.

	      procFn = (*them).getName();
	      procFn.changePath( inDir, procDir );

	      if( rename( (*them).getName(), procFn ) )
		{
		  // rename failed.
		  
		  int renameError = errno;
		  
		  // is it because the file is nolonger there?
		  
		  FileStat  inStat( *them );
		  if( inStat.good() )
		    {
		      // nope, I can NOT move it
		      return( setError( strerror( renameError ), procFn ) );
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

		  if( ! processInbound( procFn ) )
		    return( false );

		  didit = true;
		}
	    }
	  else
	    {
	      if( ! sem.good() )
		_LLg( LogLevel::Debug ) << sem.error() << endl;
	    }
	}

      if( ! didit )
	sleep( waitSecs );
    }
  return( false );
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

  dest << prefix << "file pattern:    " << fnPattern << '\n'
       << prefix << "in dir:          " << inDir << '\n'
       << prefix << "proc dir:        " << procDir << '\n'
       << prefix << "wait secs:       " << waitSecs << '\n'
    ;
  
  return( dest );
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
// $Log$
// Revision 1.1  1997/07/20 18:52:02  houghton
// Initial Version.
//
//
