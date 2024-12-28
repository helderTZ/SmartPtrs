CC=g++
CFLAGS=-Wall -Wextra

all: test_SharedPtr test_UniquePtr

test_SharedPtr:	test_SharedPtr.cpp SharedPtr.h
	$(CC) -o test_SharedPtr test_SharedPtr.cpp $(CFLAGS)

test_UniquePtr:	test_UniquePtr.cpp UniquePtr.h
	$(CC) -o test_UniquePtr test_UniquePtr.cpp $(CFLAGS)

.PHONY: clean

clean:
	if [ -f test_SharedPtr ]; then rm test_SharedPtr; fi
	if [ -f test_UniquePtr ]; then rm test_UniquePtr; fi
