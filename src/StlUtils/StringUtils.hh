#ifndef _StringUtils_hh_
#define _StringUtils_hh_
//
// File:        StringUtils.hh
// Desc:        
//
//
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/02/95 06:32
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:41:15  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:52  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <cstddef>
#else
#include <ClueCfg.hh>
#include <cstddef>
#endif


char *
CLUE_FUNCT_T
StripWhite( char *  	    buffer,
	    const char *    white = " \n\t\r\v\f",
	    size_t          bufSize = 0 );

const char *
CLUE_FUNCT_T
StringSearch( const char *  haystack,
	      size_t        hayLen,
	      const char *  needle,
	      size_t        needleLen );

const char *
CLUE_FUNCT_T
StringReverseSearch( const char *  haystack,
		     size_t        hayLen,
		     const char *  needle,
		     size_t        needleLen );

const char * 
CLUE_FUNCT_T
StringCaseSearch( const char *  haystack,
		  size_t        hayLen,
		  const char *  needle,
		  size_t        needleLen );

const char * 
CLUE_FUNCT_T
StringCaseReverseSearch( const char *  haystack,
			 size_t        hayLen,
			 const char *  needle,
			 size_t        needleLen );

int
CLUE_FUNCT_T
StringCaseCompare( const char * one, const char * two );

int
CLUE_FUNCT_T
StringCaseCompare( const char * one, const char * two, size_t len );

int
CLUE_FUNCT_T
StringCaseCompare( const char * one, size_t lenOne,
		   const char * two, size_t lenTwo );


char *
CLUE_FUNCT_T
StringLower( char * str, size_t len = 0 );

char *
CLUE_FUNCT_T
StringUpper( char * str, size_t len = 0 );

char *
CLUE_FUNCT_T
StringCapitalize( char * str, size_t len = 0 );


bool
CLUE_FUNCT_T
StringToBool( bool & 	    	dest,
	      const char *  	str,
	      size_t 	    	len = 0 );

bool
CLUE_FUNCT_T
StringTo( int &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
CLUE_FUNCT_T
StringTo( short &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
CLUE_FUNCT_T
StringTo( long &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
CLUE_FUNCT_T
StringTo( float &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
CLUE_FUNCT_T
StringTo( double &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
CLUE_FUNCT_T
StringTo( unsigned int &    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
CLUE_FUNCT_T
StringTo( unsigned short &  dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
CLUE_FUNCT_T
StringTo( unsigned long &   dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
CLUE_FUNCT_T
StringToBool( const char * str, size_t len = 0 );

int
CLUE_FUNCT_T
StringToInt( const char * str, unsigned short base = 0, size_t len = 0 );

short
CLUE_FUNCT_T
StringToShort( const char * str, unsigned short base = 0, size_t len = 0 );

long
CLUE_FUNCT_T
StringToLong( const char * str, unsigned short base = 0, size_t len = 0 );

float
CLUE_FUNCT_T
StringToFloat( const char * str, unsigned short base = 0, size_t len = 0 );

double
CLUE_FUNCT_T
StringToDouble( const char * str, unsigned short base = 0, size_t len = 0 );

unsigned int
CLUE_FUNCT_T
StringToUInt( const char * str, unsigned short base = 0, size_t len = 0 );

unsigned short
CLUE_FUNCT_T
StringToUShort( const char * str, unsigned short base = 0, size_t len = 0 );

unsigned long
CLUE_FUNCT_T
StringToULong( const char * str, unsigned short base = 0, size_t len = 0 );


const char *
CLUE_FUNCT_T
basename( const char * fn );

char *
CLUE_FUNCT_T
basename( char * fn );


// Methods in StringUtils.ii
//
// char * 
// SafeStrcpy( char * dest, const char * src, size_t size )
// 
// int
// CharToInt( char c )
//
// bool
// IsBaseDigit( char c, unsigned short base )
//

#if !defined( CLUE_SHORT_FN )
#include <StringUtils.ii>
#else
#include <StrUtil.ii>
#endif

#endif // ! def _StringUtils_hh_ 
