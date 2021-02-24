//translation table, must include trace@.ibyte=240
const su_attr_t default_su_attr[]={
    {.name="tracl",  .db_type=PT_INT32, .ibyte=0,   .nbyte=4, .su_type=SU_INT32},
    {.name="tracr",  .db_type=PT_INT32, .ibyte=4,   .nbyte=4, .su_type=SU_INT32},
    {.name="fldr",   .db_type=PT_INT32, .ibyte=8,   .nbyte=4, .su_type=SU_INT32},
    {.name="tracf",  .db_type=PT_INT32, .ibyte=12,  .nbyte=4, .su_type=SU_INT32},
    {.name="offset", .db_type=PT_INT32, .ibyte=36,  .nbyte=4, .su_type=SU_INT32},
    {.name="ns",     .db_type=PT_INT32, .ibyte=114, .nbyte=2, .su_type=SU_INT16},
    //for trace, nbyte is a place holder, always last item!
    {.name="trace",  .db_type=PT_FLOAT, .ibyte=240, .nbyte=0, .su_type=SU_FLOAT}
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
    void *work = calloc(nmemb, 4);
    int t1 = PT_INT32;  //default
    switch(su_type) {
        case SU_INT16:
            t1 = PT_INT32;
            su_int16to32(p1, nmemb, work);
            break;
        case SU_INT32:
            memcpy(work, p1, nmemb*sizeof(int32_t));
            break;
        case SU_FLOAT:
            t1 = PT_FLOAT;
            memcpy(work, p1, nmemb*sizeof(float));
            break;
        default:
            printf("Unknown type yet!");
            abort();
    }
    pt_typeconvert(work, t1, p2, t2, nmemb);
    free(work);
}

static void su_type2su(const void *p1, int db_type, void *p2,
    int su_type, int nmemb)
{
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
