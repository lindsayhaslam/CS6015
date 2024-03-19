##LINDSAY HASLAM

CXX = c++
ARGUMENTS = --test --help
CFLAGS = --std=c++11
LINKER = -o
CXXSOURCE = main.cpp
HEADERS = cmdline.h catch.h ExprTests.h Expr.h

Lib: $(CXXSOURCE) $(HEADERS)
		 $(CXX) $(CFLAGS) -o msdscript_from_lib main.cpp -L../lib -lmsdscript



msdscript: $(CXXSOURCE) $(HEADERS)
		 $(CXX) $(CFLAGS) -c $(CXXSOURCE)
		 $(CXX) $(CFLAGS) main.o cmdline.o Expr.o ExprTests.o $(LINKER) msdscript

.PHONY: clean
clean:
	   rm -f *.o *.out msdscript msdscript_from_lib

.PHONY: test
test: msdscript
		./msdscript --test
	   
run: msdscript
	./msdscript $(ARGUMENTS)

doc: msdscript
	cd documentation && doxygen


