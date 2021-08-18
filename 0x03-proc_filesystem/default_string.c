#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * main - allocates and loops string in mem
 *
 * Return: "Can't allocate memory if malloc fails
 */

int main(void)
{
	char *string;
	unsigned long int i;

	string = strdup("A day at a time");
	if (string == NULL)
	{
		fprintf(stderr, "Can't allocate memory\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (string)
	{
		printf("[%lu] %s (%p)\n", i, string, (void *)string);
		sleep(1);
		i++;
	}
	return (EXIT_SUCCESS);
}
