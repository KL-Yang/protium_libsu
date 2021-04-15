const char **su_attrs(SUID_t id, int *nattr)
{
    char **names = NULL;
    protium_suid_t *su = (protium_suid_t*)(id);
    if(nattr) *nattr = su->xattr;
    names = su->names;
    return (const char **)names;
}

#ifdef LIBSU_PYTHON
/**
 * @brief get all attributes name in a list, for example,
 *   attrs = db.attrs(id). 
 * The index in the list is the same as in db.read().
 * @param[in] id opaque object to access the database
 * @return List contains all attribute names
 * */
static PyObject * pysu_attrs(PyObject __attribute__((unused)) *self, PyObject *args)
{
    PyObject *db;
    protium_suid_t *id;
    if(!PyArg_ParseTuple(args, "O", &db))
        return NULL;

    id = PyCapsule_GetPointer(db, NULL);

    int nattr;
    PyObject *list;
    const char * const * names;
    names = su_attrs(id, &nattr);
    list = PyList_New(nattr);
    for(int i=0; i<nattr; i++)
        PyList_SetItem(list, i, Py_BuildValue("s", names[i]));
    return list;
}
#endif
