#include "signals.h"

/**
 * sigint_handler - Handler for SIGINT
 * @signum: signal to print
 * Return: fflush returns
 */
void sigint_handler(int signum)
{
	printf("Gotcha! [%i]\n", signum);
	fflush(stdout);
}

/**
 * handle_signal - Creates handler for the signal SIGINT
 * Return: 0 or -1 on error
 */
int handle_signal(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		return (-1);

	return (0);
}
