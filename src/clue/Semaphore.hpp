#ifndef _clue_Semaphore_hpp_
#define _clue_Semaphore_hpp_
// 1997-06-10 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/DumpInfo.hpp>

#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>

namespace clue {

class Semaphore
{

public:

  Semaphore( void );

  Semaphore( key_t  semKey,
	     int    numSems = 1,
	     int    flags = (IPC_CREAT | IPC_EXCL | 0664 ) );

  Semaphore( const char *   keyPath,
	     char	    proj = ' ',
	     int	    numSems = 1,
	     int	    flags = ( IPC_EXCL | 0664) );

  virtual ~Semaphore( void );

  bool	    create( key_t   semKey,
		    int	    numSems = 1,
		    int	    flags = (IPC_CREAT | IPC_EXCL | 0664) );

  bool	    create( const char *    keyPath,
		    char	    proj = ' ',
		    int		    numSems = 1,
		    int		    flags = (IPC_CREAT | IPC_EXCL | 0664) );

  bool	    open( key_t semKey, int numSems = 1 );
  bool	    open( const char * keyPath, char proj = ' ', int numSems = 1 );

  bool	    remove( void );

  bool	    lock( bool wait = true );
  bool	    unlock( void );
  bool	    islocked( void ) const;

  bool	    waitfor( void );

  inline bool	wouldBlock( void ) const;

  bool		clear( void );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;
  static const key_t	badKey;
  static const int	badSem;

  inline DumpInfo< Semaphore >
  dump( const char * prefix = "    " ) const {
    return( DumpInfo< Semaphore >( *this, prefix ) );
  };
protected:

  inline bool	setError( int err );

private:

  Semaphore( const Semaphore & from );
  Semaphore & operator =( const Semaphore & from );

  key_t	    key;
  int	    semId;

  int	    osErrno;
};


inline
bool
Semaphore::wouldBlock( void ) const
{
  return( osErrno == EAGAIN );
}

inline
bool
Semaphore::setError( int err )
{
  osErrno = err;
  return( good() );
}


}; // namespace clue
#endif // ! def _clue_Semaphore_hpp_
