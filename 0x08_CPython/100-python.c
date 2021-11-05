#include <Python.h>
/**
 * print_python_int - prints info about python int object
 * @p: Python generic object
 */
void print_python_int(PyObject *p)
{
	int numb;
	twodigits holder;
	Py_ssize_t a, i, c;
	PyLongObject *b, *d;
	digit *py, u, *cter;

	d = (PyLongObject *)p;
	numb = (33 * _PyLong_DECIMAL_SHIFT) /
		(10 * PyLong_SHIFT - 33 * _PyLong_DECIMAL_SHIFT);
	a = 1 + abs(Py_SIZE(d)) + abs(Py_SIZE(d)) / numb;
	b = _PyLong_New(a);

	if (b == NULL)
		return;

	py = d->ob_digit, cter = b->ob_digit,  a = 0;

	for (i = abs(Py_SIZE(d)); --i >= 0; )
	{
		u = py[i];
		for (c = 0; c < a; c++)
		{
			holder = (twodigits)cter[c] << PyLong_SHIFT | u;
			u = (digit)(holder / _PyLong_DECIMAL_BASE);
			cter[c] = (digit)(holder - (twodigits)u * _PyLong_DECIMAL_BASE);
		}
		while (u)
			cter[a++] = u % _PyLong_DECIMAL_BASE, u /= _PyLong_DECIMAL_BASE;
	}

	a == 0 ? cter[a++] = 0 : 0, Py_SIZE(d) < 0 ? putchar('-') : 0;

	for (i = a; --i >= 0;)
		i == a - 1 ? printf("%u", cter[i]) : printf("%09u", cter[i]);
	printf("\n");
}
