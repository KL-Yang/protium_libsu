int su_open(SUID_t *id, const char *path, int flag)
{
    protium_suid_t *su = *id = calloc(1, sizeof(protium_suid_t));
    su->flag = flag;
    if(flag==SU_CREATE) {
        su->fid = open(path, O_CREAT);
    } else {
        su->fid = open(path, 0);
        int16_t nsdt[2];
        pread(su->fid, nsdt, 4, 114); 
        su->ns = nsdt[0];
        su->si = nsdt[1];
        su->skip = 240+su->ns*sizeof(float);
        printf("%s: ns=%d si=%d\n", __func__, su->ns, su->si);
    }
    return 0;
}

int su_gettrace(SUID_t id, int *ns, int *si)
{
    protium_suid_t *su = id;
    *ns = su->ns;
    *si = su->si;
    return 0;
}

int su_settrace(SUID_t id, int ns, int si)
{
    protium_suid_t *su = id;
    if(su->flag!=SU_CREATE || su->ns!=0 || su->si!=0) {
        printf("%s: only SU_CREATE allowed to change ns and si once!\n",
            __func__);
        abort();
    }
    su->ns = ns;
    su->si = si;
    return 0;
}

int su_ninst()
{
    return 0;
}

//translation table
int su_settable();
