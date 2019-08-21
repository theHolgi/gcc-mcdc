GCC = gcc
# BASEDIR := $(shell pwd)
LCOVDIR := ../lcov
HOSTGCCDIR := ../host-x86_64-pc-linux-gnu/gcc
CC      := $(HOSTGCCDIR)/cc1
GCOV    := $(HOSTGCCDIR)/gcov
LCOV    := $(LCOVDIR)/bin/lcov
GENHTML := $(LCOVDIR)/bin/genhtml

EXE  = test
OBJS = orig/test.s arc/test.s mcdc/test.s


########## Requested outputs ##########
GCDATA = test.gcda.txt test.gcno.txt
PDFs   = testfunc.pdf testfunc2.pdf
#######################################

#all: $(GCDATA) $(OBJS) COV/index.html $(PDFs)
all: $(OBJS)

$(EXE): test.o test_test.c
	$(GCC) --coverage -o $(@) $(^)
%.gcno: %.o
%.o: %.c
	$(CC) -ftest-coverage -fprofile-arcs $(^)

CFLAGS := -I..
orig/test.s: orig/test.c
	$(CC) $(CFLAGS) -da -fdump-tree-gimple -fdump-tree-cfg $(<)
arc/test.s: arc/test.c
	$(CC) $(CFLAGS) -ftest-coverage -fprofile-arcs -da -fdump-tree-gimple -fdump-tree-cfg $(<)
mcdc/test.s: mcdc/test.c
	$(CC) $(CFLAGS) -ftest-coverage -fprofile-mcdc -da -fdump-tree-gimple -fdump-tree-cfg $(<)

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
	rm -rf $(EXE) *.o test.c.* *.s *.gc* *.info COV

testfunc.svg testfunc2.svg: test.o

%.pdf: %.svg
	dot -Tpdf < $(<) > $(@)
