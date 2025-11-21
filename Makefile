CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)

doctor: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o doctor

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj doctor

