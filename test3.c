#include "libsu.h"

int main()
{
    SUID_t su1, su2;
    su_open(&su1, "shots.total.su", SU_READONLY);
    int ninst = su_ninst(su1);
    int nsamp = su_nsamp(su1);
    printf("#ninst=%d nsamp=%d\n", ninst, nsamp);

    int32_t *fldr;
    fldr = calloc(ninst, sizeof(int32_t));
    su_read(su1, "fldr", fldr, 0, ninst);
    //for(int i=0; i<ninst; i++)
    //    printf("%3d %d\n", i, fldr[i]);

    int *first, *nmemb, nshot=0;
    first = calloc(ninst, sizeof(int));
    nmemb = calloc(ninst, sizeof(int));
    for(int i=0; i<ninst; i++) {
        if(fldr[i]!=fldr[first[nshot]]) {
            nshot++;
            first[nshot]=i;
        }
        nmemb[nshot]++;
    }
    nshot++;
    free(fldr);

    //printf("nshot=%d\n", nshot);
    first = realloc(first, nshot*sizeof(int));
    nmemb = realloc(nmemb, nshot*sizeof(int));
    for(int i=0; i<nshot; i++)
        printf("group[%4d] %8d->%8d\n", i, first[i], 
            first[i]+nmemb[i]-1);

    su_open(&su2, "shots.test3c.su", SU_CREATE);
    su_setnsamp(su2, nsamp);
    for(int i=0; i<nshot; i++) {
        float   *v1 = calloc(nmemb[i], nsamp*sizeof(float));
        int32_t *ns = calloc(nmemb[i], sizeof(int32_t));
        int32_t *fl = calloc(nmemb[i], sizeof(int32_t));
        su_read(su1,  "trace", v1, first[i], nmemb[i]);
        for(int j=0; j<nsamp*nmemb[i]; j++)
            v1[j] *= (-1.f);
        su_write(su2, "trace", v1, first[i], nmemb[i]);
        su_read(su1,  "ns", ns, first[i], nmemb[i]);
        su_write(su2, "ns", ns, first[i], nmemb[i]);
        su_read(su1,  "fldr", fl, first[i], nmemb[i]);
        su_write(su2, "fldr", fl, first[i], nmemb[i]);
        free(fl);
        free(ns);
        free(v1);
    }

    free(first);
    free(nmemb);
    su_close(su1);
    su_close(su2);
    return 0;
}
