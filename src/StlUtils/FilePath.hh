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
// Revision 1.1  1995/11/05 13:23:23  houghton
// Initaial implementation
//
//

#include <ClueConfig.hh>
#include <Str.hh>

#ifndef DIR_DELIM
#define DIR_DELIM '/'
#endif

#ifdef  CLUE_DEBUG
#define inline
#endif


class FilePath
{

public:

  inline FilePath( char dirDelim = DIR_DELIM, char extDelim = '.' );

  inline FilePath( const char * fullName,
	    char dirDelim = DIR_DELIM,
	    char extDelim = '.' );
  
  inline FilePath( const char *    dirName,
	    const char *    fileName,
	    char    	    dirDelim = DIR_DELIM,
	    char    	    extDelim = '.' );
  	    
  inline Str 	    getFullName( void ) const;
  inline Str  	    getPath( void ) const;
  inline Str  	    getFileName( void ) const;
  Str		    getName( void ) const;
  inline Str  	    getExt( void ) const;

  inline bool	set( const char * fullPath );
  bool		setPrefix( const char * prefix );
  bool      	setPath( const char * path );
  bool      	setFileName( const char * name );
  bool	    	setName( const char * name );
  bool	    	setName( const char * name, char ext );
  bool	    	setName( const char * name, const char * ext );
  bool      	setExt( const char * ext );
  bool      	setExt( const char * ext, char delim );
  bool      	setExt( const char * oldExt, const char * newExt );
  bool		setTempName( const char * prefix = 0 );
  bool		setTempName( const char * path, const char * prefix );
  
  bool      	changePath( const char * oldDirs, const char * newDirs );
  
  inline size_t	    getStreamSize( void ) const;
  inline ostream &  write( ostream & dest ) const;
  inline istream &  read( istream & src );
  
  inline int	    compare( const FilePath & two ) const;
  
  inline bool	    operator == ( const FilePath & rhs ) const;
  inline bool	    operator <  ( const FilePath & rhs ) const;

  inline FilePath & operator =  ( const char * );

  inline	    operator const char * ( void ) const;
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream & 	toStream( ostream & dest ) const;
  virtual ostream & 	dumpInfo( ostream & dest ) const;

  static const char version[];
  
protected:

private:

  char 	dirDelim;
  char  extDelim;
  
  Str	fileName;
  
};

#ifndef  inline
#include <FilePath.ii>
#else
#undef inline

int
compare( const FilePath & one, const FilePath & two );

ostream &
operator << ( ostream & dest, const FilePath & obj );

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
