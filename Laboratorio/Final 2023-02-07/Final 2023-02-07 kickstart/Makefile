CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
CC = gcc
TARGET = position
TEST = test

all: $(TARGET)

$(TARGET) : position.o list.o main.c
	$(CC) $(CFLAGS) -o $(TARGET) $^

position-test.o: position.c
	$(CC) $(CFLAGS) -c -o position-test.o $^

list.o : list.c
	$(CC) $(CFLAGS) -c $^

$(TEST) : CFLAGS += -D TEST

$(TEST) : test.o position-test.o list.o
	$(CC) $(CFLAGS) -o $(TEST) $^

run_tests: $(TEST)
	valgrind --show-reachable=yes --leak-check=full ./$(TEST)

run_main: $(TARGET)
	valgrind --show-reachable=yes --leak-check=full ./$(TARGET)

.PHONY : clean

clean:
	rm -f *.o $(TARGET) $(TEST)

