
CLUE_SRC	= ../../src/Clue

GEN_CMD		= GenC++Man.pl $< > $@

MAN_PAGES	= 		\
	ClueUtils.3		\
	StringUtils.3		\
	ClassVersion.3		\
	Compare.3		\
	LibTest.3		\
	Bit.3			\
	Bitmask.3		\
	RegexScan.3		\

all: $(MAN_PAGES)

ClueUtils.3:	$(CLUE_SRC)/ClueUtils.hh
	$(GEN_CMD)

StringUtils.3:	$(CLUE_SRC)/StringUtils.hh
	$(GEN_CMD)

ClassVersion.3:	$(CLUE_SRC)/ClassVersion.hh
	$(GEN_CMD)

Compare.3:	$(CLUE_SRC)/Compare.hh
	$(GEN_CMD)

LibTest.3:	$(CLUE_SRC)/LibTest.hh
	$(GEN_CMD)

Bit.3:	$(CLUE_SRC)/Bit.hh
	$(GEN_CMD)

Bitmask.3:	$(CLUE_SRC)/Bitmask.hh
	$(GEN_CMD)

RegexScan.3:	$(CLUE_SRC)/RegexScan.hh
	$(GEN_CMD)

clean:
	rm $(MAN_PAGES)