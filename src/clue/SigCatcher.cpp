// 1997-04-11 (cc) Paul Houghton <paul4hough@gmail.com>

#include "SigCatcher.hpp"
#include "Str.hpp"
#include "DateTime.hpp"
#include "Clue.hpp"
#include "LibLog.hpp"

#include <algorithm>
#include <errno.h>
#include <signal.h>

static clue::SigCatcher *	self(0);

namespace clue {

extern "C"
{
  static void c_catchAction( int sig );
};

static
void
c_catchAction( int sig )
{
  if( self )
    {
      clue::SigCatcher::Caught caught( sig, time(0) );
      self->caught().push_back( caught );
    }
  else
    {
      LLgError << "SigCatcher::self not set!" << std::endl;
    }
}





const SigCatcher::Flag	    SigCatcher::None;
const SigCatcher::Flag	    SigCatcher::OnStack( SA_ONSTACK );
const SigCatcher::Flag	    SigCatcher::NoDefer( SA_NODEFER );
const SigCatcher::Flag	    SigCatcher::Restart( SA_RESTART );
const SigCatcher::Flag	    SigCatcher::Siginfo( SA_SIGINFO );

SigCatcher::CaughtQueue	    SigCatcher::caughtSigList;

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

  errStr = "SigCatcher";

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


std::ostream &
SigCatcher::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

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
	dest << prefix << "caught: " << std::setw(3) << (*them).sig()
	     << "  at: " << DateTime( (*them).when(), true ) << '\n'
	  ;
      }
  }

  return( dest );
}

}; // namespace clue
