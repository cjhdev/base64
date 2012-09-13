CC=gcc
CFLAGS=-O2 -Wall

all: base64test

base64test: ../base64.o test.o
	$(CC) $^ -o b64_test

clean:
	$(RM) *.o ../*.o
