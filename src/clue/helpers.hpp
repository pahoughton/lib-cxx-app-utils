#ifndef _helpers_hpp_ // -*- c++ -*-_
#define _helpers_hpp_
// 1995-04-23 (cc) paul4hough@gmail.com

#include <clue/clue>
#include <cstdlib>

// Macros

#define static_array_size( _a_ ) ( sizeof( _a_ ) / sizeof( _a_[0] ) )

// inlines

template< class num_type >
inline
num_type
align( num_type value, size_t align_size )
{
  return( ((value % align_size) == 0) ?
	  value ? value : align_size :
	  ( value + ( align_size - ( value % align_size ) ) ) );
}

template< class num_type >
inline
num_type
align( num_type value )
{
  return( align( value, sizeof( value ) ) );
}


// t_dword_align
inline
unsigned long
dword_align( unsigned long value )
{
  return( align( value, (size_t)4 ) );
}

// t_dword_align
inline
void *
dword_align( void * addr )
{
  if( sizeof( unsigned long ) != sizeof( void * ) ) return( 0 );

  unsigned long value = (unsigned long)addr;
  return( (void *)( dword_align( value ) ) );
}


// t_mem_overlap
inline
bool
mem_overlap( const void * one, size_t len_one, const void * two, size_t len_two )
{
  const char * o = (const char *)one;
  const char * t = (const char *)two;

  return( ( ( len_one && len_two ) ?
	    ( ( o <= t ) ?
	      ( ((o + len_one)-1) >= t ) :
	      ( ((t + len_two)-1) >= o ) ) :
	    0 ) );
}


#if defined( FIXME_CLUE_HAVE_LONG_ABS )
inline
long
abs( long value )
{
  return( value < 0 ? (value * -1) : value );
}
#endif


// t_is_base_digit
inline
bool
is_base_digit( int d, unsigned short base )
{
  return( ( d >= 0 && d < base ) );
}


inline
unsigned long
union_of( long start_one, long end_one, long start_two, long end_two )
{
  if( start_two <= end_one &&
      end_two >= start_one )
    {
      return( ( (end_two - start_two) + (end_one - start_one) -
		( abs( start_one - start_two ) +
		  abs( end_two - end_one ) ) ) / 2 );
    }
  return( 0 );
}

inline
unsigned long
union_of_dur( long start_one, long dur_one, long start_two, long dur_two )
{
  return( union_of( start_one,
		   start_one + dur_one,
		   start_two,
		   start_two + dur_two ) );
}

inline
unsigned long
union_of_dur(
  unsigned long start_one,
  unsigned long dur_one,
  unsigned long start_two,
  unsigned long dur_two,
  unsigned long frequency
  )
{
  unsigned long	    union_sum = 0;

  for( unsigned long start_of_one = start_one;
       start_of_one < (start_two + dur_two );
       start_of_one += frequency )
    {
      union_sum += union_of_dur( start_of_one, dur_one, start_two, dur_two );
    }

  return( union_sum );
}

template< class num_type >
inline
num_type
round( num_type value, int factor )
{
  num_type remain = value % factor;

  if( remain < ((factor + 1) / 2) )
    {
      return( value - remain );
    }
  else
    {
      return( value + ( factor - remain ) );
    }
}

template< class num_type >
inline
num_type
round_up( num_type value, int factor  )
{
  num_type remain = value % factor;

  if( remain == 0 )
    {
      remain = factor;
    }

  return( (value - remain) + factor );
}

template< class num_type >
inline
num_type
round_down( num_type value, int factor  )
{

  num_type remain = value % factor;

  return( value - remain );
}

// Functions

int
open_flags( std::ios::open_mode open_mode );

/*
  ArraySize( array )
      Returns the number of items in an array. This will only
      work on an array who's size has been declared within
      visibility of this macro. It will NOT work with a pointer.

  int
  OpenFlags( ios::open_mode openMode )
      Returns the ios::open_mode flags converted to
      open mode flags expected by the standard 'c' open
      and create functions.
      (i.e. OpenFlags( ios::out | ios::app ) == O_WRONLY | O_APPEND )

  template< class num_type > inline
  num_type
  Align( num_type value, size_t align_size )
      If value is on an 'align_size' boundary, 'value' is returned.
      Otherwise, returns value increased to the next 'align_size'
      boundary.

  template< class num_type > inline
  num_type
  Aligh( num_type value )
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

  template< class num_type >
  inline
  num_type
  Round( num_type value, int factor )
      Return 'value' rounded to the nearest 'factor'
      (i.e. Round( 23, 5 ) == 25 ).

  tempate< class num_type >
  inline
  num_type
  RoundUp( num_type value, int factor )
      Return 'value' rounded up to the nearest 'factor'
      (i.e. Round( 22, 5 ) == 25 ).

  template< class num_type >
  inline
  num_type
  RoundDown( num_type value, int factor )
      Returns 'value' rounded down to the nearest 'factor'
      (i.e. RoundDown( 23, 5 ) == 20).

**/

#endif // ! def _helpers_hpp_
