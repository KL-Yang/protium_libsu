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

#define SU_INT16    0
#define SU_INT32    1
#define SU_FLOAT    2
#define SU_IBMF     3   //ibm float, unlikely

typedef struct protium_suid_struct * SUID_t;

//used to translate su header to attribute name
typedef struct {
    char    name[32];
    int     db_type;
    int     ibyte;      //< position in su header
    int     nbyte;      //< number of byte to read
    int     su_type;    //< su data type
} su_attr_t;

//const su_attr_t attr_NS = {.name="ns", .db_type=PT_INT32, .ibyte=114, .nbyte=2, .su_type=SU_INT16};

struct protium_suid_struct {
    int     fid;        //< su file id
    int     ninst;
    int     flag;
    int     ns;
    int     si;
    int     skip;       //< trace skip
};
typedef struct protium_suid_struct protium_suid_t;

int su_open(SUID_t *id, const char *path, int flag);

#endif
