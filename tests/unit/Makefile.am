# 2017-04-19 (cc) <paul4hough@gmail.com>
#

check_PROGRAMS = unit
unit_LDADD = ../../src/clue/libclue.la
unit_CPPFLAGS =	-I../../src			\
	-DTEST_USER='"$(USER)"'			\
	-DTEST_GROUP="\"`id -gn`\""		\
	-DTEST_APPNAME='"unit"'

unit_SOURCES =					\
	main.cpp				\
        v_AbsLong.cpp				\
        v_Align.cpp				\
        v_Between.cpp				\
        v_bit.cpp				\
        v_bitmask01.cpp				\
        v_bitmask02.cpp				\
        v_bitmask03.cpp				\
        v_CharIsBaseDigit.cpp			\
        v_CharToInt.cpp				\
        v_CommaNum.cpp				\
        v_compare01.cpp				\
        v_compare02.cpp				\
        v_DateRange.cpp				\
        v_DateRangeDaily.cpp			\
        v_DateRangeWeekly.cpp			\
        v_DateTime01.cpp			\
        v_DateTime02.cpp			\
        v_DateTime03.cpp			\
        v_DateTime04.cpp			\
        v_DateTime05.cpp			\
        v_DateTime06.cpp			\
        v_DateTime07.cpp			\
        v_DateTimeUtils.cpp			\
        v_DwordAlign.cpp			\
	v_FileBatch.cpp				\
	v_FileLock.cpp				\
        v_FileOp01.cpp				\
        v_FileOp02.cpp				\
        v_FilePath01.cpp			\
        v_FilePath02.cpp			\
        v_FilePath03.cpp			\
        v_FilePath04.cpp			\
        v_FileStat01.cpp			\
        v_FileStat02.cpp			\
        v_FileStat03.cpp			\
        v_FileStat04.cpp			\
        v_FileStat05.cpp			\
        v_FileStat06.cpp			\
	v_HotSwap.cpp				\
	v_InboundProcessor.cpp			\
        v_IsBaseDigit.cpp			\
        v_IsTimetDst.cpp			\
        v_Log01.cpp				\
        v_Log02.cpp				\
        v_Log03.cpp				\
        v_Log04.cpp				\
        v_Log05.cpp				\
        v_Log06.cpp				\
        v_Log07.cpp				\
        v_Log08.cpp				\
        v_Log09.cpp				\
        v_LogLevel.cpp				\
        v_MemOverlap.cpp			\
	v_MesgQueue.cpp				\
        v_MfNumTo.cpp				\
        v_OpenFlags.cpp				\
        v_Param01.cpp				\
        v_Param02.cpp				\
        v_Param03.cpp				\
	v_Password.cpp				\
	v_PidFile.cpp				\
        v_Round.cpp				\
	v_SafeStrcpy.cpp			\
	v_Semaphore.cpp				\
	v_SigCatcher.cpp			\
        v_SortOrder.cpp				\
        v_Str01.cpp				\
        v_Str02.cpp				\
        v_Str03.cpp				\
        v_Str04.cpp				\
        v_Str05.cpp				\
        v_Str06.cpp				\
        v_Str07.cpp				\
        v_Str08.cpp				\
        v_Str09.cpp				\
        v_Str10.cpp				\
        v_Str11.cpp				\
        v_Str12.cpp				\
        v_Str13.cpp				\
        v_Str14.cpp				\
        v_Str15.cpp				\
        v_Str16.cpp				\
        v_Str17.cpp				\
        v_Str18.cpp				\
        v_Str19.cpp				\
        v_Str20.cpp				\
        v_Str21.cpp				\
        v_Str22.cpp				\
        v_Str23.cpp				\
        v_Str24.cpp				\
        v_Str25.cpp				\
        v_Str26.cpp				\
        v_StringCapitalize.cpp			\
        v_StringCaseCompare.cpp			\
        v_StringFirstNotOf.cpp			\
        v_StringFrom.cpp			\
        v_StringLower.cpp			\
        v_StringSearch.cpp			\
        v_StringTo.cpp				\
        v_StringUpper.cpp			\
        v_StripTrailing.cpp			\
        v_StripWhite.cpp			\
        v_SubStr01.cpp				\
        v_SubStr02.cpp				\
        v_SubStr03.cpp				\
        v_SubStr04.cpp				\
        v_SubStr05.cpp				\
        v_SubStr06.cpp				\
        v_SubStr07.cpp				\
        v_TimeIt01.cpp				\
        v_UnionOf.cpp				\
        v_User.cpp				\
        v_UserGroup.cpp				\
        v_VectorResync.cpp

#

.PHONY: validate
test: unit 	\
		data/FileStat/FileStat.h.t.nnn.nnn.nnn \
		data/FileStat/FileStat.h.t.nnn.yyy.nnn
	./unit

data/FileStat/FileStat.h.t.nnn.nnn.nnn:
	touch $@ && chmod 0 $@

data/FileStat/FileStat.h.t.nnn.yyy.nnn:
	touchd $@ && chmod 070 $@

dbg: unit
	echo libtool --mode=execute gdb unit
