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
// Revision 1.1  1995/11/05 13:23:39  houghton
// Initaial implementation
//
//

#include <ClueConfig.hh>
#include <cstddef>

char *
StripWhite( char *  	    buffer,
	    const char *    white = " \n\t\r\v\f",
	    size_t          bufSize = 0 );

const char *
StringSearch( const char *  haystack,
	      size_t        hayLen,
	      const char *  needle,
	      size_t        needleLen );

const char *
StringReverseSearch( const char *  haystack,
		     size_t        hayLen,
		     const char *  needle,
		     size_t        needleLen );

const char * 
StringCaseSearch( const char *  haystack,
		  size_t        hayLen,
		  const char *  needle,
		  size_t        needleLen );

const char * 
StringCaseReverseSearch( const char *  haystack,
			 size_t        hayLen,
			 const char *  needle,
			 size_t        needleLen );

int
StringCaseCompare( const char * one, const char * two );

int
StringCaseCompare( const char * one, const char * two, size_t len );

int
StringCaseCompare( const char * one, size_t lenOne,
		   const char * two, size_t lenTwo );


char *
StringLower( char * str, size_t len = 0 );

char *
StringUpper( char * str, size_t len = 0 );

char *
StringCapitalize( char * str, size_t len = 0 );


bool
StringToBool( bool & 	    	dest,
	      const char *  	str,
	      size_t 	    	len = 0 );

bool
StringTo( int &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
StringTo( short &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
StringTo( long &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
StringTo( float &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
StringTo( double &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
StringTo( unsigned int &    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
StringTo( unsigned short &  dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
StringTo( unsigned long &   dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = 0 );

bool
StringToBool( const char * str, size_t len = 0 );

int
StringToInt( const char * str, unsigned short base = 0, size_t len = 0 );

short
StringToShort( const char * str, unsigned short base = 0, size_t len = 0 );

long
StringToLong( const char * str, unsigned short base = 0, size_t len = 0 );

float
StringToFloat( const char * str, unsigned short base = 0, size_t len = 0 );

double
StringToDouble( const char * str, unsigned short base = 0, size_t len = 0 );

unsigned int
StringToUInt( const char * str, unsigned short base = 0, size_t len = 0 );

unsigned short
StringToUShort( const char * str, unsigned short base = 0, size_t len = 0 );

unsigned long
StringToULong( const char * str, unsigned short base = 0, size_t len = 0 );


const char *
basename( const char * fn );

char *
basename( char * fn );


#include <StringUtils.ii>


#endif // ! def _StringUtils_hh_ 

