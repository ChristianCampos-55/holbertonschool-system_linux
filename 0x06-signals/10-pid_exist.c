#include <signal.h>

/**
 * pid_exist - checks if a process exists
 * @pid: id of process to check
 *
 * Return: 1 if the process exists, or 0
 */
int pid_exist(pid_t pid)
{
	return (kill(pid, 0) == 0);
}
