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
// Revision 5.1  2000/05/25 10:33:19  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:16  houghton
// Changed to Version 4
//
// Revision 3.2  1997/07/21 10:24:31  houghton
// Added defines for various types of files (used in tFileStat02.C).
//
// Revision 3.1  1996/11/14 01:25:02  houghton
// Changed to Release 3
//
// Revision 1.1  1996/02/29 19:10:32  houghton
// Initial Version
//
// Revision 2.1  1995/11/10 12:43:28  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  15:29:31  houghton
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

#if !defined( TEST_BLOCK_DEVICE )
#define TEST_BLOCK_DEVICE "/dev/fd0"
#endif

#if !defined( TEST_CHAR_DEVICE )
#define TEST_CHAR_DEVICE  "/dev/tty"
#endif

#if !defined( TEST_SOCKET_DEVICE )
#define TEST_SOCKET_DEVICE  "/dev/log"
#endif

#if !defined( TEST_SETUID_FILE )
#define TEST_SETUID_FILE    "/bin/su"
#endif

#if !defined( TEST_SETGID_FILE )
#define TEST_SETGID_FILE    "/usr/bin/chsh"
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

