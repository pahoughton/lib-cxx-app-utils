//
// File:        tAbsLong.C
// Project:	StlUtils
// Desc:        
//
//  Test for abs( long ) function.
//  
// Source Header Version: 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/31/96 07:17
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include <TestConfig.hh>
#include <LibTest.hh>
#include <StlUtilsMisc.hh>

bool
tAbsLong( LibTest & tester )
{
  {
    long  t = -12341234L;
    
    TEST( abs( t ) == 12341234L );

    t = 43214321L;
    
    TEST( abs( t ) == 43214321L );
  }

  return( true );
}

//
// $Log$
// Revision 6.1  2003/08/09 11:22:49  houghton
// Changed to version 6
//
// Revision 5.2  2001/07/26 19:28:56  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:26  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:02  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 15:11:06  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.2  1997/09/17 11:09:34  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:18  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/04 18:22:39  houghton
// Chaged include becuase StlUtils.hh renamed to StlUtilsUtils.hh.
//
// Revision 2.2  1996/11/04 14:43:56  houghton
// Added header comments.
//
//

