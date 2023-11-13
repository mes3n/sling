.PHONY: all clean run

CUSTOM_LIB = deps# Custom lib path for raylib

ifdef CUSTOM_LIB
	LD_FLAGS =-L$(CUSTOM_LIB) -lraylib -Wl,-rpath=$(shell realpath $(CUSTOM_LIB))
	CC_FLAGS =-I$(CUSTOM_LIB)
else
	LD_FLAGS =-lraylib
	CC_FLAGS =
endif

CC = gcc
OBJ = $(shell find src -name "*.c" | sed -e 's/\.c/\.o/g' -e 's/src/obj/g')

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CC_FLAGS)

main: $(OBJ)
	$(CC) $(OBJ) -o bin/main $(LD_FLAGS)

run: main
	./bin/main

all: clean main

clean:
	rm -rf bin/* obj/*

