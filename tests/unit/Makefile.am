# 2017-04-19 (cc) <paul4hough@gmail.com>
#

bin_PROGRAMS = validator
validator_LDADD = clue/libclue.la
validator_CXXFLAGS = -ggdb

validator_SOURCES =				\
	main.cpp				\
	v_bit.cpp				\
	v_compare01.cpp				\
	v_compare02.cpp				\
	v_StringTo.cpp				\
	v_StringCapitalize.cpp			\
	v_StringCaseCompare.cpp			\
	v_StringFirstNotOf.cpp			\
	v_StringFrom.cpp			\
	v_StringLower.cpp			\
	v_StringSearch.cpp			\
	v_StringUpper.cpp			\
	v_StripTrailing.cpp			\
	v_StripWhite.cpp
#

.PHONY: validate
validate: validator
	$(hide) validator
