CC = gcc
CFLAGS = -Wall
OBJECTS = util.o instruction.o

default: tester
	@./tester

tester: $(OBJECTS) tester.c
	@${CC} ${CFLAGS} $(OBJECTS) tester.c -o tester

%.o: %.c %.h
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm tester $(OBJECTS)
