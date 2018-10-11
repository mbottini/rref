CC=clang++
CFLAGS=-Wall -Werror --std=c++17

rref: rref.cpp
	${CC} ${CFLAGS} rref.cpp -o rref

clean:
	rm -f rref