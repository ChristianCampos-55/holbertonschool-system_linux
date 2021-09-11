#include "signals.h"

#ifndef NSIG
#ifndef _NSIG
#ifndef CHAR_BIT
#define CHAR_BIT (sizeof(char) * 8)
#endif
#define _NSIG (sizeof(sigset_t) * CHAR_BIT)
#endif
#define NSIG _NSIG
#endif

/**
 * def_handler - modifies SIGQUIT information
 * @sig: number of the signal
 * @info: pointer to siginfo struct
 * @ucontext: pointer to signal context struct
 */
static void def_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) ucontext;
	psiginfo(info, "Caught");
}

/**
 * all_in_one - set up a handler for all signals that may be caught
 */
void all_in_one(void)
{
	unsigned int sig = 0;
	struct sigaction def_sig;

	def_sig.sa_sigaction = def_handler;
	def_sig.sa_flags = SA_SIGINFO;

	while (++sig < NSIG)
		sigaction(sig, &def_sig, NULL);
}
