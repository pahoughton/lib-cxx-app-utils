#ifndef _FileOp_hh_
#define _FileOp_hh_
/**
   File:        FileOp.hh
   Project:	StlUtils ()
   Desc:        
  
    FileOp provides operations on entire files, such as copy and
    move (rename).
  
   Notes:
  
    This class is not fully developed or tested yet. I have only
    tested the following so far:
  
  	copy( filename, filename )
  	copy( filename, dir )
  	move( filename, filename )
  	move( filename, dir )
  
    I have tested the move across devices (file systems) works
    correctly. But I have not verified it deals with file system
    full yet.
  
   Quick Start: - short example of class usage
  
   Author:      Paul Houghton - (paul4hough@gmail.com)
   Created:     03/08/98 07:31
  
   Revision History: (See end of file for Revision Log)
  
    $Author$ 
    $Date$ 
    $Name$ 
    $Revision$ 
    $State$ 

    $Id$ 
**/

#include <StlUtilsConfig.hh>
#include <FileStat.hh>
#include <DumpInfo.hh>
#include <iostream>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class FileOp
{

public:

  typedef STLUTILS_SSIZE_T	size_type;
  
  FileOp( void );
  FileOp( const char * src );
  
  virtual ~FileOp( void );

  inline bool	copy( const char * dest,
		      bool overwrite = true );
  
  inline bool	copy( const char * src,
		      const char * dest,
		      bool overwrite = true );
  
  inline bool	move( const char * dest,
		      bool overwrite = true );
  inline bool	move( const char * src,
		      const char * dest,
		      bool overwrite = true );

  inline bool	cat( const char * dest );
  inline bool	cat( const char * src,
		     const char * dest );
  
  inline bool	remove( void );
  inline bool	remove( const char * src );

  inline bool	rmdir( const char * dirName, bool recurs = false );
  
  inline const FileStat &   getSrc( void ) const;
  inline const FileStat &   getDest( void ) const;
  
  virtual bool		clear( void );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< FileOp >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  static const ClassVersion version;

protected:

  enum OpType
  {
    OT_Copy,
    OT_Move,
    OT_Cat,
    OT_Remove,
    OT_Unknown
  };

  static const char *	OpTypeName[];
  
  bool		setDest( OpType op, const char * fn, bool overwrite );
  bool		copyFile( void );
  bool		moveFile( void );
  bool		removeFile( const char * fn );
  bool		removeDir( const char * fn, bool recurs );
  bool		catFile( void );
  bool		setDestStat( void );
  
  size_type	readfd( int fd, void * dest, size_t destSize );
  size_type	writefd( int fd, const void * src, size_t srcLen );
  
  bool	setError( int osErr, const char * desc, const char * fn );
  bool	setError( int osErr, OpType op, const char * desc, const char * fn );

  
  FileStat  src;
  FileStat  dest;

  Str	errorDesc;
  int	osError;
  
private:

  // defaults are ok
  // FileOp( const FileOp & from );
  // FileOp & operator =( const FileOp & from );

};

#if !defined( inline )
#include <FileOp.ii>
#else
#undef inline

#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	FileOp	class
//
//  Constructors:
//
//  	FileOp( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	write( ostream & dest ) const;
//	    write the data for this class in binary form to the ostream.
//
//	virtual istream &
//	read( istream & src );
//	    read the data in binary form from the istream. It is
//	    assumed it stream is correctly posistioned and the data
//	    was written to the istream with 'write( ostream & )'
//
//	virtual ostream &
//	toStream( ostream & dest ) const;
//	    output class as a string to dest (used by operator <<)
//
//	virtual istream &
//	fromStream( istream & src );
//	    Set this class be reading a string representation from
//	    src. Returns src.
//
//  	virtual Bool
//  	good( void ) const;
//  	    Return true if there are no detected errors associated
//  	    with this class, otherwise false.
//
//  	virtual const char *
//  	error( void ) const;
//  	    Return a string description of the state of the class.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. FileOp )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream & dest, const char * prefix, bool showVer );
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	static const ClassVersion version
//	    Class and project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const FileOp & src );
//
//	istream &
//	operator >> ( istream & src, FileOp & dest );
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
// 
// %PL%
// 
// $Log$
// Revision 6.3  2012/04/02 10:12:46  paul
// *** empty log message ***
//
// Revision 6.2  2011/12/30 23:57:31  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:46  houghton
// Changed to version 6
//
// Revision 5.5  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.4  2003/07/19 09:17:23  houghton
// Port to 64 bit.
//
// Revision 5.3  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.2  2000/07/31 13:39:09  houghton
// Added rmdir().
//
// Revision 5.1  2000/05/25 10:33:22  houghton
// Changed Version Num to 5
//
// Revision 1.4  1999/05/01 12:55:04  houghton
// Added cat()
//
// Revision 1.3  1998/11/02 19:20:50  houghton
// Added remove().
//
// Revision 1.2  1998/03/11 16:09:13  houghton
// Added setDestStat.
// Added getDest and getSrc.
//
// Revision 1.1  1998/03/08 18:08:28  houghton
// Initial Version.
//
//
#endif // ! def _FileOp_hh_ 

