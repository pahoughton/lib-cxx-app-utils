#ifndef _LibTest_hh_
#define _LibTest_hh_
/**
   File:        LibTest.hh
   Project:	StlUtils ()
   Desc:        
  
    LibTest was designed to make it easier to test C++ classes
    and functions. To use it, you create a 'test funcion' that
    takes a 'LibTest &' as it's argument and returns a bool value.
    A return value of false indicates a specific test failed.
  
    Once you have created you 'test function' you need to instantiate
    a Global 'TestItem[]'. A 'TestItem' is a test name and the
    'test function' to execute for that name. The last element
    of the 'TestItem[]' must be a '{ 0, 0 }'.
  
    The 'TEST macros' use a 'false' value to indicate a specific
    test failed. This can be used in your test function to verify
    specific operations.
  
    If a test fails, output is generated and the
    test application exits.
  
   Author:      Paul Houghton - (paul4hough@gmail.com)
   Created:     05/09/95 09:50
  
   Revision History: (See end of file for Revision Log)
  
    $Author$ 
    $Date$ 
    $Name$ 
    $Revision$ 
    $State$ 
  
   $Id$ 
**/

#include "StlUtilsConfig.hh"
#include <iostream>
#include <cstddef>

extern bool	_LibTest_tf;

#define TESTIT( tester_, tf_ ) tester_( __FILE__, __LINE__, tf_ )
#define TESTITR( tester_, r_, tf_ ) tester_( __FILE__, __LINE__, r_, tf_ )
#define TESTITP( tester_, tf_, p_ ) tester_( __FILE__, __LINE__, tf_, p_ )

#define TEST( tf_ ) if( ! TESTIT( tester, (tf_) ) ) return( false )
#define TESTP( tf_ ) if( ! TESTITP( tester, (tf_), (true) ) ) return( false )

#define TESTR( r_, tf_ )						    \
_LibTest_tf = (tf_); if( ! TESTITR( tester, (r_), (_LibTest_tf) ) ) return( false )

// Macro Argument descriptions for: TESTIT, TESTITR, TESTITR,
//				    TEST, TESTR & TESTP
// 
//  tester  LibTest &	    the tester
//  tf	    bool	    true=pass false=fail
//  r	    const char *    fail reason description
//  p	    bool	    true=output a progress marker (i.e. '.')

class Str;

class LibTest
{

public:

  typedef unsigned long	    size_type;
  
  struct TestItem
  {
    const char *    name;
    bool    	    (*test)( LibTest & );
  };
  
  class Results
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
				long		srcLine,
				bool		progress ) = 0;
  };
  
  LibTest( const TestItem * 	testList,
	   bool			outputLineProgress,
 	   std::ostream & 	    	dumpDest,
 	   std::ostream & 	    	output,
	   std::ostream & 	    	error );

  LibTest( const TestItem * 	testList,
	   bool			outputLineProgress,
	   Results &		resultsProcessor,
	   std::ostream & 	    	dumpDest,
	   std::ostream & 	    	output,
	   std::ostream & 	    	error );

  ~LibTest( void );

  int	    run( int & argc, char * argv[] );

  int	    run( size_type passes, const Str & testListString );
    
  bool	    test( const char *  srcFn,
		  long		srcLine,
		  const char *	reason,
		  bool		pass,
		  bool		progress = false );
  
  bool	    test( const char *  srcFn,
		  long		srcLine,
		  const Str &	reason,
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
  std::ostream & outputExpect( void );
  std::ostream & outputIs( void );

  std::ostream & getOutput( void );
  std::ostream & getError( void );
  std::ostream & getDump( void );
  
  const char * getCurrentTestName( void ) const;
  
  const char * getVersion( bool withPrjVer = true ) const;
  
  static const ClassVersion version;

  // do not use this!
  class STLUTILS_CLASS_T DefaultResults : public Results
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
				long		srcLine,
				bool		progress );
  };

protected:
  
private:

  bool	testit( size_t tNum, size_t passNum );
  
  LibTest( const LibTest & from );
  LibTest & operator =( const LibTest & from );

  static DefaultResults	defaultResultsObj;
  
  const TestItem *  testList;
  bool		    lineProgress;
  size_t    	    currentTest;
  size_t	    currentPass;
  std::ostream &	    dump;
  std::ostream &  	    out;
  std::ostream & 	    err;
  Results &	    result;
  
};

/**
    Types:
  
    	class	LibTest
  	    See description above.
  
  	struct	LibTest::TestItem
  	    This defines the structure of specific items
  	    to be tested.
  	    
  	class	LibTest::Results
  	    The Results class gives you a way to specify what
  	    actions are to be taken for each major event in the test.
  
    Constructors:
  
    	LibTest( const TestItem *   testList,
  		 bool		    outputLineProgress,
  		 std::ostream &	    dumpDest,
  		 std::ostream &	    output,
  		 std::ostream &	    error );
  	    Construct a LibTest object where the testItem is an
  	    array of specific tests to be run that is terminated by
  	    a '{ 0, 0 }' entry. When outputLineProgress is true,
  	    every call to test will send a '.' to 'output'. The
  	    dumpDest can be accessed by your test funcions to output
  	    debuging info. 'output' is where successful progress information
  	    is sent. 'error' is where failed test information is sent.
  	    The 'DefaultResults' is used for result processing.
  
  	LibTest( const TestItem *   testList,
  		 bool		    outputLineProgress,
  		 Results &	    resultsProcessor,
  		 std::ostream &	    dumpDest,
  		 std::ostream &	    output,
  		 std::ostream &	    error );
  	    Construct a LibTest object where the testItem is an
  	    array of specific tests to be run that is terminated by
  	    a '{ 0, 0 }' entry. When outputLineProgress is true,
  	    every call to test will send a '.' to 'output'.
  	    The 'resultsProcessor' is used to process the results of
  	    each test. The dumpDest can be accessed by your
  	    test funcionts to output debuging info. 'output' is
  	    where successful progress information is sent.
  	    'error' is where failed test information is sent.
  
    Public Interface:
  
  	int
  	run( int & argc, char * argv[] )
  	    Run the test specified in the 'testList' passed to the
  	    constructor. Uses argc and argv from main() to determine
  	    which test to run and how many iteration to run the test.
  	    Use -nnn (i.e. -52) as the first arg to the executable to
  	    specify the number of iterations. All other args are assumed 
  	    to be the names of the test you want to run. If no test names
  	    are specified, all test are run.
  
  	bool
  	test( const char *  srcFn,
  	      long	    srcLine,
  	      const char *  reason,
  	      bool	    pass,
  	      bool	    progress = false );
  	    Verifiy a single operation. The 'srcFn' is the current
  	    source file name (i.e. __FILE__). 'srcLine' is the current
  	    source line (i.e. __LINE__). 'reason' is a string that
  	    is output if the test failed. If 'pass' is true the test
  	    has passed, and if false, the test failed. if progress is
  	    set to true, a '.' will be output to show progress of the
  	    test.
  
  	bool
  	test( const char *  srcFn,
  	      long	    srcLine,
  	      bool	    pass,
  	      bool	    progress = false );
  	    Verifiy a single operation. The 'srcFn' is the current
  	    source file name (i.e. __FILE__). 'srcLine' is the current
  	    source line (i.e. __LINE__). If 'pass' is true the test
  	    has passed, and if false, the test failed. if progress is
  	    set to true, a '.' will be output to show progress of the
  	    test.
  
  	bool
  	file( const char *  srcFn,
  	      long	    srcLine,
  	      const char *  testFileName,
  	      const char *  expFileName );
  	    This will verify that the contents of the file
  	    'testFileName' exactly match the context of the file
  	    'expFileName'. If they do not match, it is considered
  	    a failed test and descriptive output is generated. 'srcFn'
  	    is the current source file name (i.e. __FILE__). 'srcLine'
  	    is the current source line (i.e. __LINE__).
  	    
  	bool
  	file( const char *  srcFn,
  	      long	    srcLine,
  	      const char *  testFileName );
  	    This will verify that the contents of the file
  	    'testFileName' exactly match the context of the file
  	    'testFileName.exp'. If they do not match, it is considered
  	    a failed test and descriptive output is generated. 'srcFn'
  	    is the current source file name (i.e. __FILE__). 'srcLine'
  	    is the current source line (i.e. __LINE__).
  
  
  	bool
  	operator () ( const char *  srcFn,
  		      long	    srcLine,
  		      const char *  reason,
  		      bool	    pass,
  		      bool	    progress );
  	    This is a short cut that calls 'test' with the same arguments.
  
  	bool
  	operator () ( const char *  srcFn,
  		      long	    srcLine,
  		      bool	    pass,
  		      bool	    progress );
  	    This is a short cut that calls 'test' with the same arguments.
  
  	bool
  	operator () ( const char *  srcFn,
  		      long	    srcLine,
  		      const char *  reason,
  		      bool	    pass );
  	    This is a short cut that calls 'test' with the same arguments,
  	    but progress is set to false.
  
  	bool
  	operator () ( const char *  srcFn,
  		      long	    srcLine,
  		      bool	    pass );
  	    This is a short cut that calls 'test' with the same arguments,
  	    but progress is set to false.
  
  	std::ostream &
  	outputExpect( void )
  	    This method places '\n    Expect: ' on the output stream
  	    and returns the output stream.
  
  	std::ostream &
  	outputIs( void )
  	    This method places '\n    is:     ' on the output stream
  	    and returns the ouptut stream.
  
  	std::ostream &
  	getOutput( void )
  	    Returns the std::ostream passed as 'output' to the constructor.
  
  	std::ostream &
  	getDump( void )
  	    Returns the std::ostream passed as 'dumpDest' to the constructor.
  
  	const char *
  	getCurrentTestName( void ) const
  	    Returns the name of the current test being run.
  
  	inline
  	const char *
  	getVersion( bool withPrjVer = true ) const;
  	    Return the version information for ClassVersion. Calls
  	    ClassVersion::version.getVer( withPrjVer );
  
  	static
  	const ClassVersion version;
  	    This is the version info for ClassVersion.
  
  	virtual
  	void
  	Results::start( LibTest &	tester,
  			const char *	testName,
  			size_t		testNum,
  			long		passNum ) = 0;
  	    This method is called at the start of each test.
  
  	virtual
  	bool
  	Results::completed( LibTest &	    tester,
  			    const char *    testName,
  			    size_t	    testNum,
  			    long	    passNum,
  	    		    bool	    passed ) = 0;
  	    This method is called once each test as completed.
  	    passed is actually the value returned by the test
  	    function.
  
  	virtual
  	bool
  	Results::failed( LibTest &	tester,
  			 const char *   testName,
  			 size_t		testNum,
  			 size_t		passNum,
  			 const char *	reason,
  			 const char *	srcFile,
  			 long		srcLine ) = 0;
  	    This is called whenever a single operation fails.
  	    If it returns true, testing continues. If false is
  	    returned, the run method will return with the number
  	    of the testItem in testList that failed.
  
  	virtual
  	void
  	Results::passed( LibTest &	tester,
  			 const char *   testName,
  			 size_t		testNum,
  			 size_t		passNum,
  			 const char *	srcFile,
  			 long		srcLine,
  			 bool		progress ) = 0;
  	    This is called whenever a single operation passes. 
  
    Protected Interface:
  
    Private Methods:
  
    Associated Macros:
  
  	TEST( passed )
  	    Call 'test' for a single operation, passing it all the appropriate
  	    arguments. If the test fails, the macro does a return false.
  	    This macro assumes the LibTest object is named 'tester'.
  
  	TESTR( reason, passed )
  	    Call 'test' for a single operation, passing it all the appropriate
  	    arguments. If the test fails, the macro does a return false.
  	    This macro assumes the LibTest object is named 'tester'.
  
  	TESTP( passed )
  	    Call 'test' for a single operation, passing it all the appropriate
  	    arguments along with setting the progress arg to 'true'.
  	    If the test fails, the macro does a return false. This macro
  	    assumes the LibTest object is named 'tester'.
  
    Example:
  
  	bool tClassOne( LibTest & tester )
  	{
  	  ClassOne  t;
  	  TEST( t.good() );
  
  	  return( true );
  	}
  
  	bool tTestTwo( LibTest & tester )
  	{
  	  int vOne;
  	  int vTwo;
  
  	  TEST( vOne == vTwo );
  
  	  return( true );
  	}
  
  	LibTest::TestItem   TestList[] =
  	{
  	  { "ClassOne",	tClassOne   },
  	  { "TestTwo",    tTestTwo  },
  	  { 0, 0 }
        }
  
  	int main( int argc, char * argv[] )
  	{
  	    LibTest test( TestList, false, std::cerr, std::cout, std::cerr );
  
  	    return( test.run( argc, argv );
  	}
  
   Documented Ver:  2.3
   
**/
#endif // ! def _LibTest_hh_ 
