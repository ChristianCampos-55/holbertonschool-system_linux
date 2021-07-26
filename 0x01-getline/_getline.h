#ifndef LAPS_H
#define LAPS_H
#define READ_SIZE BUFSIZ

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/**
 * struct listc - singly linked list
 * @line: number of line
 * @s: string
 * @size: size of the string
 * @next: pointer to the next node
 */
typedef struct listc
{
	size_t line;
	char *s;
	size_t size;
	struct listc *next;
} listc;
/**
 * struct listfiled - singly linked list
 * @fd: file descriptor
 * @rd: list read check
 * @head: pointer to the head of listc
 * @next: pointer to the next node
 */
typedef struct listfiled
{
	int fd;
	size_t rd;
	struct listc *head;
	struct listfiled *next;
} listfiled;
char *_getline(const int fd);

#endif
