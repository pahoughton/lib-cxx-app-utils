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
// Revision 3.1  1996/11/14 01:23:43  houghton
// Changed to Release 3
//
// Revision 2.1  1996/04/27 13:02:04  houghton
// Initial Release.
//
//

#if !defined( CLUE_SHORT_FN )
#include <Log.hh>
#else
#include <Log.hh>
#endif

extern Log *	_LibLog;

#define _LLg( level_ )							      \
    if( _LibLog && _LibLog->willOutput( level_ ) )			      \
        ( (*_LibLog)( level_, __FILE__, __LINE__ ) )

#define _LLgLock    if( _LibLog ) _LibLog->lock()

#define _LLgUnLock  if( _LibLog ) _LibLog->unlock()

#define _LLgDumpInfo( class_, level_ )					      \
    if( _LibLog && _LibLog->willOutput( level_ ) )			      \
        class_.dumpInfo( _LibLog->level( level_ ) ).flush()

#endif // ! def _LibLog_hh_ 

