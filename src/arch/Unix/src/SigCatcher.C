//
// File:        SigCatcher.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for SigCatcher
//  
// Author:      Paul A. Houghton - (paul.houghton@mci.com)
// Created:     04/11/97 08:12
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "SigCatcher.hh"
#include <Str.hh>
#include <DateTime.hh>
#include <StlUtilsMisc.hh>
#include <LibLog.hh>
#include <_StlUtilsSignal.h>
#include <algorithm>
#include <errno.h>

#include "StrSignal.h"

#if defined( STLUTILS_DEBUG )
#include "SigCatcher.ii"
#endif

STLUTILS_VERSION(
  SigCatcher,
  "$Id$ ");

static SigCatcher *	self(0);
  
extern "C"
{
  static void c_catchAction( int sig );
};
  

const SigCatcher::Flag	    SigCatcher::None;
const SigCatcher::Flag	    SigCatcher::OnStack( SA_ONSTACK );
const SigCatcher::Flag	    SigCatcher::NoDefer( SA_NODEFER );
const SigCatcher::Flag	    SigCatcher::Restart( SA_RESTART );
const SigCatcher::Flag	    SigCatcher::Siginfo( SA_SIGINFO );
const SigCatcher::Flag	    SigCatcher::NoChildWait( SA_NOCLDWAIT );
const SigCatcher::Flag	    SigCatcher::NoChildStop( SA_NOCLDSTOP );
const SigCatcher::Flag	    SigCatcher::WaitSig( SA_WAITSIG );

SigCatcher::CaughtQueue	    SigCatcher::caughtSigList;

const char *
SigCatcher::Caught::name( void ) const
{
  return( StrSignal( sigCaught ) );
}

SigCatcher::SigCatcher( void )
  : errorNum( E_OK ),
    osErrno( 0 )
{
}

SigCatcher::SigCatcher( Signal sig )
  : errorNum( E_OK ),
    osErrno( 0 )
{
  catchSig( sig );
}

SigCatcher::SigCatcher( const SigList & catchSigList )
  : errorNum( E_OK ),
    osErrno( 0 )
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
  : errorNum( E_OK ),
    osErrno( 0 )
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
  size_type	    catchCount,
  const Signal *    ignoreSigList,
  size_type	    ignoreCount
  )
  : errorNum( E_OK ),
    osErrno( 0 )
{
  {
    for( size_type s = 0; s < catchCount; ++ s )
      {
	catchSig( catchSigList[ s ] );
      }
  }
  
  {
    for( size_type s = 0; s < ignoreCount; ++ s )
      {
	ignoreSig( ignoreSigList[ s ] );
      }
  }
}
  
SigCatcher::SigCatcher(
  const Signal *    catchSigList,
  size_type	    catchCount,
  const Signal *    ignoreSigList,
  size_type	    ignoreCount,
  const Flag	    flags
  )
  : errorNum( E_OK ),
    osErrno( 0 )
{
  {
    for( size_type s = 0; s < catchCount; ++ s )
      {
	catchSig( catchSigList[ s ], flags );
      }
  }
  
  {
    for( size_type s = 0; s < ignoreCount; ++ s )
      {
	ignoreSig( ignoreSigList[ s ] );
      }
  }
}
  
SigCatcher::~SigCatcher( void )
{
}

bool
SigCatcher::catchSig( Signal sig, const Flag & flags )
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
  
  catchSigAction.sa_handler = c_catchAction;
  catchSigAction.sa_flags = flags.to_ulong();
#if defined( AIX41 )
  catchSigAction.sa_mask.losigs = 0;
  catchSigAction.sa_mask.hisigs = 0;
#endif

  if( sigaction( sig, &catchSigAction, &oldAction ) )
    return( setError( E_CATCH, sig, ::errno ) );

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
    return( setError( E_IGNORE, sig, ::errno ) );

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

static
void
c_catchAction( int sig )
{
  if( self )
    {
      SigCatcher::Caught caught( sig, time(0) );
      self->caught().push_back( caught );
    }
  else
    {
      LLgError << "SigCatcher::self no set!" << endl;
    }
}

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.5  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.4  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.3  2000/05/31 10:51:57  houghton
// Bug-Fix: caughtSigList was not defined.
//
// Revision 5.2  2000/05/25 17:07:31  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:23  houghton
// Changed Version Num to 5
//
// Revision 4.5  1999/03/02 12:52:36  houghton
// Cleanup.
//
// Revision 4.4  1998/03/30 14:08:19  houghton
// Renamed signal variable to sigCaught to avoid name clashes with the
//     'signal' function.
//
// Revision 4.3  1998/02/13 01:24:57  houghton
// Changed include _StlUtilsSignal.h (vs signal.h).
//
// Revision 4.2  1998/02/02 15:28:14  houghton
// Changed to use StrSignal() (vs SignalStrings).
// Added support for specifying singal flags.
//
// Revision 4.1  1997/09/17 15:13:36  houghton
// Changed to Version 4
//
// Revision 3.6  1997/09/17 15:10:29  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.5  1997/09/17 11:09:24  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.4  1997/08/08 13:26:25  houghton
// Added name() to return the name of the signal.
//
// Revision 3.3  1997/04/21 12:15:54  houghton
// Bug-Fix: errorNum and osErrno initializers where missing from constructors.
//
// Revision 3.2  1997/04/21 09:57:51  houghton
// Port: include errno.h.
//
// Revision 3.1  1997/04/19 09:53:04  houghton
// Initial Version.
//
//
