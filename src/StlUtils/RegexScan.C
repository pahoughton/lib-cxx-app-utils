//
// File:        RegexScan.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     04/28/95 12:07 
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:41:00  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:41  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <climits>
extern "C" {
#include <regex.h>
};
#include "RegexScan.hh"
#include "Str.hh"
#else
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <climits>
extern "C" {
#include <regex.h>
};
#include "RxScan.hh"
#include "Str.hh"
#endif

CLUE_VERSION(
  RegexScan,
  "$Id$" );

unsigned int	RegexScan::defaultSyntax = RE_SYNTAX_POSIX_EGREP;

RegexScan::RegexScan(
  const char *	pattern,
  bool	    	fast,
  size_t    	bufSize,
  const char *	tranTable
  )
{
  buf = 0;
  reg = 0;
  re_msg = 0;
  patternString = 0;
  setPattern( defaultSyntax, pattern, fast, bufSize, tranTable );
}

RegexScan::RegexScan(
  unsigned int	reSyntax,
  const char *	pattern,
  bool	    	fast,
  size_t    	bufSize,
  const char *	tranTable
  )
{
  buf = 0;
  reg = 0;
  re_msg = 0;
  patternString = 0;
  setPattern( reSyntax, pattern, fast, bufSize, tranTable );
}

RegexScan::RegexScan( const RegexScan & exp )
{
  buf = 0;
  reg = 0;
  re_msg = 0;
  patternString = 0;
  copy( exp.buf, exp.reg, exp.patternString );
}

RegexScan::~RegexScan( void )
{
  cleanup();
}

unsigned int
RegexScan::setDefaultSyntax( unsigned int newSyntax )
{
  unsigned int old = defaultSyntax;
  defaultSyntax = newSyntax;
  return( old );
}

void
RegexScan::setPattern(
  const char *	pattern,
  bool	    	fast,
  size_t    	bufSize,
  const char *	tranTable
  )
{
  setPattern( defaultSyntax, pattern, fast, bufSize, tranTable );
}

void
RegexScan::setPattern(
  unsigned int	reSyntax,
  const char *	pattern,
  bool	    	fast,
  size_t    	bufSize,
  const char *	tranTable
  )
{
  
  unsigned int oldSyntax = re_set_syntax( reSyntax );

  cleanup();

  patternString = new char [ strlen( pattern ) + 5 ];
  strcpy( patternString, pattern );
  
  size_t    patLen = (pattern) ? strlen( pattern ) : 0;

  buf = (re_pattern_buffer *)malloc( sizeof(re_pattern_buffer) );
  memset( buf, 0, sizeof( re_pattern_buffer ) );

  reg = (re_registers *)malloc( sizeof( re_registers ) );
  memset( reg, 0, sizeof( re_registers ) );
  
  if( fast )
    buf->fastmap = (char *)malloc( 1 << CHAR_BIT );
  else
    buf->fastmap = 0;
  buf->translate = (char *)tranTable;

  buf->allocated = max( bufSize, patLen );
  buf->buffer = (unsigned char*)malloc( buf->allocated );
  if( (re_msg = re_compile_pattern( pattern, patLen, buf )) )
      return;
  if( fast )
    re_compile_fastmap( buf );

  re_set_syntax( oldSyntax );
}
  
bool
RegexScan::match(
  const char * 	str,
  size_t   	strStart,
  size_t    	strLength
  ) const
{
  if( ! good() ) return( false );
  
  size_t    strLen = (strLength == NPOS ) ? strlen( str )  : strLength;  
  
  return( re_match_2( buf, 0, 0, (char *)str,
		      strLen, strStart, reg, strLen ) != -1 );
}

bool
RegexScan::search(
  const char *	str,
  size_t  	strStart,
  size_t  	strLength
  ) const
{
  if( ! good() ) return( false );
  
  size_t    strLen = (strLength == NPOS ) ? strlen( str ) : strLength;  
  
  if( re_search_2( buf, 0, 0, (char *)str, strLen, strStart,
		   strLen, reg, strLen) >= 0 )
    {
      return( true );
    }
  else
    {
      return( false );
    }
}
  

size_t
RegexScan::matchCount( void ) const
{
  return( buf->re_nsub );
}

int
RegexScan::matchStart( unsigned short regNum ) const
{
  return( reg->start[regNum] );
}

int
RegexScan::matchLength( unsigned short regNum ) const
{
  return( reg->end[regNum] - reg->start[regNum] );
}

void
RegexScan::matchInfo( int & start, int & len, unsigned short regNum ) const
{
  start = matchStart( regNum );
  len = matchLength( regNum );
}


RegexScan &
RegexScan::operator =( const RegexScan & from )
{
  cleanup();
  copy( from.buf, from.reg, from.patternString );
  return( *this );
}

RegexScan &
RegexScan::operator =  ( const char * pattern )
{
  setPattern( pattern );
  return( *this );
}

//
// Private methods
//

void
RegexScan::copy(
  re_pattern_buffer * srcBuf,
  re_registers * srcReg,
  const char * pattern
  )
{
  patternString = new char[ strlen( pattern ) + 5 ];
  strcpy( patternString, pattern );
  
  buf = new re_pattern_buffer;
  memcpy( buf, srcBuf, sizeof( re_pattern_buffer ) );

  if( buf->allocated )
    {
      buf->buffer = (unsigned char *)malloc( buf->allocated );
      memcpy( buf->buffer, srcBuf->buffer, buf->allocated );
    }
  if( srcBuf->fastmap )
    {
      buf->fastmap = (char *)malloc( 1 << CHAR_BIT );
      memcpy( buf->fastmap, srcBuf->fastmap, (1 << CHAR_BIT) );
    }
  
  reg = new re_registers;
  reg->num_regs = srcReg->num_regs;

  if( buf->regs_allocated == REGS_REALLOCATE )
    {
      reg->start = (regoff_t*)malloc( reg->num_regs * sizeof( regoff_t ) );
      reg->end   = (regoff_t*)malloc( reg->num_regs * sizeof( regoff_t ) );
      memcpy( reg->start, srcReg->start, reg->num_regs * sizeof( regoff_t ) );
      memcpy( reg->end, srcReg->end, reg->num_regs * sizeof( regoff_t ) );
    } 
}

void
RegexScan::cleanup()
{
  if( patternString ) delete patternString;
  patternString = 0;
  
  if( buf )
    {
      if( buf->fastmap ) free( buf->fastmap );
      if( buf->allocated ) free( buf->buffer );

      if( reg )
	{
	  if( buf->regs_allocated == REGS_REALLOCATE )
	    {
	      free( reg->start );
	      free( reg->end );
	    }
	  free( reg );
	}
      free( buf );
    }
}
  

// getClassName - return the name of this class
const char *
RegexScan::getClassName( void ) const
{
  return( "RegexScan" );
}

// good - return TRUE if no detected errors
bool
RegexScan::good( void ) const
{
  return( re_msg == 0 );
}

// error - return a string describing the current state
const char *
RegexScan::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName();

  if( good() )
    {
       errStr << ": Ok";
    }
  else
    {
      errStr << ": " << re_msg;
    }

  return( errStr.cstr() );
}

ostream &
RegexScan::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
 ) const
{
  if( showVer )
    dest << RegexScan::getClassName() << ":\n"
	 << RegexScan::getVersion() << '\n';

  if( ! RegexScan::good() )
    dest << prefix << "Error: " << RegexScan::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "pattern: " << patternString << '\n';
  
  dest << '\n';

  return( dest  );
}  

const char *
RegexScan::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer) );
}
