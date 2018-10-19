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

professor: row.cpp matrix.cpp rref.cpp
	python3 combine_files.py
	${CC} ${CFLAGS} consolidated_rref.cpp -o rref

clean:
	rm -f rref
	rm -f *.o
	rm -f consolidated_rref.cpp
