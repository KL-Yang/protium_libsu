#define SU_INT16    0
#define SU_INT32    1
#define SU_FLOAT    2
#define SU_IBMF     3   //ibm float, unlikely

static void su_int16to32(const int16_t *p1, int n, int32_t *p2)
{
    for(int i=0; i<n; i++)
        p2[i]=p1[i];
}

void su_typeconvert(const void *p1, int su_type, void *p2, 
    int t2, int nmemb)
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

int64_t su_sizeof(int type, int length)
{
    size_t type_size=sizeof(int32_t);
    if(type==SU_INT16)
        type_size = sizeof(int16_t);
    return type_size*length;
}
