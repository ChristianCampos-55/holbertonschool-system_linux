#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - in function, prints elf file header
 * @argc: argument counter
 * @argv: argument vector
 * @env:  environment variable
 * Return: 0 or -1 upon failure
 */
int main(int argc, char **argv, char **env)
{
	char *args_act[] = {"/usr/bin/readelf", "-W", "-h", "", NULL};

	if (argc != 2)
		exit(0);

	args_act[3] = argv[1];
	if (execve(args_act[0], args_act, env) == -1)
	{
		perror("execv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
