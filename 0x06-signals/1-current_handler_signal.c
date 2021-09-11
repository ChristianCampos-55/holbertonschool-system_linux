#include "signals.h"

/**
 * current_handler_signal - function to handle_signal
 * handler: sets a value to signal SIGINT
 * @void: void
 * Return: 0 if successful, otherwise -1
 */
void (*current_handler_signal(void))(int)
{
	void (*handler)(int) = signal(SIGINT, SIG_DFL);

	if (signal(SIGINT, handler) == SIG_ERR)
		return (NULL);

	else
		return (handler);

}
