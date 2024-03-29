#include "test_common.h"
#include "../libsu.h"

//create a su file from scratch and copy over
int main(int argc, char *argv[])
{
    if(argc<3) {
        printf("Usage: cpy a.su b.su\n"
               "    copy data only to create b.su from empty!\n");
        exit(1);
    }
    const char *aname = argv[1];
    const char *bname = argv[2];

    SUID_t su1, su2;
    su_open(&su1, aname, SU_READONLY);
    int ninst = su_ninst(su1);
    int nsamp = su_nsamp(su1, 0);
    //printf("ninst=%d, nsamp=%d\n", ninst, nsamp);

    su_open(&su2, bname, SU_CREATE);
    su_nsamp(su2, nsamp);

    float *v1 = calloc(nsamp, sizeof(float));
    float *v2 = calloc(nsamp, sizeof(float));
    for(int i=0; i<ninst; i++) {
        su_read(su1, "trace", v1, i, 1);
        for(int j=0; j<nsamp; j++)
            v2[j] = -1*v1[j];
        su_write(su2, "trace", v2, i, 1);
    }
    free(v1);
    free(v2);
    int32_t *ns = calloc(ninst, sizeof(int32_t));
    for(int i=0; i<ninst; i++)
        ns[i] = nsamp;
    su_write(su2, "ns", ns, 0, ninst);
    free(ns);
    su_close(su1);
    su_close(su2);

    printf("# test-2c  success\n");
    return 0;
}
