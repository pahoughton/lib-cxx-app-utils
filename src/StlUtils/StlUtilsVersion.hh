#ifndef _ClueVersion_hh_
#define _ClueVersion_hh_
//
// File:        ClueVersion.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     10/05/95 04:47
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:40:22  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  14:48:49  houghton
// New Class Version id method
//
//

#define CLUE_PRJ_NAME	"libClue"
#define CLUE_PRJ_VER	"2.00.00.a.02"
#define CLUE_PRJ_VER_NUM    2000002L

#define CLUE_VERSION( name_, verId_ ) \
CLASS_VERSION( name_, verId_, CLUE_PRJ_NAME, CLUE_PRJ_VER, CLUE_PRJ_VER_NUM )
				   
#define CLUE_FUNCT_VERSION( name_, verId_ )				      \
const char VERID_##name_[] =						      \
"@(#) " CLUE_PRJ_NAME " - " CLUE_PRJ_VER "\n"				      \
"    " #name_ " - " __FILE__ " - Compiled: " __DATE__ " "__TIME__ "\n"	      \
"    " verId_


#endif // ! def _ClueVersion_hh_ 

