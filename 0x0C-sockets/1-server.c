#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 12345

/**
 * main - listening socket
 * @ac: arg vector
 * @av: arg counter
 * Return: SUCCESS or FAILURE
 */

int main(int ac, char **av)
{
    int socket_in, n_socket, weight;
	struct sockaddr_in loc, client;

	socket_in = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_in == -1)
		return (EXIT_FAILURE);

	loc.sin_family = AF_INET;
	loc.sin_addr.s_addr = INADDR_ANY;
	loc.sin_port = htons(PORT);

	if (bind(socket_in, (struct sockaddr *)&loc, sizeof(loc)) < 0)
		return (EXIT_FAILURE);
	listen(socket_in, 3);
	weight = sizeof(client);
	n_socket = accept(socket_in, (struct sockaddr *)&client, (socklen_t *)&weight);
	if (n_socket < 0)
		return (EXIT_FAILURE);

	printf("Client connected: %s\n", inet_ntoa(client.sin_addr));
	close(socket_in);
	close(n_socket);
	return (0);
	(void)ac;
	(void)av;
}
