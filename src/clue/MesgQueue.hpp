#ifndef _clue_MesgQueue_hh_
#define _clue_MesgQueue_hh_
/* 1998-11-06 (cc) Paul Houghton <paul4hough@gmail.com>

   an interface to the unix message queue ipc facility.
*/
#include <clue/FilePath.hpp>
#include <clue/DumpInfo.hpp>
#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>

namespace clue {

class MesgQueue
{

public:

  struct Mesg
  {
    long    mesgType;
  };

  typedef size_t	size_type;

  MesgQueue( const char *	keyFileName,
	     char		proj = ' ',
	     std::ios::openmode mode = std::ios::in,
	     bool		create = false );

  virtual ~MesgQueue( void );

  bool	send( const Mesg & mesg, size_type size );
  bool	recv( Mesg & mesg, size_type size, long type = 0 );

  size_type	getNumMesgsInQueue( void );

  bool		remove( void );

  bool			interupted( void ) const;
  bool			clearError( void );
  int			getOsErrno( void ) const;

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				       const char *	prefix = "    " ) const;

  inline DumpInfo< MesgQueue >
  dump( const char * prefix = "    " ) const {
    return( DumpInfo< MesgQueue >( *this, prefix ) );
  };

  static const key_t	badKey;

protected:

  enum ErrorNum
  {
    E_OK,
    E_FTOK,
    E_KEY_STAT,
    E_MSGGET,
    E_SEND,
    E_RECV,
    E_REMOVE,
    E_UNDEFINED
  };

  bool	setError( ErrorNum errNum, int osErr );

  FilePath  keyFileName;
  char	    keyProj;
  key_t	    key;
  int	    queueFlags;
  int	    queueId;

  ErrorNum  errorNum;
  int	    osErrno;

private:

  MesgQueue( const MesgQueue & from );
  MesgQueue & operator =( const MesgQueue & from );

};

}; // namespace clue

#endif // ! def _clue_MesgQueue_hpp_
