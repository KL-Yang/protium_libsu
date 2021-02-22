//translation table
const su_attr_t default_su_attr[]={
    {.name="tracl",  .db_type=PT_INT32, .ibyte=0,   .nbyte=4, .su_type=SU_INT32},
    {.name="tracr",  .db_type=PT_INT32, .ibyte=4,   .nbyte=4, .su_type=SU_INT32},
    {.name="fldr",   .db_type=PT_INT32, .ibyte=8,   .nbyte=4, .su_type=SU_INT32},
    {.name="tracf",  .db_type=PT_INT32, .ibyte=12,  .nbyte=4, .su_type=SU_INT32},
    {.name="offset", .db_type=PT_INT32, .ibyte=36,  .nbyte=4, .su_type=SU_INT32},
    //for trace, nbyte is a place holder, always last item!
    {.name="trace",  .db_type=PT_FLOAT, .ibyte=240, .nbyte=0, .su_type=SU_FLOAT}
};

//there should be a default table and a translation table.
//search the user provided one first if exist!
int su_translate(SUID_t id, const su_attr_t *attr, int nattr)
{
    protium_suid_t *su = id;
    su_attr_t *buff = calloc(nattr, sizeof(su_attr_t));
    memcpy(buff, attr, nattr*sizeof(su_attr_t));
    su->new_attr = buff;
    su->new_num = nattr;
    return 0;
}
