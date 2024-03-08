CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = card.c war_match.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = test_match

.PHONY: clean

all: $(TARGET)

test: $(TARGET)
	./$(TARGET) -vf input/*.in

valgirnd: $(TARGET)
	valgrind --leak-check=full --show-reachable=yes ./$(TARGET) -vf input/*.in

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
