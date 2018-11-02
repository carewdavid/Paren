CC=gcc
CFLAGS=-Wall -Wextra -Werror -g -std=c11
EXEC=paren parenTest

paren: lexer.o
	$(CC) $(CFLAGS) $< -o paren
%.o: %.c
	$(CC) $(CFLAGS) -c $<

test: paren

clean:
	rm *.o $(EXEC)
