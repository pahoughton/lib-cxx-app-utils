#ifndef _Str_hh_
#define _Str_hh_
//
// File:        Str.hh
// Desc:        
//              
//
// Author:      Paul Houghton 2309 - (houghton@popeye)
// Created:     05/19/94 11:21
//
// Revision History:
//
// 
// $Log$
// Revision 1.2  1994/08/15 20:54:59  houghton
// Split Mapped out of mapped avl.
// Fixed a bunch of bugs.
// Fixed for ident of object modules.
// Prep for Rating QA Testing
//
// Revision 1.1  1994/06/06  13:19:45  houghton
// Lib Clue beta version used for Rating 1.0
//
//


#include <strstream.h>
  
class Str : public strstream
{

public:

  Str( void ) { };
  Str( char * buf, int bufSize, int mode );
  Str( signed char * buf, int bufSize, int mode );
  Str( unsigned char * buf, int bufSize, int mode );
  ~Str() { };

  const char *  cstr( void );

  void		reset( void );
  
protected:

private:

    Str( const Str & copyFrom );
    Str & operator=( const Str & assignFrom );

};


inline const char *
Str::cstr( void )
{
  rdbuf()->sputc(0);
  rdbuf()->seekoff( -1, ios::cur, ios::out );
  const char * cstring = str();
  rdbuf()->freeze(0);
  return( cstring );
}

inline void
Str::reset( void )
{
  rdbuf()->seekoff( 0, ios::beg, ios::out );
}  

#endif // ! def _Str_hh_ 
//
//              This software is the sole property of
// 
//                 The Williams Companies, Inc.
//                        1 Williams Center
//                          P.O. Box 2400
//        Copyright (c) 1994 by The Williams Companies, Inc.
// 
//                      All Rights Reserved.  
// 
//
