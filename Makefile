# This is the Makefile for GCC compiler. Only you need to update outest.
.SUFFIXES:
.SUFFIXES: .o .a .so .c .h .s .cm
SRC           := main.c print_set.c select_parameter.c convert.c

SHELL         =/bin/bash
CC            =gcc
COVERAGE      =-fprofile-arcs -ftest-coverage
OBJ           =$(patsubst %.c, %.o, $(SRC))
INCH          =./inc
INCS          =./src
INC           =-I$(INCH) -I$(INCS)
TARGET        =cbfi.elf
FDPS          =fdependent
OBJDIR        =obj
ADIR          =archive
RDIR          =report
IDIR          =inc
SDIR          =src
CFLAG         =-c -g -Wall -pg $(COVERAGE)
LFLAG         =-pg $(COVERAGE)
EXRLIB        =-lm
ALLDIR        =$(OBJDIR) $(ADIR) $(IDIR) $(SDIR) $(RDIR)


vpath %.o $(OBJDIR)
vpath %.c $(SDIR)

.phony:link clean run show install

$(TARGET):$(OBJ)
	$(MAKE) link


ifeq "$(MAKECMDGOALS)"  ""
-include $(FDPS)
$(FDPS):$(SRC)
	$(CC) $(INC) $(MFLAG) -MM $^ >$@
endif


ifneq ($(ALLDIR), $(wildcard $(ALLDIR)))
	@echo "Directory dependency:[" $(ALLDIR) "]"
	mkdir -vp $(filter-out $(wildcard $(ALLDIR)), $(ALLDIR))
endif


$(OBJ):%.o:%.c
	$(CC) $(INC) $(CFLAG) -o $@ $<
	mv $@ $(OBJDIR)

link:$(OBJ)
	$(CC) $(INC) $(LFLAG) -o $(TARGET) $^ $(EXRLIB)
	@echo $(shell date)
	rm $(FDPS)

run:$(TARGET)
	./$(TARGET)
	$(SHELL) genCoverage.sh

clean:
	$(cleanall)

show:
	$(call symbol, $(OBJDIR)/main.o)
	$(call dylink, $(TARGET))

install:
	cp -v $(TARGET) /usr/bin/$(basename $(TARGET))

define cleanall
	-rm -rf $(TARGET) $(OBJDIR)/*
	-rm -rf $(RDIR)/* *.gcda *.gcno
	-rm -rf $(ADIR)/*
        -rm -rf core
endef

define symbol
	nm -alp $1
endef

define dylink
	ldd $1
endef
