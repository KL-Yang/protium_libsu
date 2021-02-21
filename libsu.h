#ifndef H_LIBSU_SRC_LIBSU_PROTIUM
#define H_LIBSU_SRC_LIBSU_PROTIUM

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <search.h>
#include <string.h>
#include <inttypes.h>
#include <glib.h>
#include <protium/protium.h>

typedef struct protium_suid_struct SUID_t;

//used to translate su header to attribute name
typedef struct {
    char    name[32];
    int     locate;     //< position in su header
    int     nbyte;      //< number of byte to read
    int     type;       //< su data type
} su_attr_t;

struct protium_suid_struct {
    int     fid;        //< su file id
};
typedef struct protium_suid_struct protium_suid_t;


#endif
