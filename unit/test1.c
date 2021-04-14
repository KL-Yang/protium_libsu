#include "test_common.h"
#include "../libsu.h"

//this test update a file to its inversed data
int main(int argc, char *argv[])
{
    if(argc<3) {
        printf("Usage: inv a.su b.su\n"
               "     copy su and inverse its value!\n");
        exit(1);
    }
    const char *aname = argv[1];
    const char *bname = argv[2];
    char command[256];
    snprintf(command, 255, "cp -f %s %s", aname, bname);
    system(command);

    SUID_t id;
    su_open(&id, bname, SU_UPDATE);
    int ninst = su_ninst(id);
    int nsamp = su_nsamp(id, 0);
    float *v1 = calloc(ninst, nsamp*sizeof(float));
    float *v2 = calloc(ninst, nsamp*sizeof(float));
    su_read(id, "trace", v1, 0, ninst);
    for(int i=0; i<nsamp*ninst; i++) 
        v2[i] = -1*v1[i];
    su_write(id, "trace", v2, 0, ninst);

    int error=0;
    memset(v2, 0, nsamp*sizeof(float));
    su_read(id, "trace", v2, 0, ninst);
    for(int i=0; i<nsamp*ninst; i++) {
        if(v1[i]!=(-1*v2[i])) {
            printf("Error, value wront");
            printf(" %3d  %16e  %16e\n", i, v1[i], v2[i]);
            error++;
        }
    }
    //printf("# ninst=%d, nsamp=%d\n", ninst, nsamp);
    if(!error)
        printf("# test-1c  success\n");
    else
        printf("# test-1c  failed\n");
    su_close(id);
    free(v1);
    free(v2);
    return error;
}
