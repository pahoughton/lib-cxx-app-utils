#ifndef _Compare_hh_
#define _Compare_hh_
//
// File:        Compare.hh
// Desc:        
//
//  This file defines inline functions to compare values
//
//      int compare( number, number )
//      int compare( char, char )
//      int compare( signed char, signed char )
//      int compare( unsigned char, unsigned char )
//      int compare( short, short )
//      int compare( unsigned short, unsigned short )
//      int compare( int, int )
//      int compare( unsigned int, unsigned int )
//      int compare( long, long )
//      int compare( unsigned long, unsigned long )
//      int compare( float, float )
//      int compare( double, double )
//      int compare( char *, char * );
//      int compare( char *, const char * )
//      int compare( const char *, char * )
//      int compare( char **, char ** )
//      int compare( char **, const char ** )
//      int compare( char **, char * const * )
//      int compare( char **, const char * const * )
//      int compare( const char **, char ** )
//      int compare( const char **, const char ** )
//      int compare( const char **, char * const * )
//      int compare( const char **, const char * const * )
//      int compare( char * const *, char ** )
//      int compare( char * const *, const char ** )
//      int compare( char * const *, char * const * )
//      int compare( char * const *, const char * const * )
//      int compare( const char * const *, char ** )
//      int compare( const char * const *, const char ** )
//      int compare( const char * const *, char * const * )
//      int compare( const char * const *, const char * const * )
//
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     05/01/95 9:00
//
// Revision History:
//
// 
// $Log$
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

/* 
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
