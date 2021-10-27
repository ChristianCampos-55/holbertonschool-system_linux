#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - emulates nm command from GNU
 * @argc: command line args
 * @argv: vector of argc's
 * @env: shell environment
* Return: 1 on success, 0 otherwise
 */

int main(int argc, char **argv, char **env)
{
	char *hnmv[] = {"./hnm", "-p", "", NULL};

	(void)argc;
	hnmv[2] = argv[1];
	if (execve("/usr/bin/nm", hnmv, env) == -1)
	{
		perror("execv");
		return (0);
	}
	return (1);
}
