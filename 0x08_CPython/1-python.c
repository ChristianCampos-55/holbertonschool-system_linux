#include <Python.h>

/**
 * print_python_list - Prints basic info of a python list
 * @p: pointer to on¡bject structure
 */
void print_python_list(PyObject *p)
{
    p_ssize_t i;
    p_ssize_t ls = p_ssize_t(p);

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %lu\n", ls);
	printf("[*] Allocated = %lu\n", ((PyListObject *)p)->allocated);

	for (i = 0; i < ls; i++)
		printf("Element %ld: %s\n", i,
                ((PyListObject *)p)->ob_item[i]->ob_type->tp_name);
}
