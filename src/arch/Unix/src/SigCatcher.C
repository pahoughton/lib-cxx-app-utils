//
// File:        SigCatcher.C
// Project:	Clue
// Desc:        
//
//  Compiled sources for SigCatcher
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     04/11/97 08:12
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "SigCatcher.hh"
#include <Str.hh>
#include <DateTime.hh>
#include <LibLog.hh>
#include <algorithm>
#include <signal.h>

#if defined( CLUE_DEBUG )
#include "SigCatcher.ii"
#endif

CLUE_VERSION(
  SigCatcher,
  "$Id$");

SigCatcher *	SigCatcher::self = 0;

SigCatcher::SigCatcher( void )
{
}

SigCatcher::SigCatcher( Signal sig )
{
  catchSig( sig );
}

SigCatcher::SigCatcher( const SigList & catchSigList )
{
  for( SigList::const_iterator them = catchSigList.begin();
       them != catchSigList.end();
       ++ them )
    {
      catchSig( *them );
    }
}

SigCatcher::SigCatcher(
  const SigList & catchSigList,
  const SigList & ignoreSigList
  )
{
  {
    for( SigList::const_iterator them = catchSigList.begin();
	 them != catchSigList.end();
	 ++ them )
      {
	catchSig( *them );
      }
  }

  {
    for( SigList::const_iterator them = ignoreSigList.begin();
	 them != ignoreSigList.end();
	 ++ them )
      {
	ignoreSig( *them );
      }
  }
}

SigCatcher::SigCatcher(
  const Signal *    catchSigList,
  size_t	    catchCount,
  const Signal *    ignoreSigList,
  size_t	    ignoreCount
  )
{
  {
    for( size_t s = 0; s < catchCount; ++ s )
      {
	catchSig( catchSigList[ s ] );
      }
  }
  
  {
    for( size_t s = 0; s < ignoreCount; ++ s )
      {
	ignoreSig( ignoreSigList[ s ] );
      }
  }
}
  
SigCatcher::~SigCatcher( void )
{
}

bool
SigCatcher::catchSig( Signal sig )
{
  if( ! self )
   self = this;

  if( self && self != this )
    return( setError( E_SELF, 0, 0 ) );
  
  SigList::iterator found = find( catchList.begin(),
				  catchList.end(),
				  sig );

  // already in catchList
  if( found != catchList.end() )
    return( true );

  struct sigaction catchSigAction;
  struct sigaction oldAction;
  
  catchSigAction.sa_handler = (void (*)(int))catchAction;
  catchSigAction.sa_flags = SA_RESTART;
#if defined( AIX41 )
  catchSigAction.sa_mask.losigs = 0;
  catchSigAction.sa_mask.hisigs = 0;
#endif

  if( sigaction( sig, &catchSigAction, &oldAction ) )
    return( setError( E_CATCH, sig, errno ) );

  return( true );
}

bool
SigCatcher::ignoreSig( Signal sig )
{
  if( ! self )
   self = this;

  if( self && self != this )
    return( setError( E_SELF, 0, 0 ) );
  
  SigList::iterator found = find( ignoreList.begin(),
				  ignoreList.end(),
				  sig );

  // already in catchList
  if( found != ignoreList.end() )
    return( true );

  struct sigaction catchSigAction;
  struct sigaction oldAction;
  
  catchSigAction.sa_handler = SIG_IGN;
  catchSigAction.sa_flags = SA_RESTART;
#if defined( AIX41 )
  catchSigAction.sa_mask.losigs = 0;
  catchSigAction.sa_mask.hisigs = 0;
#endif

  if( sigaction( sig, &catchSigAction, &oldAction ) )
    return( setError( E_IGNORE, sig, errno ) );

  return( true );
}
  
  
  
bool
SigCatcher::good( void ) const
{
  return( errorNum == E_OK );
}

const char *
SigCatcher::error( void ) const
{
  static Str errStr;

  errStr = SigCatcher::getClassName();

  if( good() )
    {
      errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      switch( errorNum )
	{
	case E_SELF:
	  errStr << ": self already set, only on instance allowed!";
	  break;

	case E_CATCH:
	case E_IGNORE:
	  
	  errStr << ( errorNum == E_CATCH ?
		      ": setting handler to catch" :
		      errorNum == E_IGNORE ?
		      ": setting handler to ignore" : ": " )
		 << " signal: " << errorSig
		 << " " << strerror( osErrno );
	  break;

	default:
	  break;
	}
      
      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}

const char *
SigCatcher::getClassName( void ) const
{
  return( "SigCatcher" );
}

const char *
SigCatcher::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
SigCatcher::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << SigCatcher::getClassName() << ":\n"
	 << SigCatcher::getVersion() << '\n';

  if( ! SigCatcher::good() )
    dest << prefix << "Error: " << SigCatcher::error() << '\n';
  else
    dest << prefix << "Good" << '\n';

  {
    for( SigList::const_iterator them = ignoreList.begin();
	 them != ignoreList.end();
	 ++ them )
      dest << prefix << "ignore signal:      " << (*them) << '\n';
  }
  
  {
    for( SigList::const_iterator them = catchList.begin();
	 them != catchList.end();
	 ++ them )
      dest << prefix << "catch signal:       " << (*them) << '\n';
  }

  {
    for( CaughtQueue::const_iterator them = caughtSigList.begin();
	 them != caughtSigList.end();
	 ++ them )
      {
	dest << prefix << "caught: " << setw(3) << (*them).sig()
	     << "  at: " << DateTime( (*them).when(), true ) << '\n'
	  ;
      }
  }
  
  
  return( dest );
}

void
SigCatcher::catchAction(
  int			sig,
  int			CLUE_UNUSED( code ),
  struct sigcontext *	CLUE_UNUSED( context )
  )
{
  if( ! SigCatcher::self )
    {
      _LLg( LogLevel::Error )
	<< "SigCatcher::self no set!" << endl;
    }

  Caught caught( sig, time(0) );
  SigCatcher::self->caughtSigList.push_back( caught );
}

// Revision Log:
//
// $Log$
// Revision 3.1  1997/04/19 09:53:04  houghton
// Initial Version.
//
//
