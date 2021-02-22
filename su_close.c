//we only responsible for write ns for every trace!
int su_close(SUID_t id)
{
    protium_suid_t *su = id;
    if(su->new_num!=0 || su->new_attr!=NULL)
        free(su->new_attr);
    close(su->fid);
    free(su);
    return 0;
}
