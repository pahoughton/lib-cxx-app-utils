#ifndef _RegexScan_hh_
#define _RegexScan_hh_
//
// File:        RegexScan.hh
// Desc:        
//
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     04/28/95 11:20
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:29  houghton
// Initaial implementation
//
//

#include "ClueConfig.hh"

#include <stddef>

class ostream;

class RegexScan 
{

public:

  RegexScan( const char *   pattern,
	     bool   	    fast = 0,
	     size_t    	    bufSize = 40,
	     const char *   tranTable = 0 );

  RegexScan( unsigned int   syntax,
	     const char *   pattern,
	     bool   	    fast = 0,
	     size_t    	    bufSize = 40,
	     const char *   tranTable = 0 );

  RegexScan( const RegexScan & copyFrom );
  
  virtual ~RegexScan( void );

  static unsigned int	setDefaultSyntax( unsigned int syntax );
  
  void 	    setPattern( const char *    pattern,
			bool   	    	fast = 0,
			size_t 	    	bufSize = 40,
			const char *    tranTable = 0 );

  void 	    setPattern( unsigned int	syntax,
			const char *    pattern,
			bool   	    	fast = 0,
			size_t 	    	bufSize = 40,
			const char *    tranTable = 0 );

  bool	    match( const char *     str,
		   size_t   	    strStart = 0,
		   size_t   	    strLen = NPOS ) const;

  bool 	    search( const char *    str,
		    size_t   	    strStart = 0,
		    size_t   	    strLen = NPOS ) const;

  // these are for \(...\) registers (1 to 9)
  // regNum 0 == the entire pattern, the first \(.\) is regNum 1
  
  size_t    matchCount( void ) const;
  int	    matchStart( unsigned short  regNum = 0 ) const;
  int	    matchLength( unsigned short regNum = 0 ) const;
  void 	    matchInfo( int & start, int & len, unsigned short regNum = 0 ) const;
  
  RegexScan &   operator =  ( const RegexScan & assignFrom );
  RegexScan & 	operator =  ( const char * pattern );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream & 	dumpInfo( ostream & dest ) const;
  
  static const char version[];
  
protected:

  struct re_pattern_buffer *   buf;
  struct re_registers *        reg;
  
  const char * 	    	re_msg;

  void	    copy( struct re_pattern_buffer * srcBuf,
		  struct re_registers * srcReg );

  void 	    cleanup();
  
private:

  static unsigned int defaultSyntax;  // defaults is RE_SYNTAX_POSIX_EGREP 

};


//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	RegexScan	class
//
//  Constructors:
//
//  	RegexScan( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. RegexScan )
//
//  	virtual Bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const RegexScan & obj );
//
#endif // ! def _RegexScan_hh_ 
