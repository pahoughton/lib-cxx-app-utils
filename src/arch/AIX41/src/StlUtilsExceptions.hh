#ifndef _ClueExceptinos_hh_
#define _ClueExceptinos_hh_
//
// File:        Exceptinos.hh
// Desc:        
//
//
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     07/23/95 06:43
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 12:41:30  houghton
// Initial implementation of ClueExceptions
//
//
#include <ClueConfig.hh>

#define OUT_OF_RANGE( test_val, ret_val ) \
    if( (test_val) ) return( ret_val )

#define BAD_ALLOC( test_val, ret_val ) \
    if( (test_val) ) return( ret_val )

#endif // ! def _ClueExceptinos_hh_ 



