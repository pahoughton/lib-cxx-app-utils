#ifndef _LibTest_hh_
#define _LibTest_hh_
//
// File:        LibTest.hh
// Desc:        
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/09/95 09:50
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:25  houghton
// Initaial implementation
//
//

#include <ClueConfig.hh>

#include <iostream>

#include <cstddef>

class LibTest
{

public:

  struct TestItem
  {
    const char *    name;
    bool    	    (*test)( LibTest & test );
  };
  
  LibTest( const TestItem * 	testList,
	   ostream & 	    	output,
	   ostream & 	    	error );

  ~LibTest( void );

  // returns 0 if test pass
  
  int	    run( int & argc, char * argv[] );

  void	    test( bool pass, bool progress = false );
  void	    test( const char * name, bool pass );
  void 	    file( const char * fileName );
  
  // synonym for test
  void	    operator () (bool pass, bool progress = false);
  void	    operator () ( const char * name, bool pass );

  ostream & outputExpect( void );
  ostream & outputIs( void );

  static const char version[];
  
protected:

private:

  LibTest( const LibTest & from );
  LibTest & operator =( const LibTest & from );

  void	failed( void );
  
  const TestItem *  testList;
  size_t    	    currentTest;
  ostream &  	    out;
  ostream & 	    err;
  
};

//  Data Types: - data types defined by this header
//
//  	LibTest	class
//
//  Constructors:
//
//  	LibTest( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. LibTest )
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
//  	operator <<( ostream & dest, const LibTest & obj );
//
#endif // ! def _LibTest_hh_ 
