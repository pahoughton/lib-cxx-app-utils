#ifndef _FilePath_hh_
#define _FilePath_hh_
//
// File:        FilePath.hh
// Desc:        
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/18/95 07:43
//
// Revision History:
//
// $Log$
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

#include "ClueConfig.hh"
#include <string>

#if defined( CLUE_DEBUG )
#define inline
#endif

class FilePath : public string
{

public:

  static const char DirDelim;
  
  inline FilePath( char dirDelim = CLUE_DIR_DELIM, char extDelim = '.' );

  inline FilePath( const char *	fullName,
		   char		dirDelim = CLUE_DIR_DELIM,
		   char		extDelim = '.' );
  
  inline FilePath( const char * dirName,
		   const char * fileName,
		   char    	dirDelim = CLUE_DIR_DELIM,
		   char    	extDelim = '.' );

  inline FilePath( const FilePath & from );
  
  inline string	    getFullName( void ) const;
  inline string	    getPath( void ) const;
  inline string	    getFileName( void ) const;
  string	    getName( void ) const;
  inline string	    getExt( void ) const;
  inline size_t	    getDepth( void ) const;
  
  bool		    match( const char * pattern );
  
  inline bool	    set( const char * fullPath );
  inline bool	    set( const string & fullPath );
  bool		    setPrefix( const char * prefix );
  inline bool	    setPrefix( const string & prefix );
  bool		    setPath( const char * path );
  inline bool	    setPath( const string & path );
  bool		    setFileName( const char * name );
  inline bool	    setFileName( const string & name );
  bool		    setName( const char * name );
  inline bool	    setName( const string & name );
  bool		    setName( const char * name, char ext );
  inline bool	    setName( const string & name, char ext );
  bool		    setName( const char * name, const char * ext );
  inline bool	    setName( const string & name, const string & ext );
  bool		    setExt( const char * ext );
  bool		    setExt( const string & ext );
  bool		    setExt( const char * ext, char delim );
  bool		    setExt( const string & ext, char delim );
  bool		    setExt( const char * oldExt, const char * newExt );
  bool		    setExt( const string & oldExt, const string & newExt );
  bool		    setTempName( const char * prefix = 0 );
  bool		    setTempName( const string & prefix );
  bool		    setTempName( const char * path, const char * prefix );
  bool		    setTempName( const string & path, const string & prefix );
  
  bool		    changePath( const char * oldDirs, const char * newDirs );
  bool		    changePath( const string & oldDirs,
				const string & newDirs );

  virtual ostream &	toStream( ostream & dest ) const;
  
  virtual size_t    	getBinSize( void ) const;
  
  virtual ostream &	write( ostream & dest ) const;
  virtual istream &	read( istream & src );

  inline bool	    operator == ( const FilePath & rhs ) const;
  inline bool	    operator <  ( const FilePath & rhs ) const;
  
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
#endif // ! def _FilePath_hh_ 
