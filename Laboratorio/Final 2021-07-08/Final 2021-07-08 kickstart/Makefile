fence.o : fence.c
	gcc -Wall -Wextra -Werror -std=c99 -g -c -o $@ $^
test.o : test.cpp	
	g++ -Wall -Wextra -Werror -Wno-deprecated -std=c++11 -g -c -o $@ $^

test : test.o fence.o
	g++ -Wall -Wextra -Werror -Wno-deprecated -std=c++11 -o $@ $^

valgrind: test
	valgrind --show-reachable=yes --leak-check=full ./test
	@echo "\n\n<<< Nota: >>> Mirar solamente DEFINITELY_LOST.\n"

.PHONY: clean

clean:
	rm -f fence.o test.o test

