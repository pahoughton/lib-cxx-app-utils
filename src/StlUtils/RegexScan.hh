#ifndef _RegexScan_hh_
#define _RegexScan_hh_
//
// File:        RegexScan.hh
// Project:	StlUtils ()
// Desc:        
//
//  Regular expresion pattern matcher. This is a wrapper
//  around Gnu's regex 'c' functions. The following description
//  is specific to the default syntax of RE_SYNTAX_EGREP.
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     04/28/95 11:20
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
// $Id$ 
//

#include "StlUtilsConfig.hh"
#include <cstddef>

class Str;

class STLUTILS_CLASS_T RegexScan 
{

public:

  RegexScan( const char *   pattern,
	     bool   	    fast = false,
	     size_t    	    bufSize = 40,
	     const char *   tranTable = 0 );

  RegexScan( unsigned int   syntax,
	     const char *   pattern,
	     bool   	    fast = false,
	     size_t    	    bufSize = 40,
	     const char *   tranTable = 0 );

  RegexScan( const RegexScan & copyFrom );
  
  virtual ~RegexScan( void );

  static unsigned int	setDefaultSyntax( unsigned int syntax );

  const char *	getPattern( void ) const;
  
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

  static void	EscapeSpecialChars( Str & str );
  
  // these are for \(...\) registers (1 to 9)
  // regNum 0 == the entire pattern, the first \(.\) is regNum 1
  
  size_t    matchCount( void ) const;
  ssize_t   matchStart( unsigned short  regNum = 0 ) const;
  ssize_t   matchLength( unsigned short regNum = 0 ) const;
  void 	    matchInfo( ssize_t &	start,
		       ssize_t &	len,
		       unsigned short	regNum = 0 ) const;
  
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

//
// Types: - data types defined by this header
//
//	class RegexScan
//
// Usage:
//
//  A Regular expression  pattern is a sequence of special and
//  ordinary characters. An ordinary character is a simple regular
//  expression which matches that character and nothing else. The special
//  characters are `.', `*', `+', `?', `[', `]', `$', `^', '\', '|'
//  '(', ')', and '{', '}'.
//  
//	`.'	    is a special character that matches anything
//		    except a newline.  Using concatenation, we can
//		    make regular expressions like `a.b' which matches
//		    any three-character string which begins with `a'
//		    and ends with `b'.
//
//	`*'	    is not a construct by itself; it is a suffix,
//		    which means the preceding regular expression is to
//		    be repeated as many times as possible.  In `fo*',
//		    the `*' applies to the `o', so `fo*' matches `f'
//		    followed by any number of `o''s.
//
//		    The case of zero `o''s is allowed: `fo*' does
//		    match `f'.
//
//		    `*' always applies to the *smallest* possible
//		    preceding expression.  Thus, `fo*' has a repeating
//		    `o', not a repeating `fo'.
//
//		    The matcher processes a `*' construct by matching,
//		    immediately, as many repetitions as can be found.
//		    Then it continues with the rest of the pattern.
//		    If that fails, backtracking occurs, discarding
//		    some of the matches of the `*''d construct in case
//		    that makes it possible to match the rest of the
//		    pattern.  For example, matching `c[ad]*ar' against
//		    the string `caddaar', the `[ad]*' first matches
//		    `addaa', but this does not allow the next `a' in
//		    the pattern to match.  So the last of the matches
//		    of `[ad]' is undone and the following `a' is tried
//		    again.  Now it succeeds.
//
//	`+'	    `+' is like `*' except that at least one match for
//		    the preceding pattern is required for `+'.  Thus,
//		    `c[ad]+r' does not match `cr' but does match
//		    anything else that `c[ad]*r' would match.
//
//	`?'	    `?' is like `*' except that it allows either zero
//		    or one match for the preceding pattern.  Thus,
//		    `c[ad]?r' matches `cr' or `car' or `cdr', and
//		    nothing else.
//
//	`[ ... ]'  `[' begins a "character set", which is terminated
//		    by a `]'.  In the simplest case, the characters
//		    between the two form the set.  Thus, `[ad]'
//		    matches either `a' or `d', and `[ad]*' matches any
//		    string of `a''s and `d''s (including the empty
//		    string), from which it follows that `c[ad]*r'
//		    matches `car', etc.
//
//		    Character ranges can also be included in a
//		    character set, by writing two characters with a
//		    `-' between them.  Thus, `[a-z]' matches any
//		    lower-case letter.  Ranges may be intermixed
//		    freely with individual characters, as in
//		    `[a-z$%.]', which matches any lower case letter or
//		    `$', `%' or period.
//
//		    Note that the usual special characters are not
//		    special any more inside a character set.  A
//		    completely different set of special characters
//		    exists inside character sets: `]', `-' and `^'.
//
//		    To include a `]' in a character set, you must make
//		    it the first character.  For example, `[]a]'
//		    matches `]' or `a'.  To include a `-', you must
//		    use it in a context where it cannot possibly
//		    indicate a range: that is, as the first character,
//		    or immediately after a range.
//
//		    Finally, certain named classes of characters are
//		    predefined.  Their names are self explanatory, and
//		    they are [:alpha:], [:upper:], [:lower:],
//		    [:digit:], [:alnum:], [:xdigit:], [:space:],
//		    [:blank:], [:print:], [:punct:], [:graph:], and
//		    [:cntrl:]. Note, this construct is only availabe
//		    inside a '[ ... ]'. Example
//		    "[[:lower:][:digit:]]+" is the same as "[a-z0-9]"
//
//	`[^ ... ]'  `[^' begins a "complement character set", which
//		    matches any character except the ones specified.
//		    Thus, `[^a-z0-9A-Z]' matches all characters
//		    *except* letters and digits.
//
//		    `^' is not special in a character set unless it is
//		    the first character.  The character following the
//		    `^' is treated as if it were first (it may be a
//		    `-' or a `]').
//
//	`^'	    is a special character that matches the empty
//		    string -- but only if at the beginning of a line
//		    in the text being matched.  Otherwise it fails to
//		    match anything.  Thus, `^foo' matches a `foo'
//		    which occurs at the beginning of a line.
//
//	`$'	    is similar to `^' but matches only at the end of a
//		    line.  Thus, `xx*$' matches a string of one or
//		    more `x''s at the end of a line.
//
//	`\'	    has two functions: it quotes the above special
//		    characters (including `\'), and it introduces
//		    additional special constructs.
//
//		    Because `\' quotes special characters, `\$' is a
//		    regular expression which matches only `$', and
//		    `\[' is a regular expression which matches only
//		    `[', and so on.
//
//		    For the most part, `\' followed by any character
//		    matches only that character.  However, there are
//		    several exceptions: characters which, when
//		    preceded by `\', are special constructs.  Such
//		    characters are always ordinary when encountered on
//		    their own.
//
//		    No new special characters will ever be defined.
//		    All extensions to the regular expression syntax
//		    are made by defining new two-character constructs
//		    that begin with `\'.
//
//	`|'	    specifies an alternative.  Two regular expressions
//		    A and B with `|' in between form an expression
//		    that matches anything that either A or B will
//		    match.
//
//		    Thus, `foo|bar' matches either `foo' or `bar' but
//		    no other string.
//
//		    `|' applies to the largest possible surrounding
//		    expressions.  Only a surrounding `( ... )'
//		    grouping can limit the grouping power of `|'.
//
//		    Full backtracking capability exists when multiple
//		    `|''s are used.
//
//	`()'
//
//		    is a grouping construct that serves three
//		    purposes:
//
//		    1. To enclose a set of `|' alternatives for other
//		       operations. Thus, `(foo|bar)x' matches either
//		       `foox' or `barx'.
//
//		    2. To enclose a complicated expression for the
//		       postfix `*' to operate on.  Thus, `ba(na)*'
//		       matches `bananana', etc., with any (zero or more)
//		       number of `na''s.
//
//		    3. To mark a matched substring for future
//			reference.
//
//		    This last application is not a consequence of the
//		    idea of a parenthetical grouping; it is a separate
//		    feature which happens to be assigned as a second
//		    meaning to the same `( ... )' construct because
//		    there is no conflict in practice between the two
//		    meanings.
//
//	`\DIGIT'    After the end of a `( ... )' construct, the
//		    matcher remembers the beginning and end of the
//		    text matched by that construct.  Then, later on in
//		    the regular expression, you can use `\' followed
//		    by DIGIT to mean "match the same text matched the
//		    DIGIT'th time by the `( ... )' construct."  The `(
//		    ... )' constructs are numbered in order of
//		    commencement in the regexp.
//
//		    The strings matching the first nine `( ... )'
//		    constructs appearing in a regular expression are
//		    assigned numbers 1 through 9 in order of their
//		    beginnings.  `\1' through `\9' may be used to
//		    refer to the text matched by the corresponding `(
//		    ... )' construct.
//
//		    For example, `(.*)\1' matches any string that is
//		    composed of two identical halves.  The `(.*)'
//		    matches the first half, which may be anything, but
//		    the `\1' that follows must match the same exact
//		    text.
//
//	'{}'	    specifies the number of times to match the
//		    preceding item.  There are 4 valid forms.
//
//		      1. {n}   match exactly n times.
//		      2. {n,}  match n or more times.
//		      3. {,m}  match 0 to m times.
//		      4. {n,m} match n to m times.
//
//		    For example, `ab{2,4}c' will only match `abbc',
//		    `abbbc' and `abbbbc'.
//
//	`\b'	    matches the empty string, but only if it is at the
//		    beginning or end of a word.  Thus, `\bfoo\b'
//		    matches any occurrence of `foo' as a separate
//		    word.  `\bball\(s\|\)\b' matches `ball' or `balls'
//		    as a separate word.
//
//	`\B'	    matches the empty string, provided it is *not* at
//		    the beginning or end of a word.
//
//	`\<'	    matches the empty string, but only if it is at the
//		    beginning of a word.
//
//	`\>'	    matches the empty string, but only if it is at the
//		    end of a word.
//
//	`\w'	    matches any word-constituent character.
//
//	`\W'	    matches any character that is not a word-constituent.
//
// Constructors:
//
//  	RegexScan( const char *   pattern,
//  	    	   bool   	  fast = false,
//  	    	   size_t    	  bufSize = 40,
//  	    	   const char *   tranTable = 0 );
//	    Contruct a regex from 'pattern'. If 'fast' is true, a fastmap
//	    will be compiled. 'bufSize' is the size of the inital allocation
//	    for the pattern buffer. The 'tranTable' is a block of 256
//	    bytes that is used to  translate characters before they are
//	    compared.
//
//  	RegexScan( unsigned int   syntax,
//  	    	   const char *   pattern,
//  	    	   bool   	  fast = 0,
//  	    	   size_t    	  bufSize = 40,
//  	    	   const char *   tranTable = 0 );
//	    Contruct a regex from 'pattern' using the specified 'sytax'.
//	    The 'syntax' must be one of the RE_SYNTAX defines from
//	    GnuRegex.h (see setDefaultSyntax below for more info).
//	    If 'fast' is true, a fastmap will be compiled. 'bufSize'
//	    is the size of the inital allocation for the pattern
//	    buffer. The 'tranTable' is a block of 256 bytes that is
//	    used to  translate characters before they are compared.
//
//  	RegexScan( const RegexScan & copyFrom );
//	    Copy constructor. Uses copyFrom to initalize the RegexScan.
//
//  Public Interface:
//
//  	static
//	unsigned int
//  	setDefaultSyntax( unsigned int syntax );
//	    Set the sytax for the regular expression. This is a global
//	    parameter that changes the meaning of the special characters
//	    in the pattern. The following are the available values from
//	    GnuRegex.h (See GnuRegex.h for details).
//	    The default value is RE_SYNTAX_EGREP. The previous syntax
//	    is returned.
//
//		RE_SYNTAX_EMACS
//		RE_SYNTAX_AWK
//		RE_SYNTAX_POSIX_AWK
//		RE_SYNTAX_GREP
//		RE_SYNTAX_EGREP
//		RE_SYNTAX_POSIX_EGREP
//		RE_SYNTAX_ED
//		RE_SYNTAX_SED
//		RE_SYNTAX_POSIX_BASIC
//		RE_SYNTAX_POSIX_MINIMAL_BASIC
//		RE_SYNTAX_POSIX_EXTENDED
//		RE_SYNTAX_POSIX_MINIMAL_EXTENDED
//
//  	void
//  	setPattern( const char *    pattern,
//  	    	    bool   	    fast = 0,
//  	    	    size_t 	    bufSize = 40,
//  	    	    const char *    tranTable = 0 );
//	    Change the regex to use 'pattern'. If 'fast' is true, a fastmap
//	    will be compiled. 'bufSize' is the size of the inital allocation
//	    for the pattern buffer. The 'tranTable' is a block of 256
//	    bytes that is used to  translate characters before they are
//	    compared.
//
//	    
//  	void
//  	setPattern( unsigned int    syntax,
//  	    	    const char *    pattern,
//  	    	    bool   	    fast = 0,
//  	    	    size_t 	    bufSize = 40,
//  	    	    const char *    tranTable = 0 );
//	    Change the regex to use 'pattern' and the specified 'sytax'.
//	    The 'syntax' must be one of the RE_SYNTAX defines from
//	    GnuRegex.h (see setDefaultSyntax below for more info).
//	    If 'fast' is true, a fastmap will be compiled. 'bufSize'
//	    is the size of the inital allocation for the pattern
//	    buffer. The 'tranTable' is a block of 256 bytes that is
//	    used to  translate characters before they are compared.
//
//  	bool
//  	match( const char *     str,
//  	       size_t   	strStart = 0,
//  	       size_t   	strLen = NPOS ) const;
//	    Tries to match 'str' with the pattern, starting at 'strStart'
//	    for 'strLen' chars. This only attempts to match starting
//	    with the first char of str and strStart. Returns true
//	    if the str matches otherwise false. Additional information
//	    about a match is provided by matchCount(), matchStart(),
//	    matchLength() and matchInfo() (see below).
//	    
//  	bool
//  	search( const char *    str,
//  	    	size_t   	strStart = 0,
//  	    	size_t   	strLen = NPOS ) const;
//	    Tries to match 'str' with the pattern, starting at 'strStart'
//	    for 'strLen' chars. The entire 'str' is searched for a
//	    match. Returns true if the str matches otherwise false.
//	    Additional information about a match is provided by
//	    matchCount(), matchStart(), matchLength() and matchInfo()
//	    (see below). 
//
//  	size_t
//  	matchCount( void ) const;
//	    Returns the number of registers (i.e. () pairs) in the
//	    pattern that matched. If no registers were specifed in the
//	    pattern, 0 is returned.
//	    
//
//  	int
//  	matchStart( unsigned short  regNum = 0 ) const;
//	    Return the start pos in the str that register 'regNum'
//	    matched. 'regNum' 0 represents the entire pattern.
//
//  	int
//  	matchLength( unsigned short regNum = 0 ) const;
//	    Return the lenght in the str that register 'regNum'
//	    matched. 'regNum' 0 represents the entire pattern.
//
//  	void
//  	matchInfo( int & start, int & len, unsigned short regNum = 0 ) const;
//	    Set the start and len for the register 'regNum'. 'regNum' 0
//	    represents the entire pattern.
//
//  	RegexScan &
//  	operator =  ( const RegexScan & rhs );
//	    Set the RegexScan to the values in 'rhs'.
//
//  	RegexScan &
//  	operator =  ( const char * pattern );
//	    Sets 'pattern' to be the new pattern for the RegexScan.
//
//	virtual
//	bool
//	good( void ) const
//	    Returns true if there are no errors associated with the
//	    RegexScan.
//
//	virtual
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. RegexScan )
//
//	virtual
//	const char *
//	getVersion( bool withPrjVer = true ) const
//	    Return the version string for the RegexScan. If
//	    withPrjVer == true, the project version info will also
//	    be returned.
//
//	virtual
//	ostream &
//	dumpInfo( ostream &	dest = cerr,
//		  const char *	prefix = "    ",
//		  bool		showVer = true );
//	    Output detailed information about the current
//	    state of the RegexScan. 
//
//	static const ClassVersion version;
//	    This contains the version information for the LogLevel class.
//
//
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
//
// Example:
//
//	const char * pattern = "This (is) a ((simple)|(small)) example\."
//
//	RegexScan   regex( pattern );
//
//	// this will match
//	if( regex.match( "This is a simple example." ) )
//		      //  0123456789012345678901234
//		      //            1         2
//	  {
//	    // regex.matchCount() == 4
//	    // regex.matchStart(0) == 0
//	    // regex.matchStart(1) == 5
//	    // regex.matchStart(2) == 10
//	    // regex.matchStart(3) == 0 - did not match
//	    // regex.matchStart(4) == 10
//	    // regex.matchLength(0) == 24
//	    // regex.matchLength(1) == 2
//	    // regex.matchLength(2) == 6
//	    // regex.matchLength(3) == 0
//	    // regex.matchLength(4) == 6
//	  }
//
//	// this will NOT match
//	if( ! regex.match( " This is a simple example." ) )
//	  {
//	  }
//
//	// this will match
//	if( regex.search( " This is a small example." ) )
//		      //   0123456789012345678901234
//		      //             1         2
//	  {
//	    // regex.matchCount() == 4
//	    // regex.matchStart(0) == 1
//	    // regex.matchStart(1) == 6
//	    // regex.matchStart(2) == 0 - did not match
//	    // regex.matchStart(3) == 11
//	    // regex.matchStart(4) == 11
//	    // regex.matchLength(0) == 24
//	    // regex.matchLength(1) == 2
//	    // regex.matchLength(2) == 0
//	    // regex.matchLength(3) == 5
//	    // regex.matchLength(4) == 5
//	  }
//
// See Also:
//
//  regex(3), Gnu regex info documentation, GnuRegex.h.
//
// Files:
//
//	RegexScan.hh, GnuRegex.h, libStlUtils.a
//
// Documented Ver: 2.5
// Tested Ver: 2.5
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.1  2003/08/09 11:22:42  houghton
// Changed to version 6
//
// Revision 5.5  2003/08/09 11:20:59  houghton
// Changed ver strings.
//
// Revision 5.4  2003/07/19 09:17:12  houghton
// Port to 64 bit.
//
// Revision 5.3  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
// Revision 5.2  2000/06/04 17:58:05  houghton
// Updated documentation.
//
// Revision 5.1  2000/05/25 10:33:17  houghton
// Changed Version Num to 5
//
// Revision 4.2  1998/10/13 16:21:29  houghton
// Changed to include stddef.h.
//
// Revision 4.1  1997/09/17 15:12:47  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:08:40  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/04/03 23:23:20  houghton
// Changed include stddef to stddef.h
//
// Revision 3.2  1997/04/02 13:44:52  houghton
// Added getPattern().
//
// Revision 3.1  1996/11/14 01:23:56  houghton
// Changed to Release 3
//
// Revision 2.7  1996/11/13 17:03:31  houghton
// Removed support for short file names.
// Changed RegexScan() defalut arg from a 0 to false.
//
// Revision 2.6  1996/11/04 18:22:22  houghton
// Cleanup header comment doc.
//
// Revision 2.5  1996/11/04 14:27:53  houghton
// Restructure header comments layout.
// Updated and verified header comment documentation.
//
// Revision 2.4  1996/04/27 13:08:28  houghton
// Cleanup.
//
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
#endif // ! def _RegexScan_hh_ 
