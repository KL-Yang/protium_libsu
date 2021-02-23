static int i_su_ninst(int fd, int length)
{
    off_t file_len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    if(file_len%length!=0) {
        printf("%s: file lenght is not consistent!\n", __func__);
        abort();
    }
    return file_len/length;
}

int su_open(SUID_t *id, const char *path, int flag)
{
    protium_suid_t *su = *id = calloc(1, sizeof(protium_suid_t));
    su->flag = flag;
    su->nattr = sizeof(default_su_attr)/sizeof(su_attr_t);
    su->attr = calloc(su->nattr, sizeof(su_attr_t));
    memcpy(su->attr, default_su_attr, sizeof(default_su_attr));
    if(flag==SU_CREATE) {
        su->fid = open(path, O_RDWR|O_CREAT,
                S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    } else {
        if((su->fid=open(path, O_RDWR))<0) {
            printf("%s: failed to open(%s)!\n", __func__, path);
            abort();
        }
        int16_t nsdt; 
        if(pread(su->fid, &nsdt, 2, 114)!=2) {
            printf("%s: pread unfinished!\n", __func__);
            abort();
        }
        su->ns = nsdt;
        su->skip = 240+su->ns*sizeof(float);
        su->ninst = i_su_ninst(su->fid, su->skip);
    }
    return 0;
}

int su_nsamp(SUID_t id)
{
    return ((protium_suid_t*)id)->ns;
}

int su_setnsamp(SUID_t id, int ns)
{
    protium_suid_t *su = id;
    if(su->flag!=SU_CREATE || su->ns!=0) {
        printf("%s: only SU_CREATE can change ns!\n", __func__);
        abort();
    }
    su->ns = ns;
    su->skip = 240+ns*sizeof(float);
    return 0;
}

int su_ninst(SUID_t id)
{
    return ((protium_suid_t*)id)->ninst;
}

#ifdef LIBSU_PYTHON
/**
 * @brief Open a su file and return a handle!
 *   su.open(name, flag)
 * @param[in] flag SU_CREATE/SU_READONLY/SU_UPDATE
 * */
static PyObject * pysu_open(PyObject __attribute__((unused)) *self, PyObject *args)
{
    int flag;
    const char *name;
    if(!PyArg_ParseTuple(args, "si", &name, &flag))
      return NULL;

    SUID_t id;
    PyObject *db;
    if(su_open(&id, name, flag)!=SU_SUCCESS) {
        printf("%s: *ERROR* su_open(%s, %d) Failed\n", __func__, name, flag);
        return NULL;
    }
    db = PyCapsule_New(id, NULL, NULL);
    return db;
}

/**
 * @brief Get number of seismic traces stored in database, for example, 
 *   ntrace = su.ninst(id)
 * @param[in] id opaque object to access the database
 * @return -1 for Failure or number of traces
 * */
static PyObject * pysu_ninst(PyObject __attribute__((unused)) *self, PyObject *args)
{
    PyObject *db;
    protium_suid_t *id;
    PyArg_ParseTuple(args, "O", &db);
    id = PyCapsule_GetPointer(db, NULL);
    
    int64_t ninst;
    ninst = su_ninst(id);
    return PyLong_FromLong(ninst);
}

/**
 * @brief Get number of samples per trace stored in database, for example, 
 *   nsamp = su.nsamp(id)
 * @param[in] id opaque object to access the database
 * @return -1 for Failure or number of samples
 * */
static PyObject * pysu_nsamp(PyObject __attribute__((unused)) *self, PyObject *args)
{
    PyObject *db;
    protium_suid_t *id;
    PyArg_ParseTuple(args, "O", &db);
    id = PyCapsule_GetPointer(db, NULL);
    
    int64_t nsamp;
    nsamp = su_nsamp(id);
    return PyLong_FromLong(nsamp);
}

#endif
