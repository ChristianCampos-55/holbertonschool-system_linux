#include "multithreading.h"

static pthread_mutex_t lock;

/**
 * mutex_init - initializes lock var
 */

void mutex_init(void)
{
	if (pthread_mutex_init(&lock, NULL))
	{
		printf("Mutex init has failed\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * mutex_destroy - initializes constructor of lock var
 */

void mutex_destroy(void)
{
	if (pthread_mutex_destroy(&lock))
	{
		printf("Mutex init has failed\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * tprintf - prepends caller's Thread ID and calls vprintf function
 * Thread-safe version (mutex lock)
 * @format: formatting string
 * Return: zilch
*/

int tprintf(char const *format, ...)
{
	va_list args;

	va_start(args, format);
	if (pthread_mutex_lock(&lock))
	{
		printf("Mutex lock has failed\n");
		exit(EXIT_FAILURE);
	}
	printf("[%lu] ", pthread_self());
	vprintf(format, args);
	if (pthread_mutex_unlock(&lock))
	{
		printf("Mutex unlock has failed\n");
		exit(EXIT_FAILURE);
	};
	va_end(args);
	return (0);
}
