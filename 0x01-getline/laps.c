#include "laps.h"


/**
 * adder - adds new car to linked list
 * @head: pointer to head of ll
 * @plate: plate identifier to add
 */

void adder(c **head, int plate)
{
	c *nd, *t;

	if (!*head || plate < (*head)->plate)
	{
		nd = malloc(sizeof(c));
		if (!nd)
			exit(EXIT_FAILURE);
		nd->plate = plate;
		nd->l = 0;
		nd->n = *head;
		*head = nd;
		printf("Car %d joined the race\n", plate);
		return;
	}

	for (nd = *head; nd->n && nd->n->plate <= plate; nd = nd->n)
		;

	if (nd->plate == plate)
	{
		nd->l++;
		return;
	}

	t = malloc(sizeof(c));
	if (!t)
		exit(EXIT_FAILURE);

	t->plate = plate;
	t->l = 0;
	t->n = nd->n;
	nd->n = t;

	printf("Car %d joined the race\n", plate);
}

/**
 * race_state - determines the state
 * @plate: array of plates
 * @size: array size
 */

void race_state(int *plate, size_t size)
{
	static c *head;
	c *nd;
	size_t i;

	if (!size)
	{
		while (head)
		{
			nd = head;
			head = head->n;
			free(nd);
		}
		return;
	}
	for (i = 0; i < size; i++)
		adder(&head, plate[i]);

	printf("Race state:\n");

	for (nd = head; nd; nd = nd->n)
		printf("Car %d [%lu laps]\n", nd->plate, nd->l);
}
