#ifndef _TestConfig_hh_
#define _TestConfig_hh_
/**
  File:		TestConfig.hh
  Project:	StlUtils 
  Desc:

    
  
  Notes:
    
  Author(s):	Paul Houghton <<paul4hough@gmail.com>>
  Created:	07/19/2003 04:35
  
  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Name$
    $Revision$
    $State$

  $Id$

**/

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

#if defined( HOST_BLURR ) && !defined( TEST_BLOCK_DEVICE )
#define TEST_BLOCK_DEVICE "/dev/dsk/c0t0d0s0"
#endif

#if defined( HOST_SOUNDWAVE ) && !defined( TEST_BLOCK_DEVICE )
#define TEST_BLOCK_DEVICE "/dev/vx/dsk/rootdg/rootvol"
#endif

#if !defined( TEST_CHAR_DEVICE )
#define TEST_CHAR_DEVICE  "/dev/fd/0"
#endif

#if !defined( TEST_SETUID_FILE )
#define TEST_SETUID_FILE    "/usr/bin/su"
#endif

#if !defined( TEST_SETGID_FILE )
#define TEST_SETGID_FILE    "/usr/bin/write"
#endif

// #define STLUTILS_TEST_MULTI_GROUPS 1

/**
  Detail Documentation
  
  
  Example:
  
  See Also:
  
  Files:
  
  Documented Ver:
  
  Tested Ver:
  
**/

#endif /* ! def _TestConfig_hh_ */
