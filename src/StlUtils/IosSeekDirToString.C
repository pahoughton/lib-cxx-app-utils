//
// File:        IosSeekDirToString.C
// Project:	Clue
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

#include <ClueUtils.hh>

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
// Revision 3.1  1997/09/16 11:21:03  houghton
// Initial Version.
//
//
