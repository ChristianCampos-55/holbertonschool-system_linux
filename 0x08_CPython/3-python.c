#include <Python.h>

/**
 * print_python_float - Prints basic info of a python float
 * @p: PyObject
 */

void print_python_float(PyObject *p)
{
	double v;
	char *s;

	setbuf(stdout, NULL);

	printf("[.] float object info\n");
	if (!p || !PyFloat_Check(p))
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}

	v = (((PyFloatObject *)(p))->ob_fval);
	s = PyOS_double_to_string(v, 'r', 0, Py_DTSF_ADD_DOT_0, NULL);
	printf("  v: %s\n", s);
}

/**
 * print_python_bytes - Prints basic info of a python object
 * @p: pointer to object structure
 */

void print_python_bytes(PyObject *p)
{
	Py_ssize_t bsz;
	Py_ssize_t i;
	char *bst;

	setbuf(stdout, NULL);
	printf("[.] bytes object info\n");
	if (!p || !PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	bsz = (((PyVarObject *)(p))->ob_size);
	bst = (((PyBytesObject *)(p))->ob_sval);
	printf("  size: %ld\n", bsz);
	printf("  trying string: %s\n", bst);
	bsz = bsz > 9 ? 10 : bsz + 1;
	printf("  first %ld bytes: ", bsz);

	for (i = 0; i < bsz; i++)
		printf("%02hhx%c", bst[i], i < bsz - 1 ? ' ' : '\n');
}

/**
 * print_python_list - Prints basic info of a python list
 * @p: pointer to object structure
 */

void print_python_list(PyObject *p)
{
	Py_ssize_t ls;
	Py_ssize_t i;
	PyObject *item;

	setbuf(stdout, NULL);
	printf("[*] Python list info\n");
	if (!p || !PyList_Check(p))
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	ls = (((PyVarObject *)(p))->ob_size);
	printf("[*] Size of the Python List = %lu\n", ls);
	printf("[*] Allocated = %lu\n", ((PyListObject *)p)->allocated);
	for (i = 0; i < ls; i++)
	{
		item = ((PyListObject *)(p))->ob_item[i];
		printf("Element %ld: %s\n", i, item->ob_type->tp_name);
		if (PyBytes_Check(item))
			print_python_bytes(item);
		else if (PyFloat_Check(item))
			print_python_float(item);
	}
}
