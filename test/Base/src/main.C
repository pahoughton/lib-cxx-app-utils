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
// Revision 1.2  1995/11/05 13:43:59  houghton
// Revised Test sources
//
//

#include <LibTest.hh>

#include <iostream.h>

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
// FilePath.hh
bool	tFilePath( LibTest & tester );
// Bitmask.hh
bool	tBitmask( LibTest & tester );
// SortOrder.hh
bool	tSortOrder( LibTest & tester );
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
// Directory
bool	tDirectory( LibTest & tester );

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


LibTest::TestItem   TestList[] =
{
#ifdef COMPONENT_TEST
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
#endif  
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
  { "Str",  	    	    tStr },
  { "SubStr",  	    	    tSubStr },
  { "RegexScan",    	    tRegexScan },  
  { "DateTimeUtils",        tDateTimeUtils },  
  { "DateTime",		    tDateTime },
  { "DateRange",	    tDateRange },
  { "DateRangeDaily",	    tDateRangeDaily },
  { "DateRangeWeekly",	    tDateRangeWeekly },
  { "FilePath",		    tFilePath },
  { "Bitmask",		    tBitmask },
  { "SortOrder",	    tSortOrder },
  { "User",		    tUser },
  { "UserGroup",	    tUserGroup },
  { "FileStat",		    tFileStat },
  { "Log",		    tLog },
  { "Param",		    tParam },
  { "Directory",	    tDirectory },
  { 0, 0 }
};

    
int
main( int argc, char * argv[] )
{
  LibTest test( TestList, cout, cerr );

  return( test.run( argc, argv ) );
}
