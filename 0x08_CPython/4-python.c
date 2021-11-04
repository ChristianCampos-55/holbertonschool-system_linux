#include <Python.h>
#include <object.h>
#include <stdio.h>

/**
 * print_python_string - prints Python string on unicode
 * @p: pointer to pyObject
 */

void print_python_string(PyObject *p)
{
	wprintf(L"[.] string object info\n");
	if (strncmp(p->ob_type->tp_name, "str", 3) != 0)
	{
		wprintf(L"  [ERROR] Invalid String Object\n");
		return;
	}

	if (((PyASCIIObject *)p)->state.ascii)
		wprintf(L"  type: compact ascii\n");
	else
		wprintf(L"  type: compact unicode object\n");
	wprintf(L"  length: %ld\n", ((PyASCIIObject *)p)->length);
	wprintf(L"  value: %ls\n", PyUnicode_AS_UNICODE(p));
}
