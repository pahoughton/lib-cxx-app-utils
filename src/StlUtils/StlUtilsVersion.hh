#ifndef _StlUtilsVersion_hh_
#define _StlUtilsVersion_hh_
//
// File:        StlUtilsVersion.hh
// Project:	StlUtils
// Desc:        
//
//  Version macros for libStlUtils. 
//
// Quick Start: - short example of usage
//
//  class Test { publie: static const ClassVersion version; };
//  STLUTILS_VERSION( Test, "Id:" );
//
//  int DoThis( int i );
//  STLUTILS_FUNCT_VERSION( DoThis, "Id:" );
// 
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     10/05/95 04:47
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

// Constants
#define STLUTILS_PRJ_NAME	"libStlUtils"
#define STLUTILS_PRJ_VER	VERSION
#define STLUTILS_PRJ_VER_NUM	0x04000001L
#define STLUTILS_PRJ_VER_TAG    "BETA_4_01"

// Macros
#define STLUTILS_VERSION( name_, verId_ )				      \
CLASS_VERSION( name_,							      \
	       verId_,							      \
	       STLUTILS_PRJ_NAME,					      \
	       STLUTILS_PRJ_VER,					      \
	       STLUTILS_PRJ_VER_NUM,					      \
	       STLUTILS_PRJ_VER_TAG )
				   
#define STLUTILS_FUNCT_VERSION( name_, verId_ )				      \
const char VERID_##name_[] =						      \
"@(#) " STLUTILS_PRJ_NAME " - " STLUTILS_PRJ_VER "\n"			      \
"    " #name_ " - " __FILE__ " - Compiled: " __DATE__ " "__TIME__ "\n"	      \
"    CVS Tag: " STLUTILS_PRJ_VER_TAG "\n"				      \
"    " verId_

// Detail Documentation
//
// Constants:
//
//  STLUTILS_PRJ_NAME       project name
//  STLUTILS_PRJ_VER        project version string
//  STLUTILS_PRJ_VER_NUM	project version number
//
// Macros:
//
//	STLUTILS_VERSION( name, verid )
//	    Uses CLASS_VERSION macro to instantiate the class's static
//	    version.
//
//	STLUTILS_FUNCT_VERSION( name, verid )
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
// Revision 5.1  2000/05/25 10:33:17  houghton
// Changed Version Num to 5
//
// Revision 4.4  1998/03/23 10:45:14  houghton
// Changed to eliminate Sun5 compiler warnings.
//
// Revision 4.3  1997/12/19 14:01:20  houghton
// Cleanup
// Changed VER_TAG to BETA_4_01.
//
// Revision 4.2  1997/09/17 15:44:51  houghton
// Changed prj version info.
//
// Revision 4.1  1997/09/17 15:12:51  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:08:43  houghton
// Changed: renamed library to StlUtils.
//
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

#endif // ! def _StlUtilsVersion_hh_ 

