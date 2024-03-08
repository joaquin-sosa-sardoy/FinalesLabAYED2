CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
CC = gcc
TARGET = final
TEST = test

all: $(TARGET)

$(TARGET) : main.c dna.o
	$(CC) $(CFLAGS) -o $(TARGET) $^

dna-test.o: dna.c
	$(CC) $(CFLAGS) -c -o dna-test.o $^

$(TEST) : CFLAGS += -D TEST

$(TEST) : test.o dna-test.o CuTest.o
	$(CC) $(CFLAGS) -o $(TEST) $^

run_tests: $(TEST)
	valgrind --show-reachable=yes --leak-check=full ./$(TEST)

run_main: $(TARGET)
	valgrind --show-reachable=yes --leak-check=full ./$(TARGET)

.PHONY : clean

clean:
	rm -f *.o $(TARGET) $(TEST)
