# 2017-04-20 (cc) <paul4hough@gmail.com>
#
ACLOCAL_AMFLAGS = '-Im4'

SUBDIRS = src/clue tests/unit
dist_doc_DATA = README.md

test: all
	cd tests && ./validator.bash
