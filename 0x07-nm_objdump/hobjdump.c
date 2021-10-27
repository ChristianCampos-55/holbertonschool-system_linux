#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - emulates objdump command from GNU
 * @argc: args passed on command line
 * @argv: vector of argc's
 * @env: The environment from shell
 * Return: 1 on success, 0 otherwise
 */

int main(int argc, char **argv, char **env)
{
	char *hobjc[] = {"./hobjdump", "-sf", "", NULL};

	(void)argc;
	hobjc[2] = argv[1];
	if (execve("/usr/bin/objdump", hobjc, env) == -1)
	{
		perror("execv");
		return (0);
	}
	return (1);
}