#ifndef _StlUtilsException_hh_
#define _StlUtilsException_hh_
//
// File:        StlUtilsException.hh
// Project:	StlUtils ()
// Desc:        
//
//  Provides a specialized excpetion.
//
// Notes:
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton 719-527-7834 - (paul.houghton@mci.com)
// Created:     02/17/01 11:42
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
//  $Id$ 
//

#include <StlUtilsConfig.hh>
#include <DumpInfo.hh>
#include <Log.hh>
#include <iostream>
#include <stdexcept>

#if defined( STLUTILS_DEBUG )
#define inline
#endif

#define StlUtilsExError( errMsg )					      \
  StlUtilsException( __FILE__, __LINE__, LogLevel::Error,		      \
		     ((Str *)(&(Str() << errMsg)))->c_str() )

class StlUtilsException : public exception
{

public:

  StlUtilsException( const char *		srcFile,
		     size_t			srcLine,
		     const LogLevel::Level &	logLevel,
		     const char *		errorMesg )
  : file( srcFile ),
    line( srcLine ),
    level( logLevel ),
    when( time(0) ),
    mesg( errorMesg )
  {
  }

  virtual ~StlUtilsException( void ) {};

  virtual void logit( Log & log ) {
    log( level, file, line, when ) << mesg << endl;
  }
    
  virtual const char * what( void ) const throw() {    
    Str errorString;
    errorString
      << DateTime( when.getTimeT(), true )
      << " " << file << ':' << line
      << " " << mesg;
    return( errorString.c_str() );
  }
  
protected:
  Str		    file;
  long		    line;
  DateTime	    when;
  LogLevel::Level   level;
  Str		    mesg;

#if defined( FIXME )
  virtual ostream &	    write( ostream & dest ) const;
  virtual istream &	    read( istream & src );

  virtual ostream &	    toStream( ostream & dest ) const;
  virtual istream &	    fromStream( istream & src );

  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< StlUtilsException >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  static const ClassVersion version;
#endif
protected:

private:

  // StlUtilsException( const StlUtilsException & from );
  StlUtilsException & operator =( const StlUtilsException & from );

};

#if defined( FIXME )
#if !defined( inline )
#include <StlUtilsException.ii>
#else
#undef inline

ostream &
operator << ( ostream & dest, const StlUtilsException & src );

istream &
operator >> ( istream & src, const StlUtilsException & dest );


#endif
#endif

//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	StlUtilsException	class
//
//  Constructors:
//
//  	StlUtilsException( );
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
//  	    Return the name of this class (i.e. StlUtilsException )
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
//  	operator <<( ostream & dest, const StlUtilsException & src );
//
//	istream &
//	operator >> ( istream & src, StlUtilsException & dest );
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
// Revision 6.1  2003/08/09 11:22:43  houghton
// Changed to version 6
//
// Revision 5.2  2003/08/09 11:20:59  houghton
// Changed ver strings.
//
// Revision 5.1  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
//

// Set XEmacs mode
//
// Local Variables:
// mode: c++
// End:
//
#endif // ! def _StlUtilsException_hh_ 

