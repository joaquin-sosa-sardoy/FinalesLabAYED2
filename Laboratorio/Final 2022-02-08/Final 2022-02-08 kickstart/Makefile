CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g -Wno-format-zero-length
SOURCES = card.c unogame.c main.c pretty_helpers.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = test_uno

.PHONY: clean

all: $(TARGET)

test: $(TARGET)
	./$(TARGET) -vf input/*.in

valgrind: $(TARGET)
	valgrind --leak-check=full --show-reachable=yes ./$(TARGET) -vf input/*.in

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
