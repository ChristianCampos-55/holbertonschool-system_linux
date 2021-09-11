#include "signals.h"

/**
 * current_handler_sigaction - retrieve SIGINT's handler
 *
 * Return: pointer to handler or NULL
 */

void (*current_handler_sigaction(void))(int)
{
	struct sigaction prev_act;

	if (sigaction(SIGINT, NULL, &prev_act) < 0)
		return (NULL);

	return (prev_act.sa_handler);
}
