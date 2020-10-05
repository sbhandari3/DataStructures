#------------------------------------------------------------------------------
# Suneet Bhandari
# sugbhand
# CSE 15
# 10/20/19
# makefile for charType.c with Macros
#------------------------------------------------------------------------------

PROGRAM_NAME = charType
FLAGS        = -std=c99 -Wall
SOURCES      = $(PROGRAM_NAME).c
OBJECTS      = $(PROGRAM_NAME).o
EXEBIN       = $(PROGRAM_NAME)

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm $(EXEBIN) $(OBJECTS)

memcheck:
	valgrind --leak-check=full $(EXEBIN) $(SOURCES) outfile
