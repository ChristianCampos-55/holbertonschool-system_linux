#include "multithreading.h"

/**
 * tprintf - uses the printf family to print out a given formatted string
 * @format: formated str
 * Return: 0 on success
*/

int tprintf(char const *format, ...)
{
	va_list arg;

	va_start(arg, format);
    printf("[%lu] ", pthread_self());
    vprintf(format, arg);
	va_end(arg);
	return (0);
}
