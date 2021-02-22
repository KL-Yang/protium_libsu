int su_readbytes(SUID_t id, const su_attr_t *attr, void *buff, 
    int first, int ninst)
{
    protium_suid_t *su = id;
    assert(su->skip!=0 && su->ninst>=first+ninst);
    for(int i=0; i<ninst; i++) {
        int64_t f_offs=(first+i)*su->skip+attr->ibyte;
        int64_t b_offs=i*attr->nbyte;
        if(pread(su->fid, buff+b_offs, attr->nbyte, f_offs)!=attr->nbyte) {
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
    su_attr_t curr; memcpy(&curr, attr, sizeof(su_attr_t));
    int length=1;
    if(curr.ibyte==240) {    //must be trace!
        length=su->ns;
        curr.nbyte = su->ns*sizeof(float);
    }
    void *work = calloc(nmemb, curr.nbyte);
    su_readbytes(id, &curr, work, first, nmemb); //and conver to db required format!!!
    //for(int i=0; i<length; i++)
    //    printf(" [%d] %f\n", i, ((float*)work)[i]);
    su_type2db(work, curr.su_type, buff, curr.db_type, nmemb*length);
    free(work);
    return 0;
}
