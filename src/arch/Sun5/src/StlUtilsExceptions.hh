#ifndef _StlUtilsExceptinos_hh_
#define _StlUtilsExceptinos_hh_
//
// File:        Exceptinos.hh
// Desc:        
//
//
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     07/23/95 06:43
//
// Revision History:
//
// $Log$
// Revision 1.2  1997/09/17 11:09:17  houghton
// Changed: renamed library to StlUtils.
//
// Revision 1.1  1997/08/18 10:31:33  houghton
// Initial version.
//
// Revision 3.1  1996/11/14 01:25:18  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:06  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:01:35  houghton
// Port to AIX
//
//

#define STLUTILS_EXCPT_OUT_OF_RANGE( test_, ret_ ) \
  if( (test_) ) return( ret_ );

#define STLUTILS_EXCPT_BAD_ALLOC( test_, ret_ ) \
  if( (test_) ) return( ret_ );

#define STLUTILS_EXCPT_NR_OUT_OF_RANGE( test_ ) \
  if( (test_) ) return;

#define STLUTILS_EXCPT_NR_BAD_ALLOC( test_, ret_ ) \
  if( (test_) ) return;


#endif // ! def _StlUtilsExceptinos_hh_ 



