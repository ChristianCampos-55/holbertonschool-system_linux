#include "signals.h"

/**
 * main - Sends A SIGINT to a process to a specific process
 * @argc: args counter
 * @argv: args
 *
 * Return: EXIT_SUCCESS on success, otherwise EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		return (abs(kill(atoi(argv[1]), SIGINT)));
	}
	else
	{
		printf("Usage: %s <pid>\n", *argv);
		return (EXIT_FAILURE);
	}
}
