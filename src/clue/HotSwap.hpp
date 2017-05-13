#ifndef _clue_HotSwap_hpp_
#define _clue_HotSwap_hpp_
// 1999-05-04 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/FilePath.hpp>
#include <clue/FileLock.hpp>
#include <clue/Semaphore.hpp>
#include <clue/DumpInfo.hpp>

#include <iostream>

namespace clue {

class HotSwap
{

public:

  HotSwap( const FilePath &	lockFileName,
	   std::ios::openmode	mode );

  virtual ~HotSwap( void );

  // user methods
  bool	    lock( void );
  bool	    check( void );
  bool	    waitForSwap( void );

  // swapper methods
  bool	    swapLock( void );
  bool	    swapUnLock( void );

  bool	    swap( const FilePath &  linkName,
		  const FilePath &  linkDest );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  inline DumpInfo< HotSwap >
  dump( const char * prefix = "    " ) const {
    return( DumpInfo< HotSwap >( *this, prefix ) );
  };

protected:

  enum ErrorNum
  {
    E_OK,
    E_NOT_LINK,
    E_UNDEFINED
  };

  bool	setError( int osErr, const char * desc );
  bool	setErrorDesc( int osErr, const char * desc );
  bool	setErrorFn( ErrorNum err, const char * fn );
  bool	setErrorFn( int osErr, const char * fn );
  bool	setErrorFnDesc( int osErr, const char * fn, const char * desc );

  static const char *	ErrorDesc[];

  FilePath	lockFn;
  Semaphore	sem;
  FileLock 	filelock;

  ErrorNum	errorNum;
  FilePath	errorFileName;
  Str		errorDesc;
  int		osErrno;

private:

  HotSwap( const HotSwap & from );
  HotSwap & operator =( const HotSwap & from );

};


}; // namespace clue

#endif // ! def _clue_HotSwap_hpp_
