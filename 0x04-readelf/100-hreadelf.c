#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - main function - prints header section of ELF file
 * @argc: argument counter
 * @argv: argument vector
 * @env:  environment variable
 * Return: 0 or -1 upon failure
 */

int main(int argc, char **argv, char **env)
{
	char *act_args[] = {"/usr/bin/readelf", "-W", "-s", "", NULL};

	if (argc != 2)
		exit(0);

	act_args[3] = argv[1];
	if (execve(act_args[0], act_args, env) == -1)
	{
		perror("execv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}