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
    protium_suid_t *su = id;
    const su_attr_t *attr = su_findattr(id, name);
    if(attr==NULL) {
        printf("%s: attribute %s not found!\n", __func__, name);
        abort();
    }
    int size=attr->nbyte, length=1;
    if(attr->ibyte==240) {    //must be trace!
        size=sizeof(float);
        length=su->ns;
    }
    void *work = calloc(nmemb, length*size);
    su_readbytes(id, attr, work, first, nmemb); //and conver to db required format!!!
    su_typeconvert(work, attr->su_type, buff, attr->db_type, nmemb*length);
    free(work);
    return 0;
}
