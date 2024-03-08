CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = stack.c check_balance.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = check_balance

SOURCES_TEST = stack.c test-stack.c
OBJECTS_TEST = $(SOURCES_TEST:.c=.o) 
TARGET_TEST = test


.PHONY: clean

all: $(TARGET)

$(TARGET_TEST): $(OBJECTS_TEST)
	$(CC) $(CFLAGS) -o $(TARGET_TEST) $(OBJECTS_TEST) $(LFLAGS) $(LIBS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(OBJECTS_TEST) $(TARGET) $(TARGET_TEST)
