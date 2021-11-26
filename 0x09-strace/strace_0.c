#include "strace.h"
#include "syscalls.h"

/**
 * run_tr - executes tracer
 * @pid: pid of  tracee
 * Return: 0
 */

int run_tr(pid_t pid)
{
	int st;
	struct user_regs_struct rgt;

	waitpid(pid, &st, 0);
	ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);

	while (1)
	{
		if (w_syscall(pid))
			break;

		ptrace(PTRACE_GETREGS, pid, 0, &rgt);
		printf("%ld\n", (long) rgt.orig_rax);
		fflush(stdout);

		if (w_syscall(pid))
			break;
	}
	return (1);
}

/**
 * child_trace - Fuses child's trace
 * @argv: list of passed args
 * @env: environment
 * Return: 0 or -1 upon failure
 */

int child_trace(char **argv, char **env)
{
	ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	kill(getpid(), SIGSTOP);
	execve(argv[0], argv, env);
	return (0);
}

/**
 * w_syscall - waits for syscall
 * @pid: child pid
 * Return: 0 or 1 upon termination
 */

int w_syscall(pid_t pid)
{
	int st;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, pid, 0, 0);
		waitpid(pid, &st, 0);

		if (WIFSTOPPED(st) && WSTOPSIG(st) & 0x80)
			return (0);

		if WIFEXITED(st)
			return (1);
	}
	return (-1);
}

/**
 * main - traces and executes an arg
 * @argc: arg ammount
 * @argv: arg vector
 * @env: environment
 * Return: 0 or -1 upon failure
 */

int main(int argc, char **argv, char **env)
{
	pid_t pid;

	if (argc < 2)
	{
		printf("Usage: command\n");
		return (EXIT_FAILURE);
	}

	pid = fork();
	if (pid > 0)
		run_tr(pid);

	else if (pid == 0)
		child_trace(argv + 1, env);

	else
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}

	return (0);
}
