CC=gcc
CFLAGS=-g -c -Wall

SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)
BIN=$(OBJ:%.o=%)
TXT=code_PartB.txt encoded_PartB.txt book_code.txt book_encoded.txt new_book.txt

.PHONY: all
all: $(BIN)

$(BIN):%:%.o
	$(CC) $^ -o $@

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@


.PHONY: partb
partb:
	./encode
	$(shell diff code.txt code_PartB.txt)
	$(shell diff encoded.txt encoded_PartB.txt)
	@echo "Compare generated files with given answers"

.PHONY: partc
partc:
	./encode_book
	./decode_book

.PHONY: clean
clean:
	$(RM) $(OBJ) $(BIN) $(TXT)
