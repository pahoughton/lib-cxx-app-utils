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
// Revision 2.1  1995/11/10 12:40:35  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:34  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <Str.hh>
#else
#include <ClueCfg.hh>
#include <Str.hh>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class FilePath : public Str
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
  
  inline Str 	    getFullName( void ) const;
  inline Str  	    getPath( void ) const;
  inline Str  	    getFileName( void ) const;
  Str		    getName( void ) const;
  inline Str  	    getExt( void ) const;
  inline size_t	    getDepth( void ) const;
  
  bool		    match( const char * pattern );
  
  inline bool	    set( const char * fullPath );
  inline bool	    set( const Str & fullPath );
  inline bool	    set( const SubStr & fullPath );
  bool		    setPrefix( const char * prefix );
  bool		    setPath( const char * path );
  bool		    setFileName( const char * name );
  bool		    setName( const char * name );
  bool		    setName( const char * name, char ext );
  bool		    setName( const char * name, const char * ext );
  bool		    setExt( const char * ext );
  bool		    setExt( const char * ext, char delim );
  bool		    setExt( const char * oldExt, const char * newExt );
  bool		    setTempName( const char * prefix = 0 );
  bool		    setTempName( const char * path, const char * prefix );
  
  bool		    changePath( const char * oldDirs, const char * newDirs );

  virtual size_t    	getBinSize( void ) const;
  virtual BinStream & 	write( BinStream & dest ) const;
  virtual BinStream & 	read( BinStream & src );
  
  inline ostream &	write( ostream & dest ) const;
  inline istream &	read( istream & src );
  
  friend inline ostream & operator << ( ostream & dest, const FilePath & obj );

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
