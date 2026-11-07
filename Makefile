CC = gcc
CFLAGS = -O2 -Wall

rubik: rubik.c
	$(CC) $(CFLAGS) -o rubik rubik.c

clean:
	rm -f rubik

.PHONY: clean
