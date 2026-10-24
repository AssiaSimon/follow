CC=gcc
CCFLAGS=-g -O1 -Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer

prog: mainlist.o list.o testListHelpers.o
	$(CC) $(CCFLAGS) mainlist.o list.o testListHelpers.o -o prog

mainlist.o: mainlist.c
	$(CC) $(CCFLAGS) -c mainlist.c list.h testListHelpers.h

list.o: list.c
	$(CC) $(CCFLAGS) -c list.c list.h

testListHelpers.o: testListHelpers.c
	$(CC) $(CCFLAGS) -c testListHelpers.c testListHelpers.h list.h
