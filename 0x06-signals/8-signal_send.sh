#!/usr/bin/env sh
# Sends SIGQUIT signal to a process

if test "$#" -ne 1
then
	printf 'Usage: %s <pid>\n' "$0"
	exit 1
fi
kill -QUIT "$1"
