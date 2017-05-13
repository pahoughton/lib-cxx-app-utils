#ifndef _PidFile_hh_
#define _PidFile_hh_
/* 1997-04-15 (cc) Paul Houghton <paul4hough@gmail.com>

   Create a file containing the applications pid.
*/
#include <clue/FilePath.hpp>
#include <clue/DumpInfo.hpp>
#include <iostream>

namespace clue {

class PidFile
{

public:

  PidFile( const char * fullName );
  PidFile( const char * path, const char * name, const char * ext = ".pid" );

  virtual ~PidFile( void );

  bool	    removePidFile( void );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  inline
  DumpInfo< PidFile >
  dump( const char *  prefix = "    " ) const {
    return( DumpInfo< PidFile >( *this, prefix ) );
  };

protected:

  bool	    createPidFile( void );

private:

  FilePath	fileName;
  int		osErrno;

  PidFile( const PidFile & from );
  PidFile & operator =( const PidFile & from );

};

}; // namespace clue

#endif // ! def _clue_PidFile_hpp_
