// 2017-04-19 (cc) <paul4hough@gmail.com>
#include <valid/verify.hpp>

extern bool v_AbsLong(void);
extern bool v_Align(void);
extern bool v_Between(void);
extern bool v_CharIsBaseDigit(void);
extern bool v_CharToInt(void);
extern bool v_CommaNum(void);
extern bool v_DwordAlign(void);
extern bool v_IsBaseDigit(void);
extern bool v_IsTimetDst(void);
extern bool v_MemOverlap(void);
extern bool v_MfNumTo(void);
extern bool v_OpenFlags(void);
extern bool v_Round(void);
extern bool v_SafeStrcpy(void);
extern bool v_SortOrder(void);
extern bool v_UnionOf(void);
extern bool v_VectorResync(void);

extern bool v_bit(void);
extern bool v_bitmask01(void);
extern bool v_bitmask02(void);
extern bool v_bitmask03(void);

extern bool v_compare01(void);
extern bool v_compare02(void);

extern bool v_DateTimeUtils(void);
extern bool v_DateTime01(void);
extern bool v_DateTime02(void);
extern bool v_DateTime03(void);
extern bool v_DateTime04(void);
extern bool v_DateTime05(void);
extern bool v_DateTime06(void);
extern bool v_DateTime07(void);
extern bool v_DateRange(void);
extern bool v_DateRangeDaily(void);
extern bool v_DateRangeWeekly(void);

extern bool v_LogLevel(void);
extern bool v_StringCapitalize(void);
extern bool v_StringCaseCompare(void);
extern bool v_StringFirstNotOf(void);
extern bool v_StringFrom(void);
extern bool v_StringLower(void);
extern bool v_StringSearch(void);
extern bool v_StringTo(void);
extern bool v_StringToInt(void);
extern bool v_StringUpper(void);
extern bool v_StripTrailing(void);
extern bool v_StripWhite(void);
extern bool v_Str01(void);
extern bool v_Str02(void);
extern bool v_Str03(void);
extern bool v_Str04(void);
extern bool v_Str05(void);
extern bool v_Str06(void);
extern bool v_Str07(void);
extern bool v_Str08(void);
extern bool v_Str09(void);
extern bool v_Str10(void);
extern bool v_Str11(void);
extern bool v_Str12(void);
extern bool v_Str13(void);
extern bool v_Str14(void);
extern bool v_Str15(void);
extern bool v_Str16(void);
extern bool v_Str17(void);
extern bool v_Str18(void);
extern bool v_Str19(void);
extern bool v_Str20(void);
extern bool v_Str21(void);
extern bool v_Str22(void);
extern bool v_Str23(void);
extern bool v_Str24(void);
extern bool v_Str25(void);
extern bool v_Str26(void);
extern bool v_SubStr01(void);
extern bool v_SubStr02(void);
extern bool v_SubStr03(void);
extern bool v_SubStr04(void);
extern bool v_SubStr05(void);
extern bool v_SubStr06(void);
extern bool v_SubStr07(void);
extern bool v_User(void);
extern bool v_UserGroup(void);
extern bool v_FilePath01(void);
extern bool v_FilePath02(void);
extern bool v_FilePath03(void);
extern bool v_FilePath04(void);
extern bool v_FileStat01(void);
extern bool v_FileStat02(void);
extern bool v_FileStat03(void);
extern bool v_FileStat04(void);
extern bool v_FileStat05(void);
extern bool v_FileStat06(void);
extern bool v_FileOp01(void);
extern bool v_FileOp02(void);

extern bool v_LogLevel(void);
extern bool v_Log01(void);
extern bool v_Log02(void);
extern bool v_Log03(void);
extern bool v_Log04(void);
extern bool v_Log05(void);
extern bool v_Log06(void);
extern bool v_Log07(void);
extern bool v_Log08(void);
extern bool v_Log09(void);

extern bool v_Param01(void);
extern bool v_Param02(void);
extern bool v_Param03(void);

extern bool v_TimeIt01(void);

extern valid::verify &  v_Password(void);
extern valid::verify &  v_FileBatch(void);
extern valid::verify &  v_FileLock(void);
extern valid::verify &  v_SigCatcher(void);
extern valid::verify &  v_MesgQueue(void);
extern valid::verify &  v_Semaphore(void);
extern valid::verify &  v_HotSwap(void);
extern valid::verify &  v_InboundProcessor(void);
extern valid::verify &  v_PidFile(void);


int main( int argc, char * argv[] ) {

  bool verbose = ! true;
  bool oldStatus = v_bit()
    && v_AbsLong()
    && v_Align()
    && v_Between()
    && v_CharIsBaseDigit()
    && v_CharToInt()
    && v_CommaNum()
    && v_DwordAlign()
    && v_IsBaseDigit()
    && v_IsTimetDst()
    && v_MemOverlap()
    && v_MfNumTo()
    && v_OpenFlags()
    && v_Round()
    && v_SafeStrcpy()
    && v_SortOrder()
    && v_UnionOf()
    && v_VectorResync()
    && v_StringTo()
    && v_StringCapitalize()
    && v_StringCaseCompare()
    && v_StringFirstNotOf()
    && v_StringFrom()
    && v_StringLower()
    && v_StringSearch()
    && v_StringUpper()
    && v_StripTrailing()
    && v_StripWhite()
    && v_compare01()
    && v_compare02()
    && v_bitmask01()
    && v_bitmask02()
    && v_bitmask03()
    && v_Str01()
    && v_Str02()
    && v_Str03()
    && v_Str04()
    && v_Str05()
    && v_Str06()
    && v_Str07()
    && v_Str08()
    && v_Str09()
    && v_Str10()
    && v_Str11()
    && v_Str12()
    && v_Str13()
    && v_Str14()
    && v_Str15()
    && v_Str16()
    && v_Str17()
    && v_Str18()
    && v_Str19()
    && v_Str20()
    && v_Str21()
    && v_Str22()
    && v_Str23()
    && v_Str24()
    && v_Str25()
    && v_Str26()
    && v_SubStr01()
    && v_SubStr02()
    && v_SubStr03()
    && v_SubStr04()
    && v_SubStr05()
    && v_SubStr06()
    && v_SubStr07()
    && v_DateTimeUtils()
    && v_DateTime01()
    && v_DateTime02()
    && v_DateTime03()
    && v_DateTime04()
    && v_DateTime05()
    && v_DateTime06()
    && v_DateTime07()
    && v_DateRange()
    && v_DateRangeDaily()
    && v_DateRangeWeekly()
    && v_FilePath01()
    && v_FilePath02()
    && v_FilePath03()
    && v_FilePath04()
    && v_FileStat01()
    && v_FileStat02()
    && v_FileStat03()
    && v_FileStat04()
    && v_FileStat05()
    && v_FileStat06()
    && v_FileOp01()
    && v_FileOp02()
    && v_LogLevel()
    && v_Log01()
    && v_Log02()
    && v_Log03()
    && v_Log04()
    && v_Log05()
    && v_Log06()
    && v_Log07()
    && v_Log08()
    && v_Log09()
    && v_Param01()
    && v_Param02()
    && v_Param03()
    // FIXME - slow && v_TimeIt01()
    && v_User()
    && v_UserGroup()
    && v_VectorResync()
    ;

  if( ! oldStatus ) {
    return( 1 );
  }

  valid::verify t;

#define DOTEST( _tfunct_ )						\
    t = _tfunct_;							\
    if( verbose ) std::cout << t << std::endl;				\
    if( t.passing() ) {							\
      std::cout << t.name()  << ' '					\
		<< t.results().size()					\
		<< " validations passed :)"				\
		<< std::endl;						\
    } else {								\
      std::cout << "ERROR:" << t.name() << " one or more failures!" << std::endl; \
      return( 1 );							\
    }

  DOTEST( v_Password() );
  DOTEST( v_FileBatch() );
  DOTEST( v_FileLock() );
  DOTEST( v_SigCatcher() );
  DOTEST( v_MesgQueue() );
  DOTEST( v_Semaphore() );
  DOTEST( v_HotSwap() );
  DOTEST( v_InboundProcessor() );
  DOTEST( v_PidFile() );

  return( 0 );
}
