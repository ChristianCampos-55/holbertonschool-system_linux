#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 12345

/**
 * main - socket
 * Return: EXIT_SUCCESS or EXIT_SUCCESS
 */

int main(void)
{
	int list_socket, n_socket, weight;
	struct sockaddr_in loc, client;
	char buf[2048] = {0};

	list_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (list_socket == -1)
		return (EXIT_FAILURE);

	loc.sin_family = AF_INET;
	loc.sin_addr.s_addr = INADDR_ANY;
	loc.sin_port = htons(PORT);

	if (bind(list_socket, (struct sockaddr *)&loc, sizeof(loc)) < 0)
		return (EXIT_FAILURE);

	listen(list_socket, 3);
	printf("Server listening on port %d\n", PORT);
	weight = sizeof(client);
	n_socket = accept(list_socket, (struct sockaddr *)&client,
						(socklen_t *)&weight);

	if (n_socket < 0)
		return (EXIT_FAILURE);

	printf("Client connected: %s\n", inet_ntoa(client.sin_addr));

	if (recv(n_socket, buf, 2048, 0) < 0)
		return (EXIT_FAILURE);
	printf("Message received: \"%s\"\n", buf);
	close(list_socket);
	close(n_socket);
	return (0);
}
