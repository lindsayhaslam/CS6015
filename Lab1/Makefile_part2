#Makefile - Builds Lab1 for CS6015
#Lindsay Haslam
#
#Targets:
#program = creates executable
#printM = prints the values
#.PHONY = calls "clean"
#clean = deletes all .o, .a, binaries, etc.
#run = runs the program with "make run"

CXX = c++
CFLAGS = -c
LINKER = -o
CXXSOURCE = Caps.cpp Clothing.cpp main.cpp Pants.cpp
HEADERS = Caps.h Clothing.h Pants.h
	
program: $(CXXSOURCE) $(HEADERS)
		 $(CXX) $(CFLAGS) $(CXXSOURCE)
		 $(CXX) Caps.o Clothing.o main.o Pants.o $(LINKER) program
		 
printM:
	@echo CXX: $(CXX)
	@echo CFLAGS: $(CFLAGS)
	@echo CXXSOURCE: $(CXXSOURCE)
	@echo HEADERS: $(HEADERS)

.PHONY: clean
clean:
	   rm -f *.o *.out program
	   
run: program
	./program
