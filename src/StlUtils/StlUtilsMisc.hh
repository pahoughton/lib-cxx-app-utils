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
// Revision 1.7  1995/11/05 14:44:24  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <Clue.ii>
#include <StringUtils.hh>
#include <iostream>
#else
#include <ClueCfg.hh>
#include <Clue.ii>
#include <StrUtil.hh>
#include <iostream>
#endif

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
