#ifndef _Clue_hh_
#define _Clue_hh_
//
// File:        Clue.hh
// Project:	Clue
// Desc:        
//
//  This is a collection of general purpose functions and
//  macros.
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     04/23/95 09:13
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <cstdlib>
#else
#include <ClueCfg.hh>
#include <cstdlib>
#endif


// Macros

#define ArraySize( _a_ ) ( sizeof( _a_ ) / sizeof( _a_[0] ) )

// Functions
int
CLUE_FUNCT_T
OpenFlags( ios::open_mode openMode );

// See Clue.ii for inline Functions
#include <Clue.ii>


//
// Detail Documentation:
//
//  Macros:
//
//	ArraySize( array )
//	    Returns the number of items in an array. This will only
//	    work on an array who's size has been declared within
//	    visibility of this macro. It will NOT work with a pointer.
//
//  Functions:
//
//	int
//	OpenFlags( ios::open_mode openMode )
//	    Returns the ios::open_mode flags converted to
//	    open mode flags expected by the standard 'c' open
//	    and create functions.
//	    (i.e. OpenFlags( ios::out | ios::app ) == O_WRONLY | O_APPEND )
//
//	template< class NumberType > inline
//	NumberType
//	Align( NumberType value, size_t alignSize )
//	    If value is on an 'alignSize' boundary, 'value' is returned.
//	    Otherwise, returns value increased to the next 'alignSize'
//	    boundary.
//
//	template< class NumberType > inline
//	NumberType
//	Aligh( NumberType value )
//	    If value is on an 'sizeof(value)' boundary, 'value' is returned.
//	    Otherwise, returns value increased to the next 'sizeof(value)'
//	    boundary.
//
//	inline
//	unsigned long
//	DwordAlign( unsigned long value )
//	    Returns value aligned to a dword (4 byte) value.
//
//	inline
//	void *
//	DwordAlign( void * addr )
//	    Returns addr aligned to a dword (4 byte) value.
//
//	inline
//	bool
//	MemOverlap( const void *    one,
//		    size_t	    lenOne,
//		    const void *    two,
//		    size_t	    lenTwo )
//	    Returns true if the memory chunk at 'one' that is 'lenOne'
//	    bytes long, overlaps the memory chunk at 'two' that is
//	    'lenTwo' bytes long.
//
//	inline
//	long
//	abs( long value )
//	    Returns the absolute value of 'value'. (i.e. -5 is
//	    converted to 5 ).
//
//	inline
//	bool
//	IsBaseDigit( int d, unsigned short base )
//	    Returns true if 'd' is a valid single digit in
//	    the base 'base'.
//
//	inline
//	unsigned long
//	UnionOf( long	startOne,
//		 long	endOne,
//		 long	startTwo,
//		 long	endTwo )
//	    Returns the quantity of overlap between the two ranges.
//	    (i.e. UnionOf( 25, 50, 40, 60 ) == 10 ).
//
//
//	inline
//	unsigned long
//	UnionOfDur( long    startOne,
//		    long    durOne,
//		    long    startTwo,
//		    long    durTwo );
//	    Returns the quantiy of overlap between the two ranges.
//	    (i.e. UnionOfDur( 15, 20, 10, 10 ) == 5 ).
//
//	inline
//	unsigned long
//	UnionOfDur( unsigned long    startOne,
//		    unsigned long    durOne,
//		    unsigned long    startTwo,
//		    unsigned long    durTwo,
//		    unsigned long    frequency );
//	    Returns the quantity of overlap that the first range
//	    has in the second range with a frequency.
//	    (i.e. UnionOfDur( 10, 5, 5, 100, 10 ) == 40 );
//
//	template< class NumberType >
//	inline
//	NumberType
//	Round( NumberType value, int factor )
//	    Return 'value' rounded to the nearest 'factor'
//	    (i.e. Round( 23, 5 ) == 25 ).
//
//	tempate< class NumberType >
//	inline
//	NumberType
//	RoundUp( NumberType value, int factor )
//	    Return 'value' rounded up to the nearest 'factor'
//	    (i.e. Round( 22, 5 ) == 25 ).
//
//	template< class NumberType >
//	inline
//	NumberType
//	RoundDown( NumberType value, int factor )
//	    Returns 'value' rounded down to the nearest 'factor'
//	    (i.e. RoundDown( 23, 5 ) == 20).
//
// Files:
//
//	Clue.hh, Clue.ii
//
// Documented Ver: 2.4
// Tested Ver: 2.4
//
// Revision Log:
//
// $Log$
// Revision 2.4  1996/11/04 13:29:32  houghton
// Restructure header comments layout.
// Updated and verified header comment documentation.
//
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
#endif // ! def _Clue_hh_ 
