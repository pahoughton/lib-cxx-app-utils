
CLUE_SRC	= ../../src/Clue

GEN_CMD		= GenC++Man.pl $< > $@

MAN_PAGES	= 		\
	ClassVersion.3		\
	Compare.3		\

all: $(MAN_PAGES)

ClassVersion.3:	$(CLUE_SRC)/ClassVersion.hh
	$(GEN_CMD)

Compare.3:	$(CLUE_SRC)/Compare.hh
	$(GEN_CMD)

