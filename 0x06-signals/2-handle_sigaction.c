#include "signals.h"

/**
 * sigint_handler - function to determine SIGINT's output
 * @signum: new signal's value
 * Return: fflush return
 */
void sigint_handler(int signum)
{
	printf("Gotcha! [%i]\n", signum);
	fflush(stdout);
}

/**
 * handle_sigaction - modifies handler for SIGINT
 *
 * Return: 1 on success or -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction sig_act;

	sig_act.sa_handler = sigint_handler;
	sig_act.sa_flags = 0;

	if (sigaction(SIGINT, &sig_act, NULL) < 0)
		return (-1);
	return (0);
}
