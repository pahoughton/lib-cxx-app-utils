//
// File:        main.C
// Project:	Clue
// Desc:        
//
//  Entry point for testing libClue classes, functions & macros.
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/01/95 12:08 
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include "TestConfig.hh"
#include "LibTest.hh"
#include "TestFunctProto.hh"
#include <iostream>



LibTest::TestItem   TestList[] =
{
  { "ArraySize",    	    tArraySize },
  { "OpenFlags",	    tOpenFlags },
  { "Align",		    tAlign },
  { "DwordAlign",   	    tDwordAlign },
  { "MemOverlap",   	    tMemOverlap },
  { "AbsLong",	    	    tAbsLong },
  { "IsBaseDigit",  	    tIsBaseDigit },
  { "UnionOf",	    	    tUnionOf },
  { "Round",	    	    tRound },
  { "Bit",    	    	    tBit },
  { "Compare", 	    	    tCompare },
  { "CharToInt",    	    tCharToInt },
  { "SafeStrcpy",   	    tSafeStrcpy },
  { "CharIsBaseDigit",	    tCharIsBaseDigit },
  { "StringCapitalize",	    tStringCapitalize },
  { "StringCaseCompare",    tStringCaseCompare },
  { "StringLower",  	    tStringLower },
  { "StringSearch", 	    tStringSearch },
  { "StringTo",  	    tStringTo },
  { "StringFrom",	    tStringFrom },
  { "StringUpper",  	    tStringUpper },
  { "StripWhite",   	    tStripWhite },
  { "StringFirstNotOf",	    tStringFirstNotOf },
  { "basename",     	    tbasename },
  { "ClassVersion",	    tClassVersion },
  { "Bitmask",		    tBitmask },
  { "Str",  	    	    tStr },
  { "SubStr",  	    	    tSubStr },
  { "RegexScan",    	    tRegexScan },  
  { "DateTimeUtils",        tDateTimeUtils },  
  { "DateTime",		    tDateTime },
  { "DateRange",	    tDateRange },
  { "DateRangeDaily",	    tDateRangeDaily },
  { "DateRangeWeekly",	    tDateRangeWeekly },
  { "FilePath",		    tFilePath },
  { "User",		    tUser },
  { "UserGroup",	    tUserGroup },
  { "FileStat",		    tFileStat },
  { "LogLevel",		    tLogLevel },
  { "Log",		    tLog },
  { "Param",		    tParam },
  { "SortOrder",	    tSortOrder },
  { "TimeIt",		    tTimeIt },
#if defined( ALL )
  { "WithCommon",	    tWithCommon },
  { "WithWcf",		    tWithWcf },
#endif
  
#if defined( COMPONENT_TEST )
  { "ArraySize",    	    tArraySize },
  { "DwordAlign",   	    tDwordAlign },
  { "MemOverlap",   	    tMemOverlap },
  { "AbsLong",	    	    tAbsLong },
  { "IsBaseDigit",  	    tIsBaseDigit },
  { "UnionOf",	    	    tUnionOf },
  { "Round",	    	    tRound },
  { "Bit",    	    	    tBit },
  { "Compare01",	    tCompare01 },
  { "Compare02",	    tCompare02 },
  { "SafeStrcpy",   	    tSafeStrcpy },
  { "CharToInt",    	    tCharToInt },
  { "StripWhite",   	    tStripWhite },
  { "StringSearch", 	    tStringSearch },
  { "StringCaseCompare",    tStringCaseCompare },
  { "StringLower",  	    tStringLower },
  { "StringUpper",  	    tStringUpper },
  { "StringCapitalize",	    tStringCapitalize },
  { "StringTo",  	    tStringTo },
  { "basename",     	    tbasename },
  { "BinStream",	    tBinStream },
  { "Str01",  	    	    tStr01 },
  { "Str02",  	    	    tStr02 },
  { "Str03",  	    	    tStr03 },
  { "Str04",  	    	    tStr04 },
  { "Str05",  	    	    tStr05 },
  { "Str06",  	    	    tStr06 },
  { "Str07",  	    	    tStr07 },
  { "Str08",  	    	    tStr08 },
  { "Str09",  	    	    tStr09 },
  { "Str10",  	    	    tStr10 },
  { "Str11",  	    	    tStr11 },
  { "Str12",  	    	    tStr12 },
  { "Str13",  	    	    tStr13 },
  { "Str14",  	    	    tStr14 },
  { "Str15",  	    	    tStr15 },
  { "Str16",  	    	    tStr16 },
  { "Str17",  	    	    tStr17 },
  { "Str18",  	    	    tStr18 },
  { "Str19",  	    	    tStr19 },
  { "Str20",  	    	    tStr20 },
  { "Str21",  	    	    tStr21 },
  { "Str22",  	    	    tStr22 },
  { "Str23",  	    	    tStr23 },
  { "Str24",  	    	    tStr24 },
  { "Str25",  	    	    tStr25 },
  { "Str26",  	    	    tStr26 },
  { "SubStr01",		    tSubStr01 },
  { "SubStr02",		    tSubStr02 },
  { "SubStr03",		    tSubStr03 },
  { "SubStr04",		    tSubStr04 },
  { "SubStr05",		    tSubStr05 },
  { "SubStr06",		    tSubStr06 },
  { "SubStr07",		    tSubStr07 },
  { "RegexScan",    	    tRegexScan },  
  { "DateTimeUtils",        tDateTimeUtils },  
  { "DateTime01",	    tDateTime01 },
  { "DateTime02",	    tDateTime02 },
  { "DateTime03",	    tDateTime03 },
  { "DateTime04",	    tDateTime04 },
  { "DateTime05",	    tDateTime05 },
  { "DateTime06",	    tDateTime06 },
  { "DateTime07",	    tDateTime07 },
  { "DateTime08",	    tDateTime08 },
  { "DateRange",	    tDateRange },
  { "DateRangeDaily",	    tDateRangeDaily },
  { "DateRangeWeekly",	    tDateRangeWeekly },
  { "Bitmask01",	    tBitmask01 },
  { "Bitmask02",	    tBitmask02 },
  { "Bitmask03",	    tBitmask03 },
  { "SortOrder",	    tSortOrder },
  { "FilePath01",	    tFilePath01 },
  { "FilePath02",	    tFilePath02 },
  { "FilePath03",	    tFilePath03 },
  { "FilePath04",	    tFilePath04 },
  { "User",		    tUser },
  { "UserGroup",	    tUserGroup },
  { "FileStat01",	    tFileStat01 },
  { "FileStat02",	    tFileStat02 },
  { "FileStat03",	    tFileStat03 },
  { "FileStat04",	    tFileStat04 },
  { "FileStat05",	    tFileStat05 },
  { "FileStat06",	    tFileStat06 },
  { "LogLevel",		    tLogLevel },
  { "Log01",		    tLog01 },
  { "Log02",		    tLog02 },
  { "Log03",		    tLog03 },
  { "Log04",		    tLog04 },
  { "Log05",		    tLog05 },
  { "Param01",		    tParam01 },
#endif  
  { 0, 0 }
};

    
int
main( int argc, char * argv[] )
{
  
  // Log   log;

  // _LibLog = &log;

  // log.setOutputLevel( LogLevel::All );

#if TEST_DUMPINFO_SCREEN
  ostream & dumpDest( cout );
#else
  ofstream  dumpDest( TEST_DUMP_DEST );
#endif
  
  LibTest test( TestList, TEST_LINE_PROGRESS, dumpDest, cout, cerr );

  return( test.run( argc, argv ) );
}

//
// Revision Log:
//
// $Log$
// Revision 3.8  1997/08/12 11:11:49  houghton
// Added tStringFirstNotOf
//
// Revision 3.7  1997/07/11 15:57:00  houghton
// Added tTimeIt.
//
// Revision 3.6  1997/03/03 14:38:42  houghton
// Removed support for RW Tools++ & rpm.
//
// Revision 3.5  1996/11/24 19:13:12  houghton
// Removed support for short filenames.
//
// Revision 3.4  1996/11/22 12:26:18  houghton
// Added FilePath test.
//
// Revision 3.3  1996/11/20 12:15:26  houghton
// Added test for other souces.
//
// Revision 3.2  1996/11/19 12:33:13  houghton
// Added StringFrom.
//
// Revision 3.1  1996/11/14 01:26:17  houghton
// Changed to Release 3
//
// Revision 2.9  1996/11/08 11:46:54  houghton
// *** empty log message ***
//
// Revision 2.8  1996/11/06 18:14:47  houghton
// Changed to run all test.
//
// Revision 2.7  1996/11/04 14:43:32  houghton
// Restructure header comments layout.
// Changed to only run test on the classes/functions that are ready.
//
// Revision 2.6  1996/08/12 17:50:12  houghton
// Added test for FileBinStream.
//
// Revision 2.5  1996/06/09 09:47:01  houghton
// Added tHeapNetStream.
// Added LibLog.
//
// Revision 2.4  1996/05/03 16:17:49  houghton
// Added output for each test.
//
// Revision 2.3  1996/05/01 11:05:28  houghton
// Run all test.
//
// Revision 2.2  1996/02/29 19:11:09  houghton
// *** empty log message ***
//
// Revision 2.1  1995/11/10 12:48:40  houghton
// Change to Version 2
//
// Revision 1.5  1995/11/05  16:04:21  houghton
// Revised
//
//
