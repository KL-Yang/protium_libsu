//translation table, must include trace@.ibyte=240
//TODO: user can add their own translation definition.
const su_attr_t default_su_attr[]={
    {.name="tracl",  .db_type=PT_INT32, .ibyte=0,   .su_type=SU_INT32},
    {.name="tracr",  .db_type=PT_INT32, .ibyte=4,   .su_type=SU_INT32},
    {.name="fldr",   .db_type=PT_INT32, .ibyte=8,   .su_type=SU_INT32},
    {.name="tracf",  .db_type=PT_INT32, .ibyte=12,  .su_type=SU_INT32},
    {.name="ep",     .db_type=PT_INT32, .ibyte=16,  .su_type=SU_INT32},
    {.name="cdp",    .db_type=PT_INT32, .ibyte=20,  .su_type=SU_INT32},
    {.name="cdpt",   .db_type=PT_INT32, .ibyte=24,  .su_type=SU_INT32},
    {.name="trid",   .db_type=PT_INT32, .ibyte=28,  .su_type=SU_INT16},
    {.name="nvs",    .db_type=PT_INT32, .ibyte=30,  .su_type=SU_INT16},
    {.name="nhs",    .db_type=PT_INT32, .ibyte=32,  .su_type=SU_INT16},
    {.name="duse",   .db_type=PT_INT32, .ibyte=34,  .su_type=SU_INT16},
    {.name="offset", .db_type=PT_INT32, .ibyte=36,  .su_type=SU_INT32},
    {.name="gelev",  .db_type=PT_INT32, .ibyte=40,  .su_type=SU_INT32},
    {.name="selev",  .db_type=PT_INT32, .ibyte=44,  .su_type=SU_INT32},
    {.name="sdepth", .db_type=PT_INT32, .ibyte=48,  .su_type=SU_INT32},
    {.name="gdel",   .db_type=PT_INT32, .ibyte=52,  .su_type=SU_INT32},
    {.name="sdel",   .db_type=PT_INT32, .ibyte=56,  .su_type=SU_INT32},
    {.name="swdep",  .db_type=PT_INT32, .ibyte=60,  .su_type=SU_INT32},
    {.name="gwdep",  .db_type=PT_INT32, .ibyte=64,  .su_type=SU_INT32},
    {.name="scalel", .db_type=PT_INT32, .ibyte=68,  .su_type=SU_INT16},
    {.name="scalco", .db_type=PT_INT32, .ibyte=70,  .su_type=SU_INT16},
    {.name="sx",     .db_type=PT_FLOAT, .ibyte=72,  .su_type=SU_INT32},
    {.name="sy",     .db_type=PT_FLOAT, .ibyte=76,  .su_type=SU_INT32},
    {.name="gx",     .db_type=PT_FLOAT, .ibyte=80,  .su_type=SU_INT32},
    {.name="gy",     .db_type=PT_FLOAT, .ibyte=84,  .su_type=SU_INT32},
    {.name="counit", .db_type=PT_INT32, .ibyte=88,  .su_type=SU_INT16},
    {.name="wevel",  .db_type=PT_INT32, .ibyte=90,  .su_type=SU_INT16},
    {.name="swevel", .db_type=PT_INT32, .ibyte=92,  .su_type=SU_INT16},
    {.name="sut",    .db_type=PT_INT32, .ibyte=94,  .su_type=SU_INT16},
    {.name="gut",    .db_type=PT_INT32, .ibyte=96,  .su_type=SU_INT16},
    {.name="sstat",  .db_type=PT_INT32, .ibyte=98,  .su_type=SU_INT16},
    {.name="gstat",  .db_type=PT_INT32, .ibyte=100, .su_type=SU_INT16},
    {.name="tstat",  .db_type=PT_INT32, .ibyte=102, .su_type=SU_INT16},
    {.name="laga",   .db_type=PT_INT32, .ibyte=104, .su_type=SU_INT16},
    {.name="lagb",   .db_type=PT_INT32, .ibyte=106, .su_type=SU_INT16},
    {.name="delrt",  .db_type=PT_INT32, .ibyte=108, .su_type=SU_INT16},
    {.name="muts",   .db_type=PT_INT32, .ibyte=110, .su_type=SU_INT16},
    {.name="mute",   .db_type=PT_INT32, .ibyte=112, .su_type=SU_INT16},
    {.name="ns",     .db_type=PT_INT32, .ibyte=114, .su_type=SU_INT16},
    {.name="dt",     .db_type=PT_INT32, .ibyte=116, .su_type=SU_INT16},
    {.name="gain",   .db_type=PT_INT32, .ibyte=118, .su_type=SU_INT16},
    {.name="igc",    .db_type=PT_INT32, .ibyte=120, .su_type=SU_INT16},
    {.name="igi",    .db_type=PT_INT32, .ibyte=122, .su_type=SU_INT16},
    {.name="corr",   .db_type=PT_INT32, .ibyte=124, .su_type=SU_INT16},
    {.name="sfs",    .db_type=PT_INT32, .ibyte=126, .su_type=SU_INT16},
    {.name="sfe",    .db_type=PT_INT32, .ibyte=128, .su_type=SU_INT16},
    {.name="slen",   .db_type=PT_INT32, .ibyte=130, .su_type=SU_INT16},
    {.name="styp",   .db_type=PT_INT32, .ibyte=132, .su_type=SU_INT16},
    {.name="stas",   .db_type=PT_INT32, .ibyte=134, .su_type=SU_INT16},
    {.name="stae",   .db_type=PT_INT32, .ibyte=136, .su_type=SU_INT16},
    {.name="tatyp",  .db_type=PT_INT32, .ibyte=138, .su_type=SU_INT16},
    {.name="afilf",  .db_type=PT_INT32, .ibyte=140, .su_type=SU_INT16},
    {.name="afils",  .db_type=PT_INT32, .ibyte=142, .su_type=SU_INT16},
    //following is specific to su file
    {.name="d1",     .db_type=PT_FLOAT, .ibyte=180, .su_type=SU_FLOAT},
    {.name="f1",     .db_type=PT_FLOAT, .ibyte=184, .su_type=SU_FLOAT},
    {.name="d2",     .db_type=PT_FLOAT, .ibyte=188, .su_type=SU_FLOAT},
    {.name="f2",     .db_type=PT_FLOAT, .ibyte=192, .su_type=SU_FLOAT},
    //for trace, nbyte is a place holder, always last item!
    {.name="trace",  .db_type=PT_FLOAT, .ibyte=240, .su_type=SU_FLOAT},
    {.name="_head",  .db_type=PT_BYTE,  .ibyte=0,   .su_type=SU_BYTE} //dummy attribute
};

static void 
i_su_names(const su_attr_t *attr, int nattr, char **names)
{
    for(int i=0; i<nattr; i++) {
        names[i] = calloc(strlen(attr[i].name)+1, sizeof(char));
        strcpy(names[i], attr[i].name);
    }
    names[nattr] = NULL;
}

static void i_su_names_free(char **names, int nattr)
{
    for(int i=0; i<nattr; i++)
        free(names[i]);
    free(names);
}


//there should be a default table and a translation table.
//search the user provided one first if exist!
int su_translate(SUID_t id, const su_attr_t *attr, int nattr)
{
    protium_suid_t *su = id;
    i_su_names_free(su->names, su->nattr);
    su->attr = realloc(su->attr, nattr*sizeof(su_attr_t));
    memcpy(su->attr, attr, nattr*sizeof(su_attr_t));
    su->nattr = nattr;
    su->names = calloc(su->nattr+1, sizeof(void*));
    i_su_names(su->attr, su->nattr, su->names);
    return 0;
}

//now linear search, should be hash search.
static const su_attr_t *su_findattr(SUID_t id, const char *name)
{
    protium_suid_t *su = id;
    for(int i=0; i<su->nattr; i++)
        if(strcasecmp(name, su->attr[i].name)==0)
            return &su->attr[i];
    return NULL;
}

static void su_int16to32(const int16_t *p1, int n, int32_t *p2)
{
    for(int i=0; i<n; i++)
        p2[i]=p1[i];
}

static void su_int32to16(const int32_t *p1, int n, int16_t *p2)
{
    for(int i=0; i<n; i++)
        p2[i]=p1[i];
}

//this is a none efficient simple convert, fix later.
static void su_type2db(const void *p1, int su_type, void *p2, int t2, int nmemb)
{
    if(su_type==SU_BYTE || t2==PT_BYTE) {
        memcpy(p2, p1, nmemb);  //for unknown type nmemb=size!!
        return;
    }
    void *work = calloc(nmemb, sizeof(int32_t));
    int t1 = PT_INT32;  //default
    switch(su_type) {
        case SU_INT16:
            su_int16to32(p1, nmemb, work);
            break;
        case SU_INT32:
            for(int i=0; i<nmemb; i++)
                ((int32_t*)work)[i]=((int32_t*)p1)[i];
            break;
        case SU_FLOAT:
            t1 = PT_FLOAT;
            for(int i=0; i<nmemb; i++)
                ((float*)work)[i]=((float*)p1)[i];
            break;
        default:
            printf("Unknown type yet!");
            abort();
    }
    pt_typeconvert(work, t1, p2, t2, nmemb);
    free(work);
}

/**
 * PT_type to SU_type conversion
 * */
static void su_type2su(const void *p1, int db_type, void *p2,
    int su_type, int nmemb)
{
    if(su_type==SU_BYTE || db_type==PT_BYTE) {
        memcpy(p2, p1, nmemb);  //for unknown type nmemb=size!!
        return;
    }
    int t2 = PT_INT32;  //convert to int32 first
    if(su_type==SU_FLOAT)
        t2 = PT_FLOAT;
    void *work = calloc(nmemb, sizeof(int32_t));
    pt_typeconvert(p1, db_type, work, t2, nmemb);
    if(su_type==SU_INT16)
        su_int32to16(work, nmemb, p2);
    else
        memcpy(p2, work, nmemb*sizeof(float));
    free(work);
}
