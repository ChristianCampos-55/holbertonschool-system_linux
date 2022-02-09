#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 12345

/**
 * main - socket
 * Return: EXIT_SUCCESS or EXIT_SUCCESS
 */

int main(void)
{
	int socket_ent;
	struct sockaddr_in addr;

	socket_ent = socket(PF_INET, SOCK_STREAM, 0);
	if (socket_ent < 0)
	{
		perror("socket failed");
		return (EXIT_FAILURE);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socket_ent, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind failure");
		return (EXIT_FAILURE);
	}
	if (listen(socket_ent, 10) < 0)
	{
		perror("listen failure");
		return (EXIT_FAILURE);
	}
	printf("Listening ...\n");
	while (1)
		;
	return (EXIT_SUCCESS);
}
