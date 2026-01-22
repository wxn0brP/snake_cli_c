CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lncurses

TARGET = snake
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean run dev

all: $(TARGET)
dev: clean all run

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

run: $(TARGET)
	./$(TARGET) $(ARGS)
