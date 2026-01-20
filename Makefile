CC = gcc
CFLAGS = -Wall -Wextra -O2 -lncurses

TARGET = snake
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean run

all: $(TARGET) run

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

run: $(TARGET)
	./$(TARGET)
