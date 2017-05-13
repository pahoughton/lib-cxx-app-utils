#ifndef _clue_LibLog_hpp_
#define _clue_LibLog_hpp_
/* 1996-03-18 (cc) Paul Houghton <paul4hough@gmail.com>

   Provides and interface to an applications instance of the Log class
  from within library sources.
*/

#include <clue/Log.hpp>

namespace clue {
  extern Log *	_clueLibLog;
};

#define _LLg( level_ ) 							      \
    if( _clueLibLog && (*_clueLibLog).changeCheckOutput( level_ ) )	      \
        ( (*_clueLibLog)( level_, __FILE__, __LINE__ ) )

#define _LLgLock    if( _clueLibLog ) _clueLibLog->lock()

#define _LLgUnLock  if( _clueLibLog ) _clueLibLog->unlock()

#define _LLgDumpInfo( class_, level_ )					      \
    if( _clueLibLog && (*_clueLibLog).changeCheckOutput( level_ ) )	      \
        class_.dumpInfo( _clueLibLog->level( level_ ) ).flush()

#define LLgError _LLg( LogLevel::Error )
#define LLgWarn	 _LLg( LogLevel::Warn )
#define LLgDebug _LLg( LogLevel::Debug )
#define LLgTest  _LLg( LogLevel::Test )
#define LLgInfo  _LLg( LogLevel::Info )

#endif // ! def _clue_LibLog_hpp_
