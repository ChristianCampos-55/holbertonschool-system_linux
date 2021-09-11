#include "signals.h"

/**
 * sigint_handler - modifies SIGINT's message
 * @signum: signal to print
 */
static void sigint_handler(int signum)
{
	printf("Caught %d\n", signum);
	fflush(stdout);
}

/**
 * main - sets SIGINT handler through sigaction
 *
 * Return: EXIT_SUCCESS, or EXIT_FAILURE
 */
int main(void)
{
	struct sigaction sig_act;

	sig_act.sa_handler = sigint_handler;
	sig_act.sa_flags = 0;

	if (sigaction(SIGINT, &sig_act, NULL) < 0)
		return (EXIT_FAILURE);
	pause();
	puts("Signal received");
	return (EXIT_SUCCESS);
}
