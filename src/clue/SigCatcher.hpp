#ifndef _clue_SigCatcher_hpp_
#define _clue_SigCatcher_hpp_
// 1997-04-11 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/Bitmask.hpp>
#include <vector>
#include <deque>
#include <iostream>
#include <ctime>

namespace clue {

class SigCatcher
{

public:

  typedef int			Signal;
  typedef std::vector< Signal >	SigList;
  typedef SigList::size_type	size_type;

  typedef Bitmask Flag;

  static const Flag	None;
  static const Flag	OnStack;
  static const Flag	NoDefer;
  static const Flag	Restart;
  static const Flag	Siginfo;

  class Caught
  {
  public:
    inline Caught( void );
    inline Caught( SigCatcher::Signal caughtSig, time_t timeCaught );

    inline ~Caught(void) {};

    inline SigCatcher::Signal   sig( void ) const;
    inline time_t		when( void ) const;

    inline bool			operator == ( const Caught & rhs ) const;

  private:

    SigCatcher::Signal	sigCaught;
    time_t		whenCaught;
  };

  typedef std::deque< Caught >   CaughtQueue;

  SigCatcher( void );
  SigCatcher( Signal catchSig );
  SigCatcher( const SigList & catchSigList );
  SigCatcher( const SigList & catchSigList, const SigList & ignoreSigList );
  SigCatcher( const Signal *	catchSigList,
	      size_type		catchCount,
	      const Signal *	ignoreSigList = 0,
	      size_type		ignCount = 0 );
  SigCatcher( const Signal *	catchSigList,
	      size_type		catchCount,
	      const Signal *	ignoreSigList,
	      size_type		ignCount,
	      const Flag	flags );

  virtual ~SigCatcher( void );

  inline CaughtQueue &		caught( void );
  inline const CaughtQueue &	caught( void ) const;

  inline bool	    caught( Signal sig ) const;

  inline bool	    catchSig( Signal sig );
  bool		    catchSig( Signal sig, const Flag & flags );
  bool		    ignoreSig( Signal sig );


  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

protected:

  enum ErrorNum
  {
    E_OK,
    E_SELF,
    E_CATCH,
    E_IGNORE,
    E_UNDEFINED
  };

  inline bool	setError( ErrorNum err, Signal errSig, int osErr );

private:

  SigCatcher( const SigCatcher & from );
  SigCatcher & operator =( const SigCatcher & from );

  SigList	catchList;
  SigList	ignoreList;

  static CaughtQueue   caughtSigList;

  ErrorNum	errorNum;
  Signal	errorSig;
  int		osErrno;

};

inline
SigCatcher::Caught::Caught( void )
  : sigCaught( 0 ),
    whenCaught( 0 )
{
}

inline
SigCatcher::Caught::Caught( SigCatcher::Signal caughtSig, time_t timeCaught )
  : sigCaught( caughtSig ),
    whenCaught( timeCaught )
{
}

inline
SigCatcher::Signal
SigCatcher::Caught::sig( void ) const
{
  return( sigCaught );
}

inline
time_t
SigCatcher::Caught::when( void ) const
{
  return( whenCaught );
}

inline
bool
SigCatcher::Caught::operator == ( const Caught & rhs ) const
{
  return( sigCaught == rhs.sigCaught && whenCaught == rhs.whenCaught );
}

inline
SigCatcher::CaughtQueue &
SigCatcher::caught( void )
{
  return( caughtSigList );
}

inline
const SigCatcher::CaughtQueue &
SigCatcher::caught( void ) const
{
  return( caughtSigList );
}

inline
bool
SigCatcher::caught( Signal sig ) const
{
  for( CaughtQueue::const_iterator them = caughtSigList.begin();
       them != caughtSigList.end();
       ++ them )
    {
      if( (*them).sig() == sig )
	return( true );
    }
  return( false );
}

inline
bool
SigCatcher::catchSig( Signal sig )
{
  return( catchSig( sig, None ) );
}

inline
bool
SigCatcher::setError(
  ErrorNum	err,
  Signal	errSig,
  int		osErr
  )
{
  errorNum = err;
  errorSig = errSig;
  osErrno = osErr;
  return( good() );
}

}; // namespace clue
#endif // ! def _SigCatcher_hh_
