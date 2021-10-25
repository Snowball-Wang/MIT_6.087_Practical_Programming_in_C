CC = gcc
CFLAGS = -Wall -g
CFLAGS_STATIC = $(CFLAGS) -static
CFLAGS_DYN = -shared -fPIC
USED_LIBS = -lsqlite3
USED_LIBS_STATIC = $(USED_LIBS) -lpthread -ldl
USED_LIBS_DYN = -L -lmylib $(USED_LIBS)

all: prob1 prob1b prob1c prob1d-static prob1d-dynamic

prob1: prob1.c
	$(CC) $(CFLAGS) $^ $(USED_LIBS) -o $@

prob1b: prob1b.c
	$(CC) $(CFLAGS) $^ $(USED_LIBS) -o $@

prob1c: prob1c.c
	$(CC) $(CFLAGS) $^ $(USED_LIBS) -o $@

prob1d-static: prob1d.c mylib.c
	$(CC) $(CFLAGS) $^ $(USED_LIBS_STATIC) -o $@

libmylib.so: mylib.c
	$(CC) $(CFLAGS_DYN) $^ -o $@

prob1d-dynamic: prob1d.c libmylib.so
	$(CC) $^ $(USED_LIBS_DYN) -o $@


.phony: clean
clean:
	rm prob1 prob1b prob1c prob1d-static prob1d-dynamic libmylib.so
