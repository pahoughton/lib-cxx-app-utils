#ifndef _Clue_hh_
#define _Clue_hh_
//
// File:        Clue.hh
// Desc:        
//
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     04/23/95 09:13
//
// Revision History:
//
// $Log$
// Revision 2.3  1996/04/27 12:53:11  houghton
// Rework includes.
//
// Revision 2.2  1996/03/13 11:23:57  houghton
// Bug Fix: reorder includes
//
// Revision 2.1  1995/11/10 12:40:20  houghton
// Change to Version 2
//
// Revision 1.7  1995/11/05  14:44:24  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <Common.h>
#include <cstdlib>
#else
#include <ClueCfg.hh>
#include <Common.h>
#include <cstdlib>
#endif

#include <Clue.ii>

int
CLUE_FUNCT_T
OpenFlags( ios::open_mode openMode );

#if defined( CLUE_STRPTIME )
extern "C"
char *
CLUE_FUNCT_T
strptime( char * b, const char * fmt, struct tm * t );
#endif


#endif // ! def _Clue_hh_ 
