// 1995-05-14 (cc) Paul Houghton <paul4hough@gmail.com>


#include "Clue.hpp"
#include <iostream>
#include <fcntl.h>

namespace clue {

int
OpenFlags( std::ios::openmode openMode )
{
  int flags = 0;
  int mode = openMode;

  if( mode & (std::ios::app) )
    mode |= std::ios::out;

  if( (mode & (std::ios::in|std::ios::out)) == (std::ios::in|std::ios::out)) {
    flags = O_RDWR;

  } else if( (mode & (std::ios::in|std::ios::out)) == std::ios::in ) {
    flags = O_RDONLY;

  } else if( (mode & (std::ios::in|std::ios::out)) == std::ios::out ) {
    flags = O_WRONLY;

  }

  if( mode & std::ios::trunc)
    flags |= O_TRUNC;

  if( mode & std::ios::app )
    flags |= O_APPEND;

  return( flags );
}

}; // namespace clue
