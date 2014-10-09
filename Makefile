CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-lasound
BN=./buildnumber

all: crusher

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
alsa.o: alsa.c       
	$(CC) $(CFLAGS) -c alsa.c
crusher: main.o alsa.o
	$(BN)
	$(CC) $(CFLAGS) main.o alsa.o $(LDFLAGS) -o crusher
clean:
	rm -f *.o crusher
