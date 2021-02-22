static int i_su_ninst(int fd, int length)
{
    off_t file_len;
    file_len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    if(file_len%length!=0) {
        printf("%s: file lenght is not consistent!\n", __func__);
        printf("%s: file_len=%ld, length=%d\n", __func__, 
            file_len, length);
        abort();
    }
    return file_len/length;
}

int su_open(SUID_t *id, const char *path, int flag)
{
    protium_suid_t *su = *id = calloc(1, sizeof(protium_suid_t));
    su->flag = flag;
    su->old_attr = default_su_attr;
    su->old_num = sizeof(default_su_attr)/sizeof(su_attr_t);
    if(flag==SU_CREATE) {
        su->fid = open(path, O_CREAT);
    } else {
        if((su->fid=open(path, 0))<0) {
            printf("%s: failed to open(%s)!\n", __func__, path);
            abort();
        }
        int16_t nsdt[2]; 
        pread(su->fid, nsdt, 4, 114); 
        su->ns = nsdt[0];
        su->si = nsdt[1];
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
    if(su->flag!=SU_CREATE || su->ns!=0 || su->si!=0) {
        printf("%s: only SU_CREATE allowed to change ns and si once!\n",
            __func__);
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
