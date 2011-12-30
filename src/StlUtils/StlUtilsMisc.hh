#ifndef _StlUtilsUtils_hh_
#define _StlUtilsUtils_hh_
//
// File:        StlUtilsMisc.hh
// Project:	StlUtils ()
// Desc:        
//
//  This is a collection of general purpose functions and
//  macros.
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     04/23/95 09:13
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
// $Id$ 
//

#include "StlUtilsConfig.hh"
#include <cstdlib>

class FilePath;

// Macros

#define ArraySize( _a_ ) ( sizeof( _a_ ) / sizeof( _a_[0] ) )

#if !defined( STLUTILS_SELF_COMPARE_IMPL )
#define STLUTILS_SELF_COMPARE_IMPL( SC_TYPE, SC_OPERATOR )		      \
inline									      \
bool									      \
SC_TYPE::operator SC_OPERATOR ( const SC_TYPE & rhs ) const		      \
{									      \
  return( compare( rhs ) SC_OPERATOR 0 );				      \
}
#endif


// Functions
int
STLUTILS_FUNCT_T
OpenFlags( ios::openmode openMode );

int
Whence( ios::seek_dir dir );

ios::openmode
IosOpenModeFromString( const char * modeString );

const char * 
IosOpenModeToString( ios::openmode mode );

const char * 
IosSeekDirToString( ios::seek_dir dir );

ostream &
CommaNumber( ostream &	dest,
	     long	num,
	     size_t	width,
	     char	fill,
	     size_t	decimalPlaces = 0 );

// See StlUtilsUtils.ii for inline Functions
#include <StlUtilsMisc.ii>


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
//	OpenFlags( ios::openmode openMode )
//	    Returns the ios::openmode flags converted to
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
//	template< class RangeType, class ValueType >
//	inline
//	bool
//	Between( RangeType a, RangeType b, ValueType value );
//	    Returns true if the value is between a and b. This works 
//	    whether a > b or b > a.
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
//	template< class CounterMap >
//	inline
//	void
//	IncCounter( CounterMap & map, const CounterMap::key_type & key )
//	    Increment a counter value for a specific key within a
//	    standard 'map' container. If the key does not exisit its
//	    counter value will be 1 otherwise it it incremented. This
//	    template class will only work for a map who's data_type is
//	    can be set to 1 and the ++ operator works as expected.
//
// Files:
//
//	StlUtilsUtils.hh, StlUtilsUtils.ii
//
// Documented Ver: 2.4
// Tested Ver: 2.4
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.5  2011/12/30 23:57:19  paul
// First go at Mac gcc Port
//
// Revision 6.4  2004/12/14 15:37:51  houghton
// Changed CommaNum to CommaNumber.
//
// Revision 6.3  2004/07/17 11:25:00  houghton
// Changed CommaNum() decimalPlaces arg to default to 0.
//
// Revision 6.2  2004/04/19 18:16:30  houghton
// Added CommaNum prototype
//
// Revision 6.1  2003/08/09 11:22:43  houghton
// Changed to version 6
//
// Revision 5.6  2003/08/09 11:20:59  houghton
// Changed ver strings.
//
// Revision 5.5  2003/07/25 12:59:01  houghton
// Removed ArchiveFile prototype .. the funtion was moved to FileTools
// project.
//
// Revision 5.4  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
// Revision 5.3  2000/06/04 17:58:05  houghton
// Updated documentation.
//
// Revision 5.2  2000/05/25 17:05:46  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:17  houghton
// Changed Version Num to 5
//
// Revision 4.4  2000/03/10 11:38:30  houghton
// Added IncCounter().
//
// Revision 4.3  1999/11/09 11:09:24  houghton
// Added ArchiveFile declaration.
//
// Revision 4.2  1999/03/02 12:48:53  houghton
// Added Between.
//
// Revision 4.1  1997/09/17 15:12:50  houghton
// Changed to Version 4
//
// Revision 3.6  1997/09/17 14:10:19  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.5  1997/09/17 11:08:42  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.4  1997/09/16 11:22:26  houghton
// Added Whence decl.
// Added IosSeekDirToString decl.
//
// Revision 3.3  1997/04/04 20:52:12  houghton
// Added IosOpenModeFromString.
// Added IosOpenModeToSting.
//
// Revision 3.2  1996/11/19 12:20:51  houghton
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
//
// Revision 3.1  1996/11/14 01:23:29  houghton
// Changed to Release 3
//
// Revision 2.5  1996/11/04 18:21:16  houghton
// Renamed StlUtils.hh to StlUtilsUtils.hh.
//
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
#endif // ! def _StlUtilsUtils_hh_ 
