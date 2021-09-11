#include "signals.h"

/**
 * sigact_sigquit - print the sender's PID
 * @sig: sig number
 * @info: pointer to info about signal
 * @ucontext: signal information
 */
static void sigact_sigquit(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) ucontext;
	if (info)
	{
		printf("SIGQUIT sent by %d\n", info->si_pid);
		fflush(stdout);
	}
}

/**
 * trace_signal_sender - modifies SIGQUIT's handler
 *
 * Return: 0 or -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction sigq_act;

	sigq_act.sa_sigaction = sigact_sigquit;
	sigq_act.sa_flags = SA_SIGINFO;

	if (sigaction(SIGQUIT, &sigq_act, NULL) < 0)
		return (-1);
	return (0);
}
