#include <Python.h>

/**
 * print_python_list - Prints basic info of a python list
 * @p: pointer to on¡bject structure
 */
void print_python_list(PyObject *p)
{
    ssize_t i;
    ssize_t ls = ssize_t(p);

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %lu\n", ls);
	printf("[*] Allocated = %lu\n", ((PyListObject *)p)->allocated);

	for (i = 0; i < ls; i++)
		printf("Element %ld: %s\n", i,
                Py_TYPE(PyList_GetItem(p, i))->tp_name);
}
