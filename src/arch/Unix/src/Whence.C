//
// File:        Whence.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for Whence
//  
// Author:      Paul A. Houghton - (paul.houghton@mci.com)
// Created:     09/12/97 13:00
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "StlUtilsMisc.hh"
#include <iostream>
#include <cstdio>
#include <fcntl.h>


STLUTILS_FUNCT_VERSION(
  Whence,
  "$Id$ " );


int
Whence( ios::seek_dir dir )
{
  return( dir == ios::beg ? SEEK_SET :
	  dir == ios::cur ? SEEK_CUR :
	  dir == ios::end ? SEEK_END : -1 );
}


// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.1  2003/08/09 11:22:47  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:23  houghton
// Changed Version Num to 5
//
// Revision 4.2  1998/10/13 16:35:04  houghton
// Added include <cstdio>.
//
// Revision 4.1  1997/09/17 15:13:42  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 15:10:30  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.2  1997/09/17 11:09:29  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/09/16 11:21:27  houghton
// Initial Version.
//
//
