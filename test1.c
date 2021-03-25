#include "libsu.h"

//this test update a file to its inversed data
int main()
{
    system("cp -f wav.su wav_test1c.su");

    SUID_t id;
    su_open(&id, "wav_test1c.su", SU_UPDATE);
    int ninst = su_ninst(id);
    int nsamp = su_nsamp(id, 0);
    float *v1 = calloc(nsamp, sizeof(float));
    float *v2 = calloc(nsamp, sizeof(float));
    su_read(id, "trace", v1, 0, 1);
    for(int i=0; i<nsamp; i++) 
        v2[i] = -1*v1[i];
    su_write(id, "trace", v2, 0, 1);

    memset(v2, 0, nsamp*sizeof(float));
    su_read(id, "trace", v2, 0, 1);
    for(int i=0; i<nsamp; i++) 
        printf(" %3d  %16e  %16e\n", i, v1[i], v2[i]);
    printf("# ninst=%d, nsamp=%d\n", ninst, nsamp);
    su_close(id);
    free(v1);
    free(v2);
    return 0;
}
