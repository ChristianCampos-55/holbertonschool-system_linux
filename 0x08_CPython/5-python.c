#include <Python.h>

/**
 * print_python_int - prints Python int
 * @p: pointer to PyObject p
 */

void print_python_int(PyObject *p)
{
	digit *number;
	unsigned long v = 0;
	Py_ssize_t s, i, neg;


	if (PyLong_Check(p) == 0 || p == NULL)
	{
		printf("Invalid Int Object\n");
		return;
	}

	number = ((PyLongObject *)(p))->ob_digit;
	s = ((PyVarObject *)(p))->ob_size, neg = abs(s);


	if (neg > 3 || (neg == 3 && number[2] > 15))
	{
		printf("C unsigned long int overflow\n");
		return;
	}

	for (i = 0; i < neg; i++)
		v += number[i] * (1L << (i * PyLong_SHIFT));

	if (s < 0)
		printf("-");

	printf("%lu\n", v);
}
