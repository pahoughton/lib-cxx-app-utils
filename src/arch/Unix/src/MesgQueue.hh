#ifndef _MesgQueue_hh_
#define _MesgQueue_hh_
//
// File:        MesgQueue.hh
// Project:	StlUtils ()
// Desc:        
//
//  This class provides an interface to the Unix Message Queue IPC facility.
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@mci.com)
// Created:     11/06/98 06:19
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
#include <StlUtilsMsgq.hh>

#include <FilePath.hh>
#include <DumpInfo.hh>
#include <iostream>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class MesgQueue
{

public:

  struct Mesg
  {
    long    mesgType;
  };

  typedef size_t	size_type;
  
  MesgQueue( const char *   keyFileName,
	     char	    proj = ' ',
	     ios::open_mode mode = ios::in,
	     bool	    create = false );

  virtual ~MesgQueue( void );
  
  bool	send( const Mesg & mesg, size_type size );
  bool	recv( Mesg & mesg, size_type size, long type = 0 );

  size_type	getNumMesgsInQueue( void );

  bool	    remove( void );

  bool			interupted( void ) const;
  bool			clearError( void );
  int			getOsErrno( void ) const;
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< MesgQueue >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  static const ClassVersion version;

  static const key_t	badKey;
  
protected:

  enum ErrorNum
  {
    E_OK,
    E_FTOK,
    E_KEY_STAT,
    E_MSGGET,
    E_SEND,
    E_RECV,
    E_REMOVE,
    E_UNDEFINED
  };

  bool	setError( ErrorNum errNum, int osErr );
  
  FilePath  keyFileName;
  char	    keyProj;
  key_t	    key;
  int	    queueFlags;
  int	    queueId;
  
  ErrorNum  errorNum;
  int	    osErrno;
  
private:

  MesgQueue( const MesgQueue & from );
  MesgQueue & operator =( const MesgQueue & from );

};

#if !defined( inline )
#include <MesgQueue.ii>
#else
#undef inline

#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	MesgQueue	class
//
//  Constructors:
//
//  	MesgQueue( );
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
//  	    Return the name of this class (i.e. MesgQueue )
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
//  	operator <<( ostream & dest, const MesgQueue & src );
//
//	istream &
//	operator >> ( istream & src, MesgQueue & dest );
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
// Revision 5.3  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:22  houghton
// Changed Version Num to 5
//
// Revision 4.2  2000/03/10 11:42:12  houghton
// Added: clearError(), getOsErrno() and interupted().
//
// Revision 4.1  1999/03/02 12:51:54  houghton
// Initial Version.
//
//
#endif // ! def _MesgQueue_hh_ 

