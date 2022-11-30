CC = gcc
CFLAGS = -Wall -g
OBJECTS = util.o lexer.o

default: assembler

assembler: $(OBJECTS) assembler.c
	@${CC} ${CFLAGS} $(OBJECTS) assembler.c -o assembler

%.o: %.c %.h
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm assembler $(OBJECTS)
