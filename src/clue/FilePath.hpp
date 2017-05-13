#ifndef _clue_FilePath_hpp_
#define _clue_FilePath_hpp_
/* 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

   A FilePath is a specialized string that provides methods for
   extracting and setting various filename components such as
   directories and extentions (i.e .c ).
*/


#include <clue/Str.hpp>
#include <clue/DateTime.hpp>

#define CLUE_CLEANFN_CHARS "/\\?*:;[]"
namespace clue {

class FilePath : public Str
{

public:

  static const char DirDelim;

  inline FilePath( char dirDelim = '/', char extDelim = '.' );

  inline FilePath( const char *	fullName,
		   char		dirDelim = '/',
		   char		extDelim = '.' );

  inline FilePath( const char * dirName,
		   const char * fileName,
		   char    	dirDelim = '/',
		   char    	extDelim = '.' );

  inline FilePath( const char * dirName,
		   const char * fileName,
		   const char * fileExt,
		   char    	dirDelim = '/',
		   char    	extDelim = '.' );

  inline FilePath( const char *	    dirName,
		   const DateTime & date,
		   const char *	    fileName,
		   char		    dirDelim = '/',
		   char		    extDelim = '.' );

  inline FilePath( const FilePath & from );

  inline Str	    getFullName( void ) const;
  inline Str	    getPath( void ) const;
  inline Str	    getFileName( void ) const;
  Str		    getName( void ) const;
  inline Str	    getExt( void ) const;
  inline size_t	    getDepth( void ) const;
  inline char	    dirSep( void ) const;

  bool		    match( const char * pattern ) const;

  bool		    expand( void );

  inline bool	    set( const char * fullPath );
  inline bool	    set( const Str & fullPath );
  bool		    setPrefix( const char * prefix );
  inline bool	    setPrefix( const Str & prefix );
  bool		    setPath( const char * path );
  inline bool	    setPath( const Str & path );
  bool		    setFileName( const char * name );
  inline bool	    setFileName( const Str & name );
  bool		    setName( const char * name );
  inline bool	    setName( const Str & name );
  bool		    setName( const char * name, char ext );
  inline bool	    setName( const Str & name, char ext );
  bool		    setName( const char * name, const char * ext );
  inline bool	    setName( const Str & name, const Str & ext );
  bool		    setExt( const char * ext );
  bool		    setExt( const Str & ext );
  bool		    setExt( const char * ext, char delim );
  bool		    setExt( const Str & ext, char delim );
  bool		    setExt( const char * oldExt, const char * newExt );
  bool		    setExt( const Str & oldExt, const Str & newExt );
  bool		    setTempName( const char * prefix = 0 );
  bool		    setTempName( const Str & prefix );
  bool		    setTempName( const char * path, const char * prefix );
  bool		    setTempName( const Str & path, const Str & prefix );

  bool		    changePath( const char * oldDirs, const char * newDirs );
  bool		    changePath( const Str & oldDirs,
				const Str & newDirs );

  void              cleanFn( void );

  virtual std::ostream &	toStream( std::ostream & dest ) const;

  virtual size_type    	getBinSize( void ) const;

  virtual std::ostream &	write( std::ostream & dest ) const;

  // from std::ostream
  virtual std::ostream &	write( const char * src, int size );
  virtual std::ostream &	write( const unsigned char * src, int size );
  virtual std::ostream &	write( const wchar_t * src, int size );
  virtual std::ostream &	write( const void * src, size_type size );

  virtual std::istream &	read( std::istream & src );

  // from std::istream
  virtual std::istream &	read( char * dest, int size );
  virtual std::istream &	read( unsigned char * dest, int size );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;
private:

  char 	dirDelim;
  char  extDelim;

};


inline
FilePath::FilePath( char d, char e )
{
  dirDelim = d;
  extDelim = e;
}

inline
FilePath::FilePath( const char * fullName, char d, char e  )
{
  assign( fullName );
  dirDelim = d;
  extDelim = e;
}

inline
FilePath::FilePath(
  const char * 	dir,
  const char * 	fn,
  char 	    	d,
  char 	    	e
  )
{
  assign( dir );
  dirDelim = d;
  extDelim = e;

  if( at( size() - 1 ) != dirDelim )
    append( 1, dirDelim );

  append( fn );
}

inline
FilePath::FilePath(
  const char * 	dir,
  const char * 	fn,
  const char *  ext,
  char 	    	d,
  char 	    	e
  )
  : dirDelim( d ),
    extDelim( e )
{
  if( dir )
    {
      assign( dir );

      if( at( size() - 1 ) != dirDelim )
	append( 1, dirDelim );
    }

  if( fn )
    append( fn );

  if( ext )
    {
      if( ext[0] != extDelim )
	append( 1, extDelim );
      append( ext );
    }
}

inline
FilePath::FilePath(
  const char *	    dirName,
  const DateTime &  date,
  const char *	    fileName,
  char 	    	d,
  char 	    	e
  )
  : dirDelim( d ),
    extDelim( e )
{
  if( dirName )
    {
      assign( dirName );
      if( at( size() - 1 ) != dirDelim )
	append( 1, dirDelim );
    }

  *this << date.yymmdd() << '.' << date.hhmmss() << '.';

  if( fileName )
    append( fileName );
}


inline
FilePath::FilePath( const FilePath & from )
{
  assign( from );
  dirDelim = from.dirDelim;
  extDelim = from.extDelim;
}

inline
Str
FilePath::getFullName( void ) const
{
  return( c_str() );
}

inline
Str
FilePath::getPath( void ) const
{
  Str path;

  size_t end = rfind( dirDelim );

  if( end != npos )
    path = substr( (size_type)0, end );
  else
    path = ".";

  return( path );
}

inline
Str
FilePath::getFileName( void ) const
{
  Str name;

  size_t dirBeg = rfind( dirDelim );

  if( dirBeg != npos )
    {
      name = substr( dirBeg + 1 );
      return( name );
    }
  else
    {
      return( *this );
    }
}


inline
Str
FilePath::getExt( void ) const
{
  Str ext;

  size_t extBeg = rfind( extDelim );

  if( extBeg != npos && find( dirDelim, extBeg ) == npos )
    ext = substr( extBeg + 1 );

  return( ext );
}

inline
size_t
FilePath::getDepth( void ) const
{
  if( size() )
    {
      size_type depth = 0;
      for( size_t start = 0;
	   start != npos;
	   start = find( DirDelim, start + 1 ) )
	depth++;
      return( depth );
    }
  else
    {
      return( 0 );
    }
}

inline
char
FilePath::dirSep( void ) const
{
  return( dirDelim );
}

inline
bool
FilePath::set( const char * fullPath )
{
  assign( fullPath );
  return( true );
}

inline
bool
FilePath::set( const Str & fullPath )
{
  return( set( fullPath.c_str() ) );
}

inline
bool
FilePath::setPrefix( const Str & prefix )
{
  return( setPrefix( prefix.c_str() ) );
}

inline
bool
FilePath::setPath( const Str & path )
{
  return( setPath( path.c_str() ) );
}

inline
bool
FilePath::setFileName( const Str & name )
{
  return( setFileName( name.c_str() ) );
}

inline
bool
FilePath::setName( const Str & name )
{
  return( setName( name.c_str() ) );
}

inline
bool
FilePath::setName( const Str & name, char ext )
{
  return( setName( name.c_str(), ext ) );
}

inline
bool
FilePath::setName( const Str & name, const Str & ext )
{
  return( setName( name.c_str(), ext.c_str() ) );
}

inline
bool
FilePath::setExt( const Str & ext )
{
  return( setExt( ext.c_str() ) );
}

inline
bool
FilePath::setExt( const Str & ext, char delim )
{
  return( setExt( ext.c_str(), delim ) );
}

inline
bool
FilePath::setExt( const Str & oldExt, const Str & newExt )
{
  return( setExt( oldExt.c_str(), newExt.c_str() ) );
}

inline
bool
FilePath::setTempName( const Str & prefix )
{
  return( setTempName( prefix.c_str() ) );
}

inline
bool
FilePath::setTempName( const Str & path, const Str & prefix )
{
  return( setTempName( path.c_str(), prefix.c_str() ) );
}

inline
bool
FilePath::changePath( const Str & oldDirs, const Str & newDirs )
{
  return( changePath( oldDirs.c_str(), newDirs.c_str() ) );
}

inline
int
compare( const FilePath & one, const FilePath & two )
{
  return( one.compare( two ) );
}

inline
std::ostream &
operator << ( std::ostream & dest, const FilePath & obj )
{
  return( obj.toStream( dest ) );
}
}; // namespace clue

/**
    Data Types:

    	FilePath	class

    Constructors:

    	FilePath( char dirDelim = STLUTILS_DIR_DELIM, char extDelim = '.' );

    	FilePath( const char * fullName,
    		  char dirDelim = STLUTILS_DIR_DELIM,
    	    	  char extDelim = '.' );

    	FilePath( const char *    dirName,
    	    	  const char *    fileName,
    	    	  char    	  dirDelim = STLUTILS_DIR_DELIM,
    	    	  char    	  extDelim = '.' );

    Destructors:

    Public Interface:

    	Str
    	getFullName( void ) const;
  	    Returns the enire passed as a Str.

    	Str
    	getPath( void ) const;
  	    Return the directory portion of a file name, or if there
  	    is not one, return ".". For exampe: "filename.ext" returns
  	    "."; "dir/subdir/filename.ext" returns "dir/subdir";
  	    and "/file.ext" returns "" (empty string);

    	Str
    	getFileName( void ) const;
  	    Returns the filename without any directories. For example:
  	    "filename.ext" returns "filename.ext"; "dir/filename.ext"
  	    returns "filename.ext"; "/filename.ext" returns
  	    "filename.ext"; and "/dir/dir/" returns "" (empty string).

    	Str
    	getName( void ) const;
  	    Returns the filename without any directories or
  	    extentions. For example: "filename.ext" returns
  	    "filename"; "dir/filename.ext" returns "filename";
  	    "/filename.ext" returns "filename"; "/dir/dir/"
  	    returns "" (empty string); and "dir/.hidden" returns ""
  	    (empty string).


    	Str
    	getExt( void ) const;
  	    Returns the file extention (everthing after the last '.'
  	    in the file name. For example: "dir/filename.ext" returns
  	    "ext"; "dir/.hidden" returns "hidden" and "filename"
  	    returns the "" (empty string).

  	size_type
  	getDepth( void ) const;
  	    Return the number of directory levels in the FilePath. For
  	    example, an empty FilePath (i.e. FilePath f;) would return
  	    0, 'filename.ext' would return 1 and 'dir/subdir/file.ext'
  	    would return 3.

    	bool
    	set( const char * fullPath );

    	bool
    	setPrefix( const char * prefix );

    	bool
    	setPath( const char * path );

    	bool
    	setFileName( const char * name );

    	bool
    	setName( const char * name );

    	bool
    	setName( const char * name, char ext );

    	bool
    	setName( const char * name, const char * ext );

    	bool
    	setExt( const char * ext );

    	bool
    	setExt( const char * ext, char delim );

    	bool
    	setExt( const char * oldExt, const char * newExt );

    	bool
    	setTempName( const char * prefix = 0 );

    	bool
    	changePath( const char * oldDirs, const char * newDirs );

    	size_t
    	getBinSize( void ) const;

    	std::ostream &
    	write( std::ostream & dest ) const;

    	std::istream &
    	read( std::istream & src );

    	bool
    	operator == ( const FilePath & rhs ) const;

    	bool
    	operator <  ( const FilePath & rhs ) const;

    	operator const char * ( void ) const;


    	virtual const char *
    	getClassName( void ) const;
    	    Return the name of this class (i.e. FilePath )

    	virtual bool
    	good( void ) const;
    	    Returns true if there are no detected errors associated
    	    with this class, otherwise FALSE.

    	virtual const char *
    	error( void ) const
    	    Returns as string description of the state of the class.

    	virtual std::ostream &
    	toStream( std::ostream & dest ) const;

  	virtual
  	std::ostream &
  	dumpInfo( std::ostream &	dest = std::cerr,
  		  const char *	prefix = "    ",
  		  bool		showVer = true ) const;
  	    Output detailed information about the current
  	    state of the instance.


    Other Associated Functions:

    	std::ostream &
    	operator <<( std::ostream & dest, const FilePath & obj );

*/
#endif // ! def _clue_FilePath_hpp_
