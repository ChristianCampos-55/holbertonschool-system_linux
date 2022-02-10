#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>

#define USAGE "Usage: %s <host> <port>\n"

/**
 * main - listening socket
 * @ac: arg vector
 * @av: arg counter
 * Return: SUCCESS or FAILURE
 */

int main(int ac, char **av)
{
	struct sockaddr_in address;
	int n_socket;
	struct hostent *host;

	if (ac != 3)
		return (printf(USAGE, av[0]), EXIT_FAILURE);

	host = gethostbyname(av[1]);
	n_socket = socket(PF_INET, SOCK_STREAM, 0);

	if (n_socket < 0)
	{
		perror("socket failed");
		return (EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	inet_pton(AF_INET, inet_ntoa(*(struct in_addr *)host->h_addr),
		&address.sin_addr);
	address.sin_port = htons(atoi(av[2]));

	if (connect(n_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("connect failure");
		return (EXIT_FAILURE);
	}

	printf("Connected to %s:%s\n", av[1], av[2]);
	close(n_socket);
	return (EXIT_SUCCESS);
	(void)ac;
	(void)av;
}
