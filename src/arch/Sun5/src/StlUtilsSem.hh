#ifndef _StlUtilsSem_hh_
#define _StlUtilsSem_hh_
//
// File:        StlUtilsSem.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     07/17/97 11:07
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define STLUTILS_SEM_BADKEY	    -1
#define STLUTILS_SEM_BADSEM	    -1

//
// Revision Log:
//
// $Log$
// Revision 6.1  2003/08/09 11:22:46  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:21  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:28  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:18  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/07/25 12:26:26  houghton
// Changed version number to 3.
//
// Revision 1.1  1997/07/18 19:55:31  houghton
// Initial Version.
//
//
#endif // ! def _StlUtilsSem_hh_ 

