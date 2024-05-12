COMPILER := gcc
FILES := ./installer/installer.c ./installer/colors.c
EXE := _installer_

compile:
	$(COMPILER) -o $(EXE) $(FILES)

all: compile

run: compile
	./$(EXE)

clean:
	rm -fr *.txt
	find . -maxdepth 1 -type f -executable | xargs rm
