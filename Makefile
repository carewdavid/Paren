CC=gcc
CFLAGS=-Wall -Wextra -Werror -g -std=c99
EXEC=paren

paren: lexer.o
	$(CC) $(CFLAGS) $< -o $(EXEC)
%.o: %.c
	$(CC) $(CFLAGS) -c $<
