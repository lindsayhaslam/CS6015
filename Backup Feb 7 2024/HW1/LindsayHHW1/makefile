##LINDSAY HASLAM

CXX = c++
ARGUMENTS = --test --help
CFLAGS = --std=c++11
LINKER = -o
CXXSOURCE = main.cpp cmdline.cpp Expr.cpp ExprTests.cpp
HEADERS = cmdline.h catch.h ExprTests.h Expr.h

msdscript: $(CXXSOURCE) $(HEADERS)
		 $(CXX) $(CFLAGS) $(CXXSOURCE)
		 $(CXX) main.o cmdline.o Expr.o ExprTests.o $(LINKER) msdscript

.PHONY: clean
clean:
	   rm -f *.o *.out msdscript
	   
run: msdscript
	./msdscript $(ARGUMENTS)


