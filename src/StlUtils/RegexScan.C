//
// File:        RegexScan.C
// Project:	StlUtils
// Desc:        
//
//  Compile source code for RegexScan class.
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     04/28/95 12:07 
//
// Revision History: (See end of file for Revision Log)
//

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <climits>
extern "C" {
#include "GnuRegex.h"
};
#include "RegexScan.hh"
#include "Str.hh"
#include <algorithm>


STLUTILS_VERSION(
  RegexScan,
  "$Id$" );

unsigned int	RegexScan::defaultSyntax =
#if !defined( Hpux10 )
RE_SYNTAX_POSIX_EGREP
#else
(RE_CHAR_CLASSES        | RE_CONTEXT_INDEP_ANCHORS
   | RE_CONTEXT_INDEP_OPS | RE_HAT_LISTS_NOT_NEWLINE
   | RE_NEWLINE_ALT       | RE_NO_BK_PARENS
   | RE_NO_BK_VBAR | RE_INTERVALS | RE_NO_BK_BRACES)
#endif
  ;

  
RegexScan::RegexScan(
  const char *	pattern,
  bool	    	fast,
  size_t    	bufSize,
  const char *	tranTable
  )
  : buf( 0 ),
    reg( 0 ),
    patternString( 0 ),
    re_msg( 0 )
{
  setPattern( defaultSyntax, pattern, fast, bufSize, tranTable );
}

RegexScan::RegexScan(
  unsigned int	reSyntax,
  const char *	pattern,
  bool	    	fast,
  size_t    	bufSize,
  const char *	tranTable
  )
  : buf( 0 ),
    reg( 0 ),
    patternString( 0 ),
    re_msg( 0 )
{
  setPattern( reSyntax, pattern, fast, bufSize, tranTable );
}

RegexScan::RegexScan( const RegexScan & exp )
  : buf( 0 ),
    reg( 0 ),
    patternString( 0 ),
    re_msg( 0 )
{
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

const char *
RegexScan::getPattern( void ) const
{
  return( patternString );
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
  
  unsigned int oldSyntax = GnuRe_set_syntax( reSyntax );
  
  cleanup();

  patternString = new char [ strlen( pattern ) + 5 ];
  strcpy( patternString, pattern );
  
  size_t    patLen = (pattern) ? strlen( pattern ) : 0;

  buf = (GnuRe_pattern_buffer *)malloc( sizeof(GnuRe_pattern_buffer) );
  memset( buf, 0, sizeof( GnuRe_pattern_buffer ) );

  reg = (GnuRe_registers *)malloc( sizeof( GnuRe_registers ) );
  memset( reg, 0, sizeof( GnuRe_registers ) );
  
  if( fast )
    buf->fastmap = (char *)malloc( 1 << CHAR_BIT );
  else
    buf->fastmap = 0;
  buf->translate = (char *)tranTable;

  buf->allocated = max( bufSize, patLen );
  buf->buffer = (unsigned char*)malloc( buf->allocated );
  if( (re_msg = GnuRe_compile_pattern( pattern, patLen, buf )) )
      return;
  if( fast )
    GnuRe_compile_fastmap( buf );

  GnuRe_set_syntax( oldSyntax );
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
  
  return( GnuRe_match_2( buf, 0, 0, (char *)str,
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
  
  if( GnuRe_search_2( buf, 0, 0, (char *)str, strLen, strStart,
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
RegexScan::operator = ( const RegexScan & from )
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

  errStr = getClassName();

  if( good() )
    {
       errStr += ": ok";
    }
  else
    {
      errStr += ": ";
      errStr += re_msg;
    }

  return( errStr );
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

  dest << prefix << "syntax:  " << ( buf ? buf->syntax : 0 ) << '\n'
       << prefix << "pattern: " << patternString << '\n'
    ;
    
  
  dest << '\n';

  return( dest  );
}  

const char *
RegexScan::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer) );
}

//
// Private methods
//

void
RegexScan::copy(
  GnuRe_pattern_buffer * srcBuf,
  GnuRe_registers * srcReg,
  const char * pattern
  )
{
  patternString = new char[ strlen( pattern ) + 5 ];
  strcpy( patternString, pattern );
  
  buf = (GnuRe_pattern_buffer *)malloc( sizeof(GnuRe_pattern_buffer) );
  memcpy( buf, srcBuf, sizeof( GnuRe_pattern_buffer ) );

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
  
  reg = (GnuRe_registers *)malloc( sizeof( GnuRe_registers ) );
  
  reg->num_regs = srcReg->num_regs;

  if( buf->regs_allocated == REGS_REALLOCATE )
    {
      reg->start = (GnuRegoff_t*)malloc( reg->num_regs *
					 sizeof( GnuRegoff_t ) );
      reg->end   = (GnuRegoff_t*)malloc( reg->num_regs *
					 sizeof( GnuRegoff_t ) );
      memcpy( reg->start, srcReg->start,
	      reg->num_regs * sizeof( GnuRegoff_t ) );
      memcpy( reg->end, srcReg->end,
	      reg->num_regs * sizeof( GnuRegoff_t ) );
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
      
      if( buf->allocated )
	free( buf->buffer );
      
      free( buf );
    }
}

//
// Revision Log:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:17  houghton
// Changed Version Num to 5
//
// Revision 4.3  1998/10/23 13:05:53  houghton
// Bug-Fix: 'Memory Leak' - the 'buffer' was not being free'ed.
//
// Revision 4.2  1998/07/20 11:25:29  houghton
// Port(Hpux): RE_SYNTAX_POSIX_EGREP was causing an error.
//
// Revision 4.1  1997/09/17 15:12:46  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:08:39  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/04/02 13:45:00  houghton
// Added getPattern().
//
// Revision 3.2  1997/03/03 14:37:24  houghton
// Removed support for RW Tools++.
//
// Revision 3.1  1996/11/14 01:23:55  houghton
// Changed to Release 3
//
// Revision 2.6  1996/11/13 17:01:47  houghton
// Removed support for short file names.
//
// Revision 2.5  1996/11/11 13:35:52  houghton
// Changed to use RWCString instead of strstream where possible because
//     of an inconsitancy in the public member of strstream.
//
// Revision 2.4  1996/11/04 14:27:05  houghton
// Restructure header comments layout.
//
// Revision 2.3  1996/11/04 14:24:35  houghton
// Chagned error to use strstream instead of Str.
//     (as required by Mike Alexandar).
// Reorder methods to match header.
// Change dumpInfo to output syntax.
//
// Revision 2.2  1995/11/12 18:33:01  houghton
// Changed to use GnuRegex in libCommon.
//
// Revision 2.1  1995/11/10  12:41:00  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:41  houghton
// Ports and Version ID changes
//
//

