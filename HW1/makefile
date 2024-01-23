##LINDSAY HASLAM

CXX = c++
ARGUMENTS = --test --help
CFLAGS = -c
LINKER = -o
CXXSOURCE = main.cpp cmdline.cpp
HEADERS = cmdline.h

msdscript: $(CXXSOURCE) $(HEADERS)
		 $(CXX) $(CFLAGS) $(CXXSOURCE)
		 $(CXX) main.o cmdline.o $(LINKER) msdscript

.PHONY: clean
clean:
	   rm -f *.o *.out msdscript
	   
run: msdscript
	./msdscript $(ARGUMENTS)


