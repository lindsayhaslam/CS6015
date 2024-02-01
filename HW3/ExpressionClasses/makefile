##LINDSAY HASLAM

CXX = c++
ARGUMENTS = --test --help
CFLAGS = --std=c++11
LINKER = -o
CXXSOURCE = main.cpp cmdline.cpp Expr.cpp ExprTests.cpp
HEADERS = cmdline.h catch.h ExprTests.h Expr.h

msdscript: $(CXXSOURCE) $(HEADERS)
		 $(CXX) $(CFLAGS) -c $(CXXSOURCE)
		 $(CXX) $(CFLAGS) main.o cmdline.o Expr.o ExprTests.o $(LINKER) msdscript

.PHONY: clean
clean:
	   rm -f *.o *.out msdscript

.PHONY: test
test: msdscript
		./msdscript --test
	   
run: msdscript
	./msdscript $(ARGUMENTS)


