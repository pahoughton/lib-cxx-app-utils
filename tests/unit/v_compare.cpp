//
// File:        tCompare.C
// Project:	StlUtils
// Desc:        
//
//  Test for Compare functions found in Compare.hh
//
// Source Header Version: 2.3
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     10/27/96 04:08
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <climits>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <climits>
#endif

bool tCompare01( LibTest & test );
bool tCompare02( LibTest & test );

int CompCount;

bool
tCompare( LibTest & tester )
{
  CompCount = 7;
  
  TESTP( tCompare01( tester ) );
  TESTP( tCompare02( tester ) );

  return( true );
}

char 	    	CompChar[] =
{
  CHAR_MIN,  
  0,
  5,
  10,
  15,
  20,
  CHAR_MAX,
};
  
signed char 	CompSChar[] =
{
  SCHAR_MIN,
  -10
  -5,
  0,
  5,
  10,
  SCHAR_MAX,
};

unsigned char	CompUChar[] =
{
  0,
  5,
  10,
  15,
  20,
  25,
  UCHAR_MAX,
};

short	    	CompShort[] =
{
  SHRT_MIN,
  -10
  -5,
  0,
  5,
  10,
  SHRT_MAX,
};

unsigned short	CompUShort[] =
{
  0,
  5,
  10,
  15,
  20,
  25,
  USHRT_MAX,
};

int	    	CompInt[] =
{
  INT_MIN,
  -10
  -5,
  0,
  5,
  10,
  INT_MAX,
};
unsigned int	CompUInt[] =
{
  0,
  5,
  10,
  15,
  20,
  25,
  UINT_MAX,
};

long	    	CompLong[] =
{
  LONG_MIN,
  -10
  -5,
  0,
  5,
  10,
  LONG_MAX,
};

unsigned long	CompULong[] =
{
  0,
  5,
  10,
  15,
  20,
  25,
  ULONG_MAX,
};

float	    	CompFloat[] =
{
  -9999999999.99,
  -5.5,
  -0.5,
  0.0,
  0.5,
  5.5,
  9999999999.99,
};
  
double	    	CompDouble[] =
{
  -9999999999.99,
  -5.5,
  -0.5,
  0.0,
  0.5,
  5.5,
  9999999999.99,
};
  

//
// $Log$
// Revision 6.2  2011/12/30 23:57:43  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:27  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:06  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:39  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:26  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:47:08  houghton
// Added header comments.
// Changed TESTP args.
//
//
