#ifndef _Compare_hh_
#define _Compare_hh_
//
// File:        Compare.hh
// Desc:        
//
//  This file defines inline functions to compare values for
//  each of the following data types:
//
//  	const char
//  	const unsigned char
//  	const int
//  	const unsigned int
//  	const short
//  	const unsigned short
//  	const long
//  	const unsigned long
//  	const double
//
//  	const char * (note: this is a string - ie uses strcmp)
//  	const unsigned char * (this is NOT a string)
//  	const int *
//  	const unsigned int *
//  	const short *
//  	const unsigned short *
//  	const long *
//  	const unsigned long *
//  	const double *
//
//  	const char ** (note: this is a string - ie uses strcmp)
//  	const char * const * (note: this is a string - ie uses strcmp)
//  	const unsigned char ** (this is NOT a string)
//  	const int **
//  	const unsigned int **
//  	const short **
//  	const unsigned short **
//  	const long **
//  	const unsigned long **
//  	const double **
//
//  	const char *** (note: this is a string - ie uses strcmp)
//  	const char * const ** (note: this is a string - ie uses strcmp)
//  	const char * const * const * (note: this is a string - ie uses strcmp)
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/31/95 14:54
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1995/02/13 16:08:33  houghton
// New Style Avl an memory management. Many New Classes
//
//

#include <string.h>

inline int Compare( const char one, const char two )
{
  return( ( one  > two ) ? 1 : ( one < two ) ? -1 : 0 );
}

inline int Compare( const unsigned char one, const unsigned char two )
{
  return( ( one  > two ) ? 1 : ( one < two ) ? -1 : 0 );
}

inline int Compare( const int one, const int two )
{
  return( ( one  > two ) ? 1 : ( one < two ) ? -1 : 0 );
}

inline int Compare( const unsigned int one, const unsigned int two )
{
  return( ( one  > two ) ? 1 : ( one < two ) ? -1 : 0 );
}

inline int Compare( const short one, const short two )
{
  return( ( one  > two ) ? 1 : ( one < two ) ? -1 : 0 );
}

inline int Compare( const unsigned short one, const unsigned short two )
{
  return( ( one  > two ) ? 1 : ( one < two ) ? -1 : 0 );
}

inline int Compare( const long one, const long two )
{
  return( ( one  > two ) ? 1 : ( one < two ) ? -1 : 0 );
}

inline int Compare( const unsigned long one, const unsigned long two )
{
  return( ( one  > two ) ? 1 : ( one < two ) ? -1 : 0 );
}

inline int Compare( const double one, const double two )
{
  return( ( one  > two ) ? 1 : ( one < two ) ? -1 : 0 );
}

//
// Now the pointers
//
inline int Compare( const char * one, const char * two )
{
  return( strcmp( one, two ) );
}

inline int Compare( const unsigned char * one, const unsigned char * two )
{
  return( Compare( *one, *two ) );
}

inline int Compare( const int * one, const int * two )
{
  return( Compare( *one, *two ) );
}	  
	  
inline int Compare( const unsigned int * one, const unsigned int * two )
{
  return( Compare( *one, *two ) );
}

inline int Compare( const short * one, const short * two )
{
  return( Compare( *one, *two ) );
}

inline int Compare( const unsigned short * one, const unsigned short * two )
{
  return( Compare( *one, *two ) );
}

inline int Compare( const long * one, const long * two )
{
  return( Compare( *one, *two ) );
}

inline int Compare( const unsigned long * one, const unsigned long * two )
{
  return( Compare( *one, *two ) );
}

inline int Compare( const double * one, const double * two )
{
  return( Compare( *one, *two ) );
}

//
// Now the indirect pointers
//
inline int Compare( const char ** one, const char ** two )
{
  return( Compare( *one, *two ) );
}

inline int Compare( const char * const * one, const char * const * two )
{
  return( Compare( *one, *two ) );
}

inline int Compare( const unsigned char ** one, const unsigned char ** two )
{
  return( Compare( **one, **two ) );
}

inline int Compare( const int ** one, const int ** two )
{
  return( Compare( **one, **two ) );
}
	  	  
inline int Compare( const unsigned int ** one, const unsigned int ** two )
{
  return( Compare( **one, **two ) );
}

inline int Compare( const short ** one, const short ** two )
{
  return( Compare( **one, **two ) );
}

inline int Compare( const unsigned short ** one, const unsigned short ** two )
{
  return( Compare( **one, **two ) );
}

inline int Compare( const long ** one, const long ** two )
{
  return( Compare( **one, **two ) );
}

inline int Compare( const unsigned long ** one, const unsigned long ** two )
{
  return( Compare( **one, **two ) );
}

inline int Compare( const double ** one, const double ** two )
{
  return( Compare( **one, **two ) );
}

//
// One more level for strings
//
inline int Compare( const char * const ** one, const char * const ** two )
{
  return( Compare( **one, **two ) );
}

inline int Compare( const char * const * const * one,
		    const char * const * const * two )
{
  return( Compare( **one, **two ) );
}







#endif // ! def _Compare_hh_ 
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
