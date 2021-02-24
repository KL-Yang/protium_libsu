/**
 * Return the type after translation.
 * */
int su_getattr(SUID_t id, const char *name, int *type)
{
    const su_attr_t *attr = su_findattr(id, name);
    if(attr==NULL) {
        printf("%s: requested attribute %s not found!\n",
            __func__, name);
        abort();
    }
    *type = attr->db_type;
    return 0;
}

#ifdef LIBSU_PYTHON
/**
 * @brief Get database attribute definition, for example,
 * myattr = su.getattr(id, name).
 * @param[in] id opaque object to access the database
 * @param[in] name python string of attribute name
 * @return dictionary contains "type". 
 * type is one of "INT32", "INT64", "FLOAT" or "DOUBLE".
 * */
static PyObject * pysu_getattr(PyObject __attribute__((unused)) *self, PyObject *args)
{
    char *name;
    PyObject *db;
    protium_suid_t *id;
    if(!PyArg_ParseTuple(args, "Os", &db, &name))
      return NULL;
    id = PyCapsule_GetPointer(db, NULL);
    
    PyObject *attr;
    int type;
    su_getattr(id, name, &type);

    attr = PyDict_New();
    PyDict_SetItemString(attr, "type", PyUnicode_FromString(pt_type2str(type)));
    return attr;
}
#endif
