CC=clang++
CFLAGS=-Wall -Werror

rref: rref.cpp
	${CC} ${CFLAGS} rref.cpp -o rref

clean:
	rm -f rref