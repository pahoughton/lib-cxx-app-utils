//
// File:        IosSeekDirToString.C
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  Compiled sources for IosSeekDirToString
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/12/97 12:57
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//

#include <StlUtilsMisc.hh>

const char * 
IosSeekDirToString( ios::seek_dir dir )
{
  return( dir == ios::beg ? "beg" :
	  dir == ios::cur ? "cur" :
	  dir == ios::end ? "end" : "bad dir" );
}

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.2  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:15  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:29  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 14:10:15  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.2  1997/09/17 11:08:24  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/09/16 11:21:03  houghton
// Initial Version.
//
//
