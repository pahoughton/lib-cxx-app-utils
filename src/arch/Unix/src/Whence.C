//
// File:        Whence.C
// Project:	Clue
// Desc:        
//
//  Compiled sources for Whence
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/12/97 13:00
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "ClueUtils.hh"
#include <iostream>
#include <fcntl.h>

CLUE_FUNCT_VERSION(
  Whence,
  "$Id$" );


int
Whence( ios::seek_dir dir )
{
  return( dir == ios::beg ? SEEK_SET :
	  dir == ios::cur ? SEEK_CUR :
	  dir == ios::end ? SEEK_END : -1 );
}


// Revision Log:
//
// $Log$
// Revision 3.1  1997/09/16 11:21:27  houghton
// Initial Version.
//
//
