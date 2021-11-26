#ifndef __STRACE_H__
#define __STRACE_H__

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/wait.h>

int child_trace(char **argv, char **env);
int w_syscall(pid_t pid);

#endif