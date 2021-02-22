int su_readbytes(SUID_t id, const su_attr_t *attr, void *buff, 
    int first, int ninst)
{
    protium_suid_t *su = id;
    assert(su->skip!=0 && su->ninst>=first+ninst);
    for(int i=0; i<ninst; i++) {
        int64_t f_offs=(first+i)*su->skip+attr->ibyte;
        int64_t b_offs=i*attr->nbyte;
        pread(su->fid, buff+b_offs, attr->nbyte, f_offs);
    }
    return 0;
}

int su_read(SUID_t id, const char *name, void *buff, int first, 
    int nmemb)
{
    const su_attr_t *attr = su_findattr(id, name);
    if(attr==NULL) {
        printf("%s: attribute %s not found!\n", __func__, name);
        abort();
    }
    //TODO: add type convert later
    //void *work = calloc()
    su_readbytes(id, attr, buff, first, nmemb); //and conver to db required format!!!
    return 0;
}
