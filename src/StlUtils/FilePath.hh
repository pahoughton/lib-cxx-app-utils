#ifndef _FilePath_hh_
#define _FilePath_hh_
//
// File:        FilePath.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     05/18/95 07:43
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//


#include <StlUtilsConfig.hh>

#include <Str.hh>
#include <DateTime.hh>

#if defined( STLUTILS_DEBUG )
#define inline
#endif

class FilePath : public Str
{

public:

  static const char DirDelim;
  
  inline FilePath( char dirDelim = STLUTILS_DIR_DELIM, char extDelim = '.' );

  inline FilePath( const char *	fullName,
		   char		dirDelim = STLUTILS_DIR_DELIM,
		   char		extDelim = '.' );
  
  inline FilePath( const char * dirName,
		   const char * fileName,
		   char    	dirDelim = STLUTILS_DIR_DELIM,
		   char    	extDelim = '.' );

  inline FilePath( const char * dirName,
		   const char * fileName,
		   const char * fileExt,
		   char    	dirDelim = STLUTILS_DIR_DELIM,
		   char    	extDelim = '.' );

  inline FilePath( const char *	    dirName,
		   const DateTime & date,
		   const char *	    fileName,
		   char		    dirDelim = STLUTILS_DIR_DELIM,
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

  virtual ostream &	toStream( ostream & dest ) const;
  
  virtual size_type    	getBinSize( void ) const;
  
  virtual ostream &	write( ostream & dest ) const;

  // from ostream
  virtual ostream &	write( const char * src, int size );
#if defined( STLUTILS_STR_UNSIGNED )
  virtual ostream &	write( const unsigned char * src, int size );
#endif
  virtual ostream &	write( const wchar_t * src, int size );
  virtual ostream &	write( const void * src, size_type size );
  
  virtual istream &	read( istream & src );

  // from istream
  virtual istream &	read( char * dest, int size );
#if defined( STLUTILS_STR_UNSIGNED )
  virtual istream &	read( unsigned char * dest, int size );
#endif
  
  inline bool	    operator == ( const FilePath & rhs ) const;
  inline bool	    operator <  ( const FilePath & rhs ) const;

#if defined( STLUTILS_RELOPS_BROKEN )
  inline bool	    operator != ( const FilePath & rhs ) const;
  inline bool	    operator >  ( const FilePath & rhs ) const;
  inline bool	    operator <= ( const FilePath & rhs ) const;
  inline bool	    operator >= ( const FilePath & rhs ) const;
#endif
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
  
protected:

private:

  char 	dirDelim;
  char  extDelim;
  
};

#ifndef  inline
#include <FilePath.ii>
#else
#undef inline

ostream &
operator << ( ostream & dest, const FilePath & obj );

int
compare( const FilePath & one, const FilePath & two );

#endif

//  Data Types: - data types defined by this header
//
//  	FilePath	class
//
//  Constructors:
//
//  	FilePath( );
//
//  Destructors:
//
//  Public Interface:
//
//  	FilePath( char dirDelim = DIR_DELIM, char extDelim = '.' );
//
//  	FilePath( const char * fullName,
//  		  char dirDelim = DIR_DELIM,
//  	    	  char extDelim = '.' );
//  
//  	FilePath( const char *    dirName,
//  	    	  const char *    fileName,
//  	    	  char    	  dirDelim = DIR_DELIM,
//  	    	  char    	  extDelim = '.' );
//  	    
//  	Str
//  	getFullName( void ) const;
//
//  	Str
//  	getPath( void ) const;
//
//  	Str
//  	getFileName( void ) const;
//
//  	Str
//  	getName( void ) const;
//
//  	Str
//  	getExt( void ) const;
//
//  	bool
//  	set( const char * fullPath );
//
//  	bool
//  	setPrefix( const char * prefix );
//
//  	bool
//  	setPath( const char * path );
//
//  	bool
//  	setFileName( const char * name );
//
//  	bool
//  	setName( const char * name );
//
//  	bool
//  	setName( const char * name, char ext );
//
//  	bool
//  	setName( const char * name, const char * ext );
//
//  	bool
//  	setExt( const char * ext );
//
//  	bool
//  	setExt( const char * ext, char delim );
//
//  	bool
//  	setExt( const char * oldExt, const char * newExt );
//
//  	bool
//  	setTempName( const char * prefix = 0 );
//  
//  	bool
//  	changePath( const char * oldDirs, const char * newDirs );
//  
//  	size_t
//  	getStreamSize( void ) const;
//
//  	ostream &
//  	write( ostream & dest ) const;
//
//  	istream &
//  	read( istream & src );
//  
//  	int
//  	compare( const FilePath & two ) const;
//  
//  	bool
//  	operator == ( const FilePath & rhs ) const;
//
//  	bool
//  	operator <  ( const FilePath & rhs ) const;
//
//  	FilePath &
//  	operator =  ( const char * );
//
//  	 operator const char * ( void ) const;
//
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. FilePath )
//
//  	virtual Bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//  	virtual ostream &
//  	toStream( ostream & dest ) const;
//
//  	virtual ostream &
//  	dumpInfo( ostream & dest ) const;
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const FilePath & obj );
//
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// $Log$
// Revision 5.2  2000/05/25 17:05:46  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:15  houghton
// Changed Version Num to 5
//
// Revision 4.5  1999/06/10 11:45:11  houghton
// Added constructor that prefixes the file name with the date time
//   passed. (i.e. dir/19990602.040302.filename).
//
// Revision 4.4  1998/10/13 15:17:53  houghton
// Added dirSep().
//
// Revision 4.3  1998/03/23 10:45:04  houghton
// Changed to eliminate Sun5 compiler warnings.
//
// Revision 4.2  1997/09/19 11:20:55  houghton
// Changed to use size_type (vs size_t).
//
// Revision 4.1  1997/09/17 15:12:25  houghton
// Changed to Version 4
//
// Revision 3.8  1997/09/17 11:08:21  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.7  1997/08/08 12:37:23  houghton
// Added expand() method.
//
// Revision 3.6  1997/06/09 12:01:24  houghton
// Changed 'match' to be a const method.
//
// Revision 3.5  1997/03/12 12:01:41  houghton
// Added FilePath( dir, fn, ext, ddelim, edelim ) constructor.
// Cleanup comments.
//
// Revision 3.4  1997/03/03 14:35:49  houghton
// Changed base class from string back to Str (Massive improvement of
//     functionallity )
//
// Revision 3.3  1996/11/22 12:23:18  houghton
// Added 'set' methods that take 'string' (vs const char *).
//
// Revision 3.2  1996/11/20 12:06:27  houghton
// Changed: Major rework to change base class from Str to string.
//
// Revision 3.1  1996/11/14 01:23:42  houghton
// Changed to Release 3
//
// Revision 2.3  1996/05/14 14:17:50  houghton
// Bug-Fix: change read & write from inline to virtual.
//
// Revision 2.2  1995/11/10 14:08:36  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:35  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:34  houghton
// Revised
//
//
#endif // ! def _FilePath_hh_ 
