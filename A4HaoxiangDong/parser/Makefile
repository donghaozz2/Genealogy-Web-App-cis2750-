CC = gcc
CCFLAGS += -std=c11 -shared

all:
	$(CC) $(CCFLAGS) -o testlib.so -g -fPIC src/LinkedListAPI.c src/GEDCOMparser.c -Iinclude
clean:
	rm -rf *.o *.so
