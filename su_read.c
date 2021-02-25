int su_readbytes(SUID_t id, const su_attr_t *attr, void *buff, 
    int first, int ninst)
{
    protium_suid_t *su = id;
    assert(su->skip!=0 && su->ninst>=first+ninst);
    int nbyte=(attr->su_type==SU_INT16)?(2):(4);
    for(int i=0; i<ninst; i++) {
        int64_t f_offs=(first+i)*su->skip+attr->ibyte;
        int64_t b_offs=i*nbyte;
        if(pread(su->fid, buff+b_offs, nbyte, f_offs)!=nbyte) {
            printf("%s: pread not finished!\n", __func__);
            abort();
        }
    }
    return 0;
}

int su_read(SUID_t id, const char *name, void *buff, int first, 
    int nmemb)
{
    protium_suid_t *su = id;
    const su_attr_t *attr = su_findattr(id, name);
    if(attr==NULL) {
        printf("%s: attribute %s not found!\n", __func__, name);
        abort();
    }
    int length=(attr->ibyte==240)?(su->ns):(1);
    int size=(attr->su_type==SU_INT16)?(2):(4);
    void *work = calloc(nmemb*length, size);
    su_readbytes(id, attr, work, first, nmemb); //and conver to db required format!!!
    su_type2db(work, attr->su_type, buff, attr->db_type, nmemb*length);
    free(work);
    return 0;
}

#ifdef LIBSU_PYTHON
/**
 * @brief Read seismic attribute and return as numpy array,
 * for example, nparry = su.read(id, name, first, nmemb)
 * @param[in] id opaque object to access the database
 * @param[in] name python string of attribute name
 * @param[in] first the first trace to read start from zero
 * @param[in] nmemb number of trace to read
 * @return the numpy array contains the requested data
 * */
static PyObject * pysu_read(PyObject __attribute__((unused)) *self, PyObject *args)
{
    char *name;
    protium_suid_t *su;
    long long first, num;
    PyObject *db, *rdattr;
    if(!PyArg_ParseTuple(args, "OsLL", &db, &name, &first, &num))
        return NULL;
    su = PyCapsule_GetPointer(db, NULL);

    npy_intp dims[2];
    int nd, np_type;
    const su_attr_t *attr = su_findattr(su, name);
    if(attr==NULL) {
        printf("%s: attribute %s not found!\n", __func__, name);
        abort();
    }

    if(attr->ibyte!=240) {nd = 1; dims[0] = num; } 
    else { nd = 2; dims[0] = num; dims[1] = su->ns; }
    np_type = pt_type_pt2np(attr->db_type);

    rdattr = PyArray_SimpleNew(nd, dims, np_type);
    void *pdes = PyArray_DATA((PyArrayObject*)rdattr);
    su_read(su, name, pdes, first, num);
    return rdattr;
}
#endif
