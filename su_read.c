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

static const su_attr_t *su_findattr(SUID_t id, const char *name)
{
    printf("%s: search for %s\n", __func__, name);
    protium_suid_t *su = id;
    if(su->new_num!=0 && su->new_attr!=NULL)
        for(int i=0; i<su->new_num; i++) {
            printf("new[%d] %s\n", i, su->new_attr[i].name);
            if(strcasecmp(name, su->new_attr[i].name)==0)
                return &su->new_attr[i];
        }
    for(int i=0; i<su->old_num; i++) {
        printf("old[%d] %s\n", i, su->old_attr[i].name);
        if(strcasecmp(name, su->old_attr[i].name)==0)
            return &su->old_attr[i];
    }
    return NULL;
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
    su_readbytes(id, attr, buff, first, nmemb); //and conver to db required format!!!
    return 0;
}
