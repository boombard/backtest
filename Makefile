CXX=g++
LIB_FLAGS= -std=c++11 -stdlib=libc++ -lstdc++

all: test

test: test.o consume.o valuations.o
	${CXX} ${LIB_FLAGS} test.o consume.o valuations.o -o test

test.o: test.cpp consume.h valuations.h
	${CXX} ${LIB_FLAGS} -c test.cpp

consume.o: consume.cpp consume.h valuations.h
	${CXX} ${LIB_FLAGS} -c consume.cpp

valuations.o: valuations.cpp valuations.h
	${CXX} ${LIB_FLAGS} -c valuations.cpp

clean:
	rm -f *.o test
