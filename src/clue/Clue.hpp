#ifndef _clue_Clue_hh_
#define _clue_Clue_hh_
// 1995-04-23 (cc) Paul Houghton - (paul4hough@gmail.com)
#include <iostream>
#include <cstdlib>

// Macros

#define ArraySize( _a_ ) ( sizeof( _a_ ) / sizeof( _a_[0] ) )

namespace clue {
// inlines

template< class NumberType >
inline
NumberType
Align( NumberType value, size_t alignSize )
{
  return( ((value % alignSize) == 0) ?
	  value ? value : alignSize:
	  ( value + ( alignSize - ( value % alignSize ) ) ) );
}

template< class NumberType >
inline
NumberType
Align( NumberType value )
{
  return( Align( value, sizeof( value ) ) );
}


// tDwordAlign
inline
unsigned long
DwordAlign( unsigned long value )
{
  return( Align( value, (size_t)4 ) );
}

// tDwordAlign
inline
void *
DwordAlign( void * addr )
{
  if( sizeof( unsigned long ) != sizeof( void * ) ) return( 0 );

  unsigned long value = (unsigned long)addr;
  return( (void *)( DwordAlign( value ) ) );
}

template< class NumType >
inline
NumType
QwordAlign( NumType value )
{
  return( Align( value, (NumType)8 ) );
}

inline
void *
QwordAlign( void * addr )
{
  unsigned long value = (unsigned long)addr;
  return( (void *)( QwordAlign( value ) ) );
}

template< class NumType >
inline
bool
Overlap( NumType startOne, NumType endOne, NumType startTwo, NumType endTwo )
{
  return( ( startOne <= endTwo && endOne >= startTwo )
	  || ( startTwo <= endOne && endTwo >= startOne ) );
}

// tMemOverlap
inline
bool
MemOverlap( const void * one, size_t lenOne, const void * two, size_t lenTwo )
{
  const char * o = (const char *)one;
  const char * t = (const char *)two;

  return( ( ( lenOne && lenTwo ) ?
	    ( ( o <= t ) ?
	      ( ((o + lenOne)-1) >= t ) :
	      ( ((t + lenTwo)-1) >= o ) ) :
	    0 ) );
}


template< class RangeType, class ValueType >
inline
bool
Between( RangeType a, RangeType b, ValueType value )
{
  return( a < b ? a <= value && value <= b : b <= value && value <= a );
}

inline
bool
IsBaseDigit( int d, unsigned short base )
{
  return( ( d >= 0 && d < base ) );
}


inline
unsigned long
UnionOf( long startOne, long endOne, long startTwo, long endTwo )
{
  if( startTwo <= endOne &&
      endTwo >= startOne )
    {
      return( ( (endTwo - startTwo) + (endOne - startOne) -
		( abs( startOne - startTwo ) +
		  abs( endTwo - endOne ) ) ) / 2 );
    }
  return( 0 );
}

inline
unsigned long
UnionOfDur( long startOne, long durOne, long startTwo, long durTwo )
{
  return( UnionOf( startOne,
		   startOne + durOne,
		   startTwo,
		   startTwo + durTwo ) );
}

inline
unsigned long
UnionOfDur(
  unsigned long startOne,
  unsigned long durOne,
  unsigned long startTwo,
  unsigned long durTwo,
  unsigned long frequency
  )
{
  unsigned long	    unionSum = 0;

  for( unsigned long startOfOne = startOne;
       startOfOne < (startTwo + durTwo );
       startOfOne += frequency )
    {
      unionSum += UnionOfDur( startOfOne, durOne, startTwo, durTwo );
    }

  return( unionSum );
}

template< class NumberType >
inline
NumberType
Round( NumberType value, int factor )
{
  NumberType remain = value % factor;

  if( value < 0 ) {
    if( abs(remain) < ((factor + 1) / 2) ) {
      return( value - remain );
    } else {
      return( value - factor - remain );
    }
  } else {
    if( remain < ((factor + 1) / 2) ) {
      return( value - remain );
    } else {
      return( value + ( factor - remain ) );
    }
  }
}

template< class NumberType >
inline
NumberType
RoundUp( NumberType value, int factor  )
{
  NumberType remain = value % factor;

  if( remain == 0 ) {
    return( value );
  } else {
    if( value < 0 ) {
      return( value - remain );
    } else {
      return( value + factor - remain );
    }
  }
}

template< class NumberType >
inline
NumberType
RoundDown( NumberType value, int factor  )
{

  NumberType remain = value % factor;
  if( remain == 0 ) {
    return( value );
  } else {
    if( value < 0 ) {
      return( value - remain - factor );
    } else {
      return( value - remain );
    }
  }
}


template< class CounterMap, class KeyType >
inline
void
IncCounter( CounterMap & map, const KeyType & key )
{
  std::pair< typename CounterMap::iterator, bool >  ins;

  ins = map.insert( CounterMap::value_type( key, 1 ) );

  if( ! ins.second )
    {
      ++ (*ins.first).second;
    }
}


// Functions

int
OpenFlags( std::ios::openmode openMode );

// drwxrwxr-x
char *
FileModeString( mode_t mode, char * str, size_t strsize );

std::string
FileModeString( mode_t mode );

std::ios::openmode
IosOpenModeFromString( const char * modeString );

const char *
IosOpenModeToString( std::ios::openmode mode );

const char *
IosSeekDirToString( std::ios::seek_dir dir );

std::ostream &
CommaNumber( std::ostream &	dest,
	     long	num,
	     size_t	width,
	     char	fill,
	     size_t	decimalPlaces = 0 );

}; // namespace clue
/*
  Macros:

	ArraySize( array )
	    Returns the number of items in an array. This will only
	    work on an array who's size has been declared within
	    visibility of this macro. It will NOT work with a pointer.

  Functions:

	int
	OpenFlags( std::ios::openmode openMode )
	    Returns the std::ios::openmode flags converted to
	    open mode flags expected by the standard 'c' open
	    and create functions.
	    (i.e. OpenFlags( std::ios::out | std::ios::app ) == O_WRONLY | O_APPEND )

	template< class NumberType > inline
	NumberType
	Align( NumberType value, size_t alignSize )
	    If value is on an 'alignSize' boundary, 'value' is returned.
	    Otherwise, returns value increased to the next 'alignSize'
	    boundary.

	template< class NumberType > inline
	NumberType
	Aligh( NumberType value )
	    If value is on an 'sizeof(value)' boundary, 'value' is returned.
	    Otherwise, returns value increased to the next 'sizeof(value)'
	    boundary.

	inline
	unsigned long
	DwordAlign( unsigned long value )
	    Returns value aligned to a dword (4 byte) value.

	inline
	void *
	DwordAlign( void * addr )
	    Returns addr aligned to a dword (4 byte) value.

	inline
	bool
	MemOverlap( const void *    one,
		    size_t	    lenOne,
		    const void *    two,
		    size_t	    lenTwo )
	    Returns true if the memory chunk at 'one' that is 'lenOne'
	    bytes long, overlaps the memory chunk at 'two' that is
	    'lenTwo' bytes long.

	template< class RangeType, class ValueType >
	inline
	bool
	Between( RangeType a, RangeType b, ValueType value );
	    Returns true if the value is between a and b. This works
	    whether a > b or b > a.

	inline
	long
	abs( long value )
	    Returns the absolute value of 'value'. (i.e. -5 is
	    converted to 5 ).

	inline
	bool
	IsBaseDigit( int d, unsigned short base )
	    Returns true if 'd' is a valid single digit in
	    the base 'base'.

	inline
	unsigned long
	UnionOf( long	startOne,
		 long	endOne,
		 long	startTwo,
		 long	endTwo )
	    Returns the quantity of overlap between the two ranges.
	    (i.e. UnionOf( 25, 50, 40, 60 ) == 10 ).


	inline
	unsigned long
	UnionOfDur( long    startOne,
		    long    durOne,
		    long    startTwo,
		    long    durTwo );
	    Returns the quantiy of overlap between the two ranges.
	    (i.e. UnionOfDur( 15, 20, 10, 10 ) == 5 ).

	inline
	unsigned long
	UnionOfDur( unsigned long    startOne,
		    unsigned long    durOne,
		    unsigned long    startTwo,
		    unsigned long    durTwo,
		    unsigned long    frequency );
	    Returns the quantity of overlap that the first range
	    has in the second range with a frequency.
	    (i.e. UnionOfDur( 10, 5, 5, 100, 10 ) == 40 );

	template< class NumberType >
	inline
	NumberType
	Round( NumberType value, int factor )
	    Return 'value' rounded to the nearest 'factor'
	    (i.e. Round( 23, 5 ) == 25 ).

	tempate< class NumberType >
	inline
	NumberType
	RoundUp( NumberType value, int factor )
	    Return 'value' rounded up to the nearest 'factor'
	    (i.e. Round( 22, 5 ) == 25 ).

	template< class NumberType >
	inline
	NumberType
	RoundDown( NumberType value, int factor )
	    Returns 'value' rounded down to the nearest 'factor'
	    (i.e. RoundDown( 23, 5 ) == 20).

	template< class CounterMap >
	inline
	void
	IncCounter( CounterMap & map, const CounterMap::key_type & key )
	    Increment a counter value for a specific key within a
	    standard 'map' container. If the key does not exisit its
	    counter value will be 1 otherwise it it incremented. This
	    template class will only work for a map who's data_type is
	    can be set to 1 and the ++ operator works as expected.
*/

#endif  // ! def _Clue_Clue_hh_
