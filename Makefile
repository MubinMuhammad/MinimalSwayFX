COMPILER := g++
FILES := ./installer/main.cpp
EXE := _installer_

compile:
	$(COMPILER) -o $(EXE) $(FILES)

all: compile

run: compile
	./$(EXE)

clean:
	rm -fr *.txt ./*.cpp
	find . -maxdepth 1 -type f -executable | xargs rm
