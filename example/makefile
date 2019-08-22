GCC = gcc
# BASEDIR := $(shell pwd)
LCOVDIR := ../lcov
HOSTGCCDIR := ../host-x86_64-unknown-linux-gnu/gcc
CC      := $(HOSTGCCDIR)/cc1
GCOV    := $(HOSTGCCDIR)/gcov
LCOV    := $(LCOVDIR)/bin/lcov
GENHTML := $(LCOVDIR)/bin/genhtml
OBJS    := orig/test.s arc/test.s mcdc/test.s
EXE  = test

########## Requested outputs ##########
GCDATA = test.gcda.txt test.gcno.txt
PDFs   = testfunc.pdf testfunc2.pdf
#######################################

DUMPFLAGS := -da -fdump-tree-gimple -fdump-tree-cfg

all: $(OBJS) $(GCDATA) COV/index.html $(PDFs)

gcc: $(CC)
.PHONY: $(CC) $(OBJS)
$(CC):
	cd .. && make stage3-bubble -j4

$(EXE): test.o test_test.c
	$(GCC) --coverage -o $(@) $(^)
%.gcno: %.o
%.o: %.c
	$(CC) -ftest-coverage -fprofile-mcdc $(^)
test.gcda: $(EXE)
	./$(<)

test.c.gcov: test.gcda
	$(GCOV) -a test.c; \
	cat $(@)

%.txt:	%
	od -tx4 -v -w4 -Anone  $(<) > $(@)

COV/index.html: test.c.gcov
	$(LCOV) --capture --directory . --rc lcov_branch_coverage=1 --output-file test.info
	$(GENHTML)  --branch-coverage -o COV test.info

clean:
	rm -rf $(EXE) *.o *.gc* *.info COV

testfunc.svg testfunc2.svg: test.o

%.pdf: %.svg
	dot -Tpdf < $(<) > $(@)

orig/test.s: orig/test.c
	cd $(@D); ../$(CC) test.c $(DUMPFLAGS) -I..
arc/test.s: arc/test.c
	cd $(@D); ../$(CC) test.c -fprofile-arcs -ftest-coverage $(DUMPFLAGS) -I..
mcdc/test.s: mcdc/test.c
	cd $(@D); ../$(CC) test.c -fprofile-mcdc $(DUMPFLAGS) -I..

