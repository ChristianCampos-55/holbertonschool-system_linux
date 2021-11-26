CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
HEADERS = strace.h syscalls.h

.PHONY: clean

strace_0: strace_0.c $(HEADERS)
		$(CC) $(CFLAGS) strace_0.c -o $@

clean:
		rm *.o strace_0.c
