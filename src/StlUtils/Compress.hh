#ifndef _Compress_hh_
#define _Compress_hh_
//
// File:        Compress.hh
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  Compress or Decompress a file using the same algorithm as the
//  Unix compress(1) command.
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     10/07/99 05:42
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//
//  %PID%
//

#include <StlUtilsConfig.hh>
#include <DumpInfo.hh>
#include <FilePath.hh>
#include <iostream>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class Compress
{

public:

  Compress( void );

  virtual ~Compress( void );

  bool		compress( const char * fn );
  bool		compress( FilePath & fn, bool rmSrc = false );
  bool		compress( const char * inFn, const char * outFn );
  inline bool	compress( const FilePath & inFn, const FilePath & outFn );
  
  bool		compress( int inFd, int outFd );
  
  bool		decompress( const char * fn );
  bool		decompress( FilePath & fn, bool rmSrc = false );
  bool		decompress( const char * inFn, const char * outFn );
  inline bool	decompress( const FilePath & inFn, const FilePath & outFn );
  
  bool	    decompress( int inFd, int outFd );

  static bool		isCompressed( const Str & fn );
  static bool		isCompressed( const char * fn );
  static const char *	compExt( void );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< Compress >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  static const ClassVersion version;

protected:

  enum ErrorNum
  {
    E_OK,
    E_IN_NAME,
    E_IN_OPEN,
    E_OUT_OPEN,
    E_READ,
    E_WRITE,
    E_FORMAT,
    E_BITS,
    E_CORRUPT,
    E_REMOVE,
    E_UNDEFINED
  };

  bool	setError( ErrorNum errNum, int osErr, int errFd );
  bool	setError( ErrorNum errNum, const char * desc );
  
  FilePath  inFn;
  FilePath  outFn;

  ErrorNum	errorNum;
  int		osErrno;
  int		errorFd;
  Str		errorDesc;
  
private:

  Compress( const Compress & from );
  Compress & operator =( const Compress & from );

};

#if !defined( inline )
#include <Compress.ii>
#else
#undef inline


#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	Compress	class
//
//  Constructors:
//
//  	Compress( );
//
//  Destructors:
//
//  Public Interface:
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
//  	    Return the name of this class (i.e. Compress )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream &	dest = cerr,
//	          const char *  prefix = "    ",
//		  bool          showVer = true ) const
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
// Revision 5.4  2001/10/23 16:59:18  houghton
// Added compress( const FilePath &, const FilePath & )
// Added decompress( const FilePath &, const FilePath & )
//
// Revision 5.3  2001/07/28 01:15:00  houghton
// *** empty log message ***
//
// Revision 5.2  2001/07/26 19:29:01  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:14  houghton
// Changed Version Num to 5
//
// Revision 1.2  1999/10/08 10:20:52  houghton
// Added rmSrc arg to compress( FilePath & fn ).
// Added rmSrc arg to decompress( FilePath & fn ).
//
// Revision 1.1  1999/10/07 13:09:51  houghton
// Initial Version.
//
//
#endif // ! def _Compress_hh_ 

