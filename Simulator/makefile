CC = gcc
CFLAGS = -g
OBJECTS = fileInput.o instructionset.o

default: baby

baby: $(OBJECTS) baby.c
	@${CC} ${CFLAGS} $(OBJECTS) baby.c -o baby

%.o: %.c %.h
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm baby ${OBJECTS}
