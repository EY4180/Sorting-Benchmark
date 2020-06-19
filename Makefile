PROGRAM = main

OBJECTS = radix.o merge.o insert.o benchmark.o bubble.o quick.o util.o
HEADERS = sorting.h
CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

# build main program that depends on all objects
$(PROGRAM) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJECTS)

# all object files depend on their respective c files and a single header
%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $*.c 

clean:
	del -f *.o *.exe
