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
// Author:      Paul Houghton - (paul.houghton@wcom.com)
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
// Revision 1.1  1998/07/20 11:28:20  houghton
// Initial Version.
//
//
#endif // ! def _StlUtilsExceptions_hh_ 

