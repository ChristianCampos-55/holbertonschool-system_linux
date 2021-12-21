#include "multithreading.h"

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

__attribute__((constructor)) void begin(void)
	pthread_mutex_init(&lock, NULL);

__attribute__((destructor)) void end(void)
	pthread_mutex_destroy(&lock);

/**
 * tprintf - uses the printf family to print out a given formatted string
 * @format: given format
 * Return: Zilch
 */
int tprintf(char const *format, ...)
{
	va_list args;
	pthread_t curr_thread;

	pthread_mutex_lock(&lock);
	curr_thread = pthread_self();
	setbuf(stdout, NULL);
	va_start(args, format);
	printf("[%lu] ", curr_thread);
	vprintf(format, args);
	va_end(args);
	pthread_mutex_unlock(&lock);

	return (0);
}
