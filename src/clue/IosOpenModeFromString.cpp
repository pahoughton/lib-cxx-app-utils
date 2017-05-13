// 1997-04-04 (cc) Paul Houghton - (paul4hough@gmail.com)

#include "StringUtils.hpp"
#include <iostream>

namespace clue {

std::ios::openmode
IosOpenModeFromString( const char * modeString )
{
  std::ios::openmode    mode = (std::ios::openmode)0;

  if( StringCaseSearch( modeString, NPOS, "in", NPOS ) )
    mode = (std::ios::openmode)( mode | std::ios::in);

  if( StringCaseSearch( modeString, NPOS, "out", NPOS ) )
    mode = (std::ios::openmode)( mode | std::ios::out);

  if( StringCaseSearch( modeString, NPOS, "ate", NPOS ) )
    mode = (std::ios::openmode)( mode | std::ios::ate);

  if( StringCaseSearch( modeString, NPOS, "app", NPOS ) )
    mode = (std::ios::openmode)( mode | std::ios::app);

  if( StringCaseSearch( modeString, NPOS, "trunc", NPOS ) )
    mode = (std::ios::openmode)( mode | std::ios::trunc);

  return( mode );
}

}; // namespace clue
