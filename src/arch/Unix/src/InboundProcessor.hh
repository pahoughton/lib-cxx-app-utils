#ifndef _InboundProcessor_hh_
#define _InboundProcessor_hh_
//
// File:        InboundProcessor.hh
// Project:	Clue
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     07/20/97 06:10
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <ClueConfig.hh>
#include <InboundProcessorBase.hh>
#include <iostream>

template< class Proc >
class InboundProcessor : public InboundProcessorBase
{

public:

  InboundProcessor( const char *    fileNamePattern,
		    const char *    inDirName,
		    const char *    procDirName,
		    long	    rescanWaitSecs,
		    Proc &	    proccessor );

  virtual ~InboundProcessor( void ) {};

protected:

  inline bool	    processInbound( const FilePath & filePath ) {
    return( proc( filePath ) );
  };
  
private:

  // InboundProcessor( const InboundProcessor & from );
  // InboundProcessor & operator =( const InboundProcessor & from );

  Proc &    proc;
};

#include <InboundProcessor.ii>


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	InboundProcessor	class
//
//  Constructors:
//
//  	InboundProcessor( );
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
//  	    Return the name of this class (i.e. InboundProcessor )
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
//  	operator <<( ostream & dest, const InboundProcessor & src );
//
//	istream &
//	operator >> ( istream & src, InboundProcessor & dest );
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
// Revision 1.1  1997/07/20 18:52:01  houghton
// Initial Version.
//
//
#endif // ! def _InboundProcessor_hh_ 

