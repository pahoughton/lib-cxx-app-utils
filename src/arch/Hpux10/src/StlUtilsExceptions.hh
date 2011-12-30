#ifndef _StlUtilsExceptions_hh_
#define _StlUtilsExceptions_hh_
//
// File:        StlUtilsExceptions.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     07/09/98 11:15
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#define STLUTILS_EXCPT_OUT_OF_RANGE( test_, ret_ ) \
  if( (test_) ) return( ret_ );

#define STLUTILS_EXCPT_BAD_ALLOC( test_, ret_ ) \
  if( (test_) ) return( ret_ );

#define STLUTILS_EXCPT_NR_OUT_OF_RANGE( test_ ) \
  if( (test_) ) return;

#define STLUTILS_EXCPT_NR_BAD_ALLOC( test_, ret_ ) \
  if( (test_) ) return;

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
// Revision 6.2  2011/12/30 23:57:25  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:45  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:19  houghton
// Changed Version Num to 5
//
// Revision 1.1  1998/07/20 11:28:20  houghton
// Initial Version.
//
//
#endif // ! def _StlUtilsExceptions_hh_ 

