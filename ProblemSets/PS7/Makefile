
CC = gcc
CFLAGS = -Wall -g
USED_LIBS = -lsqlite3

prob1: prob1.c
	$(CC) $(CFLAGS) $^ $(USED_LIBS) -o $@

.phony: clean
clean:
	rm prob1
