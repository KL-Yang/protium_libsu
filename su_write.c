static int su_writebytes(SUID_t id, const su_attr_t *attr, 
    void *buff, int first, int ninst)
{
    protium_suid_t *su = id;
    assert(su->skip!=0 && su->ninst>=first+ninst);
    for(int i=0; i<ninst; i++) {
        int64_t f_offs=(first+i)*su->skip+attr->ibyte;
        int64_t b_offs=i*attr->nbyte;
        if(pwrite(su->fid, buff+b_offs, attr->nbyte, f_offs)!=attr->nbyte) {
            printf("%s: pwrite is not finished!\n", __func__);
            abort();
        }
    }
    return 0;
}

int su_write(SUID_t id, const char *name, void *buff, int first,
    int nmemb)
{
    protium_suid_t *su = id;
    su->ninst = MAX(su->ninst, first+nmemb);
    const su_attr_t *attr = su_findattr(id, name);
    if(attr==NULL) {
        printf("%s: attribute %s not found!\n", __func__, name);
        abort();
    }
    su_attr_t curr; memcpy(&curr, attr, sizeof(su_attr_t));
    int length=1;
    if(curr.ibyte==240) {    //must be trace!
        length=su->ns; assert(length!=0);
        curr.nbyte = su->ns*sizeof(float);
    }
    void *work = calloc(nmemb, curr.nbyte);
    su_type2su(buff, curr.db_type, work, curr.su_type, nmemb*length);
    //memcpy(work, buff, nmemb*length*sizeof(float));
    su_writebytes(id, &curr, work, first, nmemb);
    free(work);
    return 0;
}

#ifdef LIBSU_PYTHON
/**
 * @brief Write seismic attribute to the database, for example, 
 *   status = su.write(id, name, nparry, first, nmemb)
 * @param[in] id opaque object to access the database
 * @param[in] name python string of attribute name
 * @param[in] nparry numpy array contain the data to write,
 *                   the data can be larger but no smaller
 * @param[in] first the first trace to write start from zero
 * @param[in] nmemb number of trace to write
 * @return True if write successful and False otherwise
 * */
static PyObject * pysu_write(PyObject __attribute__((unused)) *self, PyObject *args)
{
    char *name;
    protium_suid_t *id;
    long long first, num;
    PyObject *db, *wtattr;
    if(!PyArg_ParseTuple(args, "OsOLL", &db, &name, &wtattr, &first, &num))
      return NULL;
    id = PyCapsule_GetPointer(db, NULL);

    npy_intp *dims;
    void *psrc, *pdes;
    int nd, np_type=NPY_INT32;

    const su_attr_t *attr = su_findattr(id, name);
    if(attr==NULL) {
        printf("%s: attribute %s not found!\n", __func__, name);
        abort();
    }
    int length=(attr->ibyte==240)?(id->ns):(1);
    nd = PyArray_NDIM((PyArrayObject*)wtattr);
    dims = PyArray_DIMS((PyArrayObject*)wtattr);
    if((length==1 && nd!=1) || (length!=1 && nd!=2) || (nd==2 && dims[1]!=length)) {
        printf("Dimension of nparray does not matching attribute!\n");
        Py_INCREF(Py_False);
        return Py_False;
    }

    if((nd==1 && dims[0]<num) || (nd==2 && dims[0]<num)) {
        printf("%s:Data in nparray is not enough for requested writing!\n", name);
        Py_INCREF(Py_False);
        return Py_False;
    }

    np_type = PyArray_TYPE((PyArrayObject*)wtattr);
    //np_type = np_type_to_db(np_type);
    np_type = pt_type_np2pt(np_type);

    pdes = malloc(num*pt_sizeof(attr->db_type, length));
    psrc = PyArray_DATA((PyArrayObject*)wtattr);
    pt_typeconvert(psrc, np_type, pdes, attr->db_type, num*length);
    su_write(id, name, pdes, first, num);
    free(pdes);
    Py_INCREF(Py_True);
    return Py_True;
}
#endif
