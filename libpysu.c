#define _GNU_SOURCE
#define Py_USING_UNICODE
#include <Python.h>
#define  NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

#define LIBSU_PYTHON

#include "su_i.h"
#include "su_utility.c"
#include "su_getattr.c"
#include "su_attr.c"
#include "su_read.c"
#include "su_open.c"
#include "su_close.c"
#include "su_write.c"

static PyMethodDef pysuMethods[] = {
    {"open",      pysu_open,      METH_VARARGS, "Open a Seismic Unix dataset."},
    {"close",     pysu_close,     METH_VARARGS, "Close SU dataset."},
/*    {"addattr",   pydb_addattr,   METH_VARARGS, "db.addattr(id, name, dict)."},
*/  {"attrs",     pysu_attrs,     METH_VARARGS, "Get attributes names as list."},
    {"getattr",   pysu_getattr,   METH_VARARGS, "su.getattr(id, name) return attribute info"},
    {"nsamp",     pysu_nsamp,     METH_VARARGS, "su.nsamp(id, nsamp)"},
    {"ninst",     pysu_ninst,     METH_VARARGS, "ninst = su.ninst(id)"},
    {"read",      pysu_read,      METH_VARARGS, "ndarry = su.read(id, name, first, num)"},
    {"write",     pysu_write,     METH_VARARGS, "su.write(id, name, ndarry, first, num)"},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef libpysu = {
    PyModuleDef_HEAD_INIT,
    "libpysu",   /* name of module */
    "libpysu_doc", /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    pysuMethods
};

static PyObject *PydbError;

PyMODINIT_FUNC PyInit_libpysu(void)
{
    Py_Initialize();
    PyObject *m = PyModule_Create(&libpysu);
    if (m == NULL)
      return NULL;
    import_array();
    PydbError = PyErr_NewException("db.error", NULL, NULL);
    PyModule_AddObject(m, "error", PydbError);

    PyModule_AddIntConstant(m, "CREATE",   SU_CREATE);
    PyModule_AddIntConstant(m, "READONLY", SU_READONLY);
    PyModule_AddIntConstant(m, "UPDATE",   SU_UPDATE);
    PyModule_AddIntConstant(m, "INT16",    SU_INT16);
    PyModule_AddIntConstant(m, "INT32",    SU_INT32);
    PyModule_AddIntConstant(m, "FLOAT",    SU_FLOAT);
    PyModule_AddIntConstant(m, "UNKNOWN",  SU_UNKNOWN);
    return m;
}
