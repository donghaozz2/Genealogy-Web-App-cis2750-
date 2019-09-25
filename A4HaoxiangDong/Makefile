CC = gcc
CCFLAGS += -std=c11 -shared

all:
	$(CC) $(CCFLAGS) -o testlib.so -g -fPIC parser/src/LinkedListAPI.c parser/src/GEDCOMparser.c -Iparser/include
clean:
	rm -rf *.o *.so
