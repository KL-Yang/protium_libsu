#ifndef H_LIBSU_SRC_LIBSU_PROTIUM
#define H_LIBSU_SRC_LIBSU_PROTIUM

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <search.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <protium/protium.h>

#define SU_READONLY 0
#define SU_CREATE   1
#define SU_UPDATE   2
#define SU_SUCCESS  0

#define SU_INT16    0
#define SU_INT32    1
#define SU_FLOAT    2
#define SU_IBMF     3   //ibm float, unlikely
#define SU_UNKNOWN  4

#define MAX(a,b)    ((a>b)?(a):(b))

typedef struct protium_suid_struct * SUID_t;

//used to translate su header to attribute name
typedef struct {
    char    name[32];
    int     db_type;
    int     ibyte;      //< position in su header
    int     nbyte;      //< number of byte to read
    int     su_type;    //< su data type
} su_attr_t;

struct protium_suid_struct {
    int         fid;        //< su file id
    int         ninst;
    int         flag;
    int         ns;
    int         skip;       //< trace skip
    su_attr_t * attr;
    int         nattr;
    char     ** names;
};
typedef struct protium_suid_struct protium_suid_t;

int su_open(SUID_t *id, const char *path, int flag);
int su_ninst(SUID_t id);
int su_nsamp(SUID_t id);
int su_setnsamp(SUID_t id, int ns);
int su_read(SUID_t id, const char *name, void *buff, int first, int nmemb);
int su_write(SUID_t id, const char *name, void *buff, int first, int nmemb);
int su_close(SUID_t id);

#endif
