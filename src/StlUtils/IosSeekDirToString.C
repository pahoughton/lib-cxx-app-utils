//
// File:        IosSeekDirToString.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for IosSeekDirToString
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/12/97 12:57
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <StlUtilsUtils.hh>

const char * 
IosSeekDirToString( ios::seek_dir dir )
{
  return( dir == ios::beg ? "beg" :
	  dir == ios::cur ? "cur" :
	  dir == ios::end ? "end" : "bad dir" );
}

// Revision Log:
//
// $Log$
// Revision 3.2  1997/09/17 11:08:24  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/09/16 11:21:03  houghton
// Initial Version.
//
//
