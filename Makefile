COMPILER := gcc
FILES := ./src/installer/installer.c
EXE := installer

compile:
	$(COMPILER) -o $(EXE) $(FILES)

all: compile

run: compile
	./$(EXE)
