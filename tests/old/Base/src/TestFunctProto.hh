#ifndef _TestFunctProto_hh_
#define _TestFunctProto_hh_
//
// File:        TestFunctProto.hh
// Project:	StlUtils
// Desc:        
//
//  Function prototypes for test functions
//
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     04/29/96 07:42
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

// Utils.hh
bool	tArraySize( LibTest & tester );
bool	tOpenFlags( LibTest & tester );
bool	tAlign( LibTest & tester );
bool	tDwordAlign( LibTest & tester );
bool	tMemOverlap( LibTest & tester );
bool	tBetween( LibTest & tester );
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
bool	tCharIsBaseDigit( LibTest & tester );
bool	tStripWhite( LibTest & tester );
bool	tStripTrailing( LibTest & tester );
bool	tStringSearch( LibTest & tester );
bool	tStringCaseCompare( LibTest & tester );
bool	tStringLower( LibTest & tester );
bool	tStringUpper( LibTest & tester );
bool	tStringCapitalize( LibTest & tester );
bool	tStringTo( LibTest & tester );
bool	tStringFrom( LibTest & tester );
bool	tStringFirstNotOf( LibTest & tester );
bool	tbasename( LibTest & tester );
bool	tMfNumTo( LibTest & tester );

// ClassVersion.hh
bool	tClassVersion( LibTest & tester );
// BinStream.hh
// RandomBinStream.hh
// HeapBinStream.hh
bool	tHeapBinStream( LibTest & tester );
// HeapNetStream.hh
bool	tHeapNetStream( LibTest & tester );
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
// IsTimetDst.C
bool	tIsTimetDst( LibTest & tester );

// Bitmask.hh
bool	tBitmask( LibTest & tester );
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
// File.hh
bool	tFileOp( LibTest & tester );
// SortOrder.hh
bool	tSortOrder( LibTest & tester );
// Directory.hh
bool	tDirectory( LibTest & tester );
// TimeIt.hh
bool	tTimeIt( LibTest & tester );

bool	tLruMap( LibTest & tester );
bool	tLruSash( LibTest & tester );

// libStlUtils works with LibCommon
bool	tWithCommon( LibTest & tester );
// libStlUtils works with Wcf
bool	tWithWcf( LibTest & tester );

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
// FileBinStream.hh
bool	tFileBinStream( LibTest & tester );

// VectorResync.hh
bool tVectorResync( LibTest & tester );

bool tCommaNum( LibTest & tester );

// Revision Log:
//
// $Log$
// Revision 6.4  2011/12/30 23:57:41  paul
// First go at Mac gcc Port
//
// Revision 6.3  2005/09/09 18:51:13  houghton
// *** empty log message ***
//
// Revision 6.2  2004/04/19 18:17:12  houghton
// Added tCommaNum proto
//
// Revision 6.1  2003/08/09 11:22:49  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:26  houghton
// Changed Version Num to 5
//
// Revision 4.10  1999/03/02 12:54:07  houghton
// Added tBetween.
//
// Revision 4.9  1998/11/02 19:36:18  houghton
// Changed: the File class was renamed to FileOp.
//
// Revision 4.8  1998/11/02 15:28:34  houghton
// Added LruSash
//
// Revision 4.7  1998/10/13 15:21:02  houghton
// Added LruMap tests.
//
// Revision 4.6  1998/04/02 14:19:22  houghton
// Cleanup and eliminate warnings.
//
// Revision 4.5  1998/03/21 13:55:53  houghton
// Added test for 'File'.
//
// Revision 4.4  1998/01/05 13:09:20  houghton
// Added tVectorResync
//
// Revision 4.3  1997/12/20 16:12:26  houghton
// Added tStripTrailing.
//
// Revision 4.2  1997/12/19 12:52:55  houghton
// Added tMfNumTo
//
// Revision 4.1  1997/09/17 15:14:01  houghton
// Changed to Version 4
//
// Revision 3.5  1997/09/17 11:09:33  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.4  1997/08/12 11:11:44  houghton
// Added tStringFirstNotOf
//
// Revision 3.3  1997/07/11 15:56:57  houghton
// Added tTimeIt.
//
// Revision 3.2  1996/11/19 12:33:07  houghton
// Added StringFrom.
//
// Revision 3.1  1996/11/14 01:26:16  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 14:42:59  houghton
// Restructure header comments layout.
// Added the following test function prototypes.
//     bool	tOpenFlags( LibTest & tester );
//     bool	tAlign( LibTest & tester );
//     bool	tCharIsBaseDigit( LibTest & tester );
//     bool	tClassVersion( LibTest & tester );
//
// Revision 2.3  1996/08/12 17:50:11  houghton
// Added test for FileBinStream.
//
// Revision 2.2  1996/06/09 09:46:43  houghton
// Added tHeapNetStream.
//
// Revision 2.1  1996/05/01 11:04:50  houghton
// Initial version.
//
//
#endif // ! def _TestFunctProto_hh_ 

