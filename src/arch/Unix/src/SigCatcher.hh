#ifndef _SigCatcher_hh_
#define _SigCatcher_hh_
//
// File:        SigCatcher.hh
// Project:	StlUtils
// Desc:        
//
//  Catch signals.
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     04/11/97 07:55
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
#include <Bitmask.hh>
#include <vector>
#include <deque>
#include <iostream>
#include <ctime>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class SigCatcher
{

public:

  typedef int			Signal;
  typedef vector< Signal >	SigList;
  typedef SigList::size_type	size_type;
  
  typedef Bitmask Flag;
  
  static const Flag	None;
  static const Flag	OnStack;
  static const Flag	NoDefer;
  static const Flag	Restart;
  static const Flag	Siginfo;
  static const Flag	NoChildWait;
  static const Flag	NoChildStop;
  static const Flag	WaitSig;

  class Caught
  {
  public:
    inline Caught( void );
    inline Caught( SigCatcher::Signal caughtSig, time_t timeCaught );

    inline ~Caught(void) {};
    
    inline SigCatcher::Signal   sig( void ) const;
    inline time_t		when( void ) const;
    const char *		name( void ) const;
    
    inline bool			operator == ( const Caught & rhs ) const;
    
  private:

    SigCatcher::Signal	sigCaught;
    time_t		whenCaught;
  };

  typedef deque< Caught >   CaughtQueue;
  
  SigCatcher( void );
  SigCatcher( Signal catchSig );
  SigCatcher( const SigList & catchSigList );
  SigCatcher( const SigList & catchSigList, const SigList & ignoreSigList );
  SigCatcher( const Signal *	catchSigList,
	      size_type		catchCount,
	      const Signal *	ignoreSigList = 0,
	      size_type		ignCount = 0 );
  SigCatcher( const Signal *	catchSigList,
	      size_type		catchCount,
	      const Signal *	ignoreSigList,
	      size_type		ignCount,
	      const Flag	flags );

  virtual ~SigCatcher( void );
  
  inline CaughtQueue &		caught( void );
  inline const CaughtQueue &	caught( void ) const;
  
  inline bool	    caught( Signal sig ) const;
  
  inline bool	    catchSig( Signal sig );
  bool		    catchSig( Signal sig, const Flag & flags );
  bool		    ignoreSig( Signal sig );

  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;

protected:

  enum ErrorNum
  {
    E_OK,
    E_SELF,
    E_CATCH,
    E_IGNORE,
    E_UNDEFINED
  };
  
  inline bool	setError( ErrorNum err, Signal errSig, int osErr );
  
private:

  static void catchAction( int sig, int code, struct sigcontext * context );
  
  SigCatcher( const SigCatcher & from );
  SigCatcher & operator =( const SigCatcher & from );

  SigList	catchList;
  SigList	ignoreList;
  
  CaughtQueue   caughtSigList;

  ErrorNum	errorNum;
  Signal	errorSig;
  int		osErrno;
  
  static SigCatcher *	self;
  
};

#if !defined( inline )
#include <SigCatcher.ii>
#else
#undef inline

#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	SigCatcher	class
//
//  Constructors:
//
//  	SigCatcher( );
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
//  	    Return the name of this class (i.e. SigCatcher )
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
//  	operator <<( ostream & dest, const SigCatcher & src );
//
//	istream &
//	operator >> ( istream & src, SigCatcher & dest );
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
// Revision 5.1  2000/05/25 10:33:23  houghton
// Changed Version Num to 5
//
// Revision 4.4  1999/03/02 12:52:50  houghton
// Added size_type.
// Cleanup.
//
// Revision 4.3  1998/03/30 14:08:22  houghton
// Renamed signal variable to sigCaught to avoid name clashes with the
//     'signal' function.
//
// Revision 4.2  1998/02/02 15:29:13  houghton
// Added support for specifying singal flags.
//
// Revision 4.1  1997/09/17 15:13:37  houghton
// Changed to Version 4
//
// Revision 3.6  1997/09/17 11:09:24  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.5  1997/08/08 13:26:14  houghton
// Added name() to return the name of the signal.
//
// Revision 3.4  1997/07/25 12:18:42  houghton
// Added caught() const method.
//
// Revision 3.3  1997/07/18 21:31:13  houghton
// Port(Sun5): added include <ctime>
//
// Revision 3.2  1997/04/21 09:58:14  houghton
// Port: include destructor.
//
// Revision 3.1  1997/04/19 09:53:04  houghton
// Initial Version.
//
//
#endif // ! def _SigCatcher_hh_ 

