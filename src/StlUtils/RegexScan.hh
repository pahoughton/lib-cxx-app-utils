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
// Revision 2.3  1995/11/12 18:33:05  houghton
// Changed to use GnuRegex in libCommon.
//
// Revision 2.2  1995/11/10  14:08:38  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:41:00  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:42  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include "ClueConfig.hh"
#include <stddef>
#include <iostream>
#else
#include "ClueCfg.hh"
#include <stddef>
#include <iostream>
#endif

class CLUE_CLASS_T RegexScan 
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
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
protected:

  struct GnuRe_pattern_buffer *   buf;
  struct GnuRe_registers *        reg;

  char *		patternString;
  const char * 	    	re_msg;

  void	    copy( struct GnuRe_pattern_buffer *	srcBuf,
		  struct GnuRe_registers *	srcReg,
		  const char *			pattern );

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
//  	RegexScan( const char *   pattern,
//  	    	   bool   	  fast = 0,
//  	    	   size_t    	  bufSize = 40,
//  	    	   const char *   tranTable = 0 );
//
//  	RegexScan( unsigned int   syntax,
//  	    	   const char *   pattern,
//  	    	   bool   	  fast = 0,
//  	    	   size_t    	  bufSize = 40,
//  	    	   const char *   tranTable = 0 );
//
//  	RegexScan( const RegexScan & copyFrom );
//
//  Destructors:
//
//  	virtual ~RegexScan( void );
//
//  Public Interface:
//
//  	static unsigned int
//  	setDefaultSyntax( unsigned int syntax );
//  
//  	void
//  	setPattern( const char *    pattern,
//  	    	    bool   	    fast = 0,
//  	    	    size_t 	    bufSize = 40,
//  	    	    const char *    tranTable = 0 );
//
//  	void
//  	setPattern( unsigned int    syntax,
//  	    	    const char *    pattern,
//  	    	    bool   	    fast = 0,
//  	    	    size_t 	    bufSize = 40,
//  	    	    const char *    tranTable = 0 );
//
//  	bool
//  	match( const char *     str,
//  	       size_t   	strStart = 0,
//  	       size_t   	strLen = NPOS ) const;
//
//  	bool
//  	search( const char *    str,
//  	    	size_t   	strStart = 0,
//  	    	size_t   	strLen = NPOS ) const;
//
//  	size_t
//  	matchCount( void ) const;
//
//  	int
//  	matchStart( unsigned short  regNum = 0 ) const;
//
//  	int
//  	matchLength( unsigned short regNum = 0 ) const;
//
//  	void
//  	matchInfo( int & start, int & len, unsigned short regNum = 0 ) const;
//  
//  	RegexScan &
//  	operator =  ( const RegexScan & assignFrom );
//
//  	RegexScan &
//  	operator =  ( const char * pattern );
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
