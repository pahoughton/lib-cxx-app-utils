#ifndef _Compare_hh_
#define _Compare_hh_
//
// File:        Compare.hh
// Project:	StlUtils
// Desc:        
//
//  This file defines inline functions to two compare values of the
//  same type. They are all named 'compare' and return an int.
//
//  The return value is one of <0, 0 or >0 depending on the difference
//  of the arguments.
//
//  .nf
//    if a1 <  a2 then compare( a1, a2 ) <  0;
//    if a1 == a2 then compare( a1, a2 ) == 0;
//    if a1 >  a2 then compare( a1, a2 ) >  0;
//  .fn
//
//  All 'char *' functions (i.e. * **) check the actual
//  characters and not the pointers.
// 
// Author:      Paul Houghton (paul_houghton@wcom.com)
// Created:     05/01/95 9:00
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include <cstring>	// needed for strcmp calls

#if defined( _compare_h )
#error "GNU's compare.h has been include"
#else
#define _compare_h
#endif

#if defined( Compare_SCMP_ ) || defined( Compare_PSCMP_ ) || defined( Compare_NCMP_ )

#error "Interal Compare macro already defined"
#else

#define Compare_SCMP_( T1, T2 ) \
inline int compare( T1 a, T2 b) { return( strcmp( a, b ) ); }

#define Compare_PSCMP_( T1, T2 ) \
inline int compare( T1 a, T2 b ) { return( strcmp( *a, *b ) ); }

#define Compare_NCMP( T1 ) \
inline int compare( T1 a, T1 b ) { return( (a < b ) ? -1 : ( a == b ) ? 0 : 1 ); }


Compare_SCMP_( const char *, const char * );
Compare_SCMP_( const char *, char * );
Compare_SCMP_( char *, const char * );
Compare_SCMP_( char *, char * );

Compare_PSCMP_( const char * const * , const char * const * );
Compare_PSCMP_( const char * const * , const char * * );
Compare_PSCMP_( const char * const * , char * const * );
Compare_PSCMP_( const char * const * , char * * );
Compare_PSCMP_( const char * * , const char * const * );
Compare_PSCMP_( const char * * , const char * * );
Compare_PSCMP_( const char * * , char * const * );
Compare_PSCMP_( const char * * , char * * );
Compare_PSCMP_( char * const * , const char * const * );
Compare_PSCMP_( char * const * , const char * * );
Compare_PSCMP_( char * const * , char * const * );
Compare_PSCMP_( char * const * , char * * );
Compare_PSCMP_( char * * , const char * const * );
Compare_PSCMP_( char * * , const char * * );
Compare_PSCMP_( char * * , char * const * );
Compare_PSCMP_( char * * , char * * );

Compare_NCMP( char );
Compare_NCMP( short );
Compare_NCMP( int );
Compare_NCMP( long );
Compare_NCMP( float );
Compare_NCMP( double );
Compare_NCMP( unsigned char );
Compare_NCMP( unsigned short );
Compare_NCMP( unsigned int );
Compare_NCMP( unsigned long );

#undef Compare_SCMP_
#undef Compare_PSCMP_
#undef Compare_NCMP_

#endif // defined( Compare_SCMP_ ) ...

// Detail Documentation
//
//  Functions: 
// 
//	inline
//	int
//	compare( const char * one, const char * two );
//
//	inline
//	int
//	compare( const char * one, char * two );
//
//	inline
//	int
//	compare( char * one, const char * two );
//
//	inline
//	int
//	compare( char * one, char * two );
//
//	inline
//	int
//	compare( const char * const * one, const char * const * two );
//
//	inline
//	int
//	compare( const char * const * one, const char * * two );
//
//	inline
//	int
//	compare( const char * const * one, char * const * two );
//
//	inline
//	int
//	compare(const char * const * one, char * * two );
//
//	inline
//	int
//	compare(const char * * one, const char * const * two );
//
//	inline
//	int
//	compare(const char * * one, const char * * two );
//
//	inline
//	int
//	compare( const char * * one, char * const * two );
//
//	inline
//	int
//	compare( const char * * one, char * * );
//
//	inline
//	int
//	compare( char * const * one, const char * const * two );
//
//	inline
//	int
//	compare( char * const * one, const char * * two );
//
//	inline
//	int
//	compare( char * const * one, char * const * two );
//
//	inline
//	int
//	compare( char * const * one, char * * two );
//
//	inline
//	int
//	compare( char * * one, const char * const * two );
//
//	inline
//	int
//	compare( char * * one, const char * * two );
//
//	inline
//	int
//	compare( char * * one, char * const * two );
//
//	inline
//	int
//	compare( char * * one, char * * two );
//
//	inline
//	int
//	compare( char one, char two );
//
//	inline
//	int
//	compare( short one, short two );
//
//	inline
//	int
//	compare( int one, int two );
//
//	inline
//	int
//	compare( long one, long two );
//
//	inline
//	int
//	compare( float one, float two );
//
//	inline
//	int
//	compare( double one, double two );
//
//	inline
//	int
//	compare( unsigned char one, unsigned char two );
//
//	inline
//	int
//	compare( unsigned short one, unsigned short two );
//
//	inline
//	int
//	compare( unsigned int one, unsigned int two );
//
//	inline
//	int
//	compare( unsigned long one, unsigned long two );
//
// Files:
//
//  Compare.hh
//
// Documented Ver:  2.2
// Tested Ver:	    
//
// Revision Log:
//
// $Log$
// Revision 4.1  1997/09/17 15:12:13  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:11  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:23:31  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 13:33:22  houghton
// Cleanup header comments.
//
// Revision 2.3  1996/10/27 11:12:32  houghton
// Cleanup documentation.
//
// Revision 2.2  1996/04/27 12:53:36  houghton
// Removed unneeded includes.
//
// Revision 2.1  1995/11/10 12:40:23  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  14:44:25  houghton
// Ports and Version ID changes
//
//
//

/*
  Some of this code was stolen from:
  
Copyright (C) 1988 Free Software Foundation
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

#endif // ! def _Compare_hh_ 
