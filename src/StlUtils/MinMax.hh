#ifndef _MinMax_hh_
#define _MinMax_hh_
//
// File:        MinMax.hh
// Desc:        
//
//  	
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/01/95 07:30
//
// Revision History:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:16  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:40  houghton
// Changed to Version 4
//
// Revision 3.1  1996/11/14 01:23:51  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:40:49  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  13:23:27  houghton
// Initaial implementation
//
//

/*
Copyright (C) 1992 Free Software Foundation
    written by Doug Lea (dl@rocky.oswego.edu)

This file is part of the GNU C++ Library.  This library is free
software; you can redistribute it and/or modify it under the terms of
the GNU Library General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your
option) any later version.  This library is distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU Library General Public License for more details.
You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#include <cstddef>

#ifdef _minmax_h
#error "GNU's minmax.h has been include"
#else
#include <algorithm>
#define _minmax_h
#endif

#if 0
// GNU's originials
#if ! defined( _minmax_h )

inline char min(char a, char b) { return (a < b)?a:b;}
inline unsigned char min(unsigned char a, unsigned char b) {return (a<b)?a:b;}

inline short min(short a, short b) {return (a < b) ?a:b;}
inline unsigned short min(unsigned short a, unsigned short b) {return (a < b)?a:b;}

inline int min(int a, int b) {return (a < b)?a:b;}
inline unsigned int min(unsigned int a, unsigned int b) {return (a < b)?a:b;}

inline long min(long a, long b) {return (a < b)?a:b;}
inline unsigned long min(unsigned long a, unsigned long b) {return (a<b)?a:b;}

inline float min(float a, float b) {return (a < b)?a:b;}

inline double min(double a, double b) {return (a < b)?a:b;}


inline char max(char a, char b) { return (a > b)?a:b;}
inline unsigned char max(unsigned char a, unsigned char b) {return (a>b)?a:b;}

inline short max(short a, short b) {return (a > b) ?a:b;}
inline unsigned short max(unsigned short a, unsigned short b) {return (a > b)?a:b;}

inline int max(int a, int b) {return (a > b)?a:b;}
inline unsigned int max(unsigned int a, unsigned int b) {return (a > b)?a:b;}

inline long max(long a, long b) {return (a > b)?a:b;}
inline unsigned long max(unsigned long a, unsigned long b) {return (a>b)?a:b;}

inline float max(float a, float b) {return (a > b)?a:b;}

inline double max(double a, double b) {return (a > b)?a:b;}

#endif

#endif

// Mix types
// WARNING - unsigned long to long may cause problems

#define _retmin_( a, b ) return( (a < b) ? a : b )

inline long min( unsigned long a, char b ) { _retmin_( a, b ); }
inline long min( unsigned long a, short b ) { _retmin_( a, b ); }
inline long min( unsigned long a, int b ) { _retmin_( a, b ); }
inline long min( unsigned long a, long b ) { _retmin_( a, b ); }
inline unsigned long min( unsigned long a, unsigned short b ) { _retmin_( a, b ); }
inline unsigned long min( unsigned long a, unsigned int b ) { _retmin_( a, b ); }

inline long min( char a, unsigned long b ) { _retmin_( a, b ); }
inline long min( short a, unsigned long b ) { _retmin_( a, b ); }
inline long min( int a, unsigned long b ) { _retmin_( a, b ); }
inline long min( long a, unsigned long b ) { _retmin_( a, b ); }
inline unsigned long min( unsigned short a, unsigned long b ) { _retmin_( a, b ); }
inline unsigned long min( unsigned int a, unsigned long b ) { _retmin_( a, b ); }

inline long min( long a, char b ) { _retmin_( a, b ); }
inline long min( long a, short b ) { _retmin_( a, b ); }
inline long min( long a, int b ) { _retmin_( a, b ); }
inline long min( long a, unsigned short b ) { _retmin_( a, b ); }
inline long min( long a, unsigned int b ) { _retmin_( a, b ); }

inline long min( char a, long b ) { _retmin_( a, b ); }
inline long min( short a, long b ) { _retmin_( a, b ); }
inline long min( int a, long b ) { _retmin_( a, b ); }
inline long min( unsigned short a, long b ) { _retmin_( a, b ); }
inline long min( unsigned int a, long b ) { _retmin_( a, b ); }

inline long min( unsigned int a, char b ) { _retmin_( a, b ); }
inline long min( unsigned int a, short b ) { _retmin_( a, b ); }
inline long min( unsigned int a, int b ) { _retmin_( a, b ); }
inline unsigned int min( unsigned int a, unsigned short b ) { _retmin_( a, b ); }

inline long min( char a, unsigned int b ) { _retmin_( a, b ); }
inline long min( short a, unsigned int b ) { _retmin_( a, b ); }
inline long min( int a, unsigned int b ) { _retmin_( a, b ); }
inline unsigned int min( unsigned short a, unsigned int b ) { _retmin_( a, b ); }

inline int min( int a, char b ) { _retmin_( a, b ); }
inline int min( int a, short b ) { _retmin_( a, b ); }
inline long min( int a, unsigned short b ) { _retmin_( a, b ); }

inline long min( unsigned short a, char b ) { _retmin_( a, b ); }
inline long min( unsigned short a, short b ) { _retmin_( a, b ); } 

inline long min( char a, unsigned short b ) { _retmin_( a, b ); } 
inline long min( short a, unsigned short b ) { _retmin_( a, b ); } 

inline short min( short a, char b ) { _retmin_( a, b ); } 
inline short min( char a, short b ) { _retmin_( a, b ); } 
#undef _retmin_

#define _retmax_( a, b ) return( (a < b) ? a : b )

inline unsigned long max( unsigned long a, char b ) { _retmax_( a, b ); }
inline unsigned long max( unsigned long a, short b ) { _retmax_( a, b ); }
inline unsigned long max( unsigned long a, int b ) { _retmax_( a, b ); }
inline unsigned long max( unsigned long a, long b ) { _retmax_( a, b ); }
inline unsigned long max( unsigned long a, unsigned short b ) { _retmax_( a, b ); }
inline unsigned long max( unsigned long a, unsigned int b ) { _retmax_( a, b ); }

inline unsigned long max( char a, unsigned long b ) { _retmax_( a, b ); }
inline unsigned long max( short a, unsigned long b ) { _retmax_( a, b ); }
inline unsigned long max( int a, unsigned long b ) { _retmax_( a, b ); }
inline unsigned long max( long a, unsigned long b ) { _retmax_( a, b ); }
inline unsigned long max( unsigned short a, unsigned long b ) { _retmax_( a, b ); }
inline unsigned long max( unsigned int a, unsigned long b ) { _retmax_( a, b ); }

inline long max( long a, char b ) { _retmax_( a, b ); }
inline long max( long a, short b ) { _retmax_( a, b ); }
inline long max( long a, int b ) { _retmax_( a, b ); }
inline unsigned long max( long a, unsigned short b ) { _retmax_( a, b ); }
inline unsigned long max( long a, unsigned int b ) { _retmax_( a, b ); }

inline long max( char a, long b ) { _retmax_( a, b ); }
inline long max( short a, long b ) { _retmax_( a, b ); }
inline long max( int a, long b ) { _retmax_( a, b ); }
inline long max( unsigned short a, long b ) { _retmax_( a, b ); }
inline unsigned long max( unsigned int a, long b ) { _retmax_( a, b ); }

inline unsigned long max( unsigned int a, char b ) { _retmax_( a, b ); }
inline unsigned long max( unsigned int a, short b ) { _retmax_( a, b ); }
inline unsigned long max( unsigned int a, int b ) { _retmax_( a, b ); }
inline unsigned int max( unsigned int a, unsigned short b ) { _retmax_( a, b ); }

inline unsigned long max( char a, unsigned int b ) { _retmax_( a, b ); }
inline unsigned long max( short a, unsigned int b ) { _retmax_( a, b ); }
inline unsigned long max( int a, unsigned int b ) { _retmax_( a, b ); }
inline unsigned int max( unsigned short a, unsigned int b ) { _retmax_( a, b ); }

inline int max( int a, char b ) { _retmax_( a, b ); }
inline int max( int a, short b ) { _retmax_( a, b ); }
inline long max( int a, unsigned short b ) { _retmax_( a, b ); }

inline long max( unsigned short a, char b ) { _retmax_( a, b ); }
inline long max( unsigned short a, short b ) { _retmax_( a, b ); } 

inline long max( char a, unsigned short b ) { _retmax_( a, b ); } 
inline long max( short a, unsigned short b ) { _retmax_( a, b ); } 

inline short max( short a, char b ) { _retmax_( a, b ); } 
inline short max( char a, short b ) { _retmax_( a, b ); } 

#undef _retmax_

#endif // ! def _MinMax_hh_ 
