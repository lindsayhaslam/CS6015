##LINDSAY HASLAM

CXX = c++
ARGUMENTS = --test --help
CFLAGS = --std=c++11
LINKER = -o
CXXSOURCE = main.cpp cmdline.cpp Expr.cpp ExprTests.cpp parse.cpp Val.cpp
HEADERS = cmdline.h catch.h ExprTests.h Expr.h parse.hpp Val.h

msdscript: $(CXXSOURCE) $(HEADERS)
		 $(CXX) $(CFLAGS) -c $(CXXSOURCE)
		 $(CXX) $(CFLAGS) main.o cmdline.o Expr.o ExprTests.o parse.o Val.o $(LINKER) msdscript

.PHONY: clean
clean:
	   rm -f *.o *.out msdscript

.PHONY: test
test: msdscript
		./msdscript --test
	   
run: msdscript
	./msdscript $(ARGUMENTS)

doc: msdscript
	cd documentation && doxygen

test_msdscript: test_msdscript.o exec.o expr.o
	$(CXX) expr.o exec.o test_msdscript.o -o test_msdscript
test_msdscript.o: test_msdscript.cpp
	$(CXX) $(CFLAGS) -c test_msdscript.cpp -o test_msdscript.o
exec.o: exec.cpp exec.h
	$(CXX) $(CFLAGS) -c exec.cpp -o exec.o