#ifndef _LibLog_hh_
#define _LibLog_hh_
//
// File:        LibLog.hh
// Project:	StlUtils ()
// Desc:        
//
//  Provides and interface to an applications instance of the Log class
//  from within a librar source.
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     03/18/96 06:22
//
// Revision History:
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
// $Id$ 
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

