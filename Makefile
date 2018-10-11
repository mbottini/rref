CC=clang++
CFLAGS=-Wall -Werror

all: row.o matrix.o rref.o
	${CC} ${CFLAGS} row.o matrix.o rref.o -o rref

rref.o: rref.cpp
	${CC} ${CFLAGS} -c rref.cpp

matrix.o: matrix.cpp matrix.h
	${CC} ${CLAGS} -c matrix.cpp

row.o: row.cpp row.h
	${CC} ${CFLAGS} -c row.cpp 


clean:
	rm -f rref
	rm -f *.o