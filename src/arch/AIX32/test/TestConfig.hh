#ifndef _TestConfig_hh_
#define _TestConfig_hh_
//
// File:        TestConfig.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     10/02/95 09:39
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 15:29:31  houghton
// Revised
//
//

#if !defined( TESTDATA_PATH )
#define TESTDATA_PATH "data/"
#endif


#if defined( COMPARE_UNLIKE_POINTERS )
#undef COMPARE_UNLIKE_POINTERS
#endif

#if !defined( TEST_DUMPINFO_SCREEN )
#define TEST_DUMPINFO_SCREEN 1
#endif

#if !defined( TEST_DUMP_DEST )
#define TEST_DUMP_DEST TESTDATA_PATH "TestOuput.txt"
#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	TestConfig	class
//
//  Constructors:
//
//  	TestConfig( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. TestConfig )
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
//  	operator <<( ostream & dest, const TestConfig & obj );

#endif // ! def _TestConfig_hh_ 

