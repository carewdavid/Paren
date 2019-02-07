CC=gcc
CFLAGS=-Wall -Wextra -Werror -g -std=c11
EXEC=paren parenTest

paren: paren.o parser.o error.o
	$(CC) $(CFLAGS) $^ -o paren
%.o: %.c
	$(CC) $(CFLAGS) -c $<

test: test.o parser.o
	$(CC) $(CFLAGS) $^ -o parenTest; \
	./parenTest

clean:
	rm *.o $(EXEC)
