#ifndef _SubThread_hh_
#define _SubThread_hh_
//
// File:        SubThread.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     07/16/96 06:39
//
// Revision History:
//
// $Log$
// Revision 3.2  1997/09/17 11:10:24  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:28:08  houghton
// Changed to Release 3
//
// Revision 1.1  1996/07/16 13:54:08  houghton
// *** empty log message ***
//
//

#include <StlUtilsConfig.hh>
#include <ThreadBase.hh>

class SubThread : public ThreadBase
{

public:

  SubThread( bool detach = false ) : ThreadBase( detach ) {};

  virtual ~SubThread( void );

protected:

  bool	main( void );
  
private:

  SubThread( const SubThread & from );
  SubThread & operator =( const SubThread & from );

};



//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	SubThread	class
//
//  Constructors:
//
//  	SubThread( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. SubThread )
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
//  	operator <<( ostream & dest, const SubThread & obj );

#endif // ! def _SubThread_hh_ 

