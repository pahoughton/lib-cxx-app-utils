#ifndef _ClueVersion_hh_
#define _ClueVersion_hh_
//
// File:        ClueVersion.hh
// Project:	Clue
// Desc:        
//
//  Version macros for libClue. 
//
// Quick Start: - short example of usage
//
//  class Test { publie: static const ClassVersion version; };
//  CLUE_VERSION( Test, "Id:" );
//
//  int DoThis( int i );
//  CLUE_FUNCT_VERSION( DoThis, "Id:" );
// 
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     10/05/95 04:47
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

// Constants
#define CLUE_PRJ_NAME	    "libClue"
#define CLUE_PRJ_VER	    "3.02.04"
#define CLUE_PRJ_VER_NUM    0x03020400L
#define CLUE_PRJ_VER_TAG    "PROD_3_02"

// Macros
#define CLUE_VERSION( name_, verId_ )					      \
CLASS_VERSION( name_,							      \
	       verId_,							      \
	       CLUE_PRJ_NAME,						      \
	       CLUE_PRJ_VER,						      \
	       CLUE_PRJ_VER_NUM,					      \
	       CLUE_PRJ_VER_TAG )
				   
#define CLUE_FUNCT_VERSION( name_, verId_ )				      \
const char VERID_##name_[] =						      \
"@(#) " CLUE_PRJ_NAME " - " CLUE_PRJ_VER "\n"				      \
"    " #name_ " - " __FILE__ " - Compiled: " __DATE__ " "__TIME__ "\n"	      \
"    CVS Tag: " CLUE_PRJ_VER_TAG "\n"					      \
"    " verId_

// Detail Documentation
//
// Constants:
//
//  CLUE_PRJ_NAME       project name
//  CLUE_PRJ_VER        project version string
//  CLUE_PRJ_VER_NUM	project version number
//
// Macros:
//
//	CLUE_VERSION( name, verid )
//	    Uses CLASS_VERSION macro to instantiate the class's static
//	    version.
//
//	CLUE_FUNCT_VERSION( name, verid )
//	    creates a global const char[] variable that contains the
//	    version info for a function.
//
// See Also:
//
//  ClassVersion(3)
//
// Documented Ver:  2.2
//
// Revision Log:
//
// $Log$
// Revision 3.3  1997/04/26 14:41:11  houghton
// Added project tag support.
//
// Revision 3.2  1996/11/19 12:21:15  houghton
// Changed to Version 3
//
// Revision 3.1  1996/11/14 01:23:30  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 13:33:04  houghton
// Cleanup header comments.
//
// Revision 2.3  1996/10/28 12:01:17  houghton
// Cleanup.
//
// Revision 2.2  1996/10/28 11:58:14  houghton
// Changed version number
// Cleanup.
// Added documentation.
//
// Revision 2.1  1995/11/10 12:40:22  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  14:48:49  houghton
// New Class Version id method
//
//

#endif // ! def _ClueVersion_hh_ 

