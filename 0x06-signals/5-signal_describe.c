#include "signals.h"

/**
 * main - prints a description of any signal
 * @argc: counter of args
 * @argv: args passed
 *
 * Return: EXIT_SUCCESS, otherwise EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	if (argc == 2)
	{
	printf("%s: %s\n", argv[1], strsignal(atoi(argv[1])));
	return (EXIT_SUCCESS);
	}

	else
	{
	printf("Usage: %s <signum>\n", *argv);
	return (EXIT_FAILURE);
	}
}
