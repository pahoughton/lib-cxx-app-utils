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
// Revision 1.3  1995/11/05 15:28:36  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <iostream>
#include <cstddef>
#else
#include <ClueCfg.hh>
#include <iostream>
#include <cstddef>
#endif

#define TESTIT( tester_, tf_ ) tester_( __FILE__, __LINE__, tf_ )
#define TESTITR( tester_, r_, tf_ ) tester_( __FILE__, __LINE__, r_, tf_ )
#define TESTITP( tester_, tf_, p_ ) tester_( __FILE__, __LINE__, tf_, p_ )

#define TEST( tf_ ) if( ! TESTIT( tester, (tf_) ) ) return( false )
#define TESTR( r_, tf_ ) if( ! TESTITR( tester, (r_), (tf_) ) ) return( false )
#define TESTP( tf_, p_ ) if( ! TESTITP( tester, (tf_), (p_) ) ) return( false )

// Macro Argument descriptions for: TESTIT, TESTITR, TESTITR,
//				    TEST, TESTR & TESTP
// 
//  tester  LibTest &	    the tester
//  tf	    bool	    true=pass false=fail
//  r	    const char *    fail reason description
//  p	    bool	    true=output a progress marker (i.e. '.')

class CLUE_CLASS_T LibTest
{

public:

  class CLUE_CLASS_T Results
  {
  public:
    virtual void	start( LibTest &	tester,
			       const char *	testName,
			       size_t		testNum,
			       long		passNum ) = 0;
    
    virtual bool	completed( LibTest &	    tester,
				   const char *	    testName,
				   size_t	    testNum,
				   long		    passNum,
				   bool		    passed ) = 0;
				   				 
    virtual bool	failed( LibTest &	tester,
				const char *	testName,
				size_t		testNum,
				size_t		passNum,
				const char *	reason,
				const char *	srcFile,
				long		srcLine ) = 0;
  
    virtual void	passed( LibTest &	tester,
				const char *	testName,
				size_t		testNum,
				size_t		passNum,
				const char *	srcFile,
				long		srcLine ) = 0;
  };
  
  struct TestItem
  {
    const char *    name;
    bool    	    (*test)( LibTest & );
  };
  
  LibTest( const TestItem * 	testList,
 	   ostream & 	    	dumpDest,
 	   ostream & 	    	output,
	   ostream & 	    	error );

  LibTest( const TestItem * 	testList,
	   Results &		resultsProcObj,
	   ostream & 	    	dumpDest,
	   ostream & 	    	output,
	   ostream & 	    	error );

  ~LibTest( void );

  // returns 0 if test pass
  
  int	    run( int & argc, char * argv[] );

  bool	    test( const char *  srcFn,
		  long		srcLine,
		  const char *	reason,
		  bool		pass,
		  bool		progress = false );
  
  bool	    test( const char *  srcFn,
		  long		srcLine,
		  bool		pass,
		  bool		progress = false );
    
  bool 	    file( const char *	srcFn,
		  long		srcLine,
		  const char *	testFileName,
		  const char *	expFileName );
  
  bool 	    file( const char *	srcFn,
		  long		srcLine,
		  const char *	testFileName );

  // synonym for test
  bool	    operator () ( const char *  srcFn,
			  long		srcLine,
			  const char *	reason,
			  bool		pass,
			  bool		progress );
  bool	    operator () ( const char *  srcFn,
			  long		srcLine,
			  bool		pass,
			  bool		progress );
  bool	    operator () ( const char *  srcFn,
			  long		srcLine,
			  const char *	reason,
			  bool		pass );
  bool	    operator () ( const char *  srcFn,
			  long		srcLine,
			  bool		pass );
  ostream & outputExpect( void );
  ostream & outputIs( void );

  ostream & getOut( void );
  ostream & getDump( void );
  
  const char * getCurrentTestName( void ) const;
  
  const char * getVersion( bool withPrjVer = true ) const;
  
  static const ClassVersion version;

protected:

  class CLUE_CLASS_T DefaultResults : public Results
  {
  public:
    virtual void	start( LibTest &	tester,
			       const char *	testName,
			       size_t		testNum,
			       long		passNum );
    
    virtual bool	completed( LibTest &	    tester,
				   const char *	    testName,
				   size_t	    testNum,
				   long		    passNum,
				   bool		    passed );
				   
    virtual bool	failed( LibTest &	tester,
				const char *	testName,
				size_t		testNum,
				size_t		passNum,
				const char *	reason,
				const char *	srcFile,
				long		srcLine );
  
    virtual void	passed( LibTest &	tester,
				const char *	testName,
				size_t		testNum,
				size_t		passNum,
				const char *	srcFile,
				long		srcLine );
  };

private:

  bool	testit( size_t tNum, size_t passNum );
  void  failed( const char * name,
		const char * reason,
		const char * srcFn,
		long         srcLine );
  
  LibTest( const LibTest & from );
  LibTest & operator =( const LibTest & from );

  static DefaultResults	defaultResultsObj;
  
  const TestItem *  testList;
  size_t    	    currentTest;
  size_t	    currentPass;
  ostream &	    dump;
  ostream &  	    out;
  ostream & 	    err;
  Results &	    result;
  
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
