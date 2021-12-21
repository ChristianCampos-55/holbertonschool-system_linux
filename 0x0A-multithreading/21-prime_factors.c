#include "multithreading.h"
#include "list.h"

/**
 * f_even - facorizes even numbers
 * @list: linked list
 * @n: number to factorize
 * Return: linked list
 */

void f_even(list_t *list, unsigned long *n)
{
	unsigned long *alloc_list;

	while ((*n & 1) == 0)
	{
		*n >>= 1;
		alloc_list = malloc(sizeof(*alloc_list));
		if (!alloc_list)
		{
			list_destroy(list, free);
			return;
		}
		*alloc_list = 2;
		list_add(list, (void *)alloc_list);
	}
}

/**
 * f - finds primer numbers
 * @list: linked list
 * @n: number to be factorized
 * Return: linked list
*/

list_t *f(list_t *list, unsigned long von_count)
{
	unsigned long holder;
	unsigned long *alloc_list;
	double counter;

	f_even(list, &von_count);
	counter = von_count;
	while (counter * counter > von_count)
		counter = (unsigned long)((counter + von_count / counter) / 2);
	for (holder = 3; holder <= (unsigned long)counter; holder += 2)
	{
		while (von_count % holder == 0)
		{
			von_count /= holder;
			alloc_list = malloc(sizeof(*alloc_list));
			*alloc_list = holder;
			list_add(list, (void *)alloc_list);
		}
	}
	if (von_count > 2)
	{
		alloc_list = malloc(sizeof(*alloc_list));
		*alloc_list = von_count;
		list_add(list, (void *)alloc_list);
	}
	return (list);
}

/**
 * prime_factors - calculates prime factor of given number
 * @s: number as string
 * Return: linked list
*/

list_t *prime_factors(char const *s)
{
	list_t *list;
	unsigned long von_count;
	char *nen_pter = NULL;

	if (!s)
		return (NULL);

	von_count = strtoul(s, &nen_pter, 10);

	if (errno == EINVAL || errno == ERANGE || !nen_pter)
		return (NULL);

	list = calloc(1, sizeof(*list));

	if (!list)
		return (NULL);

	if (!f(list, von_count))
	{
		list_destroy(list, free);
		return (NULL);
	}
	return (list);
}
