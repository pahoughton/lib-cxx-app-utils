#ifndef _StlUtilsExceptions_hh_
#define _StlUtilsExceptions_hh_
/**
  File:		StlUtilsExceptions.hh
  Project:	StlUtils 
  Desc:

    
  
  Notes:
    
  Author(s):	Paul Houghton <<paul.houghton@mci.com>>
  Created:	07/19/2003 04:28
  
  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Name$
    $Revision$
    $State$

  $Id$

**/

#define STLUTILS_EXCPT_OUT_OF_RANGE( test_, ret_ ) \
  if( (test_) ) return( ret_ );

#define STLUTILS_EXCPT_BAD_ALLOC( test_, ret_ ) \
  if( (test_) ) return( ret_ );

#define STLUTILS_EXCPT_NR_OUT_OF_RANGE( test_ ) \
  if( (test_) ) return;

#define STLUTILS_EXCPT_NR_BAD_ALLOC( test_, ret_ ) \
  if( (test_) ) return;


/**
  Detail Documentation
  
    Macros:  
  
  Example:
  
  See Also:
  
  Files:
  
  Documented Ver:
  
  Tested Ver:
  
**/

#endif /* ! def _StlUtilsExceptions_hh_ */
