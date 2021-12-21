#include "multithreading.h"

/**
 * thread_entry - entry point to a new thread
 * @arg: address of string to be printed
 * Return: zilch
*/

void *thread_entry(void *arg)
{
	if (!arg)
		return (NULL);
	printf("%s\n", (char *)arg);
	pthread_exit(0);
}
