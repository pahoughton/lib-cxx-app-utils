//
// File:        main.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/01/95 12:08 
//
// Revision History:
//
// $Log$
// Revision 1.4  1995/11/05 15:29:37  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <iostream>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <iostream>
#endif

// Utils.hh
bool	tArraySize( LibTest & tester );
bool	tDwordAlign( LibTest & tester );
bool	tMemOverlap( LibTest & tester );
bool	tAbsLong( LibTest & tester );
bool	tIsBaseDigit( LibTest & tester );
bool	tUnionOf( LibTest & tester );
bool	tRound( LibTest & tester );
// Bit.hh
bool	tBit( LibTest & tester );
// Compare.hh
bool	tCompare( LibTest & tester );
// StringUtils.hh
bool	tSafeStrcpy( LibTest & tester );
bool	tCharToInt( LibTest & tester );
bool	tStripWhite( LibTest & tester );
bool	tStringSearch( LibTest & tester );
bool	tStringCaseCompare( LibTest & tester );
bool	tStringLower( LibTest & tester );
bool	tStringUpper( LibTest & tester );
bool	tStringCapitalize( LibTest & tester );
bool	tStringTo( LibTest & tester );
bool	tbasename( LibTest & tester );
// BinStream.hh
// RandomBinStream.hh
// HeapBinStream.hh
bool	tHeapBinStream( LibTest & tester );
// Str.hh
bool	tStr( LibTest & tester );
// SubStr.hh
bool	tSubStr( LibTest & tester );
// RegexScan.hh
bool	tRegexScan( LibTest & tester );
// DateTimeUtils.hh
bool	tDateTimeUtils( LibTest & tester );
// DateTime.hh
bool	tDateTime( LibTest & tester );
// DateRange.hh
bool	tDateRange( LibTest & tester );
// DateRangeDaily.hh
bool	tDateRangeDaily( LibTest & tester );
// DateRangeWeekly.hh
bool	tDateRangeWeekly( LibTest & tester );
// Bitmask.hh
bool	tBitmask( LibTest & tester );
// SortOrder.hh
bool	tSortOrder( LibTest & tester );
// FilePath.hh
bool	tFilePath( LibTest & tester );
// User.hh
bool	tUser( LibTest & tester );
// UserGroup.hh
bool	tUserGroup( LibTest & tester );
// FileStat.hh
bool	tFileStat( LibTest & tester );
// LogLevel.hh LogBuf.hh Log.hh
bool	tLog( LibTest & tester );
// Param.hh
bool	tParam( LibTest & tester );

// libClue works with LibCommon
bool	tWithCommon( LibTest & tester );

// Components
bool tCompare01( LibTest & test );
bool tCompare02( LibTest & test );
bool tStr01( LibTest & test ); 
bool tStr02( LibTest & test ); 
bool tStr03( LibTest & test ); 
bool tStr04( LibTest & test ); 
bool tStr05( LibTest & test ); 
bool tStr06( LibTest & test ); 
bool tStr07( LibTest & test ); 
bool tStr08( LibTest & test ); 
bool tStr09( LibTest & test ); 
bool tStr10( LibTest & test ); 
bool tStr11( LibTest & test ); 
bool tStr12( LibTest & test ); 
bool tStr13( LibTest & test ); 
bool tStr14( LibTest & test ); 
bool tStr15( LibTest & test ); 
bool tStr16( LibTest & test ); 
bool tStr17( LibTest & test ); 
bool tStr18( LibTest & test ); 
bool tStr19( LibTest & test ); 
bool tStr20( LibTest & test ); 
bool tStr21( LibTest & test ); 
bool tStr22( LibTest & test ); 
bool tStr23( LibTest & test ); 
bool tStr24( LibTest & test );
bool tStr25( LibTest & test );
bool tStr26( LibTest & test );
bool tSubStr01( LibTest & test );
bool tSubStr02( LibTest & test );
bool tSubStr03( LibTest & test );
bool tSubStr04( LibTest & test );
bool tSubStr05( LibTest & test );
bool tSubStr06( LibTest & test );
bool tSubStr07( LibTest & test );
bool tDateTime01( LibTest & tester );
bool tDateTime02( LibTest & tester );
bool tDateTime03( LibTest & tester );
bool tDateTime04( LibTest & tester );
bool tDateTime05( LibTest & tester );
bool tDateTime06( LibTest & tester );
bool tDateTime07( LibTest & tester );
bool tDateTime08( LibTest & tester );
bool tBitmask01( LibTest & tester );
bool tBitmask02( LibTest & tester );
bool tBitmask03( LibTest & tester );
bool tFilePath01( LibTest & tester );
bool tFilePath02( LibTest & tester );
bool tFilePath03( LibTest & tester );
bool tFilePath04( LibTest & tester );
bool tLogLevel( LibTest & tester );
bool tLog01( LibTest & tester );
bool tLog02( LibTest & tester );
bool tLog03( LibTest & tester );
bool tLog04( LibTest & tester );
bool tLog05( LibTest & tester );



LibTest::TestItem   TestList[] =
{
  { "ArraySize",    	    tArraySize },
  { "DwordAlign",   	    tDwordAlign },
  { "MemOverlap",   	    tMemOverlap },
  { "AbsLong",	    	    tAbsLong },
  { "IsBaseDigit",  	    tIsBaseDigit },
  { "UnionOf",	    	    tUnionOf },
  { "Round",	    	    tRound },
  { "Bit",    	    	    tBit },
  { "Compare", 	    	    tCompare },
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
  { "HeapBinStream",	    tHeapBinStream },
  { "Str",  	    	    tStr },
  { "SubStr",  	    	    tSubStr },
  { "RegexScan",    	    tRegexScan },  
  { "DateTimeUtils",        tDateTimeUtils },  
  { "DateTime",		    tDateTime },
  { "DateRange",	    tDateRange },
  { "DateRangeDaily",	    tDateRangeDaily },
  { "DateRangeWeekly",	    tDateRangeWeekly },
  { "Bitmask",		    tBitmask },
  { "SortOrder",	    tSortOrder },
  { "FilePath",		    tFilePath },
  { "User",		    tUser },
  { "UserGroup",	    tUserGroup },
  { "FileStat",		    tFileStat },
  { "Log",		    tLog },
  { "Param",		    tParam },
  { "WithCommon",	    tWithCommon },
#if 0
#endif
#ifdef COMPONENT_TEST
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
#if TEST_DUMPINFO_SCREEN
  ostream & dumpDest( cout );
#else
  ofstream  dumpDest( TEST_DUMP_DEST );
#endif
  
  LibTest test( TestList, dumpDest, cout, cerr );

  return( test.run( argc, argv ) );
}
