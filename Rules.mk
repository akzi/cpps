#=========================================================================
#Makefileģ������
#=========================================================================

DEBUG = y
ifdef release
DEBUG = n
endif

SOLIB = y

CC  = gcc

CPP = g++

CPPFLAGS = -Wall -ansi -fexceptions -w -msse -fpermissive

OBJFLAGS = -c

AR = ar rcs

PIC = -fPIC

SO = -shared -o

RM = -rm -rf

ifeq ($(DEBUG), y)
	CPPFLAGS += -g -ggdb
else
	CPPFLAGS += -O3
endif

ifeq ($(SOLIB), y)
	OBJFLAGS += $(PIC)
endif

export DEBUG SOLIB CPP CPPFLAGS OBJFLAGS AR PIC SO RM


MACROS = -DLINUX -D_FILE_OFFSET_BITS=64

ifeq ($(DEBUG), y)
	MACROS += -D_DEBUG
else
	MACROS += -DNDEBUG
endif

export MACROS


ifeq ($(DEBUG), y)
	OUT_DIR = debug
else
	OUT_DIR = release
endif

OBJ_DIR = $(OUT_DIR)/objs

BIN_DIR = $(OUT_DIR)/bin

$(shell mkdir -p $(OUT_DIR))
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

export OUT_DIR OBJ_DIR BIN_DIR


INC_FILES = $(wildcard *.h*)
SRC_FILES = $(wildcard *.c*)
OBJ_FILES = $(addsuffix .o, $(basename $(SRC_FILES)))
GEN_OBJS  = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRC_FILES))))


INC_DIRS = -I. -I/home/mrzz/lib/libpthread -I/home/mrzz/lib/mysql/include/ -I/usr/include
LIB_DIRS = -L. -L/home/mrzz/lib -I/home/mrzz/lib/libpthread -L/home/mrzz/lib/mysql -L/lib -L/usr/lib 
LNK_LIBS = -lrt -ldl -lm -lpthread


.c.o:
	$(CC)  $(CPPFLAGS) $(OBJFLAGS) $(MACROS) $(INC_DIRS) $< -o $(OBJ_DIR)/$@

.cc.o:
	$(CPP) $(CPPFLAGS) $(OBJFLAGS) $(MACROS) $(INC_DIRS) $< -o $(OBJ_DIR)/$@

.cxx.o:
	$(CPP) $(CPPFLAGS) $(OBJFLAGS) $(MACROS) $(INC_DIRS) $< -o $(OBJ_DIR)/$@

.cpp.o:
	$(CPP) $(CPPFLAGS) $(OBJFLAGS) $(MACROS) $(INC_DIRS) $< -o $(OBJ_DIR)/$@


.PHONY: all depend install clean


ifeq (.depend,$(wildcard .depend))
include .depend
endif
