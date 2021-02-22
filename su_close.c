//we only responsible for write ns for every trace!
int su_close(SUID_t id)
{
    protium_suid_t *su = id;
    free(su->attr);
    close(su->fid);
    free(su);
    return 0;
}
