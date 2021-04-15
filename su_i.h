#ifndef H_SU_I_SRC_LIBSU_PROTIUM
#define H_SU_I_SRC_LIBSU_PROTIUM

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
#include "libsu.h"

#define MAX(a,b)    ((a>b)?(a):(b))

#define SU_FLAG_WRITE   (1<<0)  //write started

//used to translate su header to attribute name
typedef struct {
    char    name[32];
    int     db_type;
    int     ibyte;      //< position in su header
    int     su_type;    //< su data type
} su_attr_t;

typedef struct protium_suid_struct {
    int         fid;        //< su file id
    int         ninst;
    int         mode;
    int         flag;
    int         ns;
    int         skip;       //< trace skip
    su_attr_t * attr;
    int         nattr;
    int         xattr;      //exposed attributes
    char     ** names;
} protium_suid_t;

#endif
