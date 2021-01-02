CC = gcc
CFLAGS = -g -Wall -std=c11

all: t9_tests t9_demo

test: t9_tests
	./t9_tests

t9_demo: t9_demo.o t9_lib.o
	$(CC) $(CFLAGS) -o t9_demo t9_demo.o t9_lib.o 

t9_tests: t9_tests.o t9_lib.o
	$(CC) $(CFLAGS) -o $@ $^

t9_tests.o: t9_tests.c t9_lib.h safe_assert.h
	$(CC) $(CFLAGS) -o $@ -c $<

t9_lib.o: t9_lib.c t9_lib.h
	$(CC) $(CFLAGS) -c t9_lib.c


t9_demo.o: t9_demo.c t9_lib.h
	$(CC) $(CFLAGS) -c t9_demo.c

clean:
	rm -f *.o t9_demo *~
