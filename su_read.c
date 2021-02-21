int su_readbytes(SUID_t id, su_attr_t *attr, void *buff, 
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
