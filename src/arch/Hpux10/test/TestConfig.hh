#ifndef _TestConfig_hh_
#define _TestConfig_hh_
//
// File:        TestConfig.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     07/15/98 08:19
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
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
#define TEST_BLOCK_DEVICE "/dev/root"
#endif

#if !defined( TEST_CHAR_DEVICE )
#define TEST_CHAR_DEVICE  "/dev/mem"
#endif

#if !defined( TEST_SETUID_FILE )
#define TEST_SETUID_FILE    "/usr/bin/su"
#endif

#if !defined( TEST_SETGID_FILE )
#define TEST_SETGID_FILE    "/usr/bin/iostat"
#endif

// #define STLUTILS_TEST_MULTI_GROUPS 1


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
// Revision 5.1  2000/05/25 10:33:20  houghton
// Changed Version Num to 5
//
// Revision 1.2  1998/08/13 10:54:12  houghton
// *** empty log message ***
//
// Revision 1.1  1998/07/20 11:28:30  houghton
// Initial Version.
//
//
#endif // ! def _TestConfig_hh_ 

