#include <Python.h>

/**
 * print_python_bytes - Prints basic info of a python object
 * @p: pointer to object structure
 */

void print_python_bytes(PyObject *p)
{
	Py_ssize_t byte_sz;
	Py_ssize_t i;
    char *byte_py;

	printf("[.] bytes object info\n");
	if (!PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	byte_sz = (((PyVarObject *)(p))->ob_size);
	byte_py = (((PyBytesObject *)(p))->ob_sval);
	printf("  size: %ld\n", byte_sz);
	printf("  trying string: %s\n", byte_py);
	byte_sz = byte_sz > 9 ? 10 : byte_sz + 1;
	printf("  first %ld bytes: ", byte_sz);

	for (i = 0; i < byte_sz; i++)
		printf("%02hhx%c", byte_py[i], i < byte_sz - 1 ? ' ' : '\n');
}

/**
 * print_python_list - Prints basic info of a python list
 * @p: pointer to object structure
 */

void print_python_list(PyObject *p)
{
	Py_ssize_t ls = PyList_Size(p);
	Py_ssize_t i;
	PyObject *it;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %lu\n", ls);
	printf("[*] Allocated = %lu\n", ((PyListObject *)p)->allocated);

	for (i = 0; i < ls; i++)
	{
		it = ((PyListObject *)(p))->ob_it[i];
		printf("Element %ld: %s\n", i, it->ob_type->tp_name);
		if (PyBytes_Check(it))
			print_python_bytes(it);
	}
}
