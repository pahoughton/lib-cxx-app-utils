// 1997-09-12 (cc) Paul Houghton - (paul4hough@gmail.com)

#include <iostream>

namespace clue {
const char *
IosSeekDirToString( std::ios::seek_dir dir )
{
  return( dir == std::ios::beg ? "beg" :
	  dir == std::ios::cur ? "cur" :
	  dir == std::ios::end ? "end" : "bad dir" );
}
}; // namespace clue
