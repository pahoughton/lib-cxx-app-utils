# 2001-06-04 (cc) <paul4hough@gmail.com>
#


lib_LTLIBRARIES = libclue.la
libclue_la_CPPFLAGS = -I..

libcluedir = $(includedir)/clue

libclue_la_SOURCES =				\
Bitmask.cpp					\
CommaNumber.cpp					\
DateTimeUtils.cpp				\
DateTime.cpp					\
DateRange.cpp					\
DateRangeDaily.cpp				\
DateRangeWeekly.cpp				\
IsTimetDst.cpp					\
IosOpenModeFromString.cpp			\
IosOpenModeToString.cpp				\
IosSeekDirToString.cpp				\
MfNumTo.cpp					\
OpenFlags.cpp					\
LogBuf.cpp					\
Directory.cpp					\
UserGroup.cpp					\
User.cpp					\
FilePath.cpp					\
FileStat.cpp					\
FileOp.cpp					\
LogLevel.cpp					\
Log.cpp						\
StringCapitalize.cpp				\
StringCaseCompare.cpp				\
StringCaseReverseSearch.cpp			\
StringCaseSearch.cpp				\
StringFirstNotOf.cpp				\
StringFrom.cpp					\
StringLower.cpp					\
StringReverseSearch.cpp				\
StringSearch.cpp				\
StringTo.cpp					\
StringUpper.cpp					\
StripTrailing.cpp				\
StripWhite.cpp					\
StrStreambuf.cpp				\
SubStr.cpp \
Str.cpp \
Param.cpp \
TimeIt.cpp \
TimetFrom.cpp \
Password.cpp \
FileBatch.cpp \
FileLock.cpp \
FileModeString.cpp \
SigCatcher.cpp \
MesgQueue.cpp \
Semaphore.cpp \
HotSwap.cpp \
InboundProcessorBase.cpp \
PidFile.cpp


libclue_HEADERS =				\
bit						\
bitmask						\
compare						\
Bitmask.hpp					\
Clue.hpp					\
CommaNum.hpp					\
DateRangeDaily.hpp				\
DateRange.hpp					\
DateRangeWeekly.hpp				\
DateTime.hpp					\
DateTimeUtils.hpp				\
Directory.hpp					\
DumpInfo.hpp					\
FileBatch.hpp					\
FileLock.hpp					\
FileOp.hpp					\
FilePath.hpp					\
FileStat.hpp					\
helpers.hpp					\
HotSwap.hpp					\
InboundProcessorBase.hpp			\
InboundProcessor.hpp				\
LibLog.hpp					\
LogBuf.hpp					\
Log.hpp						\
LogLevel.hpp					\
MesgQueue.hpp					\
Param.hpp					\
Password.hpp					\
PidFile.hpp					\
Semaphore.hpp					\
SigCatcher.hpp					\
SortOrder.hpp					\
Str.hpp						\
StringUtils.hpp					\
StrStreambuf.hpp				\
SubStr.hpp					\
TimeIt.hpp					\
UserGroup.hpp					\
User.hpp					\
VectorResync.hpp


test: all
	$(MAKE) -C ../../tests/unit test
