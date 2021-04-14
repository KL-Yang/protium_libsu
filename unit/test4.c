#include "test_common.h"
#include "../libsu.h"

//test read/write "_head" and "trace"
int main(int argc, char *argv[])
{
    if(argc<3) {
        printf("Usage: sucp a.su b.su\n"
               "  exact copy, should have same md5sum\n");
        exit(1);
    }
    const char *aname = argv[1];
    const char *bname = argv[2];

    SUID_t id; 
    int ninst, nsamp; float *v, *h;

    su_open(&id, aname, SU_READONLY);
    ninst = su_ninst(id);
    nsamp = su_nsamp(id, 0);
    printf("# ninst=%d, nsamp=%d\n", ninst, nsamp);
    fflush(0);

    h = calloc(ninst, 240);
    v = calloc(ninst, nsamp*sizeof(float));
    su_read(id, "_head", h, 0, ninst);
    su_read(id, "trace", v, 0, ninst);
    su_close(id);

    su_open(&id, bname, SU_CREATE);
    su_nsamp(id, nsamp);
    su_write(id, "_head", h, 0, ninst);
    su_write(id, "trace", v, 0, ninst);
    su_close(id);

    free(h);
    free(v);
    printf("# finished!\n");
    return 0;
}
