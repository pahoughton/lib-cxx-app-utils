
STLUTILS_SRC	= ../../src/StlUtils

GEN_CMD		= GenC++Man.pl $< > $@

MAN_PAGES	= 		\
	StlUtilsUtils.3		\
	StringUtils.3		\
	ClassVersion.3		\
	Compare.3		\
	LibTest.3		\
	Bit.3			\
	Bitmask.3		\
	RegexScan.3		\

all: $(MAN_PAGES)

StlUtilsUtils.3:	$(STLUTILS_SRC)/StlUtilsUtils.hh
	$(GEN_CMD)

StringUtils.3:	$(STLUTILS_SRC)/StringUtils.hh
	$(GEN_CMD)

ClassVersion.3:	$(STLUTILS_SRC)/ClassVersion.hh
	$(GEN_CMD)

Compare.3:	$(STLUTILS_SRC)/Compare.hh
	$(GEN_CMD)

LibTest.3:	$(STLUTILS_SRC)/LibTest.hh
	$(GEN_CMD)

Bit.3:	$(STLUTILS_SRC)/Bit.hh
	$(GEN_CMD)

Bitmask.3:	$(STLUTILS_SRC)/Bitmask.hh
	$(GEN_CMD)

RegexScan.3:	$(STLUTILS_SRC)/RegexScan.hh
	$(GEN_CMD)

clean:
	rm $(MAN_PAGES)