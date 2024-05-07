COMPILER := gcc
FILES := ./src/installer/installer.c
EXE := installer

compile:
	$(COMPILER) -o $(EXE) $(FILES)

all: compile

run: compile
	./$(EXE)

clean:
	rm -fr *.txt
	find . -maxdepth 1 -type f -executable | xargs rm
