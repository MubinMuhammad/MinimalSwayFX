COMPILER := g++
FILES := ./installerSrc/main.cpp
EXE := installer

compile:
	$(COMPILER) -o $(EXE) $(FILES)

all: compile

clean:
	rm -fr *.txt ./*.cpp
	find . -maxdepth 1 -type f -executable | xargs rm
