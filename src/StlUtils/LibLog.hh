#ifndef _LibLog_hh_
#define _LibLog_hh_
//
// File:        LibLog.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     03/18/96 06:22
//
// Revision History:
//
// $Id$
//
// $Log$
// Revision 5.1  2000/05/25 10:33:15  houghton
// Changed Version Num to 5
//
// Revision 4.3  1999/11/04 17:32:13  houghton
// Bug-Fix: LogIf was not changing log levels.
//
// Revision 4.2  1999/03/02 12:47:19  houghton
// Added LLgError
// Added LLgWarn
// Added LLgDebug
// Added LLgTest
// Added LLgInfo
//
// Revision 4.1  1997/09/17 15:12:29  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:25  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:23:43  houghton
// Changed to Release 3
//
// Revision 2.1  1996/04/27 13:02:04  houghton
// Initial Release.
//
//

#if !defined( STLUTILS_SHORT_FN )
#include <Log.hh>
#else
#include <Log.hh>
#endif

extern Log *	_LibLog;

#define _LLg( level_ ) 							      \
    if( _LibLog && (*_LibLog).changeCheckOutput( level_ ) )		      \
        ( (*_LibLog)( level_, __FILE__, __LINE__ ) )

#define _LLgLock    if( _LibLog ) _LibLog->lock()

#define _LLgUnLock  if( _LibLog ) _LibLog->unlock()

#define _LLgDumpInfo( class_, level_ )					      \
    if( _LibLog && (*_LibLog).changeCheckOutput( level_ ) )		      \
        class_.dumpInfo( _LibLog->level( level_ ) ).flush()

#define LLgError _LLg( LogLevel::Error )
#define LLgWarn	 _LLg( LogLevel::Warn )
#define LLgDebug _LLg( LogLevel::Debug )
#define LLgTest  _LLg( LogLevel::Test )
#define LLgInfo  _LLg( LogLevel::Info )
      
#endif // ! def _LibLog_hh_ 

