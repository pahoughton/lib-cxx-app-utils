// 1997-04-04 (cc) Paul Houghton - (paul4hough@gmail.com)

#include "Str.hpp"

namespace clue {

const char *
IosOpenModeToString( std::ios::openmode mode )
{
  static Str modeStr;

  modeStr = "";

  if( mode & std::ios::in )
    modeStr << "ios::in | ";

  if( mode & std::ios::out )
    modeStr << "ios::out | ";

  if( mode & std::ios::ate )
    modeStr << "ios::ate | ";

  if( mode & std::ios::app )
    modeStr << "ios::app | ";

  if( mode & std::ios::trunc )
    modeStr << "ios::trunc | ";

  if( modeStr.size() > 3 )
    modeStr.remove( modeStr.size() - 3 );

  return( modeStr.c_str() );
}

}; // namespace clue
