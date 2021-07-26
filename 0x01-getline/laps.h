#ifndef LAPS_H
#define LAPS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * struct car - holds race car date
 * @plate: car identifier
 * @l: number of times car completed course
 * @n: pointer to next node
 */
typedef struct car
{
	int plate;
	size_t l;
	struct car *n;
} c;

void race_state(int *id, size_t size);

#endif