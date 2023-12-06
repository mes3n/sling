.PHONY: all clean run

CUSTOM_LIB = deps# Custom lib path for raylib

ifdef CUSTOM_LIB
	LD_FLAGS =-L$(CUSTOM_LIB) -lraylib -lm -Wl,-rpath=$(shell realpath $(CUSTOM_LIB))
	CC_FLAGS =-I$(CUSTOM_LIB)
else
	LD_FLAGS =-lraylib -lm
	CC_FLAGS =
endif

CC = gcc
OBJ = $(shell find src -name "*.c" | sed -e 's/\.c/\.o/g' -e 's/src/obj/g')

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CC_FLAGS)

main: $(OBJ)
	$(CC) $(OBJ) -o bin/main $(LD_FLAGS)

header: HEADER_NAME = $(shell basename $(FILE) | tr a-z A-Z | sed 's/\./_/')
		CPP_FILE = $(shell echo $(FILE) | sed 's/\.h/\.c/')

header: 
ifdef FILE
ifeq ("$(wildcard $(FILE))", "")
	@touch $(FILE) 
	@touch $(CPP_FILE)
	@echo '#ifndef $(HEADER_NAME)' >> $(FILE)
	@echo '#define $(HEADER_NAME)' >> $(FILE)
	@echo '' >> $(FILE)
	@echo '' >> $(FILE)
	@echo '' >> $(FILE)
	@echo '#endif  // $(HEADER_NAME)' >> $(FILE)

	@echo "Created c header file ($(FILE)) with header guard ($(HEADER_NAME)) and source file ($(CPP_FILE))."
	git add $(FILE) $(CPP_FILE)
else
	@echo "Header file already exists."
endif
else
	@echo "Please specify a header file name."
endif

run: main
	./bin/main

all: clean main

clean:
	rm -rf bin obj
	mkdir bin obj

