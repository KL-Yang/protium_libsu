//we only responsible for write ns for every trace!
int su_close(SUID_t id)
{
    protium_suid_t *su = id;
    i_su_names_free(su->names, su->nattr);
    free(su->attr);
    close(su->fid);
    free(su);
    return 0;
}

#ifdef LIBSU_PYTHON
/**
 * @brief close the su handle in python, for example
 *  su.destroy(id)
 * @param[in] id opaque object to access the data flow
 * @return True or False
 * */
static PyObject * pysu_close(PyObject __attribute__((unused)) *self, PyObject *args)
{
    PyObject *db;
    protium_suid_t *id;
    if(!PyArg_ParseTuple(args, "O", &db))
      return NULL;

    id = PyCapsule_GetPointer(db, NULL);
    su_close(id);
    Py_INCREF(Py_True);
    return Py_True;
}

#endif
