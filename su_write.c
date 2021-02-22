static int su_writebytes(SUID_t id, const su_attr_t *attr, 
    void *buff, int first, int ninst)
{
    protium_suid_t *su = id;
    assert(su->skip!=0 && su->ninst>=first+ninst);
    for(int i=0; i<ninst; i++) {
        int64_t f_offs=(first+i)*su->skip+attr->ibyte;
        int64_t b_offs=i*attr->nbyte;
        pwrite(su->fid, buff+b_offs, attr->nbyte, f_offs);
        printf("%s: write %d at %ld\n", __func__, attr->nbyte,
            f_offs);
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
